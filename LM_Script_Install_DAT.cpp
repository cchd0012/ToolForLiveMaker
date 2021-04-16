#include "LM_Script.h"
#include "LM_Functions.h"


#pragma warning (disable:6031)
#pragma warning (disable:4996)


//*** install.dat ��ũ��Ʈ �м� �� ���� �Լ����� �����ϴ� ����


//---------------------------- ��ũ��Ʈ Ŭ���� ���� �Լ� ----------------------------//
bool INSTALL_DAT_SCRIPT::Script_Analysis(wchar_t* DatFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Analysis: Lpb File: %s\n"), DatFile);

	HANDLE hDat = CreateFileW(DatFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDat == INVALID_HANDLE_VALUE) {
		wprintf(TEXT("%s: There's not DAT File\n"), DatFile);
		_setmode(_fileno(stdout), _O_TEXT);
		return false;
	}
	unsigned int dat_size = GetFileSize(hDat, NULL);
	unsigned char* dat_buffer = (unsigned char*)malloc(dat_size);
	ReadFile(hDat, dat_buffer, dat_size, NULL, NULL);
	unsigned char* dat_buffer_pnt = dat_buffer;
	CloseHandle(hDat);
	//*dat ���� �о���̱� (���� ��� ����ڵ嵵 ����� �ʿ� ����)

	unsigned int* _i;
	unsigned char* _b;
	char* _s;

	_s = (char*)_get_data(&dat_buffer_pnt, 2);
	_Signature = GetUniStr(_s, code);
	free(_s);
	//*�ñ״�ó ���ڿ� �о���̱�

	_s = (char*)_get_data(&dat_buffer_pnt, 3);
	_Version = GetUniStr(_s, code);
	_Version_Int = strtol(_s, NULL, 10);
	free(_s);
	//*���� �о���� �� ���� ��ȯ

	_i = _get_int(&dat_buffer_pnt);
	_unk_1 = *_i; free(_i);
	//*�𸣴� �� 1

	_s = _get_str(&dat_buffer_pnt);
	_Game_Title = GetUniStr(_s, code); free(_s);
	_s = _get_str(&dat_buffer_pnt);
	_unk_2 = GetUniStr(_s, code); free(_s);
	_s = _get_str(&dat_buffer_pnt);
	_Compile_Dir = GetUniStr(_s, code); free(_s);
	_s = _get_str(&dat_buffer_pnt);
	_unk_3 = GetUniStr(_s, code); free(_s);
	//*���ڿ� 4�� �������

	_b = _get_byte(&dat_buffer_pnt);
	_unk_4 = *_b; free(_b);
	_s = _get_str(&dat_buffer_pnt);
	_unk_5 = GetUniStr(_s, code); free(_s);
	_b = _get_byte(&dat_buffer_pnt);
	_unk_6 = *_b; free(_b);
	//*�𸣴� �� 4 / 5 / 6

	_i = _get_int(&dat_buffer_pnt);
	_Attr_Count = *_i; free(_i);
	//*�Ӽ�(?)�� ��

	_s = _get_str(&dat_buffer_pnt);
	_Execute_File_Name = GetUniStr(_s, code); free(_s);
	//*�������ϸ�

	_i = _get_int(&dat_buffer_pnt);
	_unk_7 = *_i; free(_i);
	_b = _get_byte(&dat_buffer_pnt);
	_unk_8 = *_b; free(_b);
	_b = _get_byte(&dat_buffer_pnt);
	_unk_9 = *_b; free(_b);
	//*�𸣴� �� 7 / 8 / 9

	_s = _get_str(&dat_buffer_pnt);
	_Drive_Type = GetUniStr(_s, code); free(_s);
	//*����̺� Ÿ��(?)

	_s = _get_str(&dat_buffer_pnt);
	_unk_10 = GetUniStr(_s, code); free(_s);
	//*�𸣴� �� 10

	if (_Version_Int >= 0x64) {
		_Attr_list_1 = (DAT_ATTR_ELEM_64*)malloc(sizeof(DAT_ATTR_ELEM_64) * (_Attr_Count + 1));
		memset(_Attr_list_1, 0, (sizeof(DAT_ATTR_ELEM_64) * (_Attr_Count + 1)));
		for (unsigned int i = 0; i < (_Attr_Count + 1);i++) {
			for (unsigned int j = 0; j < 8; j++) {
				_i = _get_int(&dat_buffer_pnt);
				_Attr_list_1[i]._int_list[j] = *_i; free(_i);
			}
		}
	}
	else {
		_Attr_list_2 = (DAT_ATTR_ELEM_NOT_64*)malloc(sizeof(DAT_ATTR_ELEM_NOT_64) * (_Attr_Count + 1));
		memset(_Attr_list_2, 0, (sizeof(DAT_ATTR_ELEM_NOT_64) * (_Attr_Count + 1)));
		for (unsigned int i = 0; i < (_Attr_Count + 1); i++) {
			for (unsigned int j = 0; j < 4; j++) {
				_i = _get_int(&dat_buffer_pnt);
				_Attr_list_2[i]._int_list[j] = *_i; free(_i);
			}
		}
	}
	//*�Ӽ�(?) ����ŭ �Ҵ��ϰ� �о���̱�, ������ �����ؾ� ��
	//*��� +1��ŭ �� �ؼ� �о�鿩�� �ϴϱ� �Ҵ��� �ݵ�� �ؾ� �Ѵ�

	_b = _get_byte(&dat_buffer_pnt);
	_unk_11 = *_b; free(_b);
	//*�𸣴� �� 11

	if (_Version_Int >= 0x65) {
		_b = _get_byte(&dat_buffer_pnt);
		_unk_12 = *_b; free(_b);
	}
	//*������ ���� �𸣴� �� 12

	if (_Version_Int >= 0x66) {
		_i = _get_int(&dat_buffer_pnt);
		_unk_13_count = *_i; free(_i);
		if (_unk_13_count != 0) {
			_unk_13_list = (DAT_ATTR_ELEM_66*)malloc (sizeof(DAT_ATTR_ELEM_66) * _unk_13_count);
			memset(_unk_13_list, 0, (sizeof(DAT_ATTR_ELEM_66) * _unk_13_count));
			for (unsigned int i = 0; i < _unk_13_count;i++) {
				char* _ss = _get_str(&dat_buffer_pnt);
				_unk_13_list[i]._str = GetUniStr(_ss, code);
				free(_ss);
			}
		}
	}
	//*������ ���� �𸣴� �� 13(����Ʈ)
	//*���� ���� ���� �о���� ���� �ְ� �ƴ� ���� �ִ�

	if (_Version_Int >= 0x66) {
		_b = _get_byte(&dat_buffer_pnt);
		_unk_14 = *_b; free(_b);
	}
	//*������ ���� �𸣴� �� 14

	if (_Version_Int >= 0x68) {
		_b = _get_byte(&dat_buffer_pnt);
		_unk_15 = *_b; free(_b);
	}
	//*������ ���� �𸣴� �� 15

	if (_Version_Int >= 0x69) {
		_b = _get_byte(&dat_buffer_pnt);
		_unk_16 = *_b; free(_b);
	}
	//*������ ���� �𸣴� �� 16

	if (_Version_Int >= 0x6A) {
		_i = _get_int(&dat_buffer_pnt);
		_unk_17_count = *_i; free(_i);
		if (_unk_17_count != 0) {
			_unk_17_list = (wchar_t**)malloc(sizeof(wchar_t*) * _unk_17_count);
			memset(_unk_17_list, 0, (sizeof(wchar_t*) * _unk_17_count));
			for (unsigned int i = 0; i < _unk_17_count; i++) {
				_s = _get_str(&dat_buffer_pnt);
				_unk_17_list[i] = GetUniStr(_s, code); free(_s);
			}
		}
	}
	//*������ ���� �𸣴� �� 17(����Ʈ)

	if (_Version_Int >= 0x6B) {
		_s = _get_str(&dat_buffer_pnt);
		_unk_18 = GetUniStr(_s, code); free(_s);
	}
	//*������ ���� �𸣴� �� 18

	if (_Version_Int >= 0x6C) {
		for (unsigned int i = 0; i < 2; i++) {
			_s = _get_str(&dat_buffer_pnt);
			_unk_19[i] = GetUniStr(_s, code); free(_s);
		}
	}
	//*������ ���� �𸣴� �� 19(����Ʈ)

	wprintf(TEXT("Script Analysis Complete!\n"));
	free(dat_buffer);
	_setmode(_fileno(stdout), _O_TEXT);
	return true;
}
//*install.dat ������ �ҷ��� �м��ϴ� �Լ�


void INSTALL_DAT_SCRIPT::Decompile_To_Code(wchar_t* TxtFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Decompiling to Code: Dat File: To %s\n"), TxtFile);

	HANDLE hWrite = CreateFileW(TxtFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//*�ڵ� ����

	UINT16 BOM = 0xFEFF;
	WriteFile(hWrite, &BOM, 2, NULL, NULL);
	//*�����ڵ� ���� ���� �غ� (BOM)

	memset(_txt_buf, 0, sizeof(wchar_t) * TXT_BUFF_LEN);
	//*�� ó���� �ݵ�� 0���� �ʱ�ȭ��

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s_%s[%08X]%s%s"), _Signature, _Version, _unk_1, _enter_raw_, separation_line);
	//*�ñ״�ó �� ���� �� �𸣴� �� 1 ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Game_Title]::%s%s%s%s"), text_prefix, _Game_Title, text_prefix, _enter_raw_);
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[__UNK_2__]::%s%s%s%s"), text_prefix, _unk_2, text_prefix, _enter_raw_);
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Compiled_Dir]::%s%s%s%s"), text_prefix, _Compile_Dir, text_prefix, _enter_raw_);
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[__UNK_3__]::%s%s%s%s"), text_prefix, _unk_3, text_prefix, _enter_raw_);
	//*���ڿ� 4�� ������� ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[__UNK_5_%02X_%02X__]::%s%s%s%s"), 
		_unk_4, _unk_6, text_prefix, _unk_5, text_prefix, _enter_raw_);
	//*�𸣴� �� 4 / 5 / 6 ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Execute_File]::%s%s%s%s"), text_prefix, _Execute_File_Name, text_prefix, _enter_raw_);
	//*�������ϸ� ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[__UNK_5_%02X_%02X__]::[0x%08X]%s"),
		_unk_8, _unk_9, _unk_7, _enter_raw_);
	//*�𸣴� �� 7 / 8 / 9 ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Drive_Type]::%s%s%s%s%s%s"),
		text_prefix, _Drive_Type, text_prefix, _unk_10, text_prefix, _enter_raw_);
	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*����̺� Ÿ�� / �𸣴� �� 10 ���
	//*1�� ���

	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Install_Attr:]%s"), _enter_raw_);
	for (unsigned int i = 0; i < (_Attr_Count + 1); i++) {
		if (_Version_Int >= 0x64) {
			swprintf(_txt_buf + wcslen(_txt_buf), 
				TEXT("  [Attr_Data]::[0x%08X, 0x%08X]:[0x%08X, 0x%08X]:[0x%08X, 0x%08X]:[0x%08X, 0x%08X]%s"),
				_Attr_list_1->_int_list[0], _Attr_list_1->_int_list[1], _Attr_list_1->_int_list[2], _Attr_list_1->_int_list[3],
				_Attr_list_1->_int_list[4], _Attr_list_1->_int_list[5], _Attr_list_1->_int_list[6], _Attr_list_1->_int_list[7],
				_enter_raw_);
		}
		else {
			swprintf(_txt_buf + wcslen(_txt_buf),
				TEXT("  [Attr_Data]::[0x%08X]:[0x%08X]:[0x%08X]:[0x%08X]%s"),
				_Attr_list_2->_int_list[0], _Attr_list_2->_int_list[1], _Attr_list_2->_int_list[2], _Attr_list_2->_int_list[3],
				_enter_raw_);
		}
	}
	//*���� ���ư��� �Ӽ� ��� (���� ����)

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[__UNK_VAL_1__]::[%02X_%02X]%s"), _unk_11, _unk_12, _enter_raw_);
	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*�𸣴� �� 11, 12
	//*2�� ���

	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[__UNK_13__]%s"), _enter_raw_);
	for (unsigned int i = 0; i < _unk_13_count; i++) {
		swprintf(_txt_buf + wcslen(_txt_buf),
			TEXT("  [__Data]::%s%s%s%s"),
			text_prefix, _unk_13_list[i]._str, text_prefix,
			_enter_raw_);
	}
	//*�𸣴� �� 13(����Ʈ)

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[__UNK_VAL_2__]::[%02X_%02X_%02X]%s"), _unk_14, _unk_15, _unk_16, _enter_raw_);
	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*�𸣴� �� 14 / 15 / 16
	//*3�� ���

	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[__UNK_17__]%s"), _enter_raw_);
	for (unsigned int i = 0; i < _unk_17_count; i++) {
		swprintf(_txt_buf + wcslen(_txt_buf),
			TEXT("  [__Data]::%s%s%s%s"), text_prefix, _unk_17_list[i], text_prefix, _enter_raw_);
	}
	//*�𸣴� �� 17(����Ʈ)

	swprintf(_txt_buf + wcslen(_txt_buf),
		TEXT("[__UNK_18__]::%s%s%s%s"), text_prefix, _unk_18, text_prefix, _enter_raw_);
	//*�𸣴� �� 18

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[__UNK_19__]%s"), _enter_raw_);
	for (unsigned int i = 0; i < 2; i++) {
		swprintf(_txt_buf + wcslen(_txt_buf),
			TEXT("  [__Data]::%s%s%s%s"), text_prefix, _unk_19[i], text_prefix, _enter_raw_);
	}
	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t)* wcslen(_txt_buf)), NULL, NULL);
	//*�𸣴� �� 19(����Ʈ)
	//*������ ���

	CloseHandle(hWrite);
	//*�ڵ� ����

	wprintf(TEXT("Decompiling Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*����
}
//*���������ؼ� ����ϴ� �Լ�


void INSTALL_DAT_SCRIPT::Make_To_Script(wchar_t* newDatFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Writing: Dat File: %s\n"), newDatFile);

	HANDLE hNewDat = CreateFileW(newDatFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//*�ڵ� ����

	char* _s;
	//*��Ͽ� ����

	_s = GetAnsiStr(_Signature, code);
	_write_data(hNewDat, (unsigned char*)_s, strlen(_s)); free(_s);
	//*�ñ״�ó ���

	_s = GetAnsiStr(_Version, code);
	_write_data(hNewDat, (unsigned char*)_s, strlen(_s)); free(_s);
	//*���� ���

	_write_int(hNewDat, _unk_1);
	//*_unk_1 ���

	_s = GetAnsiStr(_Game_Title, code);
	_write_str(hNewDat, _s); free(_s);
	_s = GetAnsiStr(_unk_2, code);
	_write_str(hNewDat, _s); free(_s);
	_s = GetAnsiStr(_Compile_Dir, code);
	_write_str(hNewDat, _s); free(_s);
	_s = GetAnsiStr(_unk_3, code);
	_write_str(hNewDat, _s); free(_s);
	//*���ڿ� 4�� ���

	_write_byte(hNewDat, _unk_4);
	_s = GetAnsiStr(_unk_5, code);
	_write_str(hNewDat, _s); free(_s);
	_write_byte(hNewDat, _unk_6);
	//*_unk_4, 5, 6 ���

	_write_int(hNewDat, _Attr_Count);
	//*�Ӽ� ���� ���

	_s = GetAnsiStr(_Execute_File_Name, code);
	_write_str(hNewDat, _s); free(_s);
	//*�������ϸ� ���

	_write_int(hNewDat, _unk_7);
	_write_byte(hNewDat, _unk_8);
	_write_byte(hNewDat, _unk_9);
	//*_unk_7, 8, 9 ���

	_s = GetAnsiStr(_Drive_Type, code);
	_write_str(hNewDat, _s); free(_s);
	//*����̺� Ÿ��(?) ���

	_s = GetAnsiStr(_unk_10, code);
	_write_str(hNewDat, _s); free(_s);
	//*_unk_10 ���

	for (unsigned int i = 0; i < (_Attr_Count + 1); i++) {
		if (_Version_Int >= 0x64) {
			for (unsigned int j = 0; j < 8;j++) { _write_int(hNewDat, _Attr_list_1[i]._int_list[j]); }
		}
		else {
			for (unsigned int j = 0; j < 4; j++) { _write_int(hNewDat, _Attr_list_2[i]._int_list[j]); }
		}
	}
	//*(�Ӽ� �� + 1)��ŭ ���ư��鼭 ���, ���� ����

	_write_byte(hNewDat, _unk_11);
	//*_unk_11 ���

	if (_Version_Int >= 0x65) { _write_byte(hNewDat, _unk_12); }
	//*������ ���� _unk_12 ���

	if (_Version_Int >= 0x66) {
		_write_int(hNewDat, _unk_13_count);
		for (unsigned int i = 0; i < _unk_13_count; i++) {
			char* _n_c = GetAnsiStr(_unk_13_list[i]._str, code);
			_write_str(hNewDat, _n_c);
			free(_n_c);
		}
	}
	//*������ ���� _unk_13 ���
	//*�հ��� ����ϰ� �հ��� 0�� �ƴϸ� �������� ���

	if (_Version_Int >= 0x67) { _write_byte(hNewDat, _unk_14); }
	if (_Version_Int >= 0x68) { _write_byte(hNewDat, _unk_15); }
	if (_Version_Int >= 0x69) { _write_byte(hNewDat, _unk_16); }
	//*������ ���� _unk_14, 15, 16 ���

	if (_Version_Int >= 0x6A) {
		_write_int(hNewDat, _unk_17_count);
		for (unsigned int i = 0; i < _unk_17_count; i++) {
			_s = GetAnsiStr(_unk_17_list[i], code);
			_write_str(hNewDat, _s); free(_s);
		}
	}
	//*������ ���� _unk_17 ���

	if (_Version_Int >= 0x6B) {
		_s = GetAnsiStr(_unk_18, code);
		_write_str(hNewDat, _s); free(_s);
	}
	//*������ ���� _unk_18 ���

	if (_Version_Int >= 0x6C) {
		for (unsigned int i = 0; i < 2; i++) {
			_s = GetAnsiStr(_unk_19[i], code);
			_write_str(hNewDat, _s); free(_s);
		}
	}
	//*������ ���� _unk_19 ���

	wprintf(TEXT("Writing Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*����
}
//*dat ���Ϸ� ����ϴ� �Լ�


void INSTALL_DAT_SCRIPT::Extract_Text_Data(wchar_t* DstTxtFile)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Extracting: Text File: %s\n"), DstTxtFile);

	HANDLE hTxt = CreateFileW(DstTxtFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//*�ڵ� ����

	UINT16 BOM = 0xFEFF;
	WriteFile(hTxt, &BOM, 2, NULL, NULL);
	//*�����ڵ� ���� ���� �غ� (BOM)

	memset(_txt_buf, 0, sizeof(wchar_t) * TXT_BUFF_LEN);
	//*�� ó���� �ݵ�� 0���� �ʱ�ȭ��

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Game_Title]::[%s]::%s%s%s%s"),
		text_data_prefix, text_prefix, _Game_Title, text_prefix, _enter_raw_);
	//*���� Ÿ��Ʋ ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Compile_Dir]::[%s]::%s%s%s%s"),
		text_data_prefix, text_prefix, _Compile_Dir, text_prefix, _enter_raw_);
	//*������ ���丮�� ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Execute_File]::[%s]::%s%s%s%s"),
		text_data_prefix, text_prefix, _Execute_File_Name, text_prefix, _enter_raw_);
	WriteFile(hTxt, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*�������ϸ� ��� �� ����

	CloseHandle(hTxt);
	//*�ڵ� ����

	wprintf(TEXT("Extracting Text Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*����
}
//*�ؽ�Ʈ ���� �Լ�


void INSTALL_DAT_SCRIPT::Replace_Text_Data(wchar_t* SrcTxtFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Replacing: Text File: %s\n"), SrcTxtFile);

	HANDLE hTxt = CreateFileW(SrcTxtFile, GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hTxt == INVALID_HANDLE_VALUE) {
		wprintf(TEXT("%s: Can't Open File\n"), SrcTxtFile);
		_setmode(_fileno(stdout), _O_TEXT);
		return;
	}
	//*�ڵ� ����

	UINT16 _chk = 0;
	ReadFile(hTxt, &_chk, 2, NULL, NULL);
	if (_chk != 0xFEFF) {
		wprintf(TEXT("%s: This File Isn't Unicode File\n"), SrcTxtFile);
		_setmode(_fileno(stdout), _O_TEXT);
		CloseHandle(hTxt);
		return;
	}
	//*�����ڵ� �ؽ�Ʈ���� üũ

	unsigned int txt_size = GetFileSize(hTxt, NULL);
	unsigned int total_txt_count = (txt_size / sizeof(wchar_t)) - 1;
	wchar_t* txt_buffer = (wchar_t*)malloc((txt_size));
	ReadFile(hTxt, txt_buffer, (txt_size - sizeof(wchar_t)), NULL, NULL);
	txt_buffer[total_txt_count] = 0;
	CloseHandle(hTxt);
	//*�ؽ�Ʈ ���� �о���̱� / �ڵ� ����

	unsigned int text_count = Get_Txt_Count(txt_buffer, text_data_prefix, total_txt_count);
	//*�ؽ�Ʈ �� Ȯ��

	wchar_t** text_list = (wchar_t**)malloc(sizeof(wchar_t*) * text_count);
	memset(text_list, 0, (sizeof(wchar_t*) * text_count));
	wchar_t* _txt_pnt = txt_buffer, * _txt_pnt_bak = txt_buffer;

	for (unsigned int i = 0; i < text_count; i++) {
		_txt_pnt = wcsstr(_txt_pnt_bak, text_data_prefix) + wcslen(text_data_prefix);
		_txt_pnt_bak = wcsstr(_txt_pnt, text_prefix) + wcslen(text_prefix);
		//*���� �ؽ�Ʈ ���� ��ġ �ľ�
		//*_txt_pnt_bak : �ؽ�Ʈ ���� ��ġ

		_txt_pnt = wcsstr(_txt_pnt_bak, text_prefix);
		//*_txt_pnt : �ؽ�Ʈ �� ��ġ

		unsigned int cp_len = _txt_pnt - _txt_pnt_bak;
		text_list[i] = (wchar_t*)malloc(sizeof(wchar_t) * (cp_len + 1));
		text_list[i][cp_len] = 0;
		memcpy(text_list[i], _txt_pnt_bak, (sizeof(wchar_t) * cp_len));
		//*�ؽ�Ʈ ������ �Ҵ� �� ����

		_txt_pnt_bak = _txt_pnt + wcslen(text_prefix);
		//*_txt_pnt_bak ��ġ ����
	}
	//*�ؽ�Ʈ ��ġ

	wchar_t* _tmp;

	_tmp = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(text_list[0]) + 1));
	memcpy(_tmp, text_list[0], (sizeof(wchar_t) * wcslen(text_list[0])));
	_tmp[wcslen(text_list[0])] = 0;
	if (_Game_Title != NULL) { free(_Game_Title); }
	_Game_Title = _tmp;
	//*���� Ÿ��Ʋ ����

	_tmp = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(text_list[1]) + 1));
	memcpy(_tmp, text_list[1], (sizeof(wchar_t) * wcslen(text_list[1])));
	_tmp[wcslen(text_list[1])] = 0;
	if (_Compile_Dir != NULL) { free(_Compile_Dir); }
	_Compile_Dir = _tmp;
	//*������ ���丮�� ����

	_tmp = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(text_list[2]) + 1));
	memcpy(_tmp, text_list[2], (sizeof(wchar_t) * wcslen(text_list[2])));
	_tmp[wcslen(text_list[2])] = 0;
	if (_Execute_File_Name != NULL) { free(_Execute_File_Name); }
	_Execute_File_Name = _tmp;
	//*�������ϸ� ����

	for (unsigned int i = 0; i < text_count; i++) {
		if (text_list[i] != NULL) { free(text_list[i]); }
	}
	free(text_list);
	free(txt_buffer);
	//*���� ����

	wprintf(TEXT("Replacing Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*����
}
//*�ؽ�Ʈ ��ü �Լ�


void INSTALL_DAT_SCRIPT::Convert_Codepage_J2K()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Changing Text Language Code(Jap -> Kor)...\n"));

	JPHan_2_KRHan(_Signature);
	JPHan_2_KRHan(_Version);
	JPHan_2_KRHan(_Game_Title);
	JPHan_2_KRHan(_unk_2);
	JPHan_2_KRHan(_Compile_Dir);
	JPHan_2_KRHan(_unk_3);
	JPHan_2_KRHan(_unk_5);
	JPHan_2_KRHan(_Execute_File_Name);
	JPHan_2_KRHan(_Drive_Type);
	JPHan_2_KRHan(_unk_10);
	for (unsigned int i = 0; i < _unk_17_count; i++) { JPHan_2_KRHan(_unk_17_list[i]); }
	JPHan_2_KRHan(_unk_18);
	for (unsigned int i = 0; i < 2; i++) { JPHan_2_KRHan(_unk_19[i]); }
	//*wchar_t*�� �� �͵��� ��� �ٲ۴�

	wprintf(TEXT("Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
}
//*�ؽ�Ʈ ����ڵ带 �Ϻ���� �ѱ۷� �ٲٴ� �Լ�
//---------------------------- ��ũ��Ʈ Ŭ���� ���� �Լ� ----------------------------//