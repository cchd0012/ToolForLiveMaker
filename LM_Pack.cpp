#include "LM_Pack.h"
#include "LM_Functions.h"
#include "zlib-1.2.11/zlib.h"

#pragma warning (disable:6031)
#pragma warning (disable:4996)


//*** ���� �Լ��� ����� �����ϴ� ����


void LM_Pack (char *DataFolder, char *ExeFile, int Codepage)
{
	printf ("Pack test:\ntest:DataFolder:%s, ExeFile:%s, Codepage:%d\n"
		, DataFolder, ExeFile, Codepage);
	//*** dat ���Ϸ� ����� �Ǹ� (ExeFile�� null�̸�) 'output.dat���� �����'

	bool isIncludedExeFile = false;
	if (ExeFile != NULL) { isIncludedExeFile = true; }
	//*ExeFile�� NULL�̸� ~.ext ���ϰ� ~.dat ���Ϸ� ���� ���յȴ�
	//*���� ~.dat ������ 1GB�� �Ѿ�� ������ �ɰ��� ����� �Ѵ�
	//*�̶� ��� ���ϸ��� 'game.ext'�� 'game.dat/.001/.002...' �̷� ������ ��������

	HANDLE hArchive;						//*���� ����� ��ī�̺� ���� �ڵ�
	UINT32 pure_exe_size = 0;				//*��ī�̺��� ����Ʈ ������
	unsigned char* arc_buff = NULL;			//*��ī�̺긦 �ӽ÷� ������ ����
	char new_archive_file_name[MAX_PATH];	//*���ο� ��ī�̺��� ���ϸ�
	memset(new_archive_file_name, 0, MAX_PATH);
	if (isIncludedExeFile) {
		hArchive = CreateFileA(ExeFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hArchive == INVALID_HANDLE_VALUE) {
			printf("%s: There's not File\n", ExeFile); return;
		}
		pure_exe_size = GetFileSize(hArchive, NULL);
		arc_buff = (unsigned char*)malloc(pure_exe_size);
		ReadFile(hArchive, arc_buff, pure_exe_size, NULL, NULL);
		CloseHandle(hArchive);
		//*�̸� �о�鿩 �α�
		char* tp_pnt = ExeFile;
		for (unsigned int i = 0; i < (strlen(ExeFile) + strlen("_new")); i++) {
			new_archive_file_name[i] = *(tp_pnt++);
			if ((*tp_pnt == '.')) {
				sprintf(&new_archive_file_name[i + 1], "_new");
				i += strlen("_new");
			}
		}
		//*���ο� exe ���ϸ� ����
		hArchive = CreateFileA(new_archive_file_name, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		//*�� exe ���� �����ϱ�
	}
	//*exe ������ ���� ��� exe ������ �о���δ�
	else {
		sprintf(new_archive_file_name, "game.ext");
		hArchive = CreateFileA(new_archive_file_name, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		//*game.ext ���� �ڵ� �����ϱ�
	}
	//*exe ������ �������� �ʾ����� ���������� 'game.ext' ���Ϸ� �����

	wchar_t* tp_dir = GetUniStr (DataFolder, Codepage);
	//* �����ڵ� �⺻ ���ϸ�

	unsigned int file_count = Get_Files_Pass_List(tp_dir, NULL);
	FILE_DESC* file_desc_list = (FILE_DESC*)malloc(sizeof(FILE_DESC) * file_count);
	FILE_DESC* file_desc_list_pnt = file_desc_list;
	memset(file_desc_list, 0, (sizeof(FILE_DESC) * file_count));
	Get_Files_Pass_List(tp_dir, &file_desc_list_pnt);
	printf("Total File Count:%d\n\n", file_count);
	//*�ش� ���� �� ���� �� �ľ� / �ʿ��� ���� ����(���ϰ��) �о���̱�

	printf("File name header making...");
	for (unsigned int i = 0; i < file_count;i++) {
		file_desc_list[i].FileName = GetAnsiStr((file_desc_list[i].FileName_uni + wcslen(tp_dir) + 1), Codepage);
	}
	free(tp_dir);
	//*�ڵ��������� ���� ��¥ ���ϰ�θ� ����� ���� "Datafolder\\"�� ������ ������ �߰��ؾ� �Ѵ�

	unsigned int file_name_header_size = 0;
	for (unsigned int i = 0; i < file_count;i++) {
		file_name_header_size += sizeof(int);
		file_name_header_size += strlen(file_desc_list[i].FileName);
	}
	unsigned char* file_name_header_buffer = (unsigned char*)malloc(file_name_header_size);
	unsigned char* tp_a_pnt = file_name_header_buffer;
	unsigned int i_key = 0x0;
	for (unsigned int i = 0; i < file_count; i++) {
		unsigned int File_Path_Len = strlen(file_desc_list[i].FileName);
		*(unsigned int*)tp_a_pnt = File_Path_Len; tp_a_pnt += sizeof(int);
		memcpy(tp_a_pnt, file_desc_list[i].FileName, File_Path_Len);
		for (unsigned int j = 0; j < File_Path_Len; j++) {
			i_key += (i_key << 2);
			i_key += 0x75D6EE39;
			(*tp_a_pnt) = (i_key ^ (*tp_a_pnt)) & 0xFF;
			tp_a_pnt++;
		}
	}
	printf("Finished!\n");
	//*���� �̸� ��� ���� ũ�� ���� / �����

	unsigned int file_offset_header_size = sizeof(int) * 2 * (file_count + 1);
	unsigned int* file_offset_header_buffer = (unsigned int*)malloc (file_offset_header_size);
	memset(file_offset_header_buffer, 0, file_offset_header_size);
	//*���� ������ ��� �����
	//*������ ��, üĿ���� �����ؼ� ����ĭ 2���� �Ҵ��Ѵ�
	//*�� ������ õõ�� �о���̸鼭 �����ؾ� �Ѵ�

	printf("File attribute header making...");
	unsigned char* file_attr_header_buffer = (unsigned char*)malloc(file_count);
	memset(file_attr_header_buffer, 0, file_count);
	for (unsigned int i = 0; i < file_count; i++) {
		if ((strncmp((file_desc_list[i].FileName + strlen(file_desc_list[i].FileName) - 4), ".ogg", 4) != 0)
			&& (strncmp((file_desc_list[i].FileName + strlen(file_desc_list[i].FileName) - 4), ".jpg", 4) != 0)
			&& (strncmp((file_desc_list[i].FileName + strlen(file_desc_list[i].FileName) - 4), ".gif", 4) != 0)
			&& (strncmp((file_desc_list[i].FileName + strlen(file_desc_list[i].FileName) - 4), ".png", 4) != 0)
			&& (strncmp((file_desc_list[i].FileName + strlen(file_desc_list[i].FileName) - 4), ".gal", 4) != 0)) {
			file_attr_header_buffer[i] = 0x3;
			//*Ȯ���� �߿� ogg, jpg, gif, png, gal ���� �� ������
		}
		else {
			file_attr_header_buffer[i] = 0x2;
		}
	}
	printf("Finished!\n");
	//*���� �Ӽ� ��� ����� (��ũ���� �Ӽ� ����)
	//*0x0 : ����� ������, 0x1 : �׳� ������
	//*0x2 : ��ũ����� ������, 0x3 : ���� �� ��ũ����� ������

	printf("File header writing...");
	unsigned short value_2byte;
	unsigned int value_4byte;
	if (isIncludedExeFile) {
		WriteFile(hArchive, arc_buff, pure_exe_size, NULL, NULL);
	}
	//*exe ������ ��쿡�� exe �����͸� ���� ����Ѵ�
	value_2byte = VF_MAGIC;
	WriteFile(hArchive, &value_2byte, sizeof(short), NULL, NULL);
	value_4byte = VF_VERSION;
	WriteFile(hArchive, &value_4byte, sizeof(int), NULL, NULL);
	value_4byte = file_count;
	WriteFile(hArchive, &value_4byte, sizeof(int), NULL, NULL);
	//*vf ����� �� ���� �� ���

	WriteFile(hArchive, file_name_header_buffer, file_name_header_size, NULL, NULL);
	//*���ϸ� ��� ���

	unsigned int offset_buffer_pos = SetFilePointer(hArchive, 0, NULL, FILE_CURRENT);
	SetFilePointer(hArchive, file_offset_header_size, NULL, FILE_CURRENT);
	unsigned int attr_buffer_pos = SetFilePointer(hArchive, 0, NULL, FILE_CURRENT);
	SetFilePointer(hArchive, file_count, NULL, FILE_CURRENT);
	printf("Finished!\n\n");
	//*���� �������� �����ϴ� �� �ٷ� ����� �� ������ ���߿� ����� ����ϸ鼭 ���� ����Ѵ�
	//*���� �Ӽ��� ���� Ȥ�� ��ũ������ �Ұ��� ��� �����ؾ� �� �� �ִ�

	if (!isIncludedExeFile) {
		CloseHandle(hArchive);
		hArchive = CreateFileA("game.dat", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	//*�ɰ��� ����� ���� ���� �ڵ��� �ٲ��ش�

	i_key = 0x0;
	unsigned int checker;
	unsigned int accum_offset = SetFilePointer(hArchive, 0, NULL, FILE_CURRENT) - pure_exe_size;
	unsigned int* offset_buffer_pnt = file_offset_header_buffer;
	HANDLE hEachFile;
	unsigned int each_file_size;
	unsigned char *each_file_buffer;
	char _game_part_name[0x9] = "game.dat";
	unsigned int _accum_part_idx = 0x001;
	for (unsigned int i = 0; i < file_count; i++) {

		printf("%s\n", file_desc_list[i].FileName);
		printf("[*]");

		i_key += (i_key << 2);
		i_key += 0x75D6EE39;
		checker = (i_key < 0x80000000) ? 0x00000000 : 0xFFFFFFFF;
		(*offset_buffer_pnt++) = accum_offset ^ i_key;
		(*offset_buffer_pnt++) = checker;
		//*������ ���� ����
		hEachFile = CreateFileW(file_desc_list[i].FileName_uni, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		each_file_size = GetFileSize(hEachFile, NULL);
		each_file_buffer = (unsigned char*)malloc(each_file_size);
		ReadFile(hEachFile, each_file_buffer, each_file_size, NULL, NULL);
		CloseHandle(hEachFile);
		//*�� ���� ���� �о���̱�
		if ((file_attr_header_buffer[i] == 0x0) || (file_attr_header_buffer[i] == 0x3)) {
			if (each_file_size == 0x00) { 
				file_attr_header_buffer[i] = 0x1; 
			}
			else {
				printf("Compressing...");
				unsigned int comp_size = each_file_size * 0x3;
				unsigned char* comp_buff = (unsigned char*)malloc (comp_size);
				memset(comp_buff, 0, comp_size);
				compress(comp_buff, (unsigned long*)&comp_size, each_file_buffer, each_file_size);
				free(each_file_buffer);
				each_file_buffer = comp_buff;
				each_file_size = comp_size;
			}
		}
		//*��쿡 ���� �����ϱ�, �ƿ� �� �Ǹ� �׳� �ѱ��
		if ((file_attr_header_buffer[i] == 0x2) || (file_attr_header_buffer[i] == 0x3)) {
			printf("Scrambling...");
			if (!Scramble_Data(&each_file_buffer, &each_file_size)) {
				if (file_attr_header_buffer[i] == 0x2) { file_attr_header_buffer[i] = 0x1; }
				if (file_attr_header_buffer[i] == 0x3) { file_attr_header_buffer[i] = 0x0; }
			}
		}
		//*��쿡 ���� ��ũ�����ϱ�, �����ϸ� �׳� ���� Ȥ�� �׳� �������Ϸ� �д�

		if (!isIncludedExeFile) {
			unsigned int _pos = SetFilePointer(hArchive, 0, NULL, FILE_CURRENT);
			if ((_pos + each_file_size) > 0x40000000) {
				sprintf(_game_part_name, "game.%03d", _accum_part_idx);
				unsigned int _left = (_pos + each_file_size) - 0x40000000;
				unsigned int _write = each_file_size - _left;
				WriteFile(hArchive, each_file_buffer, _write, NULL, NULL);
				CloseHandle(hArchive);
				hArchive = CreateFileA(_game_part_name, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				WriteFile(hArchive, each_file_buffer + _write, _left, NULL, NULL);
				_accum_part_idx++;
			}
			else {
				WriteFile(hArchive, each_file_buffer, each_file_size, NULL, NULL);
			}
		}
		//*�ɰ��� ����� ��, ���� �ڵ� ũ�Ⱑ 1GB�� �Ѿ �� �ϸ� �ٲ� ����Ѵ�

		else {
			WriteFile(hArchive, each_file_buffer, each_file_size, NULL, NULL);
		}
		//*�׷��� ������ ����ϰ� ����ϸ� ��

		accum_offset += each_file_size;
		free(each_file_buffer);
		printf("File Data Write Complete!\n\n");
		//*���� ��� / ������ ���� / ����
	}
	printf("All File Data Writing Finished!\n\n");
	//*���� ��� �����ʹ� ��� ������ ���������� ����Ѵ�
	//*������ �� ������ ���� �Ŀ� ��ũ���� �ǽ�

	i_key += (i_key << 2);
	i_key += 0x75D6EE39;
	checker = (i_key < 0x80000000) ? 0x00000000 : 0xFFFFFFFF;
	(*offset_buffer_pnt++) = accum_offset ^ i_key;
	(*offset_buffer_pnt++) = checker;
	//*������ ���� �����

	printf("File offset / attribute header writing...");
	if (isIncludedExeFile) {
		value_4byte = pure_exe_size;
		WriteFile(hArchive, &value_4byte, sizeof(int), NULL, NULL);
		value_2byte = LV_MAGIC;
		WriteFile(hArchive, &value_2byte, sizeof(short), NULL, NULL);
	}
	//*exe ������ ��츸 ������ ��ġ �� ��� ���

	if (!isIncludedExeFile) {
		CloseHandle(hArchive);
		hArchive = CreateFileA("game.ext", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	//*exe ������ �ƴ϶�� �ٽ� game.ext ���Ϸ� �������´�

	SetFilePointer(hArchive, attr_buffer_pos, NULL, FILE_BEGIN);
	WriteFile(hArchive, file_attr_header_buffer, file_count, NULL, NULL);
	SetFilePointer(hArchive, offset_buffer_pos, NULL, FILE_BEGIN);
	WriteFile(hArchive, file_offset_header_buffer, file_offset_header_size, NULL, NULL);
	//*���������� �Ӽ��� ������ �����͸� ����Ѵ�
	printf("Finished!\n\n");

	CloseHandle(hArchive);
	if (isIncludedExeFile) { free(arc_buff); }
	for (unsigned int i = 0; i < file_count;i++) { free(file_desc_list[i].FileName_uni); }
	free(file_desc_list);
	free(file_name_header_buffer);
	free(file_offset_header_buffer);
	free(file_attr_header_buffer);
	//*����
}
//*** ������ ���� �Լ�