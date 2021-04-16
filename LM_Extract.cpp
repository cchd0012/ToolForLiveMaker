#include "LM_Extract.h"
#include "LM_Functions.h"
#include "zlib-1.2.11/zlib.h"

#pragma warning (disable:6031)
#pragma warning (disable:4996)


//*** ���� �Լ��� ����� �����ϴ� ����


void LM_Extract_For_Ext_Dat(char* DataFile, char* OutputFolder, int Codepage);
//*.ext, *.dat�� ������ ���� �Լ�


void LM_Extract (char *DataFile, char *OutputFolder, int Codepage)
{
	if ((stristr(DataFile, ".ext") != NULL) || (stristr(DataFile, ".dat") != NULL)) {
		LM_Extract_For_Ext_Dat(DataFile, OutputFolder, Codepage);
		return;
	}
	//*Ȯ���ڰ� .ext Ȥ�� .dat�� ������ ������ ���� �Լ��� ����

	printf ("Extract:\nDataFile:%s, OutputFolder:%s, CodePage:%d\n"
		, DataFile, OutputFolder, Codepage);

	HANDLE hData = CreateFileA (DataFile, GENERIC_READ, FILE_SHARE_READ, NULL, 
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hData == INVALID_HANDLE_VALUE) {
		printf ("%s: There's not File\n", DataFile); return;
	}
	//*�ڵ� ����

	unsigned int val, Arc_Start_Pos;
	bool IsExeFile = false;
	ReadFile (hData, &val, sizeof(unsigned int), NULL, NULL);
	if (val == MZ_MAGIC) { IsExeFile = true; }
	//*exe Ȥ�� dat �������� �����ϱ�

	HANDLE hWrite;
	Arc_Start_Pos = 0;
	//*���� ������ ���� ����
	
	if (!IsExeFile) {
		printf("This function is for .exe package\n");
		CloseHandle(hData);
		return;
	}
	//*���⼭�� exe�� �ٷ絵�� �Ѵ�

	SetFilePointer (hData, -2, NULL, FILE_END);
	val = 0;
	ReadFile (hData, &val, sizeof(unsigned short), NULL, NULL);
	if (val != LV_MAGIC) { 
		printf ("%s: This isn't valid VF exe file\n", DataFile); 
		CloseHandle (hData); return;
	}
	//*�� ���� ���ڿ��� "lv"���� Ȯ��
		
	SetFilePointer (hData, -6, NULL, FILE_END);
	val = 0;
	ReadFile (hData, &val, sizeof(unsigned int), NULL, NULL);
	//*������ ����� ���۵Ǵ� ��ġ �ľ� (=exe ������ �Ѱ���)

	char ExeFile[MAX_PATH], *tp_pnt = DataFile;
	unsigned char *ExeBuff;
	memset (ExeFile, 0, MAX_PATH);
	for (tp_pnt = DataFile + (strlen(DataFile) - 1); tp_pnt >= DataFile; tp_pnt--) {
		if ((*tp_pnt == '.')) { break; }
	}
	memcpy(ExeFile, DataFile, sizeof(char) * (tp_pnt - DataFile));
	sprintf(ExeFile + strlen(ExeFile), "_pure.exe");
	//*exe ���ϸ� ����

	ExeBuff = (unsigned char*)malloc(sizeof(char)*val);
	SetFilePointer (hData, 0, NULL, FILE_BEGIN);
	ReadFile (hData, ExeBuff, val, NULL, NULL);
	Arc_Start_Pos = val;
	hWrite = CreateFileA (ExeFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile (hWrite, ExeBuff, val, NULL, NULL);
	CloseHandle (hWrite); hWrite = INVALID_HANDLE_VALUE;
	free (ExeBuff);
	//*exe ���� �κи� ���� �����Ͽ� (~_pure.exe) ��� �� ���� �ı�
	//*�� ��Ȳ�̸� hData�� ������ ��ī�̺� �������� ��ġ�ϰ� �ȴ�
	
	SetFilePointer (hData, Arc_Start_Pos, NULL, FILE_BEGIN);
	val = 0;
	ReadFile (hData, &val, sizeof(unsigned short), NULL, NULL);
	if (val != VF_MAGIC) { 
		printf ("%s: This isn't valid VF archive file\n", DataFile); 
		CloseHandle (hData); return;
	}
	//*��ī�̺� ���� ���ڿ��� "vf"���� Ȯ��

	SetFilePointer (hData, sizeof(int), NULL, FILE_CURRENT);
	//*�� �տ� �ִ� 0x66(int)�� �׳� �ñ״�ó�ε�?

	unsigned int FileCount;
	ReadFile (hData, &FileCount, sizeof(unsigned int), NULL, NULL);
	printf ("Total File Count:%d\n\n", FileCount);
	//*���� ���� �ľ�

	vector<FILE_DESC> fd_list (FileCount + 1);
	unsigned int i_key = 0x0;
	memset (&fd_list[FileCount], 0, sizeof(FILE_DESC));
	for (unsigned int i = 0;i < FileCount;i++) {
		unsigned int File_Path_Len;
		char *tmp_n_buff = (char*)malloc (MAX_PATH);
		memset (tmp_n_buff, 0, MAX_PATH);
		memset (&fd_list[i], 0, sizeof(FILE_DESC));
		ReadFile (hData, &File_Path_Len, sizeof(unsigned int), NULL, NULL);
		ReadFile (hData, tmp_n_buff, File_Path_Len, NULL, NULL);
		//*���ϰ�� ������ �о���̱�
		for (unsigned int j = 0;j < File_Path_Len;j++) {
			i_key += (i_key << 2);
			i_key += 0x75D6EE39;
			tmp_n_buff[j] = (i_key ^ tmp_n_buff[j]) & 0xFF;
		}
		fd_list[i].FileName = (char*)tmp_n_buff;
		//*���ϰ�� ������ ��ȣȭ �� ��ũ���ǿ� �߰��ϱ�
	}
	//*�� ���Ϻ��� ���� ��� ���� (���ϸ�/���Ϲ���/���Ϲ���ũ��/���࿩��/��ũ���� ����)
	//*���� ���� �̸����� �����Ѵ� (�ϴ� ���� �������� �� �����̸��κ� ũ��� 0x217F7)
	
	i_key = 0x0;
	for (unsigned int j = 0;j < (FileCount + 1);j++) {
		i_key += (i_key << 2);
		i_key += 0x75D6EE39;
		ReadFile (hData, &fd_list[j].OffsetInVF, sizeof(unsigned int), NULL, NULL);
		ReadFile (hData, &val, sizeof(unsigned int), NULL, NULL);
		unsigned int checker = (i_key < 0x80000000) ? 0x00000000 : 0xFFFFFFFF;
		if (val != checker) {
			printf ("%s: Error: File Header Cruched\n", DataFile); 
			fd_list.clear(); CloseHandle (hData);
			return;
			//*���� ���� �� �ܰ迡�� i_key Ű���� 0x80000000���� ũ�ų� ������ -1, ������ 0�̴�
			//*�׷���� �� ��Ģ�� ��Ű�� ������ ����ó��
		}
		fd_list[j].OffsetInVF ^= i_key;
		fd_list[j].OffsetInVF += Arc_Start_Pos;
		if (j >= 1) { fd_list[j-1].BufferSize = fd_list[j].OffsetInVF - fd_list[j-1].OffsetInVF; }
	}
	//*���� ������ ����. �� �κ� ũ��� ���ϼ����� �ϳ� �� ����

	for (unsigned int j = 0;j < FileCount;j++) {
		unsigned char DataType;
		ReadFile (hData, &DataType, sizeof(unsigned char), NULL, NULL);
		fd_list[j].IsScrambled = ((DataType & 0x02) != 0);
		fd_list[j].IsCompressed = 
			((DataType & 0x01) != 0) ? fd_list[j].IsScrambled : !fd_list[j].IsScrambled;
		//*0x0 : ����� ������, 0x1 : �׳� ������
		//*0x2 : ��ũ����� ������, 0x3 : ���� �� ��ũ����� ������
	}
	fd_list[FileCount].IsCompressed = true; fd_list[FileCount].IsScrambled = false;
	//*���� �д� ��� ����

	unsigned int tmp_size;
	unsigned char* tmp_buff;
	unsigned long org_size;
	for (unsigned int j = 0;j < FileCount;j++) {
		fd_list[j].FileBuffer = (unsigned char*)malloc (fd_list[j].BufferSize);
		memset (fd_list[j].FileBuffer, 0, fd_list[j].BufferSize);
		SetFilePointer (hData, fd_list[j].OffsetInVF, NULL, SEEK_SET);
		ReadFile (hData, fd_list[j].FileBuffer, fd_list[j].BufferSize, NULL, NULL);

		printf("%s\n", fd_list[j].FileName);
		wchar_t *uni_path;
		string complete_path = OutputFolder; 
		complete_path += "\\";
		complete_path += fd_list[j].FileName;
		uni_path = GetUniStr((char*)complete_path.c_str(), Codepage);
		//*��� Ȯ��

		printf("[*]");

		if (fd_list[j].IsScrambled) { 
			printf("Unscrambling...");
			Unscramble_Data (&fd_list[j].FileBuffer, &fd_list[j].BufferSize);
		}
		if (fd_list[j].IsCompressed) {
			printf("Decompressing...");
			tmp_size = fd_list[j].BufferSize * 30;
			tmp_buff = (unsigned char*)malloc(tmp_size);
			memset(tmp_buff, 0, tmp_size);
			//*30�� �Ǵ� ũ��� �̸� �Ҵ� �� �ʱ�ȭ
			org_size = tmp_size;
			uncompress(tmp_buff, &org_size, fd_list[j].FileBuffer, fd_list[j].BufferSize);
			fd_list[j].BufferSize = org_size;
			free(fd_list[j].FileBuffer); fd_list[j].FileBuffer = tmp_buff;
			//*����Ǯ� ���� ũ�� Ȯ�� �� �ٽ� ����
		}
		//*��ũ����/����Ǯ��

		hWrite = LmCreateFile (uni_path, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, 
			OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile (hWrite, fd_list[j].FileBuffer, fd_list[j].BufferSize, NULL, NULL);
		CloseHandle (hWrite); free (fd_list[j].FileBuffer); fd_list[j].FileBuffer = NULL;
		free (uni_path);
		free(fd_list[j].FileName);
		printf("File Write Complete!\n\n");
		//*����� ��ο� ��� �� �޸� ����
	}
	//*��ũ����, ����Ǯ�� ������� ����

	fd_list.clear();
	CloseHandle (hData);
	//*�۾� ��ġ�� ������ ���� �� �ڵ� �ݱ�
}
//*** ������ ���� �Լ�


void LM_Extract_For_Ext_Dat(char* DataFile, char* OutputFolder, int Codepage)
{
	char *ExtFile, *DatFile;

	bool isExtFileStr = false;
	bool isDatFileStr = false;

	if (stristr(DataFile, ".ext") != NULL) { isExtFileStr = true; }
	else if (stristr(DataFile, ".dat") != NULL) { isDatFileStr = true; }
	else {
		printf("%s:Can't Extract File\n", DataFile);
		return;
	}

	ExtFile = (char*)malloc(strlen(DataFile) + 1); memset(ExtFile, 0, (strlen(DataFile) + 1));
	DatFile = (char*)malloc(strlen(DataFile) + 1); memset(DatFile, 0, (strlen(DataFile) + 1));

	if (isExtFileStr) { 
		memcpy(ExtFile, DataFile, strlen(DataFile));
		memcpy(DatFile, DataFile, strlen(DataFile) - 3);
		sprintf(DatFile + strlen(DatFile), "dat");
	}
	else if (isDatFileStr) {
		memcpy(DatFile, DataFile, strlen(DataFile));
		memcpy(ExtFile, DataFile, strlen(DataFile) - 3);
		sprintf(ExtFile + strlen(ExtFile), "ext");
	}
	//*ext ���� ���ڿ��� dat ���� ���ڿ� �����
	printf("Extract:\nDataFile:%s / %s, OutputFolder:%s, CodePage:%d\n"
		, ExtFile, DatFile, OutputFolder, Codepage);

	unsigned int _ext_size = 0, _dat_size = 0;
	HANDLE hExt, hDat;
	unsigned int val, Arc_Start_Pos;
	hExt = CreateFileA(ExtFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hExt == INVALID_HANDLE_VALUE) {
		printf("%s: There's not File\n", ExtFile); return;
	}
	hDat = CreateFileA(DatFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDat == INVALID_HANDLE_VALUE) {
		CloseHandle(hExt);
		printf("%s: There's not File\n", DatFile); return;
	}
	//*���� ���� �غ�

	Arc_Start_Pos = 0;
	SetFilePointer(hExt, Arc_Start_Pos, NULL, FILE_BEGIN);
	val = 0;
	ReadFile(hExt, &val, sizeof(unsigned short), NULL, NULL);
	if (val != VF_MAGIC) {
		printf("%s: This isn't valid VF extention list file\n", ExtFile);
		CloseHandle(hExt); CloseHandle(hDat); return;
	}
	//*��ī�̺� ���� ���ڿ��� "vf"���� Ȯ�� (ext ���Ϸ�)

	SetFilePointer(hExt, sizeof(int), NULL, FILE_CURRENT);
	//*�� �տ� �ִ� 0x66(int)�� �׳� �ñ״�ó�ε�?

	unsigned int FileCount;
	ReadFile(hExt, &FileCount, sizeof(unsigned int), NULL, NULL);
	printf("Total File Count:%d\n\n", FileCount);
	//*���� ���� �ľ� (ext ���Ϸ�)

	vector<FILE_DESC> fd_list(FileCount + 1);
	unsigned int i_key = 0x0;
	memset(&fd_list[FileCount], 0, sizeof(FILE_DESC));
	for (unsigned int i = 0; i < FileCount; i++) {
		unsigned int File_Path_Len;
		char* tmp_n_buff = (char*)malloc(MAX_PATH);
		memset(tmp_n_buff, 0, MAX_PATH);
		memset(&fd_list[i], 0, sizeof(FILE_DESC));
		ReadFile(hExt, &File_Path_Len, sizeof(unsigned int), NULL, NULL);
		ReadFile(hExt, tmp_n_buff, File_Path_Len, NULL, NULL);
		//*���ϰ�� ������ �о���̱�
		for (unsigned int j = 0; j < File_Path_Len; j++) {
			i_key += (i_key << 2);
			i_key += 0x75D6EE39;
			tmp_n_buff[j] = (i_key ^ tmp_n_buff[j]) & 0xFF;
		}
		fd_list[i].FileName = (char*)tmp_n_buff;
		//*���ϰ�� ������ ��ȣȭ �� ��ũ���ǿ� �߰��ϱ�
	}
	//*�� ���Ϻ��� ���� ��� ���� (���ϸ�/���Ϲ���/���Ϲ���ũ��/���࿩��/��ũ���� ����)
	//*���� ���� �̸����� �����Ѵ� (�ϴ� ���� �������� �� �����̸��κ� ũ��� 0x217F7)
	//* (ext ���Ϸ�)
	
	i_key = 0x0;
	for (unsigned int j = 0; j < (FileCount + 1); j++) {
		i_key += (i_key << 2);
		i_key += 0x75D6EE39;
		ReadFile(hExt, &fd_list[j].OffsetInVF, sizeof(unsigned int), NULL, NULL);
		ReadFile(hExt, &val, sizeof(unsigned int), NULL, NULL);
		unsigned int checker = (i_key < 0x80000000) ? 0x00000000 : 0xFFFFFFFF;
		if (val != checker) {
			printf("%s: Error: File Header Cruched\n", ExtFile);
			fd_list.clear(); 
			CloseHandle(hExt); CloseHandle(hDat); return;
			//*���� ���� �� �ܰ迡�� i_key Ű���� 0x80000000���� ũ�ų� ������ -1, ������ 0�̴�
			//*�׷���� �� ��Ģ�� ��Ű�� ������ ����ó��
		}
		fd_list[j].OffsetInVF ^= i_key;
		fd_list[j].OffsetInVF += Arc_Start_Pos;
		if (j >= 1) { fd_list[j - 1].BufferSize = fd_list[j].OffsetInVF - fd_list[j - 1].OffsetInVF; }
	}
	//*���� ������ ����. �� �κ� ũ��� ���ϼ����� �ϳ� �� ���� (ext ���Ϸ�)

	for (unsigned int j = 0; j < FileCount; j++) {
		unsigned char DataType;
		ReadFile(hExt, &DataType, sizeof(unsigned char), NULL, NULL);
		fd_list[j].IsScrambled = ((DataType & 0x02) != 0);
		fd_list[j].IsCompressed =
			((DataType & 0x01) != 0) ? fd_list[j].IsScrambled : !fd_list[j].IsScrambled;
		//*0x0 : ����� ������, 0x1 : �׳� ������
		//*0x2 : ��ũ����� ������, 0x3 : ���� �� ��ũ����� ������
	}
	fd_list[FileCount].IsCompressed = true; fd_list[FileCount].IsScrambled = false;
	CloseHandle(hExt);
	//*���� �д� ��� ���� (ext ���Ϸ�)
	//*��������� ext ������ ����

	unsigned int tmp_size;
	unsigned char* tmp_buff;
	unsigned long org_size;
	for (unsigned int j = 0; j < FileCount; j++) {

		fd_list[j].FileBuffer = (unsigned char*)malloc(fd_list[j].BufferSize);
		memset(fd_list[j].FileBuffer, 0, fd_list[j].BufferSize);
		SetFilePointer(hDat, fd_list[j].OffsetInVF, NULL, SEEK_SET);
		ReadFile(hDat, fd_list[j].FileBuffer, fd_list[j].BufferSize, NULL, NULL);

		printf("%s\n", fd_list[j].FileName);
		wchar_t* uni_path;
		string complete_path = OutputFolder;
		complete_path += "\\";
		complete_path += fd_list[j].FileName;
		uni_path = GetUniStr((char*)complete_path.c_str(), Codepage);
		//*��� Ȯ��

		printf("[*]");

		if (fd_list[j].IsScrambled) {
			printf("Unscrambling...");
			Unscramble_Data(&fd_list[j].FileBuffer, &fd_list[j].BufferSize);
		}
		if (fd_list[j].IsCompressed) {
			printf("Decompressing...");
			tmp_size = fd_list[j].BufferSize * 30;
			tmp_buff = (unsigned char*)malloc(tmp_size);
			memset(tmp_buff, 0, tmp_size);
			//*30�� �Ǵ� ũ��� �̸� �Ҵ� �� �ʱ�ȭ
			org_size = tmp_size;
			uncompress(tmp_buff, &org_size, fd_list[j].FileBuffer, fd_list[j].BufferSize);
			fd_list[j].BufferSize = org_size;
			free(fd_list[j].FileBuffer); fd_list[j].FileBuffer = tmp_buff;
			//*����Ǯ� ���� ũ�� Ȯ�� �� �ٽ� ����
		}
		//*��ũ����/����Ǯ��

		HANDLE hWrite = LmCreateFile(uni_path, GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
			OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hWrite, fd_list[j].FileBuffer, fd_list[j].BufferSize, NULL, NULL);
		CloseHandle(hWrite); free(fd_list[j].FileBuffer); fd_list[j].FileBuffer = NULL;
		free(uni_path);
		free(fd_list[j].FileName);
		printf("File Write Complete!\n\n");
		//*����� ��ο� ��� �� �޸� ����
	}
	//*��ũ����, ����Ǯ�� ������� ����(dat ���Ϸ�)

	free(ExtFile); free(DatFile);
	fd_list.clear();
	CloseHandle(hDat);
	//*�۾� ��ġ�� ������ ���� �� �ڵ� �ݱ�
}
//*.ext, *.dat�� ������ ���� �Լ�