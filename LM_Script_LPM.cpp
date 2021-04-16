#include "LM_Script.h"
#include "LM_Functions.h"


#pragma warning (disable:6031)
#pragma warning (disable:4996)

//*** lpm ��ũ��Ʈ �м� �� ���� �Լ����� �����ϴ� ����


const wchar_t* _shift_jis_str = TEXT("Shift_JIS");
const wchar_t* _euc_kr_str = TEXT("EUC-KR");
//*J2K ����� xml���� �ٲ�� �� ���ڿ�



//---------------------------- ��ũ��Ʈ Ŭ���� ���� �Լ� ----------------------------//
bool LPM_SCRIPT::Script_Analysis(wchar_t* LpmFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Analysis: LPM File: %s\n"), LpmFile);

	HANDLE hLpm = CreateFileW(LpmFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hLpm == INVALID_HANDLE_VALUE) {
		wprintf(TEXT("%s: There's not LPM File\n"), LpmFile);
		_setmode(_fileno(stdout), _O_TEXT);
		return false;
	}
	char _tmp[13]; _tmp[12] = 0;
	ReadFile(hLpm, _tmp, 12, NULL, NULL);
	CloseHandle(hLpm);
	//*���� 12����Ʈ �о���̱� (���� ��� ����ڵ嵵 ����� �ʿ� ����)

	if (strcmp(_tmp, "LivePrevMenu") == 0) { return _analysis_as_binary(LpmFile, code); }
	else { return _analysis_as_xml(LpmFile, code); }
	//*�� �� 12����Ʈ�� �о�鿩 �� ���� "LivePrevMenu"�� ��������, �ƴϸ� xml�� �м��Ѵ�
}
//*lpm ������ �ҷ��� �м��ϴ� �Լ�


bool LPM_SCRIPT::_analysis_as_xml(wchar_t* LpmFile, unsigned int code)
{
	wprintf(TEXT("Analysis As XML...\n"));
	_is_xml_script = true;
	//*xml�̸� �м��� �� �ʿ䰡 ����
	//*���߿� �ٲ� ���� ����ؼ� ���۸� �����ڵ�� �ٲ� ��� ������ �� �� �ϴ�

	HANDLE hLpm = CreateFileW(LpmFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	unsigned int lpm_size = GetFileSize(hLpm, NULL);
	unsigned char* lpm_buffer = (unsigned char*)malloc(lpm_size + 1);
	ReadFile(hLpm, lpm_buffer, lpm_size, NULL, NULL);
	lpm_buffer[lpm_size] = 0;
	unsigned char* lpm_buffer_pnt = lpm_buffer;
	CloseHandle(hLpm);
	//*lpm ���� �о���̱� (���� ��� ����ڵ嵵 ����� �ʿ� ����)

	UINT16 BOM = 0xFEFF;
	if ((*(wchar_t*)lpm_buffer_pnt) == BOM) {
		_Lpm_Buffer = (wchar_t*)malloc(lpm_size);
		memset(_Lpm_Buffer, 0, lpm_size);
		memcpy(_Lpm_Buffer, lpm_buffer + sizeof(wchar_t), (lpm_size - sizeof(wchar_t)));
		//*�� ���� �����ڵ�� �պκи� ���� �ٿ��ֱ�
	}
	else {
		_Lpm_Buffer = GetUniStr((char*)lpm_buffer_pnt, code);
		//*�׷��� �ʴٸ� �����ڵ�� �ٲٰ� �ٿ��ֱ�
	}
	free(lpm_buffer);
	//*�����ڵ�ȭ�� xml(�ؽ�Ʈ ����)�� �����ϵ��� �ϱ�

	wprintf(TEXT("Script Analysis Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	return true;
}
//*xml�� ��� �м��ϴ� �Լ�


bool LPM_SCRIPT::_analysis_as_binary(wchar_t* LpmFile, unsigned int code)
{
	wprintf(TEXT("Analysis As Binary...\n"));
	_is_xml_script = false;

	HANDLE hLpm = CreateFileW(LpmFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	unsigned int lpm_size = GetFileSize(hLpm, NULL);
	unsigned char* lpm_buffer = (unsigned char*)malloc(lpm_size);
	ReadFile(hLpm, lpm_buffer, lpm_size, NULL, NULL);
	unsigned char* lpm_buffer_pnt = lpm_buffer;
	CloseHandle(hLpm);
	//*lpm ���� �о���̱� (���� ��� ����ڵ嵵 ����� �ʿ� ����)

	_PrevMenu = new LPM_PREVMENU();
	_PrevMenu->_read_from_buffer(&lpm_buffer_pnt, code);
	//*���۷κ��� �м�

	wprintf(TEXT("Script Analysis Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	return true;
}
//*�������Ϸ� ��� �м��ϴ� �Լ�


void LPM_SCRIPT::Decompile_To_Code(wchar_t* TxtFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Decompiling to Code: Lpm File: To %s\n"), TxtFile);

	HANDLE hWrite = CreateFileW(TxtFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//*�ڵ� ����

	UINT16 BOM = 0xFEFF;
	WriteFile(hWrite, &BOM, 2, NULL, NULL);
	//*�����ڵ� ���� ���� �غ� (BOM)

	if (_is_xml_script) {
		WriteFile(hWrite, _Lpm_Buffer, sizeof(wchar_t) * wcslen(_Lpm_Buffer), NULL, NULL);
	}
	//*xml ������ ��� �׳� ������ Ȯ���ڸ� �ٲ� ����Ѵ�

	else {
		_PrevMenu->_decompile_code(hWrite, code);
		//*�������� �Լ� ȣ��

		CloseHandle(hWrite);
		//*�ڵ� ����
	}
	//*�׷��� �ʴٸ� ���� ó����

	wprintf(TEXT("Decompiling Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
}
//*���������ؼ� ����ϴ� �Լ�


void LPM_SCRIPT::Make_To_Script(wchar_t* newLpmFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Writing: Lpm File: %s\n"), newLpmFile);

	HANDLE hNewLpm = CreateFileW(newLpmFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//*�ڵ� ����

	wchar_t* _pt;
	char* _write_buffer = NULL;
	if (_is_xml_script)
	{
		if (code == LM_CP_JAP) {
_DEFAULT:
			if ((_pt = wcsistr(_Lpm_Buffer, _euc_kr_str)) != NULL) {
				wchar_t* _cpy = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_euc_kr_str) + 1));
				memcpy(_cpy, _pt, (sizeof(wchar_t) * wcslen(_euc_kr_str)));
				_cpy[wcslen(_euc_kr_str)] = 0;
				wchar_t* _n_Lpm_Buffer = Replace_Text(_Lpm_Buffer, _cpy, _shift_jis_str);
				_write_buffer = GetAnsiStr(_n_Lpm_Buffer, code);
				free(_n_Lpm_Buffer);
			}
			else {
				_write_buffer = GetAnsiStr(_Lpm_Buffer, code);
			}
			//�Ϻ��� ����ڵ� : "EUC-KR" -> "Shift_JIS", ������ �׳� ���
		}
		else if (code == LM_CP_KOR) {
			if ((_pt = wcsistr(_Lpm_Buffer, _shift_jis_str)) != NULL) {
				wchar_t* _cpy = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_shift_jis_str) + 1));
				memcpy(_cpy, _pt, (sizeof(wchar_t) * wcslen(_shift_jis_str)));
				_cpy[wcslen(_shift_jis_str)] = 0;
				wchar_t* _n_Lpm_Buffer = Replace_Text(_Lpm_Buffer, _cpy, _euc_kr_str);
				_write_buffer = GetAnsiStr(_n_Lpm_Buffer, code);
				free(_n_Lpm_Buffer);
			}
			else {
				_write_buffer = GetAnsiStr(_Lpm_Buffer, code);
			}
			//�ѱ��� ����ڵ� : "Shift_JIS" -> "EUC-KR", ������ �׳� ���
		}
		else { goto _DEFAULT; }
		//*��Ͻÿ��� �ڵ忡 ���� "Shift_JIS" / "cp932" Ȥ�� "cp949"�� �ٲ�� �Ѵ� (��ҹ��� ���� ����)

		_write_data(hNewLpm, (unsigned char*)_write_buffer, strlen(_write_buffer));
		free(_write_buffer);
		//*���������� �ٲ� �ؽ�Ʈ�� �������
	}
	//*xml ����(�ؽ�Ʈ)�� ��

	else {
		_PrevMenu->_write_as_lpm(hNewLpm, code);
	}
	//*���������� �� : PrevMenu Ŭ�������� ����

	CloseHandle(hNewLpm);
	//*�ڵ� ����

	wprintf(TEXT("Writing Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*����
}
//*lpm ���Ϸ� ����ϴ� �Լ�


void LPM_SCRIPT::Extract_Text_Data(wchar_t* DstTxtFile)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Not Need To Extract...\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*���� �ؽ�Ʈ�� ������ �ʿ䰡 ����
}
//*�ؽ�Ʈ ���� �Լ�


void LPM_SCRIPT::Replace_Text_Data(wchar_t* SrcTxtFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Not Need To Replace...\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*���� �ؽ�Ʈ�� ��ġ�� �ʿ䰡 ����
}
//*�ؽ�Ʈ ��ü �Լ�


void LPM_SCRIPT::Convert_Codepage_J2K()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Changing Text Language Code(Jap -> Kor)...\n"));

	if (_is_xml_script) { 
		JPHan_2_KRHan(_Lpm_Buffer); 
	}
	//*xml ������ �� ���Ϲ��۸� �ٲ��ָ� ��

	else { _PrevMenu->_change_code_J2K(); }
	//*���������̸� PrevMenu�� �� ���鼭 �ٲ��ش�

	wprintf(TEXT("Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
}
//*�ؽ�Ʈ ����ڵ带 �Ϻ���� �ѱ۷� �ٲٴ� �Լ�
//---------------------------- ��ũ��Ʈ Ŭ���� ���� �Լ� ----------------------------//




//---------------------------- PrevMenu Ŭ���� ���� �Լ� ----------------------------//
void LPM_PREVMENU::_read_from_buffer(unsigned char** _lpm_buffer_pnt, unsigned int code)
{
	unsigned char* lpm_buffer_pnt = (*_lpm_buffer_pnt);
	char* _s;
	unsigned int* _int;

	_s = (char*)_get_data(&lpm_buffer_pnt, 12);
	_Signature = GetUniStr(_s, code);
	free(_s);
	//*�ñ״�ó ���ڿ� �о���̱�

	_s = (char*)_get_data(&lpm_buffer_pnt, 3);
	_Version = GetUniStr(_s, code);
	_Button->_Version = strtol(_s, NULL, 10);
	free(_s);
	//*���� �о���� �� ���� ��ȯ -> ��ư Ŭ������ �־��ֱ�

	_int = _get_int(&lpm_buffer_pnt);
	_Width = *_int; free(_int);
	_int = _get_int(&lpm_buffer_pnt);
	_Height = *_int; free(_int);
	//*�ʺ� / ���� �о���̱�

	_Button->_read_from_buffer(&lpm_buffer_pnt, code);
	//*�������� ��ư Ŭ�������� �о���̱�

	(*_lpm_buffer_pnt) = lpm_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�


void LPM_PREVMENU::_decompile_code(HANDLE hWrite, unsigned int code)
{
	memset(_txt_buf, 0, sizeof(wchar_t) * TXT_BUFF_LEN);
	//*�� ó���� �ݵ�� 0���� �ʱ�ȭ��

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s_%s%s%s"), _Signature, _Version, _enter_raw_, separation_line);
	//*�ñ״�ó �� ���� ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Resolution]::[%03d*%03d]%s%s"), _Width, _Height, _enter_raw_, separation_line);
	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*�ʺ� �� ���� ���
	//*1�� ���

	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	_Button->_decompile_code(hWrite, code);
	//*��ư���� �߰� ���

	WriteFile(hWrite, separation_line, (sizeof(wchar_t) * wcslen(separation_line)), NULL, NULL);
	//*���༱ �߰�
}
//*�������� �Լ�


void LPM_PREVMENU::_write_as_lpm(HANDLE hNewLpm, unsigned int code)
{
	char* _s;

	_s = GetAnsiStr(_Signature, code);
	_write_data(hNewLpm, (unsigned char*)_s, strlen(_s));
	free(_s);
	//*�ñ״�ó ���
	
	_s = GetAnsiStr(_Version, code);
	_write_data(hNewLpm, (unsigned char*)_s, strlen(_s));
	free(_s);
	//*���� ���

	_write_int(hNewLpm, _Width);
	_write_int(hNewLpm, _Height);
	//*�ʺ� / ���� ���

	_Button->_write_as_lpm(hNewLpm, code);
	//*Button Ŭ�������� ���� ���
}
//*lpm ���Ϸ� ����ϴ� �Լ�


void LPM_PREVMENU::_change_code_J2K()
{
	_Button->_change_code_J2K();
	//*��ư���� �� �ٲٰ� �Ѵ�
}
//*�ؽ�Ʈ �ڵ� ���� �Լ�
//---------------------------- PrevMenu Ŭ���� ���� �Լ� ----------------------------//




//---------------------------- Button Ŭ���� ���� �Լ� ----------------------------//
void LPM_BUTTON::_read_from_buffer(unsigned char** _lpm_buffer_pnt, unsigned int code)
{
	unsigned char* lpm_buffer_pnt = (*_lpm_buffer_pnt);
	unsigned int* _int;

	_int = _get_int(&lpm_buffer_pnt);
	_item_count = *_int; free(_int);
	_item_list = (LPM_ITEM**)malloc(sizeof(LPM_ITEM*)*_item_count);
	memset(_item_list, 0, (sizeof(LPM_ITEM*) * _item_count));
	//*������ �� �о���̰� �Ҵ��ϱ�

	for (unsigned int i = 0; i < _item_count;i++) {
		_item_list[i] = new LPM_ITEM(_Version);
		_item_list[i]->_read_from_buffer(&lpm_buffer_pnt, code);
	}
	//*�����۵� �о���̱�

	(*_lpm_buffer_pnt) = lpm_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�


void LPM_BUTTON::_decompile_code(HANDLE hWrite, unsigned int code)
{
	for (unsigned int i = 0; i < _item_count; i++) {

		memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[Item_%02d]%s"), i, _enter_raw_);
		//*��� ���� ���

		_item_list[i]->_decompile_code(hWrite, code);
		WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
		//*���������� ��� �� ���Ϸ� ����ϱ�

	}
}
//*�������� �Լ�

void LPM_BUTTON::_write_as_lpm(HANDLE hNewLpm, unsigned int code)
{
	_write_int(hNewLpm, _item_count);
	//*�� ������ �� ���

	for (unsigned int i = 0; i < _item_count;i++) {
		_item_list[i]->_write_as_lpm(hNewLpm, code);
	}
	//*����Ʈ�� ���ư��� ������ ���
}
//*lpm ���Ϸ� ����ϴ� �Լ�


void LPM_BUTTON::_change_code_J2K()
{
	for (unsigned int i = 0; i < _item_count; i++) {
		_item_list[i]->_change_code_J2K();
	}
	//*������ ��ҿ��� �ٲٰ� �Ѵ�
}
//*�ؽ�Ʈ �ڵ� ���� �Լ�
//---------------------------- Button Ŭ���� ���� �Լ� ----------------------------//




//---------------------------- item Ŭ���� ���� �Լ� ----------------------------//
void LPM_ITEM::_read_from_buffer(unsigned char** _lpm_buffer_pnt, unsigned int code)
{
	unsigned char* lpm_buffer_pnt = (*_lpm_buffer_pnt);
	char* _s;
	unsigned char* _b;
	unsigned int* _int;

	_int = _get_int(&lpm_buffer_pnt);
	_Left = *_int; free(_int);
	_int = _get_int(&lpm_buffer_pnt);
	_Top = *_int; free(_int);
	//*x��ǥ / y��ǥ �о���̱�

	_s = _get_str(&lpm_buffer_pnt);
	_Src = GetUniStr(_s, code); free(_s);
	//*src �о���̱�

	_b = _get_byte(&lpm_buffer_pnt);
	_unk_2 = *_b; free(_b);
	//*unk_2 �о���̱�

	_s = _get_str(&lpm_buffer_pnt);
	_Name = GetUniStr(_s, code); free(_s);
	//*name �о���̱�

	_s = _get_str(&lpm_buffer_pnt);
	_Src_Selected = GetUniStr(_s, code); free(_s);
	//*src_selected �о���̱�

	_s = _get_str(&lpm_buffer_pnt);
	_unk_3 = GetUniStr(_s, code); free(_s);
	_s = _get_str(&lpm_buffer_pnt);
	_unk_4 = GetUniStr(_s, code); free(_s);
	//*unk_3 ~ 4 �о���̱�

	if (_Version > 100) {
		_s = _get_str(&lpm_buffer_pnt);
		_unk_5 = GetUniStr(_s, code); free(_s);
	}
	//*������ ���� unk_5 �о���̱�

	if (_Version > 102) {
		for (unsigned int i = 0; i < 2;i++) {
			_s = _get_str(&lpm_buffer_pnt);
			_unk_6[i] = GetUniStr(_s, code); free(_s);
		}
	}
	//*������ ���� unk_6 �о���̱�

	_s = _get_str(&lpm_buffer_pnt);
	_unk_7 = GetUniStr(_s, code); free(_s);
	_s = _get_str(&lpm_buffer_pnt);
	_unk_8 = GetUniStr(_s, code); free(_s);
	_s = _get_str(&lpm_buffer_pnt);
	_unk_9 = GetUniStr(_s, code); free(_s);
	//*unk 7, 8, 9 �о���̱�

	if (_Version > 101) {
		for (unsigned int i = 0; i < 2; i++) {
			_s = _get_str(&lpm_buffer_pnt);
			_unk_10[i] = GetUniStr(_s, code); free(_s);
		}
	}
	//*������ ���� unk_10 �о���̱�

	_int = _get_int(&lpm_buffer_pnt);
	_unk_11 = *_int; free(_int);
	_int = _get_int(&lpm_buffer_pnt);
	_unk_12 = *_int; free(_int);
	//*unk_11, 12 �о���̱�

	_s = _get_str(&lpm_buffer_pnt);
	_unk_13 = GetUniStr(_s, code); free(_s);
	//*unk_13 �о���̱�

	if (_Version > 103) {
		for (unsigned int i = 0; i < 5; i++) {
			_s = _get_str(&lpm_buffer_pnt);
			_unk_14._str[i] = GetUniStr(_s, code); free(_s);
		}
		_int = _get_int(&lpm_buffer_pnt);
		_unk_14._int = *_int; free(_int);
	}
	//*������ ���� unk_14 �о���̱�

	if (_Version > 104) {
		_s = _get_str(&lpm_buffer_pnt);
		_unk_15 = GetUniStr(_s, code); free(_s);
	}
	//*������ ���� unk_15 �о���̱�

	if (_Version > 105) {
		_s = _get_str(&lpm_buffer_pnt);
		_unk_16 = GetUniStr(_s, code); free(_s);
	}
	//*������ ���� unk_16 �о���̱�

	(*_lpm_buffer_pnt) = lpm_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�


void LPM_ITEM::_decompile_code(HANDLE hWrite, unsigned int code)
{
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[(__LEFT__, __TOP__)]::(%d, %d)%s"), _indent_, _Left, _Top, _enter_raw_);
	//*�ʺ� / ����

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__SOURCE_0x%02X__]::%s%s%s%s"), 
		_indent_, _unk_2, text_prefix, _Src, text_prefix, _enter_raw_);
	//*src, unk_2

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__NAME__]::%s%s%s%s"),
		_indent_, text_prefix, _Name, text_prefix, _enter_raw_);
	//*name

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__SRC_SELECTED__]::%s%s%s%s"),
		_indent_, text_prefix, _Src_Selected, text_prefix, _enter_raw_);
	//*src_selected

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_TYPE_1__]::[%s][%s][%s][[%s][%s]]%s"),
		_indent_, _unk_3, _unk_4, _unk_5, _unk_6[0], _unk_6[1], _enter_raw_);
	//*unk_3, 4, 5, 6

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_TYPE_2__]::[%s][%s][%s][[%s][%s]]%s"),
		_indent_, _unk_7, _unk_8, _unk_9, _unk_10[0], _unk_10[1], _enter_raw_);
	//*unk_7, 8, 9, 10

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_VALUE__]::[0x%08X][0x%08X]%s"),
		_indent_, _unk_11, _unk_12, _enter_raw_);
	//*unk_11, 12

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_STR__]::%s%s%s%s"),
		_indent_, text_prefix, _unk_13, text_prefix, _enter_raw_);
	//*unk_13

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_TYPE_3_0x%08X__]::[[%s][%s][%s][%s][%s]]%s"),
		_indent_, _unk_14._int, _unk_14._str[0], _unk_14._str[1], _unk_14._str[2], _unk_14._str[3], _unk_14._str[4], _enter_raw_);
	//*unk_14

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_STR__]::%s%s%s%s"),
		_indent_, text_prefix, _unk_15, text_prefix, _enter_raw_);
	//*unk_15

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[__UNK_STR__]::%s%s%s%s"),
		_indent_, text_prefix, _unk_16, text_prefix, _enter_raw_);
	//*unk_16

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _enter_raw_);
	//*���� �߰�
}
//*�������� �Լ�

void LPM_ITEM::_write_as_lpm(HANDLE hNewLpm, unsigned int code)
{
	char* _s;

	_write_int(hNewLpm, _Left);
	_write_int(hNewLpm, _Top);
	//*left, top ���

	_s = GetAnsiStr(_Src, code);
	_write_str(hNewLpm, _s); free(_s);
	//*src ���

	_write_byte(hNewLpm, _unk_2);
	//*unk_2 ���

	_s = GetAnsiStr(_Name, code);
	_write_str(hNewLpm, _s); free(_s);
	_s = GetAnsiStr(_Src_Selected, code);
	_write_str(hNewLpm, _s); free(_s);
	//*name, src_selected ���

	_s = GetAnsiStr(_unk_3, code);
	_write_str(hNewLpm, _s); free(_s);
	_s = GetAnsiStr(_unk_4, code);
	_write_str(hNewLpm, _s); free(_s);
	//*unk_3, 4 ���

	if (_Version > 100) {
		_s = GetAnsiStr(_unk_5, code);
		_write_str(hNewLpm, _s); free(_s);
	}
	//*������ ���� unk_5 ���

	if (_Version > 102) {
		for (unsigned int i = 0; i < 2;i++) {
			_s = GetAnsiStr(_unk_6[i], code);
			_write_str(hNewLpm, _s); free(_s);
		}
	}
	//*������ ���� unk_6 ���

	_s = GetAnsiStr(_unk_7, code);
	_write_str(hNewLpm, _s); free(_s);
	_s = GetAnsiStr(_unk_8, code);
	_write_str(hNewLpm, _s); free(_s);
	_s = GetAnsiStr(_unk_9, code);
	_write_str(hNewLpm, _s); free(_s);
	//*unk_7, 8, 9 ���

	if (_Version > 101) {
		for (unsigned int i = 0; i < 2; i++) {
			_s = GetAnsiStr(_unk_10[i], code);
			_write_str(hNewLpm, _s); free(_s);
		}
	}
	//*������ ���� unk_10 ���

	_write_int(hNewLpm, _unk_11);
	_write_int(hNewLpm, _unk_12);
	//*unk_11, 12 ���

	_s = GetAnsiStr(_unk_13, code);
	_write_str(hNewLpm, _s); free(_s);
	//*unk_13 ���

	if (_Version > 103) {
		for (unsigned int i = 0; i < 5; i++) {
			_s = GetAnsiStr(_unk_14._str[i], code);
			_write_str(hNewLpm, _s); free(_s);
		}
		_write_int(hNewLpm, _unk_14._int);
	}
	//*������ ���� unk_14 ���

	_s = GetAnsiStr(_unk_15, code);
	_write_str(hNewLpm, _s); free(_s);
	_s = GetAnsiStr(_unk_16, code);
	_write_str(hNewLpm, _s); free(_s);
	//*unk_15, 16 ���
}
//*lpm ���Ϸ� ����ϴ� �Լ�


void LPM_ITEM::_change_code_J2K()
{
	JPHan_2_KRHan(_Src);
	JPHan_2_KRHan(_Name);
	JPHan_2_KRHan(_Src_Selected);
	JPHan_2_KRHan(_unk_3);
	JPHan_2_KRHan(_unk_4);
	JPHan_2_KRHan(_unk_5);
	for (unsigned int i = 0; i < 2;i++) { JPHan_2_KRHan(_unk_6[i]); }
	JPHan_2_KRHan(_unk_7);
	JPHan_2_KRHan(_unk_8);
	JPHan_2_KRHan(_unk_9);
	for (unsigned int i = 0; i < 2; i++) { JPHan_2_KRHan(_unk_10[i]); }
	JPHan_2_KRHan(_unk_13);
	for (unsigned int i = 0; i < 5; i++) { JPHan_2_KRHan(_unk_14._str[i]); }
	JPHan_2_KRHan(_unk_15);
	JPHan_2_KRHan(_unk_16);
	//* wchar_t* ������ ��� �����͸� �ٲ�ģ��
}
//*�ؽ�Ʈ �ڵ� ���� �Լ�
//---------------------------- item Ŭ���� ���� �Լ� ----------------------------//