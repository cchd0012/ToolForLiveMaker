#include "LM_Text.h"
#include "LM_Script.h"
#include "LM_Functions.h"


#pragma warning (disable:6031)
#pragma warning (disable:4996)


//*** �ؽ�Ʈ ���� �Լ����� ����� �����ϴ� ����


const char* _exe_xml_shift_jis_str = "<?xml version=\"1.0\" encoding=\"Shift_JIS\" ?>\r\n";
const char* _exe_xml_euc_kr_str = "<?xml version=\"1.0\" encoding=\"EUC-KR\" ?>\r\n";
const char* _exe_shift_jis_str_1 = "shift_jis";
const char* _exe_shift_jis_str_2 = "shift-jis";
const char* _exe_euc_kr_str_1 = "euc_kr";
const char* _exe_euc_kr_str_2 = "euc-kr";
//*J2K ����� exe ���ο��� �ٲ�� �� ���ڿ�

const unsigned char _exe_search_bs_1[6] = { 0x8A, 0x40, 0x1A, 0x88, 0x45, 0xD7 };
const unsigned char _exe_change_bs_1[6] = { 0xC6, 0x45, 0xD7, 0x81, 0x90, 0x90 };
//*������ �����ϱ� ���� ��ɾ� 1

const unsigned char _exe_search_bs_2[8] = { 0x83, 0xC0, 0xE0, 0x3D, 0xBF, 0x00, 0x00, 0x00 };
const unsigned char _exe_change_bs_2[8] = { 0x83, 0xC0, 0xE0, 0x3D, 0x60, 0x00, 0x00, 0x00 };
//*������ �����ϱ� ���� ��ɾ� 2

const unsigned char _exe_search_bs_3_1[6] = { 0x01, 0x00, 0x00, 0x00, 0xA4, 0xFD };
const unsigned char _exe_change_bs_3_1[6] = { 0x01, 0x00, 0x00, 0x00, 0xA3, 0x00 };
const unsigned char _exe_search_bs_3_2[6] = { 0x83, 0xEA, 0x30, 0x83, 0xC2, 0x4F };
const unsigned char _exe_change_bs_3_2[6] = { 0x81, 0xC2, 0x80, 0x00, 0x00, 0x00 };
const unsigned char _exe_search_bs_3_3[6] = { 0x83, 0xEA, 0x41, 0x83, 0xC2, 0x81 };
const unsigned char _exe_change_bs_3_3[6] = { 0x81, 0xC2, 0x80, 0x00, 0x00, 0x00 };
//*������ �����ϱ� ���� ��ɾ� 3_1, 3_2, 3_3

const unsigned char _exe_search_bs_4[11] = { 0x80, 0x38, 0x81, 0x75, 0x25, 0x8B, 0x03, 0x80, 0x78, 0x01, 0x40 };
const unsigned char _exe_change_bs_4[11] = { 0x80, 0x38, 0xA1, 0x75, 0x25, 0x8B, 0x03, 0x80, 0x78, 0x01, 0xA1 };
const unsigned char _exe_search_bs_5[14] = { 0x80, 0x7C, 0x30, 0xFE, 0x81, 0x75, 0x49, 0x8B, 0x03, 0x80, 0x7C, 0x30, 0xFF, 0x40 };
const unsigned char _exe_change_bs_5[14] = { 0x80, 0x7C, 0x30, 0xFE, 0xA1, 0x75, 0x49, 0x8B, 0x03, 0x80, 0x7C, 0x30, 0xFF, 0xA1 };
//*������ �����ϱ� ���� ��ɾ� 4, 5

const char _exe_font_jap_part_name_ms[5] = "�ͣ�";
const char _exe_font_jap_name_07_soft_gothic[19] = "07�䪵���������ë�";
const char _exe_font_kor_name_hy_taegothic[9] = "HY�°��";
//*J2K ����� exe ���ο��� �ٲ�� �� ��Ʈ ���ڿ� 1

const unsigned char _exe_font_jap_part_name_ms_2[16] = 
	{ 0x0F, 0x82, 0x6C, 0x82, 0x72, 0x20, 0x82, 0x6F, 0x83, 0x53, 0x83, 0x56, 0x83, 0x62, 0x83, 0x4E };
const unsigned char _exe_font_kor_name_08_seoul_namsan_eb[16] = 
	{ 0x0F, 0x30, 0x38, 0xBC, 0xAD, 0xBF, 0xEF, 0xB3, 0xB2, 0xBB, 0xEA, 0xC3, 0xBC, 0x20, 0x45, 0x42 };
//*J2K ����� exe ���ο��� �ٲ�� �� ��Ʈ ���ڿ� 2 (08���ﳲ��ü EB)


void Change_Name_Codepage_J2K (wchar_t *DataFolder);
//*�̸� �ڵ������� ����� ����Լ� ����
void Change_Data_Codepage_J2K(wchar_t* DataFolder);
//*������ �ڵ������� ����� ����Լ� ����

void Extract_Script_Text(wchar_t* DataFolder, unsigned int code);
//*lsb �ؽ�Ʈ ����� ����Լ� ����
void Replace_Script_Text(wchar_t* DataFolder, unsigned int code);
//*lsb �ؽ�Ʈ ����� ����Լ� ����
void Decompile_Script(wchar_t* DataFolder, unsigned int code);
//*�������Ͽ� ����� ����Լ� ����


void LM_Convert_Codepage_J2K(char* DataFolder)
{
	wprintf(TEXT("Changing Text Language Code(Jap -> Kor)...\n"));

	wchar_t* uni_dir = GetUniStr(DataFolder, LM_CP_KOR);
	//*���丮 �����ڵ�� �ٲ����

	Change_Name_Codepage_J2K (uni_dir);
	Change_Data_Codepage_J2K(uni_dir);
	//*�ش� ���丮�� �ִ� ��� ���Ͽ� ���� �˻�
	//*���ϸ�/���丮�� ���浵 ���� �˻��Ѵ�
	//*��� Ȯ���� : .lsb, .lpb, .lcm/.lmt, .txt, .lpm, .dat
	//*���� ������ stristr Ȥ�� wcristr�� �˻��ؼ� ó���Ѵ�

	wprintf(TEXT("Convert Complete!\n"));
	free(uni_dir);
}
//*** ���� �� ���� �ڵ������� �ϰ� ���� �Լ�
//*** �� �������� �ڵ��������� ���� ���ڴ� ���ľ� �ϸ�,
//*** �̸� ���ؼ� ��Ͽ� ���� ���ڴ� ���Ƿ� �����ؾ� �� ���ɼ��� �ִ�


void Change_Name_Codepage_J2K(wchar_t* DataFolder)
{
	HANDLE hFile;
	WIN32_FIND_DATAW wfd_w;
	wchar_t f_format[MAX_PATH];
	memset(f_format, 0, sizeof(wchar_t) * MAX_PATH);
	swprintf(f_format, TEXT("%s\\*"), DataFolder);
	//*ã�� �غ� ��ġ��

	bool is_there_next_file_or_dir = true;
	wchar_t f_d_n[MAX_PATH];
	wchar_t *f_d_n_j2k;
	DWORD _attr = 0;
	wchar_t f_n_org[MAX_PATH];
	wchar_t f_n_cvt[MAX_PATH];

	hFile = FindFirstFileW(f_format, &wfd_w);
	if (hFile != INVALID_HANDLE_VALUE) {

		do
		{
			_attr = wfd_w.dwFileAttributes;
			memset(f_d_n, 0, sizeof(wchar_t) * MAX_PATH);
			f_d_n_j2k = (wchar_t*)malloc(sizeof(wchar_t) * MAX_PATH);
			memset(f_d_n_j2k, 0, sizeof(wchar_t) * MAX_PATH);
			memcpy(f_d_n, wfd_w.cFileName, (sizeof(wchar_t) * wcslen(wfd_w.cFileName)));
			memcpy(f_d_n_j2k, wfd_w.cFileName, (sizeof(wchar_t) * wcslen(wfd_w.cFileName)));
			is_there_next_file_or_dir = FindNextFileW(hFile, &wfd_w);
			//*Ȥ�� �𸣴� ���� / �������� �ٲٱ� ���� �̸� �Ӽ��� ���� / ���ϸ� ���� ��
			//*���� ����� Ȯ���Ѵ�
			 
			JPHan_2_KRHan(f_d_n_j2k);
			//*����ڵ� �ٲ�ġ��

			memset(f_n_org, 0, sizeof(wchar_t) * MAX_PATH);
			swprintf(f_n_org, TEXT("%s\\%s"), DataFolder, f_d_n);
			//*���� ����/���丮 �̸�

			memset(f_n_cvt, 0, sizeof(wchar_t) * MAX_PATH);
			swprintf(f_n_cvt, TEXT("%s\\%s"), DataFolder, f_d_n_j2k);
			//*�ٲ� ����/���丮 �̸�

			if ((wcscmp(f_d_n_j2k, TEXT(".")) != 0) && (wcscmp(f_d_n_j2k, TEXT("..")) != 0)) {
				if (wcscmp(f_n_org, f_n_cvt) != 0) {
					_wrename(f_n_org, f_n_cvt);
				}
			}
			//*.�̳� ..�� �ƴ� ���� �̸� �ٲٱ�

			if (_attr & FILE_ATTRIBUTE_DIRECTORY) {
				if ((wcscmp(f_d_n_j2k, TEXT(".")) != 0) && (wcscmp(f_d_n_j2k, TEXT("..")) != 0)) {
					Change_Name_Codepage_J2K(f_n_cvt);
					//*�ٲ� ���丮���� �־ ��ͷ� ȣ��
				}
			}
			//*���丮 �Ӽ��� �� : "."�� ".."�� �ƴϸ� ��ͷ� �İ���

			free(f_d_n_j2k);

		} while (is_there_next_file_or_dir);
		FindClose(hFile);
	}
	//*���� / ���丮�� �ٲٱ�
}
//*�̸� �ڵ������� ����� ����Լ�


void Change_Data_Codepage_J2K(wchar_t* DataFolder)
{
	HANDLE hFile;
	WIN32_FIND_DATAW wfd_w;
	wchar_t f_format[MAX_PATH];
	memset(f_format, 0, sizeof(wchar_t) * MAX_PATH);
	swprintf(f_format, TEXT("%s\\*"), DataFolder);
	//*ã�� �غ� ��ġ��

	bool is_there_next_file_or_dir = true;
	wchar_t f_d_n[MAX_PATH];
	DWORD _attr = 0;
	wchar_t f_n_org[MAX_PATH];

	hFile = FindFirstFileW(f_format, &wfd_w);
	if (hFile != INVALID_HANDLE_VALUE) {

		do
		{
			_attr = wfd_w.dwFileAttributes;
			memset(f_d_n, 0, sizeof(wchar_t) * MAX_PATH);
			memcpy(f_d_n, wfd_w.cFileName, (sizeof(wchar_t) * wcslen(wfd_w.cFileName)));
			is_there_next_file_or_dir = FindNextFileW(hFile, &wfd_w);
			//*Ȥ�� �𸣴� ���� / �������� �ٲٱ� ���� �̸� �Ӽ��� ���� / ���ϸ� ���� ��
			//*���� ����� Ȯ���Ѵ�

			memset(f_n_org, 0, sizeof(wchar_t) * MAX_PATH);
			swprintf(f_n_org, TEXT("%s\\%s"), DataFolder, f_d_n);
			//*����/���丮 �̸�

			if (_attr & FILE_ATTRIBUTE_DIRECTORY) {
				if ((wcscmp(f_d_n, TEXT(".")) != 0) && (wcscmp(f_d_n, TEXT("..")) != 0)) {
					Change_Data_Codepage_J2K(f_n_org);
					//*�ٲ� ���丮���� �־ ��ͷ� ȣ��
				}
			}
			//*���丮 �Ӽ��� �� : "."�� ".."�� �ƴϸ� ��ͷ� �İ���

			else {
				if ((wcsistr(f_d_n, TEXT(".lsb")) != 0) || (wcsistr(f_d_n, TEXT(".lpb")) != 0)
					|| (wcsistr(f_d_n, TEXT(".lpm")) != 0) || (wcsistr(f_d_n, TEXT(".lcm")) != 0)
					|| (wcsistr(f_d_n, TEXT(".lmt")) != 0) || (wcsistr(f_d_n, TEXT("install.dat")) != 0))
				{
					LM_BASE_SCRIPT* _scr;
					if (wcsistr(f_d_n, TEXT(".lsb")) != 0) { _scr = new LSB_SCRIPT(); }
					else if (wcsistr(f_d_n, TEXT(".lpb")) != 0) { _scr = new LPB_SCRIPT(); }
					else if (wcsistr(f_d_n, TEXT(".lpm")) != 0) { _scr = new LPM_SCRIPT(); }
					else if ((wcsistr(f_d_n, TEXT(".lcm")) != 0) || (wcsistr(f_d_n, TEXT(".lmt")) != 0))
					{
						_scr = new LCM_LMT_SCRIPT();
					}
					else { _scr = new INSTALL_DAT_SCRIPT(); }
					_scr->Script_Analysis(f_n_org, LM_CP_JAP);
					_scr->Convert_Codepage_J2K();
					_scr->Make_To_Script(f_n_org, LM_CP_KOR);
					delete _scr;
					//*��ũ��Ʈ�� ������, Ȯ���ں��� ������ ����
				}
				else if (wcsistr(f_d_n, TEXT(".lft")) != 0)
				{
					HANDLE hLft = CreateFileW(f_n_org, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if (hLft == INVALID_HANDLE_VALUE) {
						wprintf(TEXT("%s: Can't Open File\n"), f_n_org);
						_setmode(_fileno(stdout), _O_TEXT);
						if (!is_there_next_file_or_dir) { FindClose(hFile); return; }
						else { continue; }
					}
					//*�ڵ� ����

					unsigned int lft_size = GetFileSize(hLft, NULL);
					char* lft_buffer = (char*)malloc(lft_size);
					ReadFile(hLft, lft_buffer, lft_size, NULL, NULL);
					CloseHandle(hLft);
					//*���� �о���̱�

					memset((lft_buffer + 0x1A), 0, 0x40);
					memcpy (lft_buffer + 0x1A, _exe_font_kor_name_hy_taegothic, strlen(_exe_font_kor_name_hy_taegothic));
					//*��Ʈ�� ���� ���

					hLft = CreateFileW(f_n_org, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					WriteFile(hLft, lft_buffer, lft_size, NULL, NULL);
					free(lft_buffer);
					CloseHandle(hLft);
					//*�ٽ� ��� �� ����

					//*��Ʈ������ ���� 0x1A ��ġ�� ����ϸ� �ȴ�
				}
				else if ((wcsistr(f_d_n, TEXT(".txt")) != 0) || (wcsistr(f_d_n, TEXT(".tsv")) != 0))
				{
					HANDLE hTxt = CreateFileW(f_n_org, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if (hTxt == INVALID_HANDLE_VALUE) {
						wprintf(TEXT("%s: Can't Open File\n"), f_n_org);
						_setmode(_fileno(stdout), _O_TEXT);
						if (!is_there_next_file_or_dir) { FindClose(hFile); return; }
						else { continue; }
					}
					//*�ڵ� ����

					unsigned int txt_size = GetFileSize(hTxt, NULL);
					if (txt_size == 0) {
						wprintf(TEXT("%s: File Size Is 0\n"), f_n_org);
						_setmode(_fileno(stdout), _O_TEXT);
						CloseHandle(hTxt);
						if (!is_there_next_file_or_dir) { FindClose(hFile); return; }
						else { continue; }
					}
					//*ũ�Ⱑ 0�̸� �������� ����

					UINT16 _chk = 0;
					ReadFile(hTxt, &_chk, 2, NULL, NULL);
					if (_chk == 0xFEFF) {
						wprintf(TEXT("%s: This File Isn't Unicode File\n"), f_n_org);
						_setmode(_fileno(stdout), _O_TEXT);
						CloseHandle(hTxt);
						if (!is_there_next_file_or_dir) { FindClose(hFile); return; }
						else { continue; }
					}
					//*�����ڵ尡 �ƴ� �� ����, �����غ��� txt ������ ���� �����ڵ尡 �ƴϾ���

					SetFilePointer(hTxt, 0, NULL, FILE_BEGIN);
					char* txt_buffer = (char*)malloc(txt_size + 1);
					ReadFile(hTxt, txt_buffer, txt_size, NULL, NULL);
					txt_buffer[txt_size] = 0;
					CloseHandle(hTxt);
					//*���� �о���̱�

					wchar_t* _txt_uni = GetUniStr(txt_buffer, LM_CP_JAP);
					free(txt_buffer);
					JPHan_2_KRHan(_txt_uni);
					char* _txt_j2k = GetAnsiStr(_txt_uni, LM_CP_KOR);
					free(_txt_uni);
					//*�����ڵ� -> ����ڵ� ���� -> �ٽ� ansi�ڵ�

					hTxt = CreateFileW(f_n_org, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					WriteFile(hTxt, _txt_j2k, strlen(_txt_j2k), NULL, NULL);
					free(_txt_j2k);
					CloseHandle(hTxt);
					//*�ٽ� ��� �� ����
				}
			}
			//*���� �Ӽ��� �� : ���˿� �����ϸ� ���� ���뵵 �ѱ��� ����ڵ�� ����

		} while (is_there_next_file_or_dir);
		FindClose(hFile);
	}
	//*���ϵ� ������ �ٲٱ�
}
//*������ �ڵ������� ����� ����Լ�




void CHANGE_DATA_IN_BUFFER (unsigned char* org_buff, unsigned int org_size, 
	const unsigned char* org_data, const unsigned char *chg_data, unsigned int data_len, bool is_once)
{
	unsigned char *_exe_buff_pnt = org_buff;
	bool Found_Bs;
	while (_exe_buff_pnt < (org_buff + org_size - data_len)) {
		while ((*(_exe_buff_pnt) != (org_data)[0]) && (_exe_buff_pnt < (org_buff + org_size - data_len)))
		{ _exe_buff_pnt++; }
		Found_Bs = true;
		for (unsigned int i = 0; i < data_len; i++) {
			if (_exe_buff_pnt[i] != (org_data)[i]) { Found_Bs = false; break; }
		}
		if (Found_Bs) { 
			memcpy(_exe_buff_pnt, chg_data, data_len); 
			if (is_once) { break; }
		}
		else { _exe_buff_pnt++; }
	}
	return;
}
//*���� ������ �� ������ �ٲٱ�

void LM_Convert_Exe_Codepage_J2K(char* ExeFile)
{
	wchar_t* uni_exe = GetUniStr(ExeFile, LM_CP_KOR);

	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Converting Exe Codepage(Jap -> Kor): Exe File: To %s\n"), uni_exe);

	HANDLE hExe = CreateFileW(uni_exe, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	free(uni_exe);
	if (hExe == INVALID_HANDLE_VALUE) {
		wprintf(TEXT("Failed!\n"));
		_setmode(_fileno(stdout), _O_TEXT);
		return; 
	}
	//*�ڵ� ����

	unsigned int ExeSize = GetFileSize(hExe, NULL);
	unsigned char* ExeBuffer = (unsigned char*)malloc(ExeSize);
	ReadFile(hExe, ExeBuffer, ExeSize, NULL, NULL);
	CloseHandle(hExe);
	//*���� �о���̱� / �ڵ� ����

	unsigned char* _exe_buff_pnt;

	CHANGE_DATA_IN_BUFFER (ExeBuffer, ExeSize, _exe_search_bs_1, _exe_change_bs_1, 6, true);
	//*ù° ��ɾ� �ٲٱ� (LOGFONT ����ü�� 0x81 ���� ����)

	CHANGE_DATA_IN_BUFFER (ExeBuffer, ExeSize, _exe_search_bs_2, _exe_change_bs_2, 8, true);
	//*��° ��ɾ� �ٲٱ� (�ݰ��� �������� �ٲٴ� �Լ��� �ִµ� �ѱ� �ϼ��� �����θ� �ٲٰ� �ϱ�)

	CHANGE_DATA_IN_BUFFER (ExeBuffer, ExeSize, _exe_search_bs_4, _exe_change_bs_4, 11, true);
	CHANGE_DATA_IN_BUFFER (ExeBuffer, ExeSize, _exe_search_bs_5, _exe_change_bs_5, 14, true);
	//*��°, �ټ�° ��ɾ� �ٲٱ� (81 40 ��Ī�� A1 A1 ��Ī���� �ٲٱ�)

	CHANGE_DATA_IN_BUFFER (ExeBuffer, ExeSize, _exe_font_jap_part_name_ms_2, _exe_font_kor_name_08_seoul_namsan_eb, 16, false);
	//*�Ϻ� ��ɾ� �� ��Ʈ �ٲٱ� (���� ���ͷ� �ɷ��� �� �����Ƿ� ���� ���� ����)
	//*��� ��Ʈ�� �ٲ�� �ϴ� ��ó�� �ؾ� �Ѵ�

	unsigned int data_section_start_pos = *(unsigned int*)(ExeBuffer + 0x220 + (sizeof(int) * 5));
	unsigned int data_section_size = *(unsigned int*)(ExeBuffer + 0x220 + (sizeof(int) * 4));
	unsigned int* pnt = (unsigned int*)(ExeBuffer + data_section_start_pos);
	for (unsigned int i = 0; i < (data_section_size / 4);i++) {
		if (pnt[i] == 0x3A4) { pnt[i] = 0x3B5; }
	}
	//*�߰��� 3A4 -> 3B5�� �� ���� ����
	//*code ���� data ������ ������ �� �� ������ �����ٵ� �ű⸸ �ٲ��ָ� �ȴ�
	//*������ 4����� �������� �׳� �׷��� �Ǵ��ϸ� �Ǵ� �� ����

	_exe_buff_pnt = ExeBuffer;
	unsigned char* _last_pnt = NULL;
	while (_exe_buff_pnt < (ExeBuffer + ExeSize - 5)) {
		if (((*_exe_buff_pnt) == 0) && (*(unsigned int*)(_exe_buff_pnt + 1) == 0x3A4)) { _last_pnt = _exe_buff_pnt; }
		_exe_buff_pnt++;
	}
	if (_last_pnt != NULL) { *(unsigned int*)(_last_pnt + 1) = 0x3B5; }
	//*������ �ϳ��� ������ �� ������ �ٲ�� ��
	//*������ �ٲ��� ����.

	unsigned char* _exe_pnt = ExeBuffer;
	unsigned char* _exe_pnt_2 = ExeBuffer;
	unsigned char* _exe_pnt_3 = ExeBuffer;
	unsigned char* _exe_pnt_4 = ExeBuffer;
	while (_exe_pnt < (ExeBuffer + ExeSize)) {
		if ((*(unsigned int*)_exe_pnt) != 0xFFFFFFFF) { _exe_pnt++; }
		else {
			_exe_pnt_2 = (_exe_pnt + sizeof(int));
			unsigned int _str_len = *(unsigned int*)_exe_pnt_2;
			if ((_str_len == 0) || (_str_len >= 0x400)) { _exe_pnt++; }
			else {
				_exe_pnt_3 = (_exe_pnt_2 + sizeof(int));
				char* _str = (char*)malloc(_str_len + 1);
				memset(_str, 0, (_str_len + 1));
				bool _is_real_str = true;
				for (unsigned int i = 0; i < _str_len;i++) {
					if (_exe_pnt_3[i] == 0) { _is_real_str = false; }
					_str[i] = (char)_exe_pnt_3[i];
				}
				if (!_is_real_str) { free(_str); _exe_pnt++; }
				else {
					_exe_pnt_4 = (_exe_pnt_3 + _str_len);
					if ((*_exe_pnt_4) != 0x00) { free(_str); _exe_pnt++; }
					else {
						//*_exe_pnt : 0xFFFFFFFF
						//*_exe_pnt_2 : ���ڿ� ���� ��ġ
						//*_exe_pnt_3 : ���ڿ� ������
						//*_exe_pnt_4 : ���ڿ� ���κ�

						wchar_t* _t_uni = GetUniStr(_str, LM_CP_JAP);
						free(_str);
						JPHan_2_KRHan(_t_uni);
						char* _t_cvt = GetAnsiStr(_t_uni, LM_CP_KOR);
						free(_t_uni);
						//*���� ���� �̾Ƴ���

						if (stricmp(_exe_xml_shift_jis_str, _t_cvt) == 0) {
							for (unsigned char* _ppt = _exe_pnt_2; _ppt < _exe_pnt_4; _ppt++) { *_ppt = 0; }
							*(unsigned int*)_exe_pnt_2 = strlen(_exe_xml_euc_kr_str);
							memcpy((_exe_pnt_2 + sizeof(int)), _exe_xml_euc_kr_str, strlen(_exe_xml_euc_kr_str));
						}
						else if (stricmp(_exe_shift_jis_str_1, _t_cvt) == 0) {
							for (unsigned char* _ppt = _exe_pnt_2; _ppt < _exe_pnt_4; _ppt++) { *_ppt = 0; }
							*(unsigned int*)_exe_pnt_2 = strlen(_exe_euc_kr_str_1);
							memcpy((_exe_pnt_2 + sizeof(int)), _exe_euc_kr_str_1, strlen(_exe_euc_kr_str_1));
						}
						else if (stricmp(_exe_shift_jis_str_2, _t_cvt) == 0) {
							for (unsigned char* _ppt = _exe_pnt_2; _ppt < _exe_pnt_4; _ppt++) { *_ppt = 0; }
							*(unsigned int*)_exe_pnt_2 = strlen(_exe_euc_kr_str_2);
							memcpy((_exe_pnt_2 + sizeof(int)), _exe_euc_kr_str_2, strlen(_exe_euc_kr_str_2));
						}
						else if ((stristr(_t_cvt, _exe_font_jap_part_name_ms) != NULL)
							|| (stristr(_t_cvt, _exe_font_jap_name_07_soft_gothic) != NULL)) {
							for (unsigned char* _ppt = _exe_pnt_2; _ppt < _exe_pnt_4; _ppt++) { *_ppt = 0; }
							*(unsigned int*)_exe_pnt_2 = strlen(_exe_font_kor_name_hy_taegothic);
							memcpy((_exe_pnt_2 + sizeof(int)), 
								_exe_font_kor_name_hy_taegothic, strlen(_exe_font_kor_name_hy_taegothic));
						}
						//*Ư���� ����� ���� ���� ���۸� ���׸� ���� ���ϴ� �������� ä���ִ´�
						//*��Ʈ�� ���ܰ� �� �������� �ֱ� �ѵ� �Ƹ� "�ͣ�"�� �˻��ص� ���� �� �ɸ��Ű�
						//*�ȵȴ� ������ ���ܸ� �����ϸ� �ȴ�

						else {

							if (strcmp(_t_cvt, "����") == 0) { memcpy(_exe_pnt_3, "����", strlen("����")); }
							else if (strcmp(_t_cvt, "�������") == 0) { memcpy(_exe_pnt_3, "ȭ����ȯ", strlen("ȭ����ȯ")); }
							else { memcpy(_exe_pnt_3, _t_cvt, strlen(_t_cvt)); }
							free(_t_cvt);
							//*���ڿ� ����ڵ� �ٲ�ġ�� _exe_pnt_3�� ����ϸ� ��
							//*Ư���� ���ڴ� ���� ���
						}

						_exe_pnt = (_exe_pnt_4 + 1);
					}
					//*���Ⱑ ��¥�̹Ƿ� ��ġ�� ��°�� �����Ѵ�
				}
			}
		}
	}
	//*�����ͷ� ���ư��鼭 ��ġ�� ã�� üũ�ϱ�
	//[FF FF FF FF][���� ����][���� ����Ʈ][00 00 00 00] �̷� ������ �Ǿ��ִ� �κ��� �� �ٲ۴�

	CHANGE_DATA_IN_BUFFER(ExeBuffer, ExeSize, _exe_search_bs_3_1, _exe_change_bs_3_1, 6, false);
	CHANGE_DATA_IN_BUFFER(ExeBuffer, ExeSize, _exe_search_bs_3_2, _exe_change_bs_3_2, 6, true);
	CHANGE_DATA_IN_BUFFER(ExeBuffer, ExeSize, _exe_search_bs_3_3, _exe_change_bs_3_3, 6, true);
	//*���������� ��° ��ɾ� �ٲٱ� (�ݰ�->���� ��ȯ�� ���ĺ� / ���ڸ� ���������� �ν��ϰ� �ϱ�)

	char _n_ExeFile[MAX_PATH], *tp_pnt = ExeFile;
	memset(_n_ExeFile, 0, MAX_PATH);
	for (tp_pnt = ExeFile + (strlen(ExeFile) - 1); tp_pnt >= ExeFile; tp_pnt--) {
		if ((*tp_pnt == '.')) { break; }
	}
	memcpy(_n_ExeFile, ExeFile, sizeof(char) * (tp_pnt - ExeFile));
	sprintf(_n_ExeFile + strlen(_n_ExeFile), "_h.exe");
	//*exe ���ϸ� ����

	wchar_t* _n_exe_uni = GetUniStr(_n_ExeFile, LM_CP_KOR);
	hExe = CreateFileW(_n_exe_uni, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	free(_n_exe_uni);
	WriteFile(hExe, ExeBuffer, ExeSize, NULL, NULL);
	CloseHandle(hExe);
	free(ExeBuffer);
	wprintf(TEXT("Finished!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
//	CloseHandle(hTxt);
	//*��� �� ����
}
//*exe���� �ڵ������� ����� �Լ�




void LM_Extract_All_Script_Text(char* DataFolder, unsigned int code)
{
	wchar_t* uni_dir = GetUniStr(DataFolder, LM_CP_KOR);

	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Extracting Lsb Text: In Directory: %s\n"), uni_dir);

	Extract_Script_Text(uni_dir, code);

	wprintf(TEXT("Extract Complete!\n"));
	free(uni_dir);
}
//*�ش� ���丮 �� ��� lsb ���� �ؽ�Ʈ�� �����ϴ� �Լ�


void Extract_Script_Text(wchar_t* DataFolder, unsigned int code)
{
	HANDLE hFile;
	WIN32_FIND_DATAW wfd_w;
	wchar_t f_format[MAX_PATH];
	memset(f_format, 0, sizeof(wchar_t) * MAX_PATH);
	swprintf(f_format, TEXT("%s\\*"), DataFolder);
	//*ã�� �غ� ��ġ��

	wchar_t f_d_n[MAX_PATH];
	DWORD _attr = 0;
	wchar_t f_n_org[MAX_PATH];
	//*��Ÿ ����

	hFile = FindFirstFileW(f_format, &wfd_w);
	if (hFile != INVALID_HANDLE_VALUE) {

		do
		{
			_attr = wfd_w.dwFileAttributes;
			memset(f_d_n, 0, sizeof(wchar_t) * MAX_PATH);
			memcpy(f_d_n, wfd_w.cFileName, (sizeof(wchar_t) * wcslen(wfd_w.cFileName)));

			memset(f_n_org, 0, sizeof(wchar_t) * MAX_PATH);
			swprintf(f_n_org, TEXT("%s\\%s"), DataFolder, f_d_n);
			//*����/���丮 �̸�

			if (_attr & FILE_ATTRIBUTE_DIRECTORY) {
				if ((wcscmp(f_d_n, TEXT(".")) != 0) && (wcscmp(f_d_n, TEXT("..")) != 0)) {
					Extract_Script_Text(f_n_org, code);
					//*�ٲ� ���丮���� �־ ��ͷ� ȣ��
				}
			}
			//*���丮 �Ӽ��� �� : "."�� ".."�� �ƴϸ� ��ͷ� �İ���

			else {

				if ((wcsistr(f_d_n, TEXT(".lsb")) != 0) 
					|| (wcsistr(f_d_n, TEXT(".lpb")) != 0)
					|| (wcsistr(f_d_n, TEXT("install.dat")) != 0))
				{
					LM_BASE_SCRIPT* _scr;
					if (wcsistr(f_d_n, TEXT(".lsb")) != 0) { _scr = new LSB_SCRIPT(); }
					else if (wcsistr(f_d_n, TEXT(".lpb")) != 0) { _scr = new LPB_SCRIPT(); }
					else { _scr = new INSTALL_DAT_SCRIPT(); }

					wchar_t* _tp_name = (wchar_t*)malloc(sizeof(wchar_t) * MAX_PATH);
					memset(_tp_name, 0, (sizeof(wchar_t) * MAX_PATH));
					memcpy(_tp_name, f_n_org, (sizeof(wchar_t) * (wcslen(f_n_org) - 4)));
					swprintf(_tp_name + wcslen(_tp_name), TEXT(".ext.txt"));
					//*���ϸ� �����

					_scr->Script_Analysis(f_n_org, code);
					_scr->Extract_Text_Data(_tp_name);
					delete _scr;
					free(_tp_name);
					//* ��¸� : '~.lsb' -> '~.ext.txt'
				}
			}
			//*���� �Ӽ��� �� : ���˿� �����ϸ�( = .lsb Ȥ�� lpb Ȥ�� dat ����) �ؽ�Ʈ ����

		} while (FindNextFileW(hFile, &wfd_w));

	}
	//*����� ȣ��
}
//*lsb �ؽ�Ʈ ����� ����Լ� ����




void LM_Replace_All_Script_Text(char* DataFolder, unsigned int code)
{
	wchar_t* uni_dir = GetUniStr(DataFolder, LM_CP_KOR);

	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Replacing Lsb Text: In Directory: %s\n"), uni_dir);

	Replace_Script_Text(uni_dir, code);

	wprintf(TEXT("Replace Complete!\n"));
	free(uni_dir);
}
//*�ش� ���丮 �� ��� lsb ������ ��ġ�ϴ� �Լ�


void Replace_Script_Text(wchar_t* DataFolder, unsigned int code)
{
	HANDLE hFile;
	WIN32_FIND_DATAW wfd_w;
	wchar_t f_format[MAX_PATH];
	memset(f_format, 0, sizeof(wchar_t) * MAX_PATH);
	swprintf(f_format, TEXT("%s\\*"), DataFolder);
	//*ã�� �غ� ��ġ��

	wchar_t f_d_n[MAX_PATH];
	DWORD _attr = 0;
	wchar_t f_n_org[MAX_PATH];
	//*��Ÿ ����

	hFile = FindFirstFileW(f_format, &wfd_w);
	if (hFile != INVALID_HANDLE_VALUE) {

		do
		{
			_attr = wfd_w.dwFileAttributes;
			memset(f_d_n, 0, sizeof(wchar_t) * MAX_PATH);
			memcpy(f_d_n, wfd_w.cFileName, (sizeof(wchar_t) * wcslen(wfd_w.cFileName)));

			memset(f_n_org, 0, sizeof(wchar_t) * MAX_PATH);
			swprintf(f_n_org, TEXT("%s\\%s"), DataFolder, f_d_n);
			//*����/���丮 �̸�

			if (_attr & FILE_ATTRIBUTE_DIRECTORY) {
				if ((wcscmp(f_d_n, TEXT(".")) != 0) && (wcscmp(f_d_n, TEXT("..")) != 0)) {
					Replace_Script_Text(f_n_org, code);
					//*�ٲ� ���丮���� �־ ��ͷ� ȣ��
				}
			}
			//*���丮 �Ӽ��� �� : "."�� ".."�� �ƴϸ� ��ͷ� �İ���

			else {

				if ((wcsistr(f_d_n, TEXT(".lsb")) != 0)
					|| (wcsistr(f_d_n, TEXT(".lpb")) != 0)
					|| (wcsistr(f_d_n, TEXT("install.dat")) != 0))
				{
					LM_BASE_SCRIPT* _scr;
					if (wcsistr(f_d_n, TEXT(".lsb")) != 0) { _scr = new LSB_SCRIPT(); }
					else if (wcsistr(f_d_n, TEXT(".lpb")) != 0) { _scr = new LPB_SCRIPT(); }
					else { _scr = new INSTALL_DAT_SCRIPT(); }

					wchar_t* _tp_txt_name = (wchar_t*)malloc(sizeof(wchar_t) * MAX_PATH);
					memset(_tp_txt_name, 0, (sizeof(wchar_t) * MAX_PATH));
					memcpy(_tp_txt_name, f_n_org, (sizeof(wchar_t) * (wcslen(f_n_org) - 4)));
					swprintf(_tp_txt_name + wcslen(_tp_txt_name), TEXT(".ext.txt"));
					//*����Ǿ��� ���ϸ� �����

					HANDLE hT = CreateFileW(_tp_txt_name, GENERIC_READ, FILE_SHARE_READ,
						NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if (hT == INVALID_HANDLE_VALUE) {
						wprintf(TEXT("%s: There's no Extracted Txt File\n"), _tp_txt_name);
						free(_tp_txt_name); continue;
					}
					CloseHandle(hT);
					//*�� ���ϸ� ������ �׳� continue

					_scr->Script_Analysis(f_n_org, code);
					_scr->Replace_Text_Data(_tp_txt_name, code);
					_wremove(f_n_org);
					_scr->Make_To_Script(f_n_org, code);
					delete _scr;
					free(_tp_txt_name);
					//* ��¸� : '~.lsb' -> '~.ext.txt'
					//* ���� ������ ������ �Ѵ�
				}
			}
			//*���� �Ӽ��� �� : ���˿� �����ϸ�( = .lsb Ȥ�� lpb Ȥ�� dat ����) �ؽ�Ʈ ����

		} while (FindNextFileW(hFile, &wfd_w));

	}
	//*����� ȣ��
}
//*lsb �ؽ�Ʈ ��ġ�� ����Լ� ����




void LM_Decompile_All_Script(char* DataFolder, unsigned int code)
{
	wchar_t* uni_dir = GetUniStr(DataFolder, LM_CP_KOR);

	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Decompiling All Script: In Directory: %s\n"), uni_dir);

	Decompile_Script(uni_dir, code);

	wprintf(TEXT("Decompile Complete!\n"));
	free(uni_dir);
}
//*�ش� ���丮 �� ��� ��ũ��Ʈ ������ ���������ϴ� �Լ�


void Decompile_Script(wchar_t* DataFolder, unsigned int code)
{
	HANDLE hFile;
	WIN32_FIND_DATAW wfd_w;
	wchar_t f_format[MAX_PATH];
	memset(f_format, 0, sizeof(wchar_t) * MAX_PATH);
	swprintf(f_format, TEXT("%s\\*"), DataFolder);
	//*ã�� �غ� ��ġ��

	wchar_t f_d_n[MAX_PATH];
	DWORD _attr = 0;
	wchar_t f_n_org[MAX_PATH];
	//*��Ÿ ����

	hFile = FindFirstFileW(f_format, &wfd_w);
	if (hFile != INVALID_HANDLE_VALUE) {

		do
		{
			_attr = wfd_w.dwFileAttributes;
			memset(f_d_n, 0, sizeof(wchar_t) * MAX_PATH);
			memcpy(f_d_n, wfd_w.cFileName, (sizeof(wchar_t) * wcslen(wfd_w.cFileName)));

			memset(f_n_org, 0, sizeof(wchar_t) * MAX_PATH);
			swprintf(f_n_org, TEXT("%s\\%s"), DataFolder, f_d_n);
			//*����/���丮 �̸�

			if (_attr & FILE_ATTRIBUTE_DIRECTORY) {
				if ((wcscmp(f_d_n, TEXT(".")) != 0) && (wcscmp(f_d_n, TEXT("..")) != 0)) {
					Decompile_Script(f_n_org, code);
					//*�ٲ� ���丮���� �־ ��ͷ� ȣ��
				}
			}
			//*���丮 �Ӽ��� �� : "."�� ".."�� �ƴϸ� ��ͷ� �İ���

			else {


				if ((wcsistr(f_d_n, TEXT(".lsb")) != 0) || (wcsistr(f_d_n, TEXT(".lpb")) != 0)
					|| (wcsistr(f_d_n, TEXT(".lpm")) != 0) || (wcsistr(f_d_n, TEXT(".lcm")) != 0)
					|| (wcsistr(f_d_n, TEXT(".lmt")) != 0) || (wcsistr(f_d_n, TEXT("install.dat")) != 0))
				{
					LM_BASE_SCRIPT* _scr;
					if (wcsistr(f_d_n, TEXT(".lsb")) != 0) { _scr = new LSB_SCRIPT(); }
					else if (wcsistr(f_d_n, TEXT(".lpb")) != 0) { _scr = new LPB_SCRIPT(); }
					else if (wcsistr(f_d_n, TEXT(".lpm")) != 0) { _scr = new LPM_SCRIPT(); }
					else if ((wcsistr(f_d_n, TEXT(".lcm")) != 0) || (wcsistr(f_d_n, TEXT(".lmt")) != 0))
					{
						_scr = new LCM_LMT_SCRIPT();
					}
					else { _scr = new INSTALL_DAT_SCRIPT(); }

					wchar_t* _tp_txt_name = (wchar_t*)malloc(sizeof(wchar_t) * MAX_PATH);
					memset(_tp_txt_name, 0, (sizeof(wchar_t) * MAX_PATH));
					memcpy(_tp_txt_name, f_n_org, (sizeof(wchar_t) * (wcslen(f_n_org) - 4)));
					swprintf(_tp_txt_name + wcslen(_tp_txt_name), TEXT(".txt"));
					//*���ϸ� �����

					_scr->Script_Analysis(f_n_org, code);
					_scr->Decompile_To_Code(_tp_txt_name, code);
					free(_tp_txt_name);
					delete _scr;
					//*��ũ��Ʈ�� ������, Ȯ���ں��� ������ ����
				}
			}
			//*���� �Ӽ��� �� : ���˿� �����ϸ�( = .lsb Ȥ�� lpb Ȥ�� dat ����) �ؽ�Ʈ ����

		} while (FindNextFileW(hFile, &wfd_w));

	}
	//*����� ȣ��
}
//*�������Ͽ� ����Լ� ����