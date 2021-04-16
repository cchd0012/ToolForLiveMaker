#include "LM_Script.h"
#include "LM_Functions.h"


#pragma warning (disable:6031)
#pragma warning (disable:4996)

//*** lcm/lmt ��ũ��Ʈ �м� �� ���� �Լ����� �����ϴ� ����




//---------------------------- ��ũ��Ʈ Ŭ���� ���� �Լ� ----------------------------//
bool LCM_LMT_SCRIPT::Script_Analysis(wchar_t* Lcm_Lmt_File, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Analysis: Lcm/Lmt File: %s\n"), Lcm_Lmt_File);

	HANDLE h_Lcm_Lmt = CreateFileW(Lcm_Lmt_File, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h_Lcm_Lmt == INVALID_HANDLE_VALUE) {
		wprintf(TEXT("%s: There's not LCM/LMT File\n"), Lcm_Lmt_File);
		_setmode(_fileno(stdout), _O_TEXT);
		return false;
	}
	unsigned int lcm_lmt_size = GetFileSize(h_Lcm_Lmt, NULL);
	unsigned char* lcm_lmt_buffer = (unsigned char*)malloc(lcm_lmt_size);
	ReadFile(h_Lcm_Lmt, lcm_lmt_buffer, lcm_lmt_size, NULL, NULL);
	CloseHandle(h_Lcm_Lmt);
	//*lcm/lmt ���� �о���̱� (���� ��� ����ڵ嵵 ����� �ʿ� ����)

	unsigned char* lcm_lmt_buffer_pnt = lcm_lmt_buffer;
	//*�ʿ��� ������

	char* _s;
	unsigned char* _b;
	unsigned int* _int;

	_s = (char*)_get_data(&lcm_lmt_buffer_pnt, 10);
	_Signature = GetUniStr(_s, code);
	free(_s);
	//*�ñ״�ó �о���̱�, cinema�� motion�̳� ���̰� ���Ƽ� ���̸� ����� ���ص� �ȴ�

	_s = (char*)_get_data(&lcm_lmt_buffer_pnt, 3);
	_Version = GetUniStr(_s, code);
	unsigned int _Version_Int = strtol(_s, NULL, 10);
	free(_s);
	//*���� �о���̱�

	_int = _get_int(&lcm_lmt_buffer_pnt);
	_Width = *_int; free(_int);
	_int = _get_int(&lcm_lmt_buffer_pnt);
	_Height = *_int; free(_int);
	//*�ʺ� / ���� �о���̱�

	for (unsigned int i = 0; i < 4;i++) {
		_int = _get_int(&lcm_lmt_buffer_pnt);
		_unk_1[i] = *_int; free(_int);
	}
	//*�𸣴� �� �о���̱� (���� �迭)

	_b = _get_byte(&lcm_lmt_buffer_pnt);
	_unk_2 = *_b; free(_b);
	//*�𸣴� �� �о���̱� (����Ʈ)

	_int = _get_int(&lcm_lmt_buffer_pnt);
	_elem_count = *_int; free(_int);
	//*����� �� �о���̱�

	_elem_list = (LCM_LMT_SCRIPT_ELEM**)malloc(sizeof(LCM_LMT_SCRIPT_ELEM*) * _elem_count);
	memset(_elem_list, 0, (sizeof(LCM_LMT_SCRIPT_ELEM*) * _elem_count));
	for (unsigned int i = 0; i < _elem_count;i++) {
		_elem_list[i] = new LCM_LMT_SCRIPT_ELEM(_Version_Int);
		_elem_list[i]->_read_from_buffer(&lcm_lmt_buffer_pnt, code);
	}
	//*��� �迭 �Ҵ� �� ������ �о���̱�

	wprintf(TEXT("Script Analysis Complete!\n"));
	free(lcm_lmt_buffer);
	_setmode(_fileno(stdout), _O_TEXT);
	return true;
	//*����
}
//*lcm/lmt ������ �ҷ��� �м��ϴ� �Լ�


void LCM_LMT_SCRIPT::Decompile_To_Code(wchar_t* TxtFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Decompiling to Code: Lcm/Lmt File: To %s\n"), TxtFile);

	HANDLE hWrite = CreateFileW(TxtFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//*�ڵ� ����

	UINT16 BOM = 0xFEFF;
	WriteFile(hWrite, &BOM, 2, NULL, NULL);
	//*�����ڵ� ���� ���� �غ� (BOM)

	memset(_txt_buf, 0, sizeof(wchar_t) * TXT_BUFF_LEN);
	//*�� ó���� �ݵ�� 0���� �ʱ�ȭ��

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s_%s%s%s"), _Signature, _Version, _enter_raw_, separation_line);
	//*�ñ״�ó �� ���� ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Resolution]::[%03d*%03d]%s%s"), _Width, _Height, _enter_raw_, separation_line);
	//*�ʺ� �� ���� ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[__UNK_ARR_0x%02X__]::[0x%08X][0x%08X][0x%08X][0x%08X]%s%s"), 
		_unk_2, _unk_1[0], _unk_1[1], _unk_1[2], _unk_1[3], _enter_raw_, separation_line);
	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*�𸣴� ������ �迭 �� ��Ÿ ���� ���
	//*1�� ���

	for (unsigned int i = 0; i < _elem_count;i++) {
		memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
		_elem_list[i]->_decompile_code(hWrite, code);
		WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	}
	//*�������� ��Ҹ� �������� ���

	WriteFile(hWrite, separation_line, (sizeof(wchar_t) * wcslen(separation_line)), NULL, NULL);
	//*���༱ �߰�

	CloseHandle(hWrite);
	//*�ڵ� ����

	wprintf(TEXT("Decompiling Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*����
}
//*���������ؼ� ����ϴ� �Լ�


void LCM_LMT_SCRIPT::Make_To_Script(wchar_t* new_Lcm_Lmt_File, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Writing: Lcm/Lmt File: %s\n"), new_Lcm_Lmt_File);

	HANDLE hNew_Lcm_Lmt = CreateFileW(new_Lcm_Lmt_File, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//*�ڵ� ����

	char* _s;
	//*��Ͽ� ����

	_s = GetAnsiStr(_Signature, code);
	_write_data(hNew_Lcm_Lmt, (unsigned char*)_s, strlen(_s)); free(_s);
	//*�ñ״�ó ���

	_s = GetAnsiStr(_Version, code);
	_write_data(hNew_Lcm_Lmt, (unsigned char*)_s, strlen(_s)); free(_s);
	//*���� ���

	_write_int(hNew_Lcm_Lmt, _Width);
	_write_int(hNew_Lcm_Lmt, _Height);
	//*�ʺ�/���� ���

	for (unsigned int i = 0; i < 4;i++) { _write_int(hNew_Lcm_Lmt, _unk_1[i]); }
	_write_byte(hNew_Lcm_Lmt, _unk_2);
	//*���� ����Ʈ, ����Ʈ�� ���

	_write_int(hNew_Lcm_Lmt, _elem_count);
	for (unsigned int i = 0; i < _elem_count;i++) {
		_elem_list[i]->_write_as_lcm_or_lmt(hNew_Lcm_Lmt, code);
	}
	//*��� ���� �� �� ����� ������ ���

	CloseHandle(hNew_Lcm_Lmt);
	//*�ڵ� ����

	wprintf(TEXT("Writing Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*����
}
//*lsb ���Ϸ� ����ϴ� �Լ�


void LCM_LMT_SCRIPT::Extract_Text_Data(wchar_t* DstTxtFile)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Not Need To Extract...\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*���� �ؽ�Ʈ�� ������ �ʿ䰡 ����
}
//*�ؽ�Ʈ ���� �Լ�


void LCM_LMT_SCRIPT::Replace_Text_Data(wchar_t* SrcTxtFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Not Need To Replace...\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*���� �ؽ�Ʈ�� ��ġ�� �ʿ䰡 ����
}
//*�ؽ�Ʈ ��ü �Լ�


void LCM_LMT_SCRIPT::Convert_Codepage_J2K()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Changing Text Language Code(Jap -> Kor)...\n"));

	for (unsigned int i = 0; i < _elem_count; i++) {
		JPHan_2_KRHan(_elem_list[i]->_SrcFile);
	}
	//*�� ����� srcfile�� �ٲٸ� ��

	wprintf(TEXT("Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
}
//*�ؽ�Ʈ ����ڵ带 �Ϻ���� �ѱ۷� �ٲٴ� �Լ�
//---------------------------- ��ũ��Ʈ Ŭ���� ���� �Լ� ----------------------------//




//---------------------------- ��ũ��Ʈ ��� Ŭ���� ���� �Լ� ----------------------------//
void LCM_LMT_SCRIPT_ELEM::_read_from_buffer(unsigned char** _lcm_lmt_buffer_pnt, unsigned int code)
{
	unsigned char* lcm_lmt_buffer_pnt = (*_lcm_lmt_buffer_pnt);
	char* _s;
	unsigned char* _b;
	unsigned int* _int;
	double* _do;

	_b = _get_byte(&lcm_lmt_buffer_pnt);
	_elem_type = *_b; free(_b);
	//*Ÿ�� �о���̱�

	for (unsigned int i = 0; i < 6;i++) {
		_int = _get_int(&lcm_lmt_buffer_pnt);
		_unk_2[i] = *_int; free(_int);
	}
	//*���� ����Ʈ �о���̱�

	for (unsigned int i = 0; i < 3; i++) {
		_b = _get_byte(&lcm_lmt_buffer_pnt);
		_unk_3[i] = *_b; free(_b);
	}
	//*����Ʈ ����Ʈ �о���̱�

	if (_Version >= 0x71) {
		_s = _get_str(&lcm_lmt_buffer_pnt);
		_unk_3_1 = GetUniStr(_s, code); free(_s);
	}
	//*������ 113 �̻��̸� ���ڿ� ����

	if (_elem_type == 0) {
		_elem_info_0_1 = (LCM_LMT_TILE_INFO_1*)malloc(sizeof(LCM_LMT_TILE_INFO_1));
		_elem_info_0_2 = (LCM_LMT_TILE_INFO_2*)malloc(sizeof(LCM_LMT_TILE_INFO_2));
		_unk_5 = (LCM_LMT_UNK_65*)malloc(sizeof(LCM_LMT_UNK_65));
		_unk_6 = (LCM_LMT_UNK_69*)malloc(sizeof(LCM_LMT_UNK_69));
		_unk_7 = (LCM_LMT_UNK_6D*)malloc(sizeof(LCM_LMT_UNK_6D));
		memset(_elem_info_0_1, 0, sizeof(LCM_LMT_TILE_INFO_1));
		memset(_elem_info_0_2, 0, sizeof(LCM_LMT_TILE_INFO_2));
		memset(_unk_5, 0, sizeof(LCM_LMT_UNK_65));
		memset(_unk_6, 0, sizeof(LCM_LMT_UNK_69));
		memset(_unk_7, 0, sizeof(LCM_LMT_UNK_6D));
		//*�ʿ��� ���� �Ҵ� �� �ʱ�ȭ

		for (unsigned int i = 0; i < 6;i++) {
			_int = _get_int(&lcm_lmt_buffer_pnt);
			_elem_info_0_1->_int_list[i] = *_int; free(_int);
		}
		for (unsigned int i = 0; i < 2; i++) {
			_b = _get_byte(&lcm_lmt_buffer_pnt);
			_elem_info_0_1->_char_list[i] = *_b; free(_b);
		}
		//*_elem_info_0_1

		if (_Version >= 0x6E) {
			_unk_4_1 = (LCM_LMT_UNK_6E*)malloc(sizeof(LCM_LMT_UNK_6E));
			memset(_unk_4_1, 0, sizeof(LCM_LMT_UNK_6E));
			for (unsigned int i = 0; i < 2;i++) {
				_do = _get_double(&lcm_lmt_buffer_pnt);
				_unk_4_1->_double_list[i] = *_do; free(_do);
			}
		}
		else {
			_unk_4_2 = (LCM_LMT_UNK_NOT_6E*)malloc(sizeof(LCM_LMT_UNK_NOT_6E));
			memset(_unk_4_2, 0, sizeof(LCM_LMT_UNK_NOT_6E));
			for (unsigned int i = 0; i < 2; i++) {
				_int = _get_int(&lcm_lmt_buffer_pnt);
				_unk_4_2->_int_list[i] = *_int; free(_int);
			}
		}
		//*������ ���� _unk_4_1 Ȥ�� _unk_4_2 �о���̱�

		for (unsigned int i = 0; i < 2; i++) {
			_do = _get_double(&lcm_lmt_buffer_pnt);
			_elem_info_0_2->_double_list[i] = *_do; free(_do);
		}
		_b = _get_byte(&lcm_lmt_buffer_pnt);
		_elem_info_0_2->_char_1 = *_b; free(_b);
		for (unsigned int i = 0; i < 2; i++) {
			_int = _get_int(&lcm_lmt_buffer_pnt);
			_elem_info_0_2->_int_list[i] = *_int; free(_int);
		}
		_b = _get_byte(&lcm_lmt_buffer_pnt);
		_elem_info_0_2->_char_2 = *_b; free(_b);
		//*_elem_info_0_2

		if (_Version >= 0x65) {
			for (unsigned int i = 0; i < 8; i++) {
				_int = _get_int(&lcm_lmt_buffer_pnt);
				_unk_5->_int_list[i] = *_int; free(_int);
			}
			for (unsigned int i = 0; i < 2;i++) {
				_b = _get_byte(&lcm_lmt_buffer_pnt);
				_unk_5->_char_list[i] = *_b; free(_b);
			}
		}
		//*������ ���� unk_5 �о���̱�

		if (_Version >= 0x69) {
			for (unsigned int i = 0; i < 2; i++) {
				_do = _get_double(&lcm_lmt_buffer_pnt);
				_unk_6->_double_list[i] = *_do; free(_do);
			}
			_b = _get_byte(&lcm_lmt_buffer_pnt);
			_unk_6->_char = *_b; free(_b);
		}
		//*������ ���� unk_6 �о���̱�

		if (_Version >= 0x6D) {
			for (unsigned int i = 0; i < 4; i++) {
				_int = _get_int(&lcm_lmt_buffer_pnt);
				_unk_7->_int_list[i] = *_int; free(_int);
			}
		}
		//*������ ���� unk_7 �о���̱�

		_s = _get_str(&lcm_lmt_buffer_pnt);
		_SrcFile = GetUniStr(_s, code); free(_s);
		//*���� ���ڿ� �о���̱�
	}
	//*Ÿ���� 0�� ��

	else if (_elem_type == 2) {
		_elem_info_2 = (LCM_LMT_BOX_INFO*)malloc(sizeof(LCM_LMT_BOX_INFO));
		_unk_5 = (LCM_LMT_UNK_65*)malloc(sizeof(LCM_LMT_UNK_65));
		_unk_7 = (LCM_LMT_UNK_6D*)malloc(sizeof(LCM_LMT_UNK_6D));
		memset(_elem_info_2, 0, sizeof(LCM_LMT_BOX_INFO));
		memset(_unk_5, 0, sizeof(LCM_LMT_UNK_65));
		memset(_unk_7, 0, sizeof(LCM_LMT_UNK_6D));
		//*�ʿ��� ���� �Ҵ� �� �ʱ�ȭ

		for (unsigned int i = 0; i < 4;i++) {
			_int = _get_int(&lcm_lmt_buffer_pnt);
			_elem_info_2->_int_list_1[i] = *_int; free(_int);
		}
		for (unsigned int i = 0; i < 2; i++) {
			_b = _get_byte(&lcm_lmt_buffer_pnt);
			_elem_info_2->_char_list[i] = *_b; free(_b);
		}
		for (unsigned int i = 0; i < 12; i++) {
			_int = _get_int(&lcm_lmt_buffer_pnt);
			_elem_info_2->_int_list_2[i] = *_int; free(_int);
		}
		//*_elem_info_2

		if (_Version >= 0x65) {
			for (unsigned int i = 0; i < 8; i++) {
				_int = _get_int(&lcm_lmt_buffer_pnt);
				_unk_5->_int_list[i] = *_int; free(_int);
			}
			for (unsigned int i = 0; i < 2; i++) {
				_b = _get_byte(&lcm_lmt_buffer_pnt);
				_unk_5->_char_list[i] = *_b; free(_b);
			}
		}
		//*������ ���� unk_5 �о���̱�

		if (_Version >= 0x6D) {
			for (unsigned int i = 0; i < 4; i++) {
				_int = _get_int(&lcm_lmt_buffer_pnt);
				_unk_7->_int_list[i] = *_int; free(_int);
			}
		}
		//*������ ���� unk_7 �о���̱�
	}
	//*Ÿ���� 2�� ��

	else if (_elem_type == 4) {
		_elem_info_4 = (LCM_LMT_SOUND_INFO*)malloc(sizeof(LCM_LMT_SOUND_INFO));
		memset(_elem_info_4, 0, sizeof(LCM_LMT_SOUND_INFO));
		//*�ʿ��� ���� �Ҵ� �� �ʱ�ȭ

		_s = _get_str(&lcm_lmt_buffer_pnt);
		_SrcFile = GetUniStr(_s, code); free(_s);
		//*���� ���ڿ� �о���̱�

		for (unsigned int i = 0; i < 4; i++) {
			_int = _get_int(&lcm_lmt_buffer_pnt);
			_elem_info_4->_int_list[i] = *_int; free(_int);
		}
		for (unsigned int i = 0; i < 2; i++) {
			_b = _get_byte(&lcm_lmt_buffer_pnt);
			_elem_info_4->_char_list[i] = *_b; free(_b);
		}
		//*_elem_info_4
	}
	//*Ÿ���� 4�� ��

	else { ; }
	//*�ƹ��͵� �ƴ� ��

	(*_lcm_lmt_buffer_pnt) = lcm_lmt_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�


void LCM_LMT_SCRIPT_ELEM::_decompile_code(HANDLE hWrite, unsigned int code)
{
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("Element::[__TYPE_0x%02X__]%s"), _elem_type, _enter_raw_);
	//*Ÿ��

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_INT_ARR__]::[%d, %d, %d, %d, %d, %d]%s"),
		_indent_, _unk_2[0], _unk_2[1], _unk_2[2], _unk_2[3], _unk_2[4], _unk_2[5], _enter_raw_);
	//*���� �𸣴� ���� ���� (�׳� �������·� ���)

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_CHAR_ARR__]::[%d, %d, %d]%s"),
		_indent_, _unk_3[0], _unk_3[1], _unk_3[2], _enter_raw_);
	//*���� �𸣴� ����Ʈ ���� (�׳� �������·� ���)

	if (_Version >= 0x71) {
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_STR__]::%s%s%s%s"), 
			_indent_, text_prefix, _unk_3_1, text_prefix, _enter_raw_);
	}
	//*������ ���� _unk_3_1 (���ڿ��� ���)

	if (_elem_type == 0) {
		
		swprintf(_txt_buf + wcslen(_txt_buf), 
			TEXT("%s[__ELEM_0_1__]::[%d, %d]@[%d, %d]@[%d, %d]::[_%02X_]@[_%02X_]%s"),
			_indent_, 
			_elem_info_0_1->_int_list[0], _elem_info_0_1->_int_list[1], 
			_elem_info_0_1->_int_list[2], _elem_info_0_1->_int_list[3], 
			_elem_info_0_1->_int_list[4], _elem_info_0_1->_int_list[5],
			_elem_info_0_1->_char_list[0], _elem_info_0_1->_char_list[1],
			_enter_raw_);
		//*_elem_info_0_1

		if (_Version >= 0x6E) {
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_4_1__]::[%lf, %lf]%s"),
				_indent_, _unk_4_1->_double_list[0], _unk_4_1->_double_list[1], _enter_raw_);
		}
		else {
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_4_2__]::[%d, %d]%s"),
				_indent_, _unk_4_2->_int_list[0], _unk_4_2->_int_list[1], _enter_raw_);
		}
		//*������ ���� _unk_4_1 Ȥ�� _unk_4_2

		swprintf(_txt_buf + wcslen(_txt_buf),
			TEXT("%s[__ELEM_0_2__]::[%lf, %lf]::[_%02X_]::[%d, %d]::[_%02X_]%s"),
			_indent_,
			_elem_info_0_2->_double_list[0], _elem_info_0_2->_double_list[1],
			_elem_info_0_2->_char_1,
			_elem_info_0_2->_int_list[0], _elem_info_0_2->_int_list[1],
			_elem_info_0_2->_char_2,
			_enter_raw_);
		//*_elem_info_0_2

		if (_Version >= 0x65) {
			swprintf(_txt_buf + wcslen(_txt_buf),
				TEXT("%s[__UNK_5__]::[%d, %d]@[%d, %d]@[%d, %d]@[%d, %d]::[_%02X_]@[_%02X_]%s"),
				_indent_,
				_unk_5->_int_list[0], _unk_5->_int_list[1],
				_unk_5->_int_list[2], _unk_5->_int_list[3],
				_unk_5->_int_list[4], _unk_5->_int_list[5],
				_unk_5->_int_list[6], _unk_5->_int_list[7],
				_unk_5->_char_list[0], _unk_5->_char_list[1],
				_enter_raw_);
		}
		//*������ ���� _unk_5

		if (_Version >= 0x69) {
			swprintf(_txt_buf + wcslen(_txt_buf),
				TEXT("%s[__UNK_6__]::[%lf, %lf]::[_%02X_]%s"),
				_indent_,
				_unk_6->_double_list[0], _unk_6->_double_list[1],
				_unk_6->_char,
				_enter_raw_);
		}
		//*������ ���� _unk_6

		if (_Version >= 0x6D) {
			swprintf(_txt_buf + wcslen(_txt_buf),
				TEXT("%s[__UNK_7__]::[%d, %d, %d, %d]%s"),
				_indent_,
				_unk_7->_int_list[0], _unk_7->_int_list[1],
				_unk_7->_int_list[2], _unk_7->_int_list[3],
				_enter_raw_);
		}
		//*������ ���� _unk_7

		swprintf(_txt_buf + wcslen(_txt_buf),
			TEXT("%s[__SRC__]::%s%s%s%s"),
			_indent_, text_prefix, _SrcFile, text_prefix,
			_enter_raw_);
		//*_SrcFile
	}
	//*_elem_type�� 0�� �� ��Ϲ��

	else if (_elem_type == 2) {

		swprintf(_txt_buf + wcslen(_txt_buf),
			TEXT("%s[__ELEM_2__]::[%d, %d]@[%d, %d]::[_%02X_]@[_%02X_]::"),
			_indent_,
			_elem_info_2->_int_list_1[0], _elem_info_2->_int_list_1[1],
			_elem_info_2->_int_list_1[2], _elem_info_2->_int_list_1[3],
			_elem_info_2->_char_list[0], _elem_info_2->_char_list[1]);
		swprintf(_txt_buf + wcslen(_txt_buf),
			TEXT("[%d, %d]@[%d, %d]@[%d, %d]@[0x%08X, 0x%08X]@[%d, %d]@[%d, %d]%s"),
			_elem_info_2->_int_list_2[0], _elem_info_2->_int_list_2[1],
			_elem_info_2->_int_list_2[2], _elem_info_2->_int_list_2[3],
			_elem_info_2->_int_list_2[4], _elem_info_2->_int_list_2[5],
			_elem_info_2->_int_list_2[6], _elem_info_2->_int_list_2[7],
			_elem_info_2->_int_list_2[8], _elem_info_2->_int_list_2[9],
			_elem_info_2->_int_list_2[10], _elem_info_2->_int_list_2[11],
			_enter_raw_);
		//*_elem_info_2

		if (_Version >= 0x65) {
			swprintf(_txt_buf + wcslen(_txt_buf),
				TEXT("%s[__UNK_5__]::[%d, %d]@[%d, %d]@[%d, %d]@[%d, %d]::[_%02X_]@[_%02X_]%s"),
				_indent_,
				_unk_5->_int_list[0], _unk_5->_int_list[1],
				_unk_5->_int_list[2], _unk_5->_int_list[3],
				_unk_5->_int_list[4], _unk_5->_int_list[5],
				_unk_5->_int_list[6], _unk_5->_int_list[7],
				_unk_5->_char_list[0], _unk_5->_char_list[1],
				_enter_raw_);
		}
		//*������ ���� _unk_5

		if (_Version >= 0x6D) {
			swprintf(_txt_buf + wcslen(_txt_buf),
				TEXT("%s[__UNK_7__]::[%d, %d, %d, %d]%s"),
				_indent_,
				_unk_7->_int_list[0], _unk_7->_int_list[1],
				_unk_7->_int_list[2], _unk_7->_int_list[3],
				_enter_raw_);
		}
		//*������ ���� _unk_7
	}
	//*_elem_type�� 2�� �� ��Ϲ��

	else if (_elem_type == 4) {

		swprintf(_txt_buf + wcslen(_txt_buf),
			TEXT("%s[__ELEM_4__]::[%d, %d]@[%d, %d]::[_%02X_]@[_%02X_]%s"),
			_indent_,
			_elem_info_4->_int_list[0], _elem_info_4->_int_list[1],
			_elem_info_4->_int_list[2], _elem_info_4->_int_list[3],
			_elem_info_4->_char_list[0], _elem_info_4->_char_list[1],
			_enter_raw_);
		//*_elem_info_4

		swprintf(_txt_buf + wcslen(_txt_buf),
			TEXT("%s[__SRC__]::%s%s%s%s"),
			_indent_, text_prefix, _SrcFile, text_prefix,
			_enter_raw_);
		//*_SrcFile
	}
	//*_elem_type�� 4�� �� ��Ϲ��

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _enter_raw_);
	//*���� �߰�
}
//*�������� �Լ�


void LCM_LMT_SCRIPT_ELEM::_write_as_lcm_or_lmt(HANDLE hNew_Lcm_Lmt, unsigned int code)
{
	char* _s;
	//*��Ͽ� ����

	_write_byte(hNew_Lcm_Lmt, _elem_type);
	//*��� Ÿ�� ���

	for (unsigned int i = 0; i < 6;i++) { _write_int(hNew_Lcm_Lmt, _unk_2[i]); }
	for (unsigned int i = 0; i < 3; i++) { _write_byte(hNew_Lcm_Lmt, _unk_3[i]); }
	//*ù ��������Ʈ / ����Ʈ����Ʈ ���

	if (_Version >= 0x71) {
		_s = GetAnsiStr(_unk_3_1, code);
		_write_str(hNew_Lcm_Lmt, _s); free(_s);
	}
	//*������ ���� unk_3_1 ���

	if (_elem_type == 0) {
		for (unsigned int i = 0; i < 6; i++) { _write_int(hNew_Lcm_Lmt, _elem_info_0_1->_int_list[i]); }
		for (unsigned int i = 0; i < 2; i++) { _write_byte(hNew_Lcm_Lmt, _elem_info_0_1->_char_list[i]); }
		//*_elem_info_0_1

		if (_Version >= 0x6E) {
			for (unsigned int i = 0; i < 2; i++) { _write_double(hNew_Lcm_Lmt, _unk_4_1->_double_list[i]); }
		}
		else {
			for (unsigned int i = 0; i < 2; i++) { _write_int(hNew_Lcm_Lmt, _unk_4_2->_int_list[i]); }
		}
		//*������ ���� _unk_4_1 Ȥ�� _unk_4_2

		for (unsigned int i = 0; i < 2; i++) { _write_double(hNew_Lcm_Lmt, _elem_info_0_2->_double_list[i]); }
		_write_byte(hNew_Lcm_Lmt, _elem_info_0_2->_char_1);
		for (unsigned int i = 0; i < 2; i++) { _write_int(hNew_Lcm_Lmt, _elem_info_0_2->_int_list[i]); }
		_write_byte(hNew_Lcm_Lmt, _elem_info_0_2->_char_2);
		//*_elem_info_0_2

		if (_Version >= 0x65) {
			for (unsigned int i = 0; i < 8; i++) { _write_int(hNew_Lcm_Lmt, _unk_5->_int_list[i]); }
			for (unsigned int i = 0; i < 2; i++) { _write_byte(hNew_Lcm_Lmt, _unk_5->_char_list[i]); }
		}
		//*������ ���� _unk_5

		if (_Version >= 0x69) {
			for (unsigned int i = 0; i < 2; i++) { _write_double(hNew_Lcm_Lmt, _unk_6->_double_list[i]); }
			_write_byte(hNew_Lcm_Lmt, _unk_6->_char);
		}
		//*������ ���� _unk_6

		if (_Version >= 0x6D) {
			for (unsigned int i = 0; i < 4; i++) { _write_int(hNew_Lcm_Lmt, _unk_7->_int_list[i]); }
		}
		//*������ ���� _unk_7

		_s = GetAnsiStr(_SrcFile, code);
		_write_str(hNew_Lcm_Lmt, _s); free(_s);
		//*���� ���ڿ�
	}
	//*��� Ÿ���� 0�� �� ��Ϲ��

	else if (_elem_type == 2) {
		for (unsigned int i = 0; i < 4; i++) { _write_int(hNew_Lcm_Lmt, _elem_info_2->_int_list_1[i]); }
		for (unsigned int i = 0; i < 2; i++) { _write_byte(hNew_Lcm_Lmt, _elem_info_2->_char_list[i]); }
		for (unsigned int i = 0; i < 12; i++) { _write_int(hNew_Lcm_Lmt, _elem_info_2->_int_list_2[i]); }
		//*_elem_info_2

		if (_Version >= 0x65) {
			for (unsigned int i = 0; i < 8; i++) { _write_int(hNew_Lcm_Lmt, _unk_5->_int_list[i]); }
			for (unsigned int i = 0; i < 2; i++) { _write_byte(hNew_Lcm_Lmt, _unk_5->_char_list[i]); }
		}
		//*������ ���� _unk_5

		if (_Version >= 0x6D) {
			for (unsigned int i = 0; i < 4; i++) { _write_int(hNew_Lcm_Lmt, _unk_7->_int_list[i]); }
		}
		//*������ ���� _unk_7
	}
	//*��� Ÿ���� 2�� �� ��Ϲ��

	else if (_elem_type == 4) {
		_s = GetAnsiStr(_SrcFile, code);
		_write_str(hNew_Lcm_Lmt, _s); free(_s);
		//*���� ���ڿ�

		for (unsigned int i = 0; i < 4; i++) { _write_int(hNew_Lcm_Lmt, _elem_info_4->_int_list[i]); }
		for (unsigned int i = 0; i < 2; i++) { _write_byte(hNew_Lcm_Lmt, _elem_info_4->_char_list[i]); }
		//*_elem_info_4
	}
	//*��� Ÿ���� 4�� �� ��Ϲ��
}
//*lcm/lmt ���Ϸ� ����ϴ� �Լ�
//---------------------------- ��ũ��Ʈ ��� Ŭ���� ���� �Լ� ----------------------------//