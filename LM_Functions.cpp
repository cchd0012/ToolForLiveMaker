#include "LM_Functions.h"
#include <random>


#pragma warning (disable:6031)
#pragma warning (disable:4996)

using namespace std;
//*** ȣ�� �Լ����� ����� �Ǵ� �Լ��� �����ϴ� ����


wchar_t *_txt_buf = NULL;
//*** �ؽ�Ʈ ����

void GetRandomValue(unsigned int seed, unsigned int* RandomKeyArray);
//*���� Ű ȹ�� �Լ�

void Mul_64Bit(unsigned int a, unsigned int b,
	unsigned int* res, unsigned int* over, unsigned int* carry);
void Add_64Bit(unsigned int a, unsigned int b,
	unsigned int* res, unsigned int* carry);
void Add_With_Carry_64Bit(unsigned int a, unsigned int b, unsigned int carry,
	unsigned int* res, unsigned int* res_carry);
void Permutation_Round(unsigned int* KeyArray);
//*���� Ű ȹ�� ���� �Լ�


void Initialize_Tool()
{
	Load_Hanja();
	_txt_buf = (wchar_t*)malloc(sizeof(wchar_t) * TXT_BUFF_LEN);
	memset(_txt_buf, 0, (sizeof(wchar_t) * TXT_BUFF_LEN));
	//*�������� �ε� �� �ؽ�Ʈ ��¿� ���� ���� �Ҵ�
}
//*�� �ʱ�ȭ �Լ�

void Terminate_Tool()
{
	free(_txt_buf);
	Release_Hanja();
	//*�������� ��ε� �� �ؽ�Ʈ ��¿� ���� ����
}
//*�� ��ġ�� �Լ�



void CreateDir (wchar_t* Path)
{
    wchar_t DirName[MAX_PATH];	//������ ���丮 �̸�
    wchar_t* p = Path;			//���ڷ� ���� ���丮
    wchar_t* q = DirName;  
 
    while(*p)
    {
        if (('\\' == *p) || ('/' == *p))   //��Ʈ���丮 Ȥ�� Sub���丮
        {
            if (':' != *(p-1))
            {
                CreateDirectoryW(DirName, NULL);
            }
        }
        *q++ = *p++;
        *q = '\0';
    }
}
//*��ο� �ִ� ��� ���丮�� �����ϴ� �Լ�

HANDLE LmCreateFile (LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, 
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) 
{
	CreateDir ((wchar_t*)lpFileName);
	return CreateFileW( lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}
//CreateFile �����Լ�. ��� ���丮 �ѹ��� ����




wchar_t* J2U(char* string);
wchar_t* K2U(char* string);
char* U2K(wchar_t* string);
char* U2J(wchar_t* string);

wchar_t* GetUniStr(char *string, unsigned int code)
{
	if (code == LM_CP_JAP) { return J2U(string); }
	else if (code == LM_CP_KOR) { return K2U(string); }
	else { return J2U(string); }
}
//*����ڵ忡 ���� ���ڿ��� �ٲ� �����ڵ�� ��ȯ��

char* GetAnsiStr(wchar_t* string, unsigned int code)
{
	if (code == LM_CP_JAP) { return U2J(string); }
	else if (code == LM_CP_KOR) { return U2K(string); }
	else { return U2J(string); }
}
//*����ڵ忡 ���� ���ڿ��� �ٲ� ansi�� ��ȯ��

wchar_t* J2U (char *string)
{
	wchar_t *bstr;
	int nLen = MultiByteToWideChar(932, 0, string, -1, NULL, NULL);
	bstr = (wchar_t*)malloc(sizeof(wchar_t)*(nLen+1));
	bstr[nLen] = 0;
	MultiByteToWideChar(932, 0, string, -1, bstr, nLen);
	return bstr;
}

wchar_t* K2U (char *string)
{
	wchar_t *bstr;
	int nLen = MultiByteToWideChar(949, 0, string, -1, NULL, NULL);
	bstr = (wchar_t*)malloc(sizeof(wchar_t)*(nLen+1));
	bstr[nLen] = 0;
	MultiByteToWideChar(949, 0, string, -1, bstr, nLen);
	return bstr;
}

char* U2K (wchar_t *string)
{
	char *lstr;
	int nLen = WideCharToMultiByte(949, 0, string, -1, NULL, NULL, NULL, NULL);
	lstr = (char*)malloc(sizeof(char)*(nLen+1));
	lstr[nLen] = 0;
	WideCharToMultiByte(949, 0, string, -1, lstr, nLen, NULL, NULL);
	return lstr;
}

char* U2J (wchar_t *string)
{
	char *lstr;
	int nLen = WideCharToMultiByte(932, 0, string, -1, NULL, NULL, NULL, NULL);
	lstr = (char*)malloc(sizeof(char)*(nLen+1));
	lstr[nLen] = 0;
	WideCharToMultiByte(932, 0, string, -1, lstr, nLen, NULL, NULL);
	return lstr;
}


UINT32 Get_Txt_Count(wchar_t* src_txt_buffer, const wchar_t* find_txt, UINT32 src_txt_size)
{
	UINT32 total_count = 0;
	wchar_t* txt_buffer_pnt = src_txt_buffer;
	while (txt_buffer_pnt < (src_txt_buffer + src_txt_size)) {
		wchar_t* check_str = wcsstr(txt_buffer_pnt, find_txt);
		if (check_str != NULL) {
			total_count++;
			txt_buffer_pnt = check_str + wcslen(find_txt);
		}
		else { break; }
	}
	return total_count;
}
//*���� �ؽ�Ʈ ���� ���� ã�� �ؽ�Ʈ�� �� ���� �ִ��� �ľ��ϴ� �Լ�




void Unscramble_Data(unsigned char** Buffer, unsigned int* BufferSize)
{
	unsigned int BlockSize = *(unsigned int*)(*Buffer);
	unsigned int Seed = *(unsigned int*)((*Buffer) + sizeof(int));
	Seed ^= 0xF8EA;
	unsigned int BlockCount = ((*BufferSize) - (sizeof(int) * 2)) / BlockSize;
	if ((((*BufferSize) - (sizeof(int) * 2)) % BlockSize) != 0) { BlockCount++; }
	//*�� ����ũ��, ���� �� ���� �����õ� �ľ��ϱ�

	unsigned int RandomKeyArray[5];
	GetRandomValue(Seed, RandomKeyArray);
	//*�����õ带 ������� ������ ��� (5�� int)

	unsigned __int64 _tmp_64bit;
	vector<unsigned int> Origin_Block_Idx_List(BlockCount);
	for (unsigned int i = 0; i < BlockCount; i++) { Origin_Block_Idx_List[i] = i; }
	vector<unsigned int> New_Block_Idx_List(BlockCount, 0);
	for (int i = BlockCount; i > 0; i--) {
		Permutation_Round(RandomKeyArray);
		_tmp_64bit = (unsigned __int64)RandomKeyArray[0] * (unsigned __int64)(i - 1);
		unsigned int idx = (unsigned int)(_tmp_64bit / 0x100000000);
		New_Block_Idx_List[Origin_Block_Idx_List[idx]] = (BlockCount - i);
		Origin_Block_Idx_List.erase(Origin_Block_Idx_List.begin() + idx);
		Origin_Block_Idx_List.push_back((BlockCount - i));
		//*0���� BlockCount-1 ����
	}
	//*�� �� �ε����� ����

	unsigned char* org_buff = (unsigned char*)malloc((*BufferSize));
	memset(org_buff, 0, (*BufferSize));
	for (unsigned int i = 0; i < BlockCount; i++) {
		unsigned int cp_len = (i != (BlockCount - 1)) ? BlockSize : ((*BufferSize) - (BlockSize * i) - (sizeof(int) * 2));
		memcpy(&org_buff[(BlockSize * i)], &(*Buffer)[(BlockSize * New_Block_Idx_List[i]) + (sizeof(int) * 2)], cp_len);
	}
	free(*Buffer);
	(*Buffer) = org_buff;
	(*BufferSize) -= 8;
	//*�� �� �ε������ �������� �ű� �� ���� �ٲ�ġ��
}
//*** ��ũ����� �����͸� Ǯ���ִ� �Լ�


bool Scramble_Data(unsigned char** Buffer, unsigned int* BufferSize)
{
	unsigned int BlockSize = (*BufferSize) / DEFAULT_BLOCK_COUNT;
	if (BlockSize == 0) { return false; }
	//*�� ������ ���
	//*���� �� ����� 0�� ������ �׳� ���Ѵ�

	unsigned int BlockCount = (*BufferSize) / BlockSize;
	if (((*BufferSize) % BlockSize) != 0) { BlockCount++; }
	//*�� �� ����

	unsigned int res_buff_size = (*BufferSize) + (sizeof(int) * 2);
	unsigned char* res_buff = (unsigned char*)malloc(res_buff_size);
	memset(res_buff, 0, res_buff_size);
	*(unsigned int*)res_buff = BlockSize;
	//*���� ��ȯ�� ũ�⸸ŭ �Ҵ��ϰ� �� ũ�� ����

	random_device rd;
	mt19937 mersenne(rd());
	uniform_int_distribution<> die(0x1111, 0xFFFF);
	unsigned short Seed1 = (unsigned int)die(mersenne);
	unsigned short Seed2 = (unsigned int)die(mersenne);
	unsigned int Seed = ((unsigned int)Seed1 << 0x10) | Seed2;
	*(unsigned int*)(res_buff + sizeof(int)) = Seed;
	Seed ^= 0xF8EA;
	//*�õ尪 ���� �� ���� �غ�

	unsigned int RandomKeyArray[5];
	GetRandomValue(Seed, RandomKeyArray);
	//*�����õ带 ������� ������ ��� (5�� int)

	unsigned __int64 _tmp_64bit;
	vector<unsigned int> Origin_Block_Idx_List(BlockCount);
	for (unsigned int i = 0; i < BlockCount; i++) { Origin_Block_Idx_List[i] = i; }
	vector<unsigned int> New_Block_Idx_List(BlockCount, 0);
	for (int i = BlockCount; i > 0; i--) {
		Permutation_Round(RandomKeyArray);
		_tmp_64bit = (unsigned __int64)RandomKeyArray[0] * (unsigned __int64)(i - 1);
		unsigned int idx = (unsigned int)(_tmp_64bit / 0x100000000);
		New_Block_Idx_List[Origin_Block_Idx_List[idx]] = (BlockCount - i);
		Origin_Block_Idx_List.erase(Origin_Block_Idx_List.begin() + idx);
		Origin_Block_Idx_List.push_back((BlockCount - i));
		//*0���� BlockCount-1 ����
	}
	//*�� �� �ε����� ����

	vector<unsigned int> Reverse_Block_Idx_List(BlockCount, 0);
	for (unsigned int i = 0; i < BlockCount;i++) {
		Reverse_Block_Idx_List[New_Block_Idx_List[i]] = i;
	}
	//*New_Block_Idx_List�� Origin_Block_Idx_List�� ���踦 �����Ͽ�
	//*���Ӱ� ���͸� �ϳ� �� ����� �����Ѵ�

	unsigned int last_idx = Reverse_Block_Idx_List[BlockCount -1];

	for (unsigned int i = 0; i < BlockCount; i++) {
		unsigned int cp_len = (i != (BlockCount - 1)) ? BlockSize : ((*BufferSize) - (BlockSize * i));
		memcpy(&res_buff[(BlockSize * i) + (sizeof(int)*2)], &(*Buffer)[(BlockSize * Reverse_Block_Idx_List[i])], cp_len);
	}
	//*���Ӱ� ���� ��� �߶󳻾� �����Ѵ�

	free(*Buffer);
	(*Buffer) = res_buff;
	(*BufferSize) = res_buff_size;
	return true;
	//*���� ���Ҵ�� ���ο� ũ�Ⱑ �ʿ��ϴ�
}
//*** ������ ��ũ����, ��ũ������ �����ߴٴ� ��ȣ�� ������ �ϹǷ� bool �Լ��� �Ѵ�




void GetRandomValue(unsigned int seed, unsigned int* RandomKeyArray)
{
	unsigned int seed1, seed2;
	seed1 = seed;
	for (unsigned int i = 0; i < 5; i++) {
		seed2 = (seed1 << 0x0D) ^ seed1;
		seed1 = seed2 ^ (seed2 >> 0x11);
		seed1 = seed1 ^ (seed1 << 0x05);
		RandomKeyArray[i] = seed1;
	}
	//*5�� �õ尪 ���
	for (unsigned int i = 0; i < 0x13; i++) { Permutation_Round(RandomKeyArray); }
	//*������ �������� �ǵ��� 19���� ���� ����
}
//*�õ� ��� ������ ��� (5�� int)


void Permutation_Round(unsigned int* KeyArray)
{
	unsigned int m, carry, eax, ecx, edx, edi;
	Mul_64Bit(0x7DD4FFC7, KeyArray[3], &m, &edi, &carry);
	ecx = m;

	Mul_64Bit(0x000005D4, KeyArray[2], &m, &edx, &carry);
	Add_64Bit(ecx, m, &ecx, &carry);
	KeyArray[3] = KeyArray[2];
	Add_With_Carry_64Bit(edi, edx, carry, &edi, &carry);

	Mul_64Bit(0x000006F0, KeyArray[1], &m, &edx, &carry);
	Add_64Bit(ecx, m, &ecx, &carry);
	KeyArray[2] = KeyArray[1];
	Add_With_Carry_64Bit(edi, edx, carry, &edi, &carry);

	Mul_64Bit(0x000013FB, KeyArray[0], &m, &edx, &carry);
	Add_64Bit(0, m, &eax, &carry);
	KeyArray[1] = KeyArray[0];

	Add_64Bit(eax, ecx, &eax, &carry);
	Add_With_Carry_64Bit(edx, edi, carry, &edx, &carry);

	Add_64Bit(eax, KeyArray[4], &eax, &carry);
	Add_With_Carry_64Bit(edx, 0, carry, &edx, &carry);

	KeyArray[0] = eax;
	KeyArray[4] = edx;
}
//*�������� �����ϴ� ����


void Mul_64Bit(unsigned int a, unsigned int b,
	unsigned int* res, unsigned int* over, unsigned int* carry)
{
	unsigned __int64 _tmp_64bit = (unsigned __int64)a * (unsigned __int64)b;
	(*res) = (unsigned int)_tmp_64bit;
	(*over) = (_tmp_64bit >= 0x100000000) ? (unsigned int)(_tmp_64bit / 0x100000000) : 0;
	(*carry) = (_tmp_64bit >= 0x100000000) ? 1 : 0;
}


void Add_64Bit(unsigned int a, unsigned int b,
	unsigned int* res, unsigned int* carry)
{
	unsigned __int64 _tmp_64bit = (unsigned __int64)a + (unsigned __int64)b;
	(*res) = (unsigned int)_tmp_64bit;
	(*carry) = (_tmp_64bit >= 0x100000000) ? 1 : 0;
}


void Add_With_Carry_64Bit(unsigned int a, unsigned int b, unsigned int carry,
	unsigned int* res, unsigned int* res_carry)
{
	unsigned __int64 _tmp_64bit = (unsigned __int64)a + (unsigned __int64)b + (unsigned __int64)carry;
	(*res) = (unsigned int)_tmp_64bit;
	(*res_carry) = (_tmp_64bit >= 0x100000000) ? 1 : 0;
}




unsigned int Get_Files_Pass_List (wchar_t *DataFolder, FILE_DESC **f_desc_list_pnt)
{
	HANDLE hFile;
	unsigned int res_count = 0;
	WIN32_FIND_DATAW wfd_w;
	wchar_t f_format[MAX_PATH];
	memset(f_format, 0, sizeof(wchar_t) * MAX_PATH);
	swprintf(f_format, TEXT("%s\\*"), DataFolder);
	hFile = FindFirstFileW(f_format, &wfd_w);
	if (hFile != INVALID_HANDLE_VALUE) {
		do
		{
			wchar_t f_n_format[MAX_PATH];
			memset(f_n_format, 0, sizeof(wchar_t) * MAX_PATH);
			swprintf(f_n_format, TEXT("%s\\%s"), DataFolder, wfd_w.cFileName);
			if (wfd_w.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if ((wcscmp(wfd_w.cFileName, TEXT(".")) != 0) && (wcscmp(wfd_w.cFileName, TEXT("..")) != 0)) {
					res_count += Get_Files_Pass_List(f_n_format, f_desc_list_pnt);
				}
			}
			//*���丮 �Ӽ��� �� : "."�� ".."�� �ƴϸ� ��ͷ� �İ���
			else { 
				res_count++;
				if (f_desc_list_pnt != NULL) {
					wchar_t* tp_str = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(f_n_format) + 1));
					tp_str[wcslen(f_n_format)] = 0;
					memcpy(tp_str, f_n_format, (sizeof(wchar_t)* wcslen(f_n_format)));
					(*f_desc_list_pnt)->FileName_uni = tp_str;
					(*f_desc_list_pnt)++;
				}
			}
			//*���� �Ӽ��� �� : �׳� ���ϱ�, f_desc_list ���� null�� �ƴϸ� �ٿ��ֱ�
		} while (FindNextFileW (hFile, &wfd_w));
		FindClose(hFile);
	}
	//*���� Ȯ�� �� ã�ƺ���

	return res_count;
	//*��ģ �� ��ȯ
}
//*���ϰ�θ� ��Ī���� �ִ� �Լ� / ������ null�̸� �׳� ���� ���� ����




bool Replace_Data(TEX_REPLACE* _rep_util, UINT32 org_data_offset, UINT32 org_data_length, UINT8* new_data, UINT32 new_data_length)
{
	if (_rep_util == NULL) { return false; }
	if ((_rep_util->n_b == NULL) || (_rep_util->n_b_sav == NULL)) { return false; }
	if ((_rep_util->n_b->_buffer == NULL) || (_rep_util->n_b_sav->_buffer == NULL)) { return false; }
	//*���� üũ

	if (org_data_offset > (_rep_util->n_b->_size)) { return false; }
	if ((org_data_offset + org_data_length) > (_rep_util->n_b->_size)) { return false; }
	//*�߰� ���� üũ (�������� �����°� ���̰� ���� ũ�⸦ ����� �ȵ�)

	if (org_data_length == new_data_length) {
		memcpy((_rep_util->n_b->_buffer + org_data_offset), new_data, org_data_length);
		return true;
	}
	//*���࿡ ���� ������ ���̿� �� ������ ���̰� ���ٸ� �׳� �����ϰ� ������ ��

	UINT32 rev1_length = org_data_offset;
	UINT32 rev2_length = (_rep_util->n_b->_size - (org_data_offset + org_data_length));
	memcpy(_rep_util->rev1, _rep_util->n_b->_buffer, rev1_length);
	memcpy(_rep_util->rev2, (_rep_util->n_b->_buffer + org_data_offset + org_data_length), rev2_length);
	//*�� �κ��� �������� rev1�� rev2�� ����

	memcpy(_rep_util->n_b_sav->_buffer, _rep_util->rev1, rev1_length);
	memcpy((_rep_util->n_b_sav->_buffer) + rev1_length, new_data, new_data_length);
	memcpy((_rep_util->n_b_sav->_buffer) + (rev1_length + new_data_length), _rep_util->rev2, rev2_length);
	_rep_util->n_b_sav->_size = rev1_length + new_data_length + rev2_length;
	//*�׸��� ���Ӱ� ���ܳ��� �� ���� ����

	_BUFFER_INFO* tbp = _rep_util->n_b;
	_rep_util->n_b = _rep_util->n_b_sav;
	_rep_util->n_b_sav = tbp;
	//*������ �ٲ�ġ��

	return true;
}
//*������ ��ü �Լ�


wchar_t* Replace_Text(wchar_t* org_txt, const wchar_t* org_part, const wchar_t* change_part)
{
	wchar_t* ret_txt;
	if (wcsstr(org_txt, org_part) == NULL) {
		ret_txt = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(org_txt) + 1));
		memcpy(ret_txt, org_txt, (sizeof(wchar_t) * wcslen(org_txt)));
		ret_txt[wcslen(org_txt)] = 0;
		return ret_txt;
	}
	//*�ٲ� ���ڿ��� ã�� �� ������ �׳� �����ϰ� ��ȯ��
	UINT32 new_txt_len = wcslen(org_txt);
	UINT32 cnt = Get_Txt_Count(org_txt, org_part, wcslen(org_txt));
	for (UINT32 i = 0; i < cnt; i++) {
		new_txt_len -= wcslen(org_part);
		new_txt_len += wcslen(change_part);
	}
	//*�ٲ� ���̸� �̸� üũ��
	ret_txt = (wchar_t*)malloc(sizeof(wchar_t) * (new_txt_len + 1));
	memset(ret_txt, 0, sizeof(wchar_t) * (new_txt_len + 1));
	wchar_t* tmp_str_pnt = org_txt;
	wchar_t* tmp_str_2_pnt = ret_txt;
	while (tmp_str_pnt < (org_txt + wcslen(org_txt))) {
		if (wcsncmp(tmp_str_pnt, org_part, wcslen(org_part)) == 0) {
			memcpy(tmp_str_2_pnt, change_part, wcslen(change_part) * sizeof(wchar_t));
			tmp_str_pnt += wcslen(org_part);
			tmp_str_2_pnt += wcslen(change_part);
		}
		else {
			*(tmp_str_2_pnt) = *(tmp_str_pnt);
			tmp_str_pnt++; tmp_str_2_pnt++;
		}
	}
	return ret_txt;
	//*���ڿ� ���� �ٲ�ġ�� ��ȯ
}
//*���ڿ� ��ü �Լ� (��������� �ٲ� ���ڿ� ��ȯ)




wchar_t* unicode_table_J2K = NULL;
//wchar_t* _Inv_Inicode_table_J2K = NULL;
UINT32 HanjaCnt = 0;

void Load_Hanja()
{
	wchar_t *JapHanja = NULL, *KorHanja = NULL;
	HanjaCnt = 0;
	//*�̸� �ʱ�ȭ�ϱ�

	HANDLE hHanja = CreateFileW(L"Hanja.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hHanja == INVALID_HANDLE_VALUE) {
		MessageBoxW(NULL, L"Hanja.txt ������ �����ϴ�.\n�� ������ ������ ���� �̸��� �������� �����ؾ� �մϴ�.", L"Alert", MB_OK);
		return;
	}

	unsigned int HanjaListSize = (GetFileSize(hHanja, NULL) / sizeof(wchar_t)) - 1;
	wchar_t* buff = (wchar_t*)malloc((HanjaListSize + 1) * sizeof(wchar_t));
	memset(buff, 0, ((HanjaListSize + 1) * sizeof(wchar_t)));
	SetFilePointer(hHanja, sizeof(wchar_t), NULL, FILE_BEGIN);
	ReadFile(hHanja, buff, (HanjaListSize * sizeof(wchar_t)), NULL, NULL);
	CloseHandle(hHanja);
	//*���� �о���̱�

	for (unsigned int i = 0; i < HanjaListSize - 3; i++) {
		if ((buff[i] == '<') && (buff[i + 1] == '-') && (buff[i + 2] == '>')) { HanjaCnt++; }
	}
	//*�ε��ϱ�

	KorHanja = (wchar_t*)malloc(sizeof(wchar_t) * HanjaCnt);
	memset(KorHanja, 0, (sizeof(wchar_t) * HanjaCnt));
	JapHanja = (wchar_t*)malloc(sizeof(wchar_t) * HanjaCnt);
	memset(JapHanja, 0, (sizeof(wchar_t) * HanjaCnt));
	//*�Ҵ� �� �ʱ�ȭ

	unsigned int buffpntidx = 0;
	for (unsigned int i = 0; i < HanjaCnt; i++) {
		while (!((buff[buffpntidx] == '<') && (buff[buffpntidx + 1] == '-') && (buff[buffpntidx + 2] == '>'))) { buffpntidx++; }
		JapHanja[i] = buff[buffpntidx - 2]; KorHanja[i] = buff[buffpntidx + 4];
		buffpntidx++;
	}
	//*���ۿ��� ���� �Ѹ���

	unicode_table_J2K = (wchar_t*)malloc(sizeof(wchar_t*) * 0x10000);
	memset(unicode_table_J2K, 0, (sizeof(wchar_t*) * 0x10000));
	for (unsigned int i = 0; i < 0x10000;i++) { unicode_table_J2K[i] = i; }
	//*�����ڵ� ���̺� �� �Űֱܳ�(ó�� �ʱ�ȭ�� �״��)

//	_Inv_Inicode_table_J2K = (wchar_t*)malloc(sizeof(wchar_t) * 0x10000);
//	memset(_Inv_Inicode_table_J2K, 0, (sizeof(wchar_t) * 0x10000));
//	//*������ ���̺� Ȱ��ȭ

	for (unsigned int i = 0; i < HanjaCnt; i++) { 
		unicode_table_J2K[JapHanja[i]] = KorHanja[i];
//		_Inv_Inicode_table_J2K[KorHanja[i]] = JapHanja[i];
	}
	//*�Ϻ��� ���ڸ� �ε����� ��� �ѱ��� ���ڸ� ������ �ﵵ�� ������
	//*������� ���� ���� �׳� ����

	free(JapHanja);
	free(KorHanja);
	free(buff);
	//*���� ����
}
//*"Hanja.txt" ���� �ε� �Լ�


void Release_Hanja()
{
	if (unicode_table_J2K != NULL) { free(unicode_table_J2K); }
//	if (_Inv_Inicode_table_J2K != NULL) { free(_Inv_Inicode_table_J2K); }
}
//*"Hanja.txt" ���� ���� �Լ�


void JPHan_2_KRHan(wchar_t* str)
{
	if (str != NULL) {
		UINT32 str_length = wcslen(str);
		for (unsigned int j = 0; j < str_length; j++) {
			if (str[j] == 0x3005) {
				if (j > 0) { str[j] = str[j - 1]; }
				else { str[j] = 0x2015; }
			}
			//*�ߺ� ����
			else {
				str[j] = unicode_table_J2K[str[j]];
				//*��Ī�Ǵ� ���ڸ� ã�Ƽ� �ٲ�ġ��
			}
		}
	}
}
//*������ ���ڿ����� �ٲ� �� �ִ� ���ڴ� ��� �ѱ����ڷ� �ٲٴ� �Լ�


/*
void Make_J2K_Table()
{
	Load_Hanja();
	//*���̺� �ҷ�����

	char* jap_table = (char*)malloc(0x30000);
	memset(jap_table, 0, 0x30000);
	
	for (unsigned int i = 0x20; i <= 0x7E;i++) { jap_table[3 * i] = i; }
	//*ascii
	
	for (unsigned int i = 0xA1; i <= 0xDF; i++) { jap_table[3 * i] = i; }
	//*�ݰ�

	for (unsigned int i = 0x81; i <= 0x9F;i++) {
		for (unsigned int j = 0x40; j <= 0xFF;j++) {
			wchar_t _val = ((wchar_t)i * 0x100) + j;
			jap_table[3 * _val] = i;
			jap_table[(3 * _val) + 1] = j;
			wchar_t* _wt = J2U(&jap_table[3 * _val]);
			if (_wt[0] == '?') {
				jap_table[3 * _val] = jap_table[(3 * _val) + 1] = 0;
			}
			free(_wt);
			//*������ Ȯ���Ϸ��� �Ӹ��� �㰡 �� �� ������ �����ڵ�� �ٲ㺸�°� �� ���� �� �ϴ�
		}
	}
	//*���� (ù��° ����)

	for (unsigned int i = 0xE0; i <= 0xEE; i++) {
		for (unsigned int j = 0x40; j <= 0xFF; j++) {
			wchar_t _val = ((wchar_t)i * 0x100) + j;
			jap_table[3 * _val] = i;
			jap_table[(3 * _val) + 1] = j;
			wchar_t* _wt = J2U(&jap_table[3 * _val]);
			if (_wt[0] == '?') {
				jap_table[3 * _val] = jap_table[(3 * _val) + 1] = 0;
			}
			free(_wt);
			//*������ Ȯ���Ϸ��� �Ӹ��� �㰡 �� �� ������ �����ڵ�� �ٲ㺸�°� �� ���� �� �ϴ�
		}
	}
	//*���� (�ι�° ����)

	for (unsigned int i = 0xFA; i <= 0xFC; i++) {
		for (unsigned int j = 0x40; j <= 0xFF; j++) {
			wchar_t _val = ((wchar_t)i * 0x100) + j;
			jap_table[3 * _val] = i;
			jap_table[(3 * _val) + 1] = j;
			wchar_t* _wt = J2U(&jap_table[3 * _val]);
			if (_wt[0] == '?') {
				jap_table[3 * _val] = jap_table[(3 * _val) + 1] = 0;
			}
			free(_wt);
			//*������ Ȯ���Ϸ��� �Ӹ��� �㰡 �� �� ������ �����ڵ�� �ٲ㺸�°� �� ���� �� �ϴ�
		}
	}
	//*���� (����° ����)

	wchar_t** _jap_table_uni = (wchar_t**)malloc(sizeof(wchar_t*) * 0x10000);
	memset(_jap_table_uni, 0, (sizeof(wchar_t*) * 0x10000));
	for (unsigned int i = 0; i < 0x10000;i++) {
		if (jap_table[3 * i] != 0) { _jap_table_uni[i] = J2U(&jap_table[3 * i]); }
	}
	//*�Ϻ��� �������� ���� ���ڵ鸸 �α׸� �ܾ �����ڵ� ���̺�� �ϳ� �����

	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	//*�Է�/����� unicode�� �غ�

	for (unsigned int i = 0x20; i <= 0x7E; i++) {
		_Inv_Inicode_table_J2K[i] = i;
	}
	//*ascii �ڵ�� �״�� ����

	for (unsigned int i = 0xA1; i <= 0xDF; i++) { 
		if ((i >= 0xA1) && (i <= 0xBA)) { 
			unicode_table_J2K[i] = (i - 0xA1) + 'A';
			_Inv_Inicode_table_J2K[(i - 0xA1) + 'A'] = i;
		}
		//*�빮��
		else if ((i >= 0xBB) && (i <= 0xD4)) {
			unicode_table_J2K[i] = (i - 0xBB) + 'a';
			_Inv_Inicode_table_J2K[(i - 0xBB) + 'a'] = i;
		}
		//*�ҹ���
		else {
			if ((i - 0xD5) <= 9) {
				unicode_table_J2K[i] = (i - 0xD5) + '0';
				_Inv_Inicode_table_J2K[(i - 0xD5) + '0'] = i;
			}
			else {
				unicode_table_J2K[i] = '@';
				_Inv_Inicode_table_J2K['@'] = i;
			}
		}
		//*����
	}
	//*�ݰ��� ���ĺ� ������ ���߾� ó���Ѵ�

	//*** _jap_table_uni : �ε����� ansi, ���� unicode

	char* _kor_c;
	wchar_t _tp_char[2];
	_tp_char[0] = _tp_char[1] = 0;
	//*�ӽ÷� ���� �޾ƿ� ����

	random_device rd;
	mt19937 engine(rd());
	uniform_int<> distribution_1(0xB0, 0xFE);
	uniform_int<> distribution_2(0xA1, 0xFF);
	//*���� ���� �غ�, �ѱ��� �ּ�ȭ�ؾ� ���� �� ���ҵ��ϴ�

	uniform_int<> distribution_3(0x81, 0xC7);
	uniform_int<> distribution_4(0x41, 0xFF);
	//*���������� �� ���� �߰���

	for (unsigned int i = 0x8140; i < 0x10000;i++) {
		if (_jap_table_uni[i] != NULL) {

			wchar_t _get_uni_char = _jap_table_uni[i][0];
			//*�����ڵ� ���� ���

			if (_get_uni_char == 0x3005) { continue; }
			//*�ߺ����ڰ� �ƴ� ���� �����Ѵ�

			_kor_c = U2K(_jap_table_uni[i]);
			//*�ѱ��� ����ڵ�� �ٲ��� �� ���� ���

			if (_kor_c[0] == '?') {
				free(_kor_c);
				//*���� ���� ��������� ����

				_tp_char[0] = unicode_table_J2K[_get_uni_char];
				_kor_c = U2K(_tp_char);
				//*������ ��ϵ� ���̺� �ִ� ���� Ȯ���� ����

				if (_kor_c[0] == '?') {

					setlocale(LC_ALL, ".932");
					wprintf(TEXT("'%s'[%04X]::"), _jap_table_uni[i], _jap_table_uni[i][0]);
					setlocale(LC_ALL, ".949");
					//*�Ϻ����� ��� �� �ǵ�����

					if (_jap_table_uni[i][0] == 0x86EC) {
						bool _ss = true;
					}

					wprintf(TEXT("�ѱ��� �ڵ� ���ڰ� �ƴϰ� ���̺��� �����ϴ�.\n"));
					wprintf(TEXT("���Ƿ� ��Ī�մϴ�...\n"));
					while (1)
					{
//						if (_jap_table_uni[i][0] >= 0xE700) {
							_tp_char[0] = (distribution_1(engine) << 8) | distribution_2(engine);
//						}
//						else {
//							_tp_char[0] = (distribution_3(engine) << 8) | distribution_4(engine);
//						}
						_tp_char[1] = 0;
						//*�Է¹ޱ�...�� �ʹ� �����
						//*�׳� �ѱ� ����ڵ� �߿� �������� �ٲٴ� �� ���� �� �ϴ�
						//*euc-kr ���� 0xCAA0 ~ 0xFDFE���� ������Ī?, �յ� �ϳ��� ����

						_kor_c = U2K(_tp_char);
						if (_kor_c[0] == '?') {
//							wprintf(TEXT("�ش� ���ڴ� �ѱ��� �ڵ� ���ڰ� �ƴմϴ�.\n"));
							free(_kor_c);
							continue;
						}
						//*�ش� ���ڰ� �ѱ��� ����ڵ� �������� Ȯ��

						if (_Inv_Inicode_table_J2K[_tp_char[0]] != 0) {
//							wprintf(TEXT("�ش� ���ڴ� �̹� ��ϵ� �����Դϴ�.\n"));
							free(_kor_c);
							continue;
						}
						//*�ѱ��� ����ڵ尡 �´ٸ� �ߺ���ϵ� �������� Ȯ��

						_Inv_Inicode_table_J2K[_tp_char[0]] = _get_uni_char;
						unicode_table_J2K[_get_uni_char] = _tp_char[0];
						free(_kor_c);
						setlocale(LC_ALL, ".932");
						wprintf(TEXT("'%s' <-> "), _jap_table_uni[i]);
						setlocale(LC_ALL, ".949");
						wprintf(TEXT("'%s'\n\n"), _tp_char);
						break;
						//*�ߺ���ϵ� ���ڰ� �ƴ϶�� �������� ����ϰ� �������´�
						//*�׸��� ������ �ٲ�ģ��
					}
					//*�Է·���
				}
				//*���⼭�� ��ϵ� ���� ������ ���� �Է¹޾ƾ� �Ѵ�

				else {
					_Inv_Inicode_table_J2K[_tp_char[0]] = _get_uni_char;
					free(_kor_c);
				}
				//*��ϵ� ���� ������ �װɷ� �ϸ� �ȴ�
			}
			//*�ѱ��� ����ڵ忡 ���� ������ ��

			else {
				_Inv_Inicode_table_J2K[_get_uni_char] = _get_uni_char;
				free(_kor_c);
				//*�����ڵ带 �״�� ������ָ� �ȴ�
			}
			//*�ѱ��� ����ڵ忡 �ִ� ������ ��

		}
	}
	//*���� ó��
	//*�Ϻ���� �ѱ���� �ٲ� �� ������ ���ڰ� �ִ��� Ȯ���ϰ� �ٲ� ���� �Է¹ޱ�
	//*�ٲ� ���ڸ� �޾��� �� �ߺ� �˻�
	//*ascii�� �ǵ��� ����

	HANDLE hWrite = CreateFile(TEXT("Output_Hanja.txt"), GENERIC_WRITE, FILE_SHARE_WRITE,
		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	wchar_t _str[0x10];
	wchar_t tps_1[2], tps_2[2];
	wchar_t BOM = 0xFEFF;
	WriteFile(hWrite, &BOM, sizeof(wchar_t), NULL, NULL);
	tps_1[0] = tps_1[1] = tps_2[0] = tps_2[1] = 0;
	for (unsigned int i = 0; i < 0x10000;i++) {
		if ((_Inv_Inicode_table_J2K[i] != 0x00)) {
			tps_1[0] = _Inv_Inicode_table_J2K[i];
			tps_2[0] = i;
			if (tps_1[0] != tps_2[0]) {
				wsprintf(_str, TEXT("%s <-> %s\r\n"), tps_1, tps_2);
				WriteFile(hWrite, _str, (sizeof(wchar_t)* wcslen(_str)), NULL, NULL);
			}
		}
	}
	CloseHandle(hWrite);
	//*���������� �ϼ��� ���̺��� �ؽ�Ʈ���Ϸ� ����ϱ�
	//*���� ������ �׳� ������� �ʴ´�
	//_Inv_Inicode_table_J2K[KorHanja[i]] = JapHanja[i];

	free(jap_table);
	for (unsigned int i = 0; i < 0x10000; i++) {
		if (_jap_table_uni[i] != NULL) { free(_jap_table_uni[i]); }
	}
	free(_jap_table_uni);
	//*����

	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
	//*�Է�/����� ������� �ǵ���
}
*/


bool is_Pure_Ascii_String(wchar_t *_str)
{
	for (unsigned int i = 0; i < wcslen(_str);i++) {
		if (_str[i] >= 0x80) { return false; }
		else if (_str[i] == '\\') { 
			return false; 
		}
	}
	return true;
}
//*�ش� ���ڿ��� ���� ascii ���ڿ����� �Ǻ��ϴ� �Լ�


bool is_File_Path_String(wchar_t* _str)
{
	unsigned int i = 0;
	while (i < wcslen(_str)) {
		if (_str[i] == '\\') { 
			if (i < (wcslen(_str) - 1)) {
				if ((_str[i + 1] == 'r') || (_str[i + 1] == 'n')) { i += 2; }
				else { return true; }
			}
			else { return true; }
		}
		else { i++; }
	}
	return false;
}
//*�ش� ���ڿ��� ��� ���ڿ����� �Ǻ��ϴ� �Լ�
//"\r"�̳� "\n"�� ��� ���ڿ��� ġ�� �ʴ´�




char* _get_str(unsigned char** _buffer_pnt)
{
	unsigned char* buffer_pnt = (*_buffer_pnt);

	unsigned int str_len = *(unsigned int*)buffer_pnt;
	buffer_pnt += sizeof(int);
	//*���ڿ� ���� ���

	char* str_buffer = (char*)malloc(str_len + 1);
	str_buffer[str_len] = 0;
	memcpy(str_buffer, buffer_pnt, str_len);
	buffer_pnt += str_len;
	//*���̸�ŭ �Ҵ� �� ���ڿ� ���� 

	(*_buffer_pnt) = buffer_pnt;
	return str_buffer;
}
//*���ڿ��� �о���̴� �Լ�

void _write_str(HANDLE hWrite, char* _str)
{
	unsigned int _len = strlen(_str);
	WriteFile(hWrite, &_len, sizeof(int), NULL, NULL);
	WriteFile(hWrite, _str, _len, NULL, NULL);
}
//*���ڿ��� ����ϴ� �Լ�


double* _get_double(unsigned char** _buffer_pnt)
{
	unsigned char* buffer_pnt = (*_buffer_pnt);

	double* double_buffer = (double*)malloc(sizeof(double));
	*double_buffer = *(double*)buffer_pnt;
	buffer_pnt += sizeof(double);
	//*���� �Ҵ� �� ���� 

	(*_buffer_pnt) = buffer_pnt;
	return double_buffer;
}
//*double�� �о���̴� �Լ�

void _write_double(HANDLE hWrite, double _do)
{
	WriteFile(hWrite, &_do, sizeof(double), NULL, NULL);
}
//*double�� ����ϴ� �Լ�


unsigned int* _get_int(unsigned char** _buffer_pnt)
{
	unsigned char* buffer_pnt = (*_buffer_pnt);

	unsigned int* int_buffer = (unsigned int*)malloc(sizeof(int));
	*int_buffer = *(unsigned int*)buffer_pnt;
	buffer_pnt += sizeof(int);
	//*���� �Ҵ� �� ���� 

	(*_buffer_pnt) = buffer_pnt;
	return int_buffer;
}
//*������ �о���̴� �Լ�

void _write_int(HANDLE hWrite, unsigned int _int)
{
	WriteFile(hWrite, &_int, sizeof(int), NULL, NULL);
}
//*������ ����ϴ� �Լ�


unsigned short* _get_word(unsigned char** _buffer_pnt)
{
	unsigned char* buffer_pnt = (*_buffer_pnt);

	unsigned short* word_buffer = (unsigned short*)malloc(sizeof(short));
	*word_buffer = *(unsigned short*)buffer_pnt;
	buffer_pnt += sizeof(short);
	//*���� �Ҵ� �� ���� 

	(*_buffer_pnt) = buffer_pnt;
	return word_buffer;
}
//*���带 �о���̴� �Լ�

void _write_word(HANDLE hWrite, unsigned short _s)
{
	WriteFile(hWrite, &_s, sizeof(short), NULL, NULL);
}
//*���带 ����ϴ� �Լ�


unsigned char* _get_byte(unsigned char** _buffer_pnt)
{
	unsigned char* buffer_pnt = (*_buffer_pnt);

	unsigned char* byte_buffer = (unsigned char*)malloc(sizeof(char));
	*byte_buffer = *buffer_pnt;
	buffer_pnt++;
	//*���� �Ҵ� �� ���� 

	(*_buffer_pnt) = buffer_pnt;
	return byte_buffer;
}
//*����Ʈ�� �о���̴� �Լ�

void _write_byte(HANDLE hWrite, unsigned char _c)
{
	WriteFile(hWrite, &_c, sizeof(char), NULL, NULL);
}
//*����Ʈ�� ����ϴ� �Լ�


unsigned char* _get_data(unsigned char** _buffer_pnt, unsigned int _len)
{
	unsigned char* buffer_pnt = (*_buffer_pnt);

	unsigned char* data_buffer = (unsigned char*)malloc(_len + 1);
	memcpy(data_buffer, buffer_pnt, _len);
	data_buffer[_len] = 0;
	buffer_pnt += _len;
	//*���̸�ŭ �Ҵ� �� ������ ���� 
	//*���ڿ��� ���� ���� ������ ���κп� ����ó���� �Ѵ�

	(*_buffer_pnt) = buffer_pnt;
	return data_buffer;
}
//*���� ���̸�ŭ �о���̴� �Լ�

void _write_data(HANDLE hWrite, unsigned char* _buff, unsigned int _len)
{
	WriteFile(hWrite, _buff, _len, NULL, NULL);
}
//*���� ���̸�ŭ ����ϴ� �Լ�


char* stristr(const char* str1, const char* str2)
{
	const char* p1 = str1;
	const char* p2 = str2;
	const char* r = *p2 == 0 ? str1 : 0;

	while (*p1 != 0 && *p2 != 0)
	{
		if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
		{
			if (r == 0) { r = p1; }
			p2++;
		}
		else
		{
			p2 = str2;
			if (r != 0) { p1 = r + 1; }
			if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2)) { r = p1; p2++; }
			else { r = 0; }
		}
		p1++;
	}

	return *p2 == 0 ? (char*)r : 0;
}
//*��ҹ��� ���� ���� strstr

wchar_t* wcsistr(const wchar_t* str1, const wchar_t* str2)
{
	const wchar_t* p1 = str1;
	const wchar_t* p2 = str2;
	const wchar_t* r = *p2 == 0 ? str1 : 0;

	while (*p1 != 0 && *p2 != 0)
	{
		if (towlower((unsigned short)*p1) == towlower((unsigned short)*p2))
		{
			if (r == 0) { r = p1; }
			p2++;
		}
		else
		{
			p2 = str2;
			if (r != 0) { p1 = r + 1; }
			if (towlower((unsigned short)*p1) == towlower((unsigned short)*p2)) { r = p1; p2++; }
			else { r = 0; }
		}
		p1++;
	}

	return *p2 == 0 ? (wchar_t*)r : 0;
}
//*��ҹ��� ���� ���� wcsstr