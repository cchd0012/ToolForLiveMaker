#include "LM_Script.h"
#include "LM_Functions.h"


#pragma warning (disable:6031)
#pragma warning (disable:4996)

//*** lsb ��ũ��Ʈ �м� �� ���� �Լ����� �����ϴ� ����

LSB_INST_BASE* getInstClass(LSB_INST_TYPES _type, unsigned int _script_ver, LSB_HEADER* _header);
//*** ��캰�� Ÿ�Կ� ���� �Ҵ� �� ��ȯ�ϴ� �Լ�




//---------------------------- ��ũ��Ʈ Ŭ���� ���� �Լ� ----------------------------//
bool LSB_SCRIPT::Script_Analysis(wchar_t* LsbFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Analysis: Lsb File: %s\n"), LsbFile);

	HANDLE hLsb = CreateFileW(LsbFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hLsb == INVALID_HANDLE_VALUE) {
		wprintf(TEXT("%s: There's not LSB File\n"), LsbFile);
		_setmode(_fileno(stdout), _O_TEXT);
		return false;
	}
	unsigned int lsb_size = GetFileSize(hLsb, NULL);
	unsigned char* lsb_buffer = (unsigned char*)malloc(lsb_size);
	ReadFile(hLsb, lsb_buffer, lsb_size, NULL, NULL);
	CloseHandle(hLsb);
	//*lsb ���� �о���̱� (���� ��� ����ڵ嵵 ����� �ʿ� ����)

	unsigned char* lsb_buffer_pnt = lsb_buffer;
	//*�ʿ��� ������

	if (!LSB_Header_Analysis(LsbFile, lsb_buffer, &lsb_buffer_pnt)) {
		_setmode(_fileno(stdout), _O_U16TEXT);
		wprintf(TEXT("%s: Error occured while analysing header\n"), LsbFile);
		free(lsb_buffer);
		_setmode(_fileno(stdout), _O_TEXT);
		return false;
	}
	//*��� �м�

	if (!LSB_Body_Analysis(LsbFile, lsb_buffer, &lsb_buffer_pnt, code)) {
		_setmode(_fileno(stdout), _O_U16TEXT);
		wprintf(TEXT("%s: Error occured while analysing body\n"), LsbFile);
		free(lsb_buffer);
		_setmode(_fileno(stdout), _O_TEXT);
		return false;
	}
	//*���� �м�

	wprintf(TEXT("Script Analysis Complete!\n"));
	free(lsb_buffer);
	_setmode(_fileno(stdout), _O_TEXT);
	return true;
	//*����
}
//*** lsb ��ũ��Ʈ ���� �м� �Լ�


bool LSB_SCRIPT::LSB_Header_Analysis(wchar_t* LsbFile, unsigned char* _org_pnt, unsigned char** _lsb_buffer_pnt)
{
	_setmode(_fileno(stdout), _O_TEXT);
	if (_lsb_buffer_pnt == NULL) { return false; }
	//*�ʼ�����

	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	lm_version = *(unsigned int*)(lsb_buffer_pnt);
	lsb_buffer_pnt += sizeof(int);
	if (lm_version != LM_VERSION_1) { printf("Lm script version : 1\n"); }
	else if (lm_version != LM_VERSION_2) { printf("Lm script version : 2\n"); }
	else if (lm_version != LM_VERSION_3) { printf("Lm script version : 3\n"); }
	else {
		_setmode(_fileno(stdout), _O_U16TEXT);
		wprintf(TEXT("%s: Not supported LSB script file\n"), LsbFile);
		_setmode(_fileno(stdout), _O_TEXT);
		return false;
	}
	//*���� ���� �� ���� ����Ʈ �м�

	flag = (*lsb_buffer_pnt); lsb_buffer_pnt++;
	//*ù 1����Ʈ

	_header = new LSB_HEADER(lm_version);
	_header->Header_Read(_org_pnt, &lsb_buffer_pnt);
	//*��� ������ �о���̱�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
	return true;
	//*��ġ ���� �ݿ�
}
//*** ��� �м� �Լ�


bool LSB_SCRIPT::LSB_Body_Analysis(wchar_t* LsbFile, unsigned char* _org_pnt, unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	_setmode(_fileno(stdout), _O_TEXT);
	if (_lsb_buffer_pnt == NULL) { return false; }
	//*�ʼ�����

	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);

	_body = new LSB_BODY(lm_version, _header);
	_body->Body_Read(_org_pnt, &lsb_buffer_pnt, code);
	//*��� ���� �� ��ü ������ �о���̱�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
	return true;
	//*��ġ ���� �ݿ�
}
//*** ���� �м� �Լ�


void LSB_SCRIPT::Decompile_To_Code(wchar_t* TxtFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Decompiling to Code: Lsb File: To %s\n"), TxtFile);

	HANDLE hWrite = CreateFileW(TxtFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//*�ڵ� ����

	UINT16 BOM = 0xFEFF;
	WriteFile(hWrite, &BOM, 2, NULL, NULL);
	//*�����ڵ� ���� ���� �غ� (BOM)
	
	memset(_txt_buf, 0, sizeof(wchar_t) * TXT_BUFF_LEN);
	//*�� ó���� �ݵ�� 0���� �ʱ�ȭ��

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("Livemaker Script Version_0x%02X%s%s"), lm_version, _enter_raw_, separation_line);
	//*���� ���

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[HEADER]%s"), _enter_raw_);
	if (_header != NULL) { _header->_decompile_code(hWrite); }
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), separation_line);
	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*��� Ŭ������ ���� ���

	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[BODY]%s"), _enter_raw_);
	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);

	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	if (_body != NULL) { _body->_decompile_code (hWrite, code); }

	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), separation_line);
	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*���� Ŭ������ ���� ���

	CloseHandle(hWrite);
	//*�ڵ� ����

	wprintf(TEXT("Decompiling Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
}
//*��ũ��Ʈ Ŭ���� : �������� �Լ�


void LSB_SCRIPT::Make_To_Script(wchar_t* newLsbFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Writing: Lsb File: %s\n"), newLsbFile);

	HANDLE hNewLsb = CreateFileW(newLsbFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//*�ڵ� ����

	WriteFile(hNewLsb, &lm_version, sizeof(int), NULL, NULL);
	WriteFile(hNewLsb, &flag, sizeof(char), NULL, NULL);
	//* ���� / �÷��� ���

	if (_header != NULL) { _header->_write_as_lsb(hNewLsb); }
	//* ��� ���

	if (_body != NULL) { _body->_write_as_lsb(hNewLsb, code); }
	//* ���� ���

	CloseHandle(hNewLsb);
	//*�ڵ� ����

	wprintf(TEXT("Writing Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*����
}
//*��ũ��Ʈ Ŭ���� : lsb ���Ϸ� ����ϴ� �Լ� (���� ����ڵ� �� ���ڿ� ��ȯ�� �ٸ� �Լ�����)


void LSB_SCRIPT::Extract_Text_Data(wchar_t* DstTxtFile)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Extracting: Text File: %s\n"), DstTxtFile);

	HANDLE hTxt = CreateFileW(DstTxtFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//*�ڵ� ����

	UINT16 BOM = 0xFEFF;
	WriteFile(hTxt, &BOM, 2, NULL, NULL);
	//*�����ڵ� ���� ���� �غ� (BOM)

	_body->_extract_text(hTxt);
	//*�ؽ�Ʈ ���� �Լ� ȣ��

	CloseHandle(hTxt);
	//*�ڵ� ����

	wprintf(TEXT("Extracting Text Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*����
}
//*�ؽ�Ʈ ���� �Լ�

void LSB_SCRIPT::Replace_Text_Data(wchar_t* SrcTxtFile, unsigned int code)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Replacing: Text File: %s\n"), SrcTxtFile);

	HANDLE hTxt = CreateFileW(SrcTxtFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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

	unsigned int line_count = Get_Txt_Count (txt_buffer, line_prefix, total_txt_count);
	//*�ؽ�Ʈ�� �ִ� ���� �� Ȯ��

	LSB_TEXTS_PER_INST* _txt_list = (LSB_TEXTS_PER_INST*)malloc(sizeof(LSB_TEXTS_PER_INST) * line_count);
	memset(_txt_list, 0, (sizeof(LSB_TEXTS_PER_INST) * line_count));
	//*���δ� ���� �ؽ�Ʈ ����ü �Ҵ�

	wchar_t* _line_pnt = txt_buffer, * _line_pnt_bak = txt_buffer;
	wchar_t line_num[9]; line_num[8] = 0x00;
	for (unsigned int i = 0; i < line_count;i++) {

		_line_pnt = wcsstr(_line_pnt_bak, line_prefix);
		_line_pnt += (wcslen(line_prefix) + 1);
		memcpy(line_num, _line_pnt, (sizeof(wchar_t) * 8));
		_txt_list[i]._line = wcstol(line_num, NULL, 10);
		//*_line_pnt : ���� ���ڿ� ���� ����
		//*���� ���ڿ� + ':' ��ŭ ���̸� ���� �� ���̸� ����

		if (i != (line_count - 1)) {
			_line_pnt_bak = wcsstr(_line_pnt, line_prefix);
		}
		else {
			_line_pnt_bak = (txt_buffer + total_txt_count);
		}
		//*_line_pnt_bak : �ش� ������ ������ ����
		//*���� ������ ī��Ʈ�� ��ġ�� �� ã�� ������ �������� �������� �����Ѵ�

		unsigned int _tp_buf_size = _line_pnt_bak - _line_pnt;
		wchar_t* _tp_buf = (wchar_t*)malloc(sizeof(wchar_t) * (_tp_buf_size + 1));
		_tp_buf[_tp_buf_size] = 0;
		memcpy(_tp_buf, _line_pnt, (sizeof(wchar_t) * _tp_buf_size));
		//*�ش� ������ ���� ī�Ǹ� ���� ������

		_txt_list[i]._txt_count = Get_Txt_Count(_tp_buf, text_data_prefix, _tp_buf_size);
		//*�ش� ��ɾ� �� �ؽ�Ʈ �� �ľ�

		if (_txt_list[i]._txt_count != 0) {

			_txt_list[i]._txt_list_per_inst = (wchar_t**)malloc(sizeof(wchar_t*) * _txt_list[i]._txt_count);
			memset(_txt_list[i]._txt_list_per_inst, 0, (sizeof(wchar_t*) * _txt_list[i]._txt_count));
			//*���� �Ҵ�

			wchar_t* _txt_pnt = _tp_buf, * _txt_pnt_bak = _tp_buf;
			for (unsigned int j = 0; j < _txt_list[i]._txt_count;j++) {

				_txt_pnt = wcsstr(_txt_pnt_bak, text_data_prefix);
				_txt_pnt += wcslen(text_data_prefix);
				_txt_pnt_bak = wcsstr(_txt_pnt, text_prefix);
				_txt_pnt_bak += wcslen(text_prefix);
				//*_txt_pnt_bak : �ؽ�Ʈ ���� ����

				_txt_pnt = wcsstr(_txt_pnt_bak, text_prefix);
				//*_txt_pnt : �ؽ�Ʈ ������ ����

				wchar_t* _tmp = (wchar_t*)malloc(sizeof(wchar_t) * (_txt_pnt - _txt_pnt_bak + 1));
				memcpy(_tmp, _txt_pnt_bak, (sizeof(wchar_t) * (_txt_pnt - _txt_pnt_bak)));
				_tmp[(_txt_pnt - _txt_pnt_bak)] = 0;
				_txt_list[i]._txt_list_per_inst[j] = _tmp;
				//*������ �Ҵ� / ī�� �� �ٿ��ֱ� / ����Ʈ�� ����

				_txt_pnt_bak = _txt_pnt + wcslen(text_prefix);
				//*_txt_pnt_bak�� �� ���� ������ �����Ѵ�

			}
			//*�ؽ�Ʈ ����ŭ ���� ����

		}
		//*�ؽ�Ʈ ���� 0�� �ƴ� ���� ����

		else if (wcsstr (_tp_buf, _inst_type_list[TYPE_INST_TEXT_INST]) != NULL) {
			_txt_list[i]._txt_count = 1;
			_txt_list[i]._txt_list_per_inst = (wchar_t**)malloc(sizeof(wchar_t*));
			_txt_list[i]._txt_list_per_inst[0] = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_tp_buf) + 1));
			memset(_txt_list[i]._txt_list_per_inst[0], 0, (sizeof(wchar_t) * (wcslen(_tp_buf) + 1)));
			memcpy(_txt_list[i]._txt_list_per_inst[0], _tp_buf, (sizeof(wchar_t) * wcslen(_tp_buf)));
		}
		//*�ؽ�Ʈ ���� 0�� ���� _TEXT_INST���� Ȯ���غ��� ���� �׷��ٸ� �״�� �����ؼ� �߰��� �ش�
		
		free(_tp_buf);
		//*�� ���������� �ӽ� ���� ����

	}
	//*�о���� ���Ϸ� �ؽ�Ʈ ����

	_body->_replace_text(_txt_list, line_count, code);
	//*�ؽ�Ʈ ��ü �Լ� ȣ��

	for (unsigned int i = 0; i < line_count; i++) { 
		for (unsigned int j = 0; j < _txt_list[i]._txt_count; j++) { free(_txt_list[i]._txt_list_per_inst[j]); }
		if (_txt_list[i]._txt_list_per_inst != NULL) { free(_txt_list[i]._txt_list_per_inst); }
	}
	free (txt_buffer);
	//*���� ����

	wprintf(TEXT("Replacing Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
	//*����
}
//*�ؽ�Ʈ ��ü �Լ�


void LSB_SCRIPT::Convert_Codepage_J2K()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(TEXT("Changing Text Language Code(Jap -> Kor)...\n"));

	_body->_change_code_J2K();

	wprintf(TEXT("Complete!\n"));
	_setmode(_fileno(stdout), _O_TEXT);
}
//*�ؽ�Ʈ ����ڵ带 �Ϻ���� �ѱ۷� �ٲٴ� �Լ�
//---------------------------- ��ũ��Ʈ Ŭ���� ���� �Լ� ----------------------------//




//---------------------------- ��� Ŭ���� ���� �Լ� ----------------------------//
bool LSB_HEADER::Header_Read(unsigned char* _org_pnt, unsigned char** _lsb_buffer_pnt)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);

	opcode_count = *(unsigned int*)(lsb_buffer_pnt);
	lsb_buffer_pnt += sizeof(int);
	opcode_property_count = *(unsigned int*)(lsb_buffer_pnt);
	lsb_buffer_pnt += sizeof(int);
	//*��� ���� : ������Ʈ �� / ������Ʈ ũ�� �м�

	opcode_property_table = (unsigned char**)malloc(sizeof(unsigned char*) * opcode_count);
	for (unsigned int i = 0; i < opcode_count; i++) {
		opcode_property_table[i] = (unsigned char*)malloc(opcode_property_count);
		memcpy(opcode_property_table[i], lsb_buffer_pnt, opcode_property_count);
		lsb_buffer_pnt += opcode_property_count;
	}
	//*�� ũ�⿡ ���߾� �Ҵ� �� ����

	opcode_property_boolean_table = (bool**)malloc(sizeof(bool*) * opcode_count);
	for (unsigned int i = 0; i < opcode_count; i++) {
		opcode_property_boolean_table[i] = (bool*)malloc(opcode_property_count * 8);
		for (unsigned int j = 0; j < opcode_property_count; j++) {
			for (unsigned int k = 0; k < 8; k++) {
				opcode_property_boolean_table[i][(j * 8) + k] = (opcode_property_table[i][j] & (1 << k)) != 0;
			}
		}
	}
	//*�� ũ�⿡ ���߾� �Ҵ� (bool�̹Ƿ� 8�� �ø���)
	//*�Ƹ� �� ��ũ��Ʈ ������ ���� ver2�� 0xA5��, ver3�� 0xAC���� ���ѵ� �� �ѵ�
	//*ũ�� �Ű� �� �ʿ�� ���� �� �ϴ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
	return true;
	//*��ġ ���� �ݿ�
}
//*��� Ŭ���� : ���ۿ��� ������ �޾ƿ���


void LSB_HEADER::_decompile_code(HANDLE hWrite)
{
	if (opcode_property_table != NULL) {
		for (unsigned int i = 0; i < opcode_count; i++) {

			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_);
			//*�鿩���� ���

			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s%02d]::"), property_array_prefix, i);
			//*�Ӽ� ��� ���

			for (unsigned int j = 0; j < opcode_property_count; j++) {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%02X]"), opcode_property_table[i][j]);
			}
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _enter_raw_);
			//*��� ���� ���
		}
	}
	//*opcode �迭 ���
}
//*��� Ŭ���� : �������� �Լ�


void LSB_HEADER::_write_as_lsb(HANDLE hNewLsb)
{
	WriteFile(hNewLsb, &opcode_count, sizeof(int), NULL, NULL);
	WriteFile(hNewLsb, &opcode_property_count, sizeof(int), NULL, NULL);
	//*��ɾ� �� / �� ��ɾ�� �Ӽ� �� ���

	for (unsigned int i = 0; i < opcode_count; i++) {
		WriteFile(hNewLsb, opcode_property_table[i], opcode_property_count, NULL, NULL);
	}
	//*�Ӽ� ���� �迭 ���

	wprintf(TEXT("Header Writing Complete...\n"));
}
//*��� Ŭ���� : lsb ���Ϸ� ����ϴ� �Լ�
//---------------------------- ��� Ŭ���� ���� �Լ� ----------------------------//




//---------------------------- ��ü Ŭ���� ���� �Լ� ----------------------------//
bool LSB_BODY::Body_Read(unsigned char* _org_pnt, unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);

	inst_list_count = *(unsigned int*)(lsb_buffer_pnt);
	lsb_buffer_pnt += sizeof(int);
	inst_list_arr = (LSB_INST_BASE**)malloc(sizeof(LSB_INST_BASE*) * inst_list_count);
	memset(inst_list_arr, 0, sizeof(LSB_INST_BASE*) * inst_list_count);
	//*�� ��ɾ� ��� �� �ľ� / �Ҵ�

	for (unsigned int i = 0; i < inst_list_count; i++) {
		unsigned char _opcode = *(lsb_buffer_pnt++);
		inst_list_arr[i] = getInstClass((LSB_INST_TYPES)_opcode, _script_ver, _header);
		if (inst_list_arr[i] == NULL) {
			printf("Illegal command : 0x%02X at [0x%08X]\n", _opcode, ((lsb_buffer_pnt - 1) - _org_pnt));
			return false;
		}
		//*opcode �б�, ver2������ 0x3C������ �����ϴ� �� �ѵ� �װű��� �Ű澲�� ���� �ʴ�
		//*��ǻ� read_function_prologue�� ��� ��ɾ ����Ǵ� �� �ϴ�
		inst_list_arr[i]->_read_inst_data(&lsb_buffer_pnt, code);
		//*�� ��ɾ �ɸ°� ������ �о���̱�
	}
	//*��ũ��Ʈ�� ����� ��ɾ��� ���ư��� �о���̱�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
	return true;
	//*��ġ ���� �ݿ�
}
//*��ü Ŭ���� : ���ۿ��� ������ �޾ƿ���


void LSB_BODY::_decompile_code(HANDLE hWrite, unsigned int code)
{
	if (inst_list_arr != NULL) {
		for (unsigned int i = 0; i < inst_list_count; i++) {
			inst_list_arr[i]->_decompile_code(hWrite, i, code, 1);
		}
	}
	//*�鿩���� �߰�
}
//*��ü Ŭ���� : �������� �Լ�


void LSB_BODY::_write_as_lsb(HANDLE hNewLsb, unsigned int code)
{
	WriteFile(hNewLsb, &inst_list_count, sizeof(int), NULL, NULL);
	//*�� ��ɾ� �� ���

	for (unsigned int i = 0; i < inst_list_count; i++) {
		inst_list_arr[i]->_write_as_lsb(hNewLsb, code);
	}
	//*��ɾŭ ���ư��� ���

	wprintf(TEXT("Body Writing Complete...\n"));
}
//*���� Ŭ���� : lsb ���Ϸ� ����ϴ� �Լ�


void LSB_BODY::_extract_text(HANDLE hTxt)
{
	for (unsigned int i = 0; i < inst_list_count; i++) {
		inst_list_arr[i]->_extract_text(hTxt);
	}
	//*��ɾŭ ���ư��� ����

	wprintf(TEXT("Text Extracting Complete...\n"));
}
//*���� Ŭ���� : �ؽ�Ʈ ���� �Լ�


void LSB_BODY::_replace_text(LSB_TEXTS_PER_INST* txt_list, unsigned int txt_list_count, unsigned int code)
{
	for (unsigned int i = 0; i < txt_list_count; i++) {

		LSB_INST_BASE* _pnt = NULL;
		for (unsigned int j = 0; j < inst_list_count; j++) {
			if (inst_list_arr[j]->_line == txt_list[i]._line) { 
				_pnt = inst_list_arr[j]; break; 
			}
		}
		//*�������� ��ϵ� ��ɾ� ã��

		if (_pnt != NULL) { 
			_pnt->_replace_text (&txt_list[i], code); 
		}
		//*null�̸� �׳� ����, ã�Ƴ��� ������

	}
	//*������ ��ϵǾ� �ִ� ��ɾŭ ���ư��� ��ġ

	wprintf(TEXT("Text Replacing Complete...\n"));
}
//*���� Ŭ���� : �ؽ�Ʈ ��ü �Լ�


void LSB_BODY::_change_code_J2K()
{
	for (unsigned int i = 0; i < inst_list_count; i++) {
		inst_list_arr[i]->_change_code_J2K();
	}
	//*���� ���鼭 �ٲ�ġ��
}
//*���� Ŭ���� : �ؽ�Ʈ �ڵ� ���� �Լ�
//---------------------------- ��ü Ŭ���� ���� �Լ� ----------------------------//




//---------------------------- �⺻ Ŭ���� �Լ� ----------------------------//
void LSB_INST_BASE::_decompile_code(HANDLE hWrite, unsigned int offset, unsigned int code, unsigned int _indent)
{
	//----------- �ؽ�Ʈ ���ۿ� ������ -----------//
	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	for (unsigned int i = 0; i < _indent; i++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*�鿩���� ��� (�ؽ�Ʈ ���Ϸ�)
	//----------- �ؽ�Ʈ ���ۿ� ������ -----------//

	//----------- �ؽ�Ʈ ���ۿ� ������ -----------//
	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s:%08d][%s:%08d][%08X][%02X][%02X][%s:%s]%s"),
		line_prefix, _line, offset_prefix, offset, this->_indent, _mute, _not_update, inst_type_prefix, _inst_type_list[_op_type], _enter_raw_);
	//*��ɾ� ���� ���

	unsigned int _param_c = 0, _addi = 0;
	for (unsigned int i = 0; i < _data_chunks_count; i++) {

		if (_param_c != 0) { _addi = 1; _param_c--; }
		else { _addi = 0; }
		//*�Լ� ���� ����ŭ �鿩���� �ݿ�

		for (unsigned int j = 0; j < (_indent + _addi + 1); j++) {
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_);
		}
		//*�鿩���� ���, �Լ� ���� ��½� ��ĭ �� �ٿ� ����ؾ� ��

		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%s"), text_prefix, (wchar_t*)_data_chunks[i]._str);
		//*Ÿ�Ը� �Ϻκи� ���� ���
		//* ([��]Ÿ�Ը�)

		if (wcscmp(_data_chunks[i]._str, TEXT("Target_Label_Offset")) == 0)
		{
			unsigned int _val = *(unsigned int*)_data_chunks[i]._data;
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%08d%s%s"), text_prefix, _val, text_prefix, _enter_raw_);
		}
		else if ((wcscmp(_data_chunks[i]._str, TEXT("Parameter_Count")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Type")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Scope")) == 0))
		{
			unsigned int _val = *(unsigned int*)_data_chunks[i]._data;
			if (wcscmp(_data_chunks[i]._str, TEXT("Parameter_Count")) == 0) { _param_c = _val; }
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s0x%08X%s%s"), text_prefix, _val, text_prefix, _enter_raw_);
		}
		//*�ܼ� ����, �Լ� ���� ����� ���� ���� �����Ѵ�
		//* ([��]0x%08X[��]\r\n)

		else if ((wcscmp(_data_chunks[i]._str, TEXT("Var_Scope_Byte")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("All_Clear_Byte")) == 0))
		{
			unsigned char _val = *(unsigned char*)_data_chunks[i]._data;
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s0x%02X%s%s"), text_prefix, _val, text_prefix, _enter_raw_);
		}
		//*�ܼ� ����Ʈ
		//* ([��]0x%02X[��]\r\n)

		else if ((wcscmp(_data_chunks[i]._str, TEXT("Result")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Script_Page")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Label")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Name")) == 0))
		{
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%s%s%s"), text_prefix, (wchar_t*)_data_chunks[i]._data, text_prefix, _enter_raw_);
		}
		//*�ܼ� ���ڿ� (�ڵ尪�� ���� ����)
		//* ([��]���ڿ�[��]\r\n)

		else if ((wcscmp(_data_chunks[i]._str, TEXT("Event_Block")) == 0))
		{
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%s"), text_prefix, _enter_raw_);
			//*���� ó��

			LSB_EVENT* _evb = (LSB_EVENT*)_data_chunks[i]._data;
			_evb->_decompile_code(hWrite, code, (_indent + _addi + 2));
			//*������ ���
		}
		//*�̺�Ʈ ��

		else {
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%s"), text_prefix, _enter_raw_);
			//*���� ó��

			LSB_PARAMETERS* _pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
			_pnt->_decompile_code(hWrite, code, (_indent + _addi + 2));
		}
		//*�ܴ̿� ���� �з����� ����Ʈ
	}
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _enter_raw_);
	//----------- �ؽ�Ʈ ���ۿ� ������ -----------//

	WriteFile(hWrite, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*���� �� �� �� �ϰ� ���
}
//*** ���� ���������� ����ϴ� �Լ�


void LSB_INST_BASE::_write_as_lsb(HANDLE hNewLsb, unsigned int code)
{
	WriteFile(hNewLsb, &_op_type, sizeof(char), NULL, NULL);
	//*�� �տ� �� ��ɾ��� �Ӽ�(1����Ʈ) ���

	WriteFile(hNewLsb, &_indent, sizeof(int), NULL, NULL);
	WriteFile(hNewLsb, &_mute, sizeof(char), NULL, NULL);
	WriteFile(hNewLsb, &_not_update, sizeof(char), NULL, NULL);
	WriteFile(hNewLsb, &_line, sizeof(int), NULL, NULL);
	//*�鿩����(indent) / mute / _not_update_(static?) / ���� ��ġ ���

	for (unsigned int i = 0; i < _data_chunks_count; i++) {

		if ((wcscmp(_data_chunks[i]._str, TEXT("Target_Label_Offset")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Parameter_Count")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Scope")) == 0))
		{
			_write_int(hNewLsb, *(unsigned int*)_data_chunks[i]._data);
		}
		//*�ܼ� ����

		else if ((wcscmp(_data_chunks[i]._str, TEXT("Var_Type")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Scope_Byte")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("All_Clear_Byte")) == 0))
		{
			_write_byte(hNewLsb, *(unsigned char*)_data_chunks[i]._data);
		}
		//*�ܼ� ����Ʈ

		else if ((wcscmp(_data_chunks[i]._str, TEXT("Result")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Script_Page")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Label")) == 0)
			|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Name")) == 0))
		{
			wchar_t* _w1 = Replace_Text((wchar_t*)_data_chunks[i]._data, hex_1_plained, hex_1_raw);
			free(_data_chunks[i]._data);
			_data_chunks[i]._data = Replace_Text(_w1, _enter_plained_, _enter_raw_);
			free(_w1);
			char* _ansi = GetAnsiStr((wchar_t*)_data_chunks[i]._data, code);
			_write_str(hNewLsb, _ansi);
			free(_ansi);
			//*��ġ �ʿ�, ansi ���ڿ��� �ٲٰ� ���
		}
		//*�ܼ� ���ڿ�

		else if ((wcscmp(_data_chunks[i]._str, TEXT("Event_Block")) == 0))
		{
			LSB_EVENT* _t = (LSB_EVENT*)_data_chunks[i]._data;
			_t->_write_as_lsb(hNewLsb, code);
		}
		//*�̺�Ʈ ��

		else {
			LSB_PARAMETERS *_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
			_t->_write_as_lsb(hNewLsb, code);
		}
		//*�з����� ����Ʈ

		//*�� �Ӽ��� ���� ����� (���� / ���ڿ� / �̺�Ʈ �� / �з����� ����Ʈ)
	}
	//*������ ��� ����ŭ ���ư��� ���, ������ ��� ���� ������� ����
	//*�׳� ������� ����ϸ� ��
}
//*�⺻ Ŭ���� : lsb ���Ϸ� ����ϴ� �Լ�


void LSB_INST_BASE::_extract_text(HANDLE hTxt)
{
	//----------- �ؽ�Ʈ ���ۿ� ������ -----------//
	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s:%08d][%s:%s]%s"),
		line_prefix, _line, inst_type_prefix, _inst_type_list[_op_type], _enter_raw_);
	WriteFile(hTxt, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//*���� �ѹ� ���� ���
	//----------- �ؽ�Ʈ ���ۿ� ������ -----------//

	//----------- �ؽ�Ʈ ���ۿ� ������ -----------//
	memset(_txt_buf, 0, sizeof(wchar_t) * wcslen(_txt_buf));
	
	_extract_text_each_inst(hTxt);
	//*�� ��ɾ�� ���� �ǽ�

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _enter_raw_);
	//*�������� �������� ���� �߰�

	WriteFile(hTxt, _txt_buf, (sizeof(wchar_t) * wcslen(_txt_buf)), NULL, NULL);
	//----------- �ؽ�Ʈ ���ۿ� ������ -----------//
}
//*�⺻ Ŭ���� : �ؽ�Ʈ ���� �Լ�


void LSB_INST_BASE::_replace_text(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	_replace_text_each_inst(txt_list_elem, code);
	//* �� ��ɾ�� ��ü �ǽ�
}
//*�⺻ Ŭ���� : �ؽ�Ʈ ��ü �Լ�


void LSB_INST_BASE::_change_code_J2K()
{
	if (_data_chunks != NULL) {
		for (unsigned int i = 0; i < _data_chunks_count; i++) {
			if ((wcscmp(_data_chunks[i]._str, TEXT("Result")) == 0)
				|| (wcscmp(_data_chunks[i]._str, TEXT("Script_Page")) == 0)
				|| (wcscmp(_data_chunks[i]._str, TEXT("Label")) == 0)
				|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Name")) == 0))
			{
				JPHan_2_KRHan((wchar_t*)_data_chunks[i]._data);
			}
			//*���ڿ��� ���� �ٲ�ġ��

			else if (wcscmp(_data_chunks[i]._str, TEXT("Event_Block")) == 0)
			{
				LSB_EVENT* _t = (LSB_EVENT*)_data_chunks[i]._data;
				_t->_change_code_J2K();
			}
			//*�̺�Ʈ Ŭ������ �ٽ� ȣ��

			else if ((wcscmp(_data_chunks[i]._str, TEXT("Parameter_Count")) == 0)
				|| (wcscmp(_data_chunks[i]._str, TEXT("Target_Label_Offset")) == 0)
				|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Type")) == 0)
				|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Scope")) == 0)
				|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Scope_Byte")) == 0)
				|| (wcscmp(_data_chunks[i]._str, TEXT("All_Clear_Byte")) == 0))
			{;}
			//*�������� �׳� �����Ѵ�

			else {
				LSB_PARAMETERS* _t = (LSB_PARAMETERS*)_data_chunks[i]._data;
				_t->_change_code_J2K();
			}
			//*�з����� Ŭ������ �ٽ� ȣ��
		}
	}
	//*�������鼭 ����
}
//*�⺻ Ŭ���� : �ؽ�Ʈ �ڵ� ���� �Լ�


LSB_INST_BASE* getInstClass(LSB_INST_TYPES _type, unsigned int _script_ver, LSB_HEADER* _header)
{
	switch (_type)
	{
		case TYPE_INST_IF: { return new LSB_INST_IF(_type, _script_ver, _header); }
		case TYPE_INST_ELIF: { return new LSB_INST_ELIF(_type, _script_ver, _header); }
		case TYPE_INST_ELSE: { return new LSB_INST_ELSE(_type, _script_ver, _header); }

		case TYPE_INST_LABEL: { return new LSB_INST_LABEL(_type, _script_ver, _header); }
		case TYPE_INST_JUMP: { return new LSB_INST_JUMP(_type, _script_ver, _header); }

		case TYPE_INST_CALL: { return new LSB_INST_CALL(_type, _script_ver, _header); }

		case TYPE_INST_EXIT: { return new LSB_INST_EXIT(_type, _script_ver, _header); }

		case TYPE_INST_WAIT: { return new LSB_INST_WAIT(_type, _script_ver, _header); }
		case TYPE_INST_TIMER: { return new LSB_INST_TIMER(_type, _script_ver, _header); }

		case TYPE_INST_CALC_FUNC: { return new LSB_INST_CALC_FUNC(_type, _script_ver, _header); }

		case TYPE_INST_BOX_NEW: { return new LSB_INST_BOX_NEW(_type, _script_ver, _header); }
		case TYPE_INST_IMAGE_NEW: { return new LSB_INST_IMAGE_NEW(_type, _script_ver, _header); }
		case TYPE_INST_MESSAGE_NEW: { return new LSB_INST_MESSAGE_NEW(_type, _script_ver, _header); }
		case TYPE_INST_PARTICLE_NEW: { return new LSB_INST_PARTICLE_NEW(_type, _script_ver, _header); }
		case TYPE_INST_FIRE_NEW: { return new LSB_INST_FIRE_NEW(_type, _script_ver, _header); }
		case TYPE_INST_EDIT_NEW: { return new LSB_INST_EDIT_NEW(_type, _script_ver, _header); }
		case TYPE_INST_MEMO_NEW: { return new LSB_INST_MEMO_NEW(_type, _script_ver, _header); }
		case TYPE_INST_MAP_IMAGE_NEW: { return new LSB_INST_MAP_IMAGE_NEW(_type, _script_ver, _header); }
		case TYPE_INST_WAVE_NEW: { return new LSB_INST_WAVE_NEW(_type, _script_ver, _header); }
		case TYPE_INST_TILE_NEW: { return new LSB_INST_TILE_NEW(_type, _script_ver, _header); }
		case TYPE_INST_SLIDER_NEW: { return new LSB_INST_SLIDER_NEW(_type, _script_ver, _header); }
		case TYPE_INST_SCROLL_BAR_NEW: { return new LSB_INST_SCROLL_BAR_NEW(_type, _script_ver, _header); }
		case TYPE_INST_GAUGE_NEW: { return new LSB_INST_GAUGE_NEW(_type, _script_ver, _header); }
		case TYPE_INST_PREV_MENU_NEW: { return new LSB_INST_PREV_MENU_NEW(_type, _script_ver, _header); }

		case TYPE_INST_VAR_NEW: { return new LSB_INST_VAR_NEW(_type, _script_ver, _header); }
		case TYPE_INST_VAR_DELETE: { return new LSB_INST_VAR_DELETE(_type, _script_ver, _header); }

		case TYPE_INST_MOVIE: { return new LSB_INST_MOVIE(_type, _script_ver, _header); }
		case TYPE_INST_FLIP: { return new LSB_INST_FLIP(_type, _script_ver, _header); }
		case TYPE_INST_MOVIE_STOP: { return new LSB_INST_MOVIE_STOP(_type, _script_ver, _header); }

		case TYPE_INST_CINEMA: { return new LSB_INST_CINEMA(_type, _script_ver, _header); }

		case TYPE_INST_GET_PROPERTY: { return new LSB_INST_GET_PROPERTY(_type, _script_ver, _header); }
		case TYPE_INST_SET_PROPERTY: { return new LSB_INST_SET_PROPERTY(_type, _script_ver, _header); }

		case TYPE_INST_OBJECT_DELETE: { return new LSB_INST_OBJECT_DELETE(_type, _script_ver, _header); }

		case TYPE_INST_TEXT_INST: { return new LSB_INST_TEXT_INST(_type, _script_ver, _header); }
		case TYPE_INST_TEXT_CLEAR: { return new LSB_INST_TEXT_CLEAR(_type, _script_ver, _header); }

		case TYPE_INST_CLEAR_HISTORY: { return new LSB_INST_CLEAR_HISTORY(_type, _script_ver, _header); }
		case TYPE_INST_CALL_HISTORY: { return new LSB_INST_CALL_HISTORY(_type, _script_ver, _header); }
		case TYPE_INST_FORMAT_HISTORY: { return new LSB_INST_FORMAT_HISTORY(_type, _script_ver, _header); }

		case TYPE_INST_CAPTION: { return new LSB_INST_CAPTION(_type, _script_ver, _header); }
		case TYPE_INST_CG_CAPTION: { return new LSB_INST_CG_CAPTION(_type, _script_ver, _header); }

		case TYPE_INST_MENU: { return new LSB_INST_MENU(_type, _script_ver, _header); }
		case TYPE_INST_MENU_CLOSE: { return new LSB_INST_MENU_CLOSE(_type, _script_ver, _header); }
		case TYPE_INST_BUTTON: { return new LSB_INST_BUTTON(_type, _script_ver, _header); }

		case TYPE_INST_COMMENT: { return new LSB_INST_COMMENT(_type, _script_ver, _header); }

		case TYPE_INST_WHILE: { return new LSB_INST_WHILE(_type, _script_ver, _header); }
		case TYPE_INST_WHILE_INIT: { return new LSB_INST_WHILE_INIT(_type, _script_ver, _header); }
		case TYPE_INST_WHILE_LOOP: { return new LSB_INST_WHILE_LOOP(_type, _script_ver, _header); }
		case TYPE_INST_BREAK: { return new LSB_INST_BREAK(_type, _script_ver, _header); }
		case TYPE_INST_CONTINUE: { return new LSB_INST_CONTINUE(_type, _script_ver, _header); }

		case TYPE_INST_GAME_SAVE: { return new LSB_INST_GAME_SAVE(_type, _script_ver, _header); }
		case TYPE_INST_GAME_LOAD: { return new LSB_INST_GAME_LOAD(_type, _script_ver, _header); }
		case TYPE_INST_CLEAR_LOAD: { return new LSB_INST_CLEAR_LOAD(_type, _script_ver, _header); }

		case TYPE_INST_PC_RESET: { return new LSB_INST_PC_RESET(_type, _script_ver, _header); }
		case TYPE_INST_RESET: { return new LSB_INST_RESET(_type, _script_ver, _header); }

		case TYPE_INST_SOUND: { return new LSB_INST_SOUND(_type, _script_ver, _header); }
		case TYPE_INST_MEDIA_PLAY: { return new LSB_INST_MEDIA_PLAY(_type, _script_ver, _header); }

		case TYPE_INST_TERMINATE: { return new LSB_INST_TERMINATE(_type, _script_ver, _header); }

		case TYPE_INST_DO_EVENT: { return new LSB_INST_DO_EVENT(_type, _script_ver, _header); }

		case TYPE_INST_PROPERTY_MOTION: { return new LSB_INST_PROPERTY_MOTION(_type, _script_ver, _header); }

		case TYPE_INST_SAVE_CABINET: { return new LSB_INST_SAVE_CABINET(_type, _script_ver, _header); }
		case TYPE_INST_LOAD_CABINET: { return new LSB_INST_LOAD_CABINET(_type, _script_ver, _header); }

		case TYPE_INST_MACRO_IFDEF: { return new LSB_INST_MACRO_IFDEF(_type, _script_ver, _header); }
		case TYPE_INST_MACRO_IFNDEF: { return new LSB_INST_MACRO_IFNDEF(_type, _script_ver, _header); }
		case TYPE_INST_MACRO_ENDIF: { return new LSB_INST_MACRO_ENDIF(_type, _script_ver, _header); }

		default: { return NULL; }
	}
}
//*** ��캰�� Ÿ�Կ� ���� �Ҵ� �� ��ȯ�ϴ� �Լ�
//---------------------------- �⺻ Ŭ���� �Լ� ----------------------------//




//---------------------------- �з����� ����Ʈ Ŭ���� ----------------------------//
void LSB_PARAMETERS::_read_parameter_list(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);

	_count = *(unsigned int*)lsb_buffer_pnt;
	lsb_buffer_pnt += sizeof(int);
	if (_count == 0) {
		(*_lsb_buffer_pnt) = lsb_buffer_pnt;
		return;
	}

	_list = (LSB_PARAMETER*)malloc(sizeof(LSB_PARAMETER) * _count);
	memset(_list, 0, (sizeof(LSB_PARAMETER) * _count));
	//*�з����� �� �ľ� �� �׸�ŭ �Ҵ�
	//*���� �з����� ���� 0�̸� �׳� �����Ѵ�

	char* _s;
	for (unsigned int i = 0; i < _count; i++) {
		_list[i]._type = (LSB_OPER_TYPES) * (lsb_buffer_pnt++);	//*** �з����� Ÿ��
		_s = _get_str(&lsb_buffer_pnt);
		_list[i]._name = GetUniStr (_s, code);			//*** �з����� �̸�
		free(_s);
		_list[i].arg_count = *(unsigned int*)lsb_buffer_pnt;	//*** �з����Ͱ� ���� ������ ��
		lsb_buffer_pnt += sizeof(int);
		_list[i].arg_list = (LM_SCR_ARG*)malloc(sizeof(LM_SCR_ARG) * _list[i].arg_count);
		memset(_list[i].arg_list, 0, (sizeof(LM_SCR_ARG) * _list[i].arg_count));
		//*���� ����ŭ �о���̰� �Ҵ�

		if (_list[i]._type == TYPE_ARG_CALC_FUNC) {
			_list[i]._calc_func = (LSB_CALC_FUNC_TYPES)(*lsb_buffer_pnt++);
		}
		else {
			_list[i]._calc_func = TYPE_CF_UNKNOWN;
		}
		//*�з����� Ÿ���� calc_func�̶�� ���� �о���δ�
		//*�ϴ��� ��ȣ�� �߸��Ǹ� �ȵǴ� ó���� �� �� �ִµ� �׳� ����

		for (unsigned int j = 0; j < _list[i].arg_count; j++) {
			_list[i].arg_list[j]._type = (LM_SCR_TYPES) * (lsb_buffer_pnt++);
			switch (_list[i].arg_list[j]._type)
			{
				case TYPE_ARG_INT:
				{
					_list[i].arg_list[j]._data = _get_int(&lsb_buffer_pnt);
					break;
					//*** ���� ó��
				}
				case TYPE_ARG_FLOAT: 
				{
					_list[i].arg_list[j]._data = _get_data(&lsb_buffer_pnt, 0xA);
					break;
					//*** �Ҽ� ó��, ������ 0xA ũ�⸸ŭ ��ƸԴ´�
				}
				case TYPE_ARG_BOOL:
				{
					_list[i].arg_list[j]._data = _get_data(&lsb_buffer_pnt, 0x1);
					break;
					//*** ���� ó��, ������ 0x1 ũ�⸸ŭ ��ƸԴ´�
				}
				case TYPE_ARG_STR:
				{
					_s = _get_str(&lsb_buffer_pnt);
					_list[i].arg_list[j]._data = GetUniStr (_s, code);
					free(_s);
					break;
					//*** ���ڿ� ó��
				}
				default:
				{
					_s = _get_str(&lsb_buffer_pnt);
					_list[i].arg_list[j]._data = GetUniStr(_s, code);
					free(_s);
					break;
					//*** �̿��� ���(VAR ��)�� �׳� ���ڿ� ó���Ѵ�
				}
			}
			//*Ÿ�Կ� ���� ó���� ������
		}
		//*���� ����ŭ �����ϱ�
	}
	//*�з����� ����ŭ �о���̱�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*�з����͸� �о���̴� �Լ�


void LSB_PARAMETERS::_decompile_code(HANDLE hWrite, unsigned int code, unsigned int _indent)
{
	for (unsigned int i = 0; i < _count; i++) {

		for (unsigned int j = 0; j < (_indent); j++) {
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_);
		}
		//*�鿩���� ���

		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s:%s][_TYPE_:%s]"), 
			arg_name_prefix, (wchar_t*)_list[i]._name, _op_list[_list[i]._type]);
		//*���� �̸� ���

		if (_list[i]._type == TYPE_ARG_CALC_FUNC) {
			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[_CF_:%s]"), (wchar_t*)_cf_list[_list[i]._calc_func]);
		}
		//*CALC_FUNC�� ��� �߰� ���

		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _enter_raw_);
		//*���� ������

		for (unsigned int j = 0; j < _list[i].arg_count; j++) {
			for (unsigned int j = 0; j < (_indent + 1); j++) {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_);
			}
			//*�鿩���� ���

			switch (_list[i].arg_list[j]._type)
			{
				case TYPE_ARG_INT:
				{
					swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[_INT_:0x%08X]%s"), *(unsigned int*)(_list[i].arg_list[j]._data), _enter_raw_);
					break;
					//*** ���� ó��
				}
				case TYPE_ARG_FLOAT:
				{
					swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[_FLOAT_:%lf]%s"), *(double*)(_list[i].arg_list[j]._data), _enter_raw_);
					break;
					//*** �Ҽ� ó��, ������ 0xA ũ�⸸ŭ ��ƸԴ´�
				}
				case TYPE_ARG_BOOL:
				{
					if (*(bool*)_list[i].arg_list[j]._data) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[_BOOL_:True]%s"), _enter_raw_); }
					else { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[_BOOL_:False]%s"), _enter_raw_); }
					break;
					//*** ���� ó��, ������ 0x1 ũ�⸸ŭ ��ƸԴ´�
				}
				case TYPE_ARG_STR:
				default:
				{
					wchar_t* _n_w = Replace_Text((wchar_t*)_list[i].arg_list[j]._data, _enter_raw_, _enter_plained_);
					wchar_t* _n_w_2 = Replace_Text(_n_w, hex_1_raw, hex_1_plained); free(_n_w);
					if (_list[i].arg_list[j]._type == TYPE_ARG_STR) {
						swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[_STR_:%s]%s"), _n_w_2, _enter_raw_);
					}
					else {
						swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[_VAR_:%s]%s"), _n_w_2, _enter_raw_);
					}
					free(_n_w_2);
					break;
					//*** ���ڿ� ó�� / ��Ÿ�� ���� �������� / ��ü �ʿ�
				}
			}
			//*Ÿ�Կ� ���� ���� ���
		}
	}
}
//*�з����� ����Ʈ Ŭ���� : �ڵ�� ����ϴ� �Լ�

void LSB_PARAMETERS::_write_as_lsb(HANDLE hNewLsb, unsigned int code)
{
	_write_int(hNewLsb, _count);
	//*�з����� �� ���

	char* _s;
	for (unsigned int i = 0; i < _count;i++) {

		_write_byte(hNewLsb, _list[i]._type);
		_s = GetAnsiStr(_list[i]._name, code);
		_write_str(hNewLsb, _s);
		free(_s);
		_write_int(hNewLsb, _list[i].arg_count);
		//*Ÿ�� / �̸� / �з������� ���� �� ���

		if (_list[i]._type == TYPE_ARG_CALC_FUNC) {
			_write_byte(hNewLsb, _list[i]._calc_func);
		}
		//*�з����� Ÿ���� calc_func�̶�� �� ���� �߰��� ����Ѵ�

		for (unsigned int j = 0; j < _list[i].arg_count; j++) {
			_write_byte(hNewLsb, _list[i].arg_list[j]._type);
			//*������ Ÿ�� ���
			switch (_list[i].arg_list[j]._type)
			{
				case TYPE_ARG_INT:
				{
					_write_int(hNewLsb, *(unsigned int*)_list[i].arg_list[j]._data);
					break;
					//*** ���� ó��
				}
				case TYPE_ARG_FLOAT:
				{
					_write_data(hNewLsb, (unsigned char*)_list[i].arg_list[j]._data, 0xA);
					break;
					//*** �Ҽ� ó��, ������ 0xA ũ�⸸ŭ ��ƸԴ´�
				}
				case TYPE_ARG_BOOL:
				{
					_write_byte(hNewLsb, *(unsigned char*)_list[i].arg_list[j]._data);
					break;
					//*** ���� ó��, ������ 0x1 ũ�⸸ŭ ��ƸԴ´�
				}
				case TYPE_ARG_STR:
				default:
				{
					_s = GetAnsiStr((wchar_t*)_list[i].arg_list[j]._data, code);
					_write_str(hNewLsb, _s);
					free(_s);
					break;
					//*** ���ڿ� Ȥ�� �̿��� ���(VAR ��)�� �׳� ���ڿ� ó���Ѵ�
				}
			}
			//*Ÿ�Կ� ���� ó���� ������
		}
		//*���� ����ŭ ����ϱ�

	}
	//*�з����͵��� ���ư��� ���
}
//*�з����� ����Ʈ : lsb ���Ϸ� ����ϴ� �Լ�


void LSB_PARAMETERS::_extract_text(HANDLE hTxt)
{
	for (unsigned int i = 0; i < _count; i++) {
		for (unsigned int j = 0; j < _list[i].arg_count; j++) {
			if ((_list[i].arg_list[j]._type != TYPE_ARG_INT)
				&& (_list[i].arg_list[j]._type != TYPE_ARG_FLOAT)
				&& (_list[i].arg_list[j]._type != TYPE_ARG_BOOL)) {

				wchar_t* _print_str = (wchar_t*)_list[i].arg_list[j]._data;
				if (is_Pure_Ascii_String(_print_str) || is_File_Path_String(_print_str)) { continue; }
				//*���� ������ �ʿ� ������ ������� ����

				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[%s]%s%s%s%s"), 
					_indent_, text_data_prefix, text_prefix, (wchar_t*)_list[i].arg_list[j]._data, text_prefix, _enter_raw_);
				//*���ڿ� ���
				//*���⼭ ���ڿ� ��ġ�� ���� �� �ʿ䰡 ���� �� �ϴ�

			}
			//*���� ������ ���ڿ��� ���� �̾Ƴ����� �Ѵ�
			//*�̸��� ��µǴ� �� �ƴϹǷ� ���⼭�� �ǵ��� �ʴ´�
		}
		//*�� �з������� ���� ����Ʈ ����
	}
	//*�� �з����� ����
}
//*�з����� ����Ʈ Ŭ���� : �ؽ�Ʈ ���� �Լ�


void LSB_PARAMETERS::_replace_text(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int *accum_count)
{
	//*accum_count�� ���� �ε����� ��� ���� �ּҴ�

	for (unsigned int i = 0; i < _count; i++) {
		for (unsigned int j = 0; j < _list[i].arg_count; j++) {
			if ((_list[i].arg_list[j]._type != TYPE_ARG_INT)
				&& (_list[i].arg_list[j]._type != TYPE_ARG_FLOAT)
				&& (_list[i].arg_list[j]._type != TYPE_ARG_BOOL)) {

				if (is_Pure_Ascii_String((wchar_t*)_list[i].arg_list[j]._data)
					|| is_File_Path_String((wchar_t*)_list[i].arg_list[j]._data)) { continue; }

				if (_list[i].arg_list[j]._data != NULL) { free(_list[i].arg_list[j]._data); }
				//*�̹� �����Ͱ� ������ ������

				wchar_t* cp_txt = txt_list_elem->_txt_list_per_inst[(*accum_count)++];
				wchar_t* n_txt = (wchar_t*)malloc (sizeof(wchar_t) * (wcslen(cp_txt) + 1));
				n_txt[wcslen(cp_txt)] = 0;
				memcpy (n_txt, cp_txt, (sizeof(wchar_t) * wcslen(cp_txt)));
				_list[i].arg_list[j]._data = n_txt;
				//*�޸� ���� �� ��ġ

			}
			//*���� ������ ���ڿ��� ���� ��ġ�ϵ��� �Ѵ�
			//*�̸��� ��µǴ� �ؽ�Ʈ�� �ƴϹǷ� ���⼭�� �ǵ��� �ʴ´�
		}
		//*�� �з������� ���� ����Ʈ ����
	}
	//*�� �з����� ����
}
//*�з����� ����Ʈ Ŭ���� : �ؽ�Ʈ ��ü �Լ�


const wchar_t* _part_j_font = TEXT("�ͣ�");
const wchar_t* _part_j_font_2 = TEXT("07�䪵���������ë�");
const wchar_t* _n_font = TEXT("HY�°��");

void LSB_PARAMETERS::_change_code_J2K()
{
	for (unsigned int i = 0; i < _count; i++) {

		JPHan_2_KRHan (_list[i]._name);
		//*�̸��� ����ڵ� �ٲٱ�

		for (unsigned int j = 0; j < _list[i].arg_count; j++) {
			if ((_list[i].arg_list[j]._type != TYPE_ARG_INT)
				&& (_list[i].arg_list[j]._type != TYPE_ARG_FLOAT)
				&& (_list[i].arg_list[j]._type != TYPE_ARG_BOOL)) {
				JPHan_2_KRHan((wchar_t*)_list[i].arg_list[j]._data);
				wchar_t* _chk = (wchar_t*)_list[i].arg_list[j]._data;
				if ((wcsstr(_chk, _part_j_font) != NULL)
					|| (wcsstr(_chk, _part_j_font_2) != NULL)) {
					_chk = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_n_font) + 1));
					memset(_chk, 0, (sizeof(wchar_t) * (wcslen(_n_font) + 1)));
					memcpy(_chk, _n_font, (sizeof(wchar_t) * wcslen(_n_font)));
					free(_list[i].arg_list[j]._data);
					_list[i].arg_list[j]._data = _chk;
				}
			}
			//*���� ������ ���ڿ��� ���� �ڵ带 �ٲٵ��� �Ѵ�
		}
		//*�� �з������� ���� ����Ʈ ����
	}
	//*�� �з����� ����
}
//*�з����� ����Ʈ Ŭ���� : �ؽ�Ʈ �ڵ� ���� �Լ�


void LSB_PARAMETERS::_release()
{
	if (_list != NULL) {
		for (unsigned int i = 0; i < _count; i++) {
			for (unsigned int j = 0; j < _list[i].arg_count; j++) {
				if (_list[i].arg_list[j]._data != NULL) {
					free(_list[i].arg_list[j]._data);
				}
			}
			free(_list[i].arg_list);
		}
		free(_list); _list = NULL;
	}
}
//*�з����͸� �����ϴ� �Լ�
//---------------------------- �з����� ����Ʈ Ŭ���� ----------------------------//




//---------------------------- �̺�Ʈ ���� Ŭ���� ----------------------------//
void LSB_EVENT::_read_event_script(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);

	unsigned int* _int;
	unsigned char* _c;
	char* __s;

	_int = _get_int(&lsb_buffer_pnt);
	unsigned int _ev_scr_size = *_int; free(_int);
	unsigned char* ev_scr_end_pnt = lsb_buffer_pnt + _ev_scr_size;
	//* ��ü ���� �ľ� / �� ��ġ ����

	__s = (char*)_get_data(&lsb_buffer_pnt, 6);
	_tpword = GetUniStr (__s, code);
	free(__s);
	__s = (char*)_get_data(&lsb_buffer_pnt, 3);
	_ver = GetUniStr(__s, code);
	free(__s);
	_tpword_ver = wcstol(_ver, NULL, 10);
	//* ���� ����Ʈ �� ���� �о���̱�

	_int = _get_int(&lsb_buffer_pnt);
	_attribute_count = *_int; free(_int);
	//*������ ���� �ľ�

	if (_attribute_count > 0) {
		_attribute_list = (LSB_EV_TXT_ATTRIBUTE**)malloc(sizeof(LSB_EV_TXT_ATTRIBUTE*) * _attribute_count);
		memset(_attribute_list, 0, (sizeof(LSB_EV_TXT_ATTRIBUTE*) * _attribute_count));
		for (unsigned int i = 0; i < _attribute_count; i++) {
			_attribute_list[i] = new LSB_EV_TXT_ATTRIBUTE (_tpword_ver);
			_attribute_list[i]->_read_var_data(&lsb_buffer_pnt, code);
		}
	}
	//*���� ������ŭ �Ҵ��ϰ� �о���̱�

	if (_tpword_ver >= 0x69) {
		_ev_header = new LSB_EVENT_HEADER();
		_ev_header->_read_event_header(&lsb_buffer_pnt, code);
	}
	//*������ ���� �̺�Ʈ ��� �� �б�

	_int = _get_int(&lsb_buffer_pnt);
	_total_inst_count = *_int; free(_int);
	_several_inst_count = _total_inst_count;
	//*�� ��ɾ� �� �ľ�

	unsigned int* _chk_count_arr = NULL;
	if (_attribute_count > 0) {
		_chk_count_arr = (unsigned int*)malloc(sizeof(int) * _attribute_count);
		memset(_chk_count_arr, 0, (sizeof(int) * _attribute_count));
	}
	//*üũ��

	_main_inst_list = new LSB_EVENT_ARG_LIST(_attribute_list, _attribute_count, _tpword_ver);
	//*���� ������ ���⼭ �Ҵ��ؾ� �ҵ���

	LSB_EVENT_OP_INST* arg_elem = NULL;
	LSB_EV_OPCODE_TYPES _ev_op_type;
	unsigned int _txt_accum_idx = 0;
	unsigned int _several_count_chk = 0;
	unsigned int _char_op_count_chk = 0;
	for (unsigned int i = 0; i < _total_inst_count; i++) {

		_c = _get_byte(&lsb_buffer_pnt);
		_ev_op_type = (LSB_EV_OPCODE_TYPES)*_c;
		free(_c);
		//*��ɾ� Ÿ�� �о���̱�

		if ((_ev_op_type != TYPE_EV_OP_IMG) && (_ev_op_type != TYPE_EV_OP_ALIGN)) {
			_several_count_chk++;
		}
		//*���� ���������� �� �𸣰����� �ƹ�ư �� �� ������ ������ ������ ī�����Ѵ�

		if (_ev_op_type == TYPE_EV_OP_CHAR) {
			if (arg_elem == NULL) { 
				arg_elem = new LSB_EVENT_OP_INST(_ev_op_type, _attribute_list, _attribute_count, _tpword_ver); 
			}
			//*arg_elem�� NULL�̸� ���� �Ҵ����ֱ�
			arg_elem->_read_ev_data(&lsb_buffer_pnt, _txt_accum_idx, code);
			//*������ �о���̱�
			if (_chk_count_arr != NULL) { _chk_count_arr[arg_elem->_last_idx]++; }
			//*üũ�� �ݿ�
			_txt_accum_idx++;
			//*�ؽ�Ʈ �ε��� ����

			if (_tpword_ver >= 0x69) { _char_op_count_chk++; }
			//*������ ���� �� �߰�
		}
		//*��ɾ� Ÿ���� char��� ��� ���ٿ��ֱ�

		else {
			_txt_accum_idx = 0;
			//*������ �ؽ�Ʈ ī��Ʈ �ʱ�ȭ
			if (arg_elem != NULL) {
				_main_inst_list->Append(arg_elem);
			}
			//*���� arg_elem�� NULL�� �ƴ϶�� �� ���� ����Ʈ�� �߰��� �ش�
			arg_elem = new LSB_EVENT_OP_INST(_ev_op_type, _attribute_list, _attribute_count, _tpword_ver);
			arg_elem->_read_ev_data(&lsb_buffer_pnt, _txt_accum_idx, code);
			if ((_ev_op_type == TYPE_EV_OP_VAR) || (_ev_op_type == TYPE_EV_OP_HISTORY_CHAR)) {
				if (_chk_count_arr != NULL) { _chk_count_arr[arg_elem->_last_idx]++; }
				if (_tpword_ver >= 0x69) { _char_op_count_chk++; }
				//*������ ���� �� �߰�
			}
			//*üũ�� �ݿ�
			_main_inst_list->Append(arg_elem);
			arg_elem = NULL;
			//*�׸��� �ٽ� �Ҵ��� �� �о���̰� �߰��ϰ� NULL�� �ٲٸ� ��
		}
		//*�ٸ� ��쿡�� �Ϲ������� �����ϵ� ����
	}
	//*��ɾ� ������ŭ �о���̱�
	//*��ɾ� Ÿ���� char�� ���� ���Ҵ��� �ƴ϶� ��� ���ư��鼭 �о���δ�

	if (arg_elem != NULL) { _main_inst_list->Append(arg_elem); }
	//*���������� �������� �װ͵� �߰���

	for (unsigned int i = 0; i < _attribute_count; i++) {
		if (_attribute_list[i]->_ev_op_ref_count != _chk_count_arr[i]) {
			wprintf(TEXT("�ε��� ���� ��Ī�� ��ġ���� �ʽ��ϴ�.\n���߿� �ݿ��� �� ������ ���� �� �ֽ��ϴ�.\n"));
		}
	}
	if (_tpword_ver >= 0x69) {
		if ((_several_count_chk != _ev_header->_several_op_count) 
			&& (_total_inst_count != _ev_header->_several_op_count)) {
			wprintf(TEXT("�ε����� ���� ��ġ���� �ʽ��ϴ�.\n���߿� �ݿ��� �� ������ ���� �� �ֽ��ϴ�.\n"));
		}
		if (_ev_header->_elem_count != 0) {
			if (_char_op_count_chk != _ev_header->_elem_list[0]._ref_count) {
				wprintf(TEXT("�ε����� ���� ��ġ���� �ʽ��ϴ�.(0x%X, 0x%X)\n���߿� �ݿ��� �� ������ ���� �� �ֽ��ϴ�.\n"),
					_char_op_count_chk, _ev_header->_elem_list[0]._ref_count);
			}
		}
	}
	//*����� �迭���� ���� ��߳��� �޽��� ����

	if (_chk_count_arr != NULL) { free(_chk_count_arr); }
	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
	//*��ġ ���� �ݿ�
}
//*�̺�Ʈ ���� �о���̴� �Լ�


void LSB_EVENT::_decompile_code(HANDLE hWrite, unsigned int code, unsigned int _indent)
{
	for (unsigned int i = 0; i < _indent; i++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s]%s"), event_attr_prefix, _enter_raw_);
	//*�̺�Ʈ ���� ��� ���

	for (unsigned int i = 0; i < _attribute_count; i++) {
		_attribute_list[i]->_decompile_code(hWrite, code, _indent + 1);
	}
	//*�̺�Ʈ ���� ������ ���ư��鼭 ���

	if (_tpword_ver>= 0x69) {
		_ev_header->_decompile_code(hWrite, code, _indent);
	}
	//*�̺�Ʈ ��� �� ���

	for (unsigned int i = 0; i < _indent; i++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s]%s"), event_inst_prefix, _enter_raw_);
	//*�̺�Ʈ ��ɾ� ��� ��� ���

	LSB_EVENT_OP_INST* _eapt = _main_inst_list->_dummy_start->_next;
	for (unsigned int i = 0; i < _main_inst_list->_count; i++) {
		_eapt->_decompile_code(hWrite, code, _indent + 1);
		_eapt = _eapt->_next;
	}
	//*��ɾ�� ���ư��鼭 ���
}
//*�̺�Ʈ Ŭ���� : �ڵ�� ����ϴ� �Լ�


void LSB_EVENT::_recompile_from_txt(wchar_t* _code_txt_buffer, unsigned int code)
{
	//*** _tpword, _ver�� ���� �������� �����Դ� ������

	wchar_t* _code_txt_pnt = _code_txt_buffer, * _code_txt_pnt_2 = _code_txt_buffer;
	wchar_t* _tm_cpy = NULL;
	//*�ؽ�Ʈ�� ��� ���� ����

	_attribute_count = Get_Txt_Count(_code_txt_buffer, refer_attr_prefix, wcslen(_code_txt_buffer));
	wchar_t* _attr_end_pnt = NULL;
	if (_tpword_ver >= 0x69) {
		_attr_end_pnt = wcsstr(_code_txt_buffer, event_header_prefix);
	}
	else {
		_attr_end_pnt = wcsstr(_code_txt_buffer, event_inst_prefix);
	}
	//*��쿡 ���� �������� �ٸ��� �����Ѵ�

	if (_attribute_count != 0) {
		_attribute_list = (LSB_EV_TXT_ATTRIBUTE**)malloc(sizeof(LSB_EV_TXT_ATTRIBUTE*) * _attribute_count);
		memset(_attribute_list, 0, (sizeof(LSB_EV_TXT_ATTRIBUTE*) * _attribute_count));
		for (unsigned int i = 0; i < _attribute_count;i++) {
			_attribute_list[i] = new LSB_EV_TXT_ATTRIBUTE(_tpword_ver);
			//*�ʱ�ȭ
			_code_txt_pnt_2 = wcsstr(_code_txt_pnt, refer_attr_prefix) + wcslen(refer_attr_prefix);
			_code_txt_pnt = wcsstr(_code_txt_pnt_2, refer_attr_prefix);
			if (_code_txt_pnt == NULL) { _code_txt_pnt = _attr_end_pnt; }
			_tm_cpy = (wchar_t*)malloc(sizeof(wchar_t) * (_code_txt_pnt - _code_txt_pnt_2 + 1));
			memset(_tm_cpy, 0, (sizeof(wchar_t) * (_code_txt_pnt - _code_txt_pnt_2 + 1)));
			memcpy(_tm_cpy, _code_txt_pnt_2, (sizeof(wchar_t) * (_code_txt_pnt - _code_txt_pnt_2)));
			//*�ʿ��� �ؽ�Ʈ�� �����ؿ���
			_attribute_list[i]->_recompile_from_txt(_tm_cpy);
			//*�Ӽ��� �о���̱�
			free(_tm_cpy);
			//*������ ���� �غ�
		}
	}
	//*�̺�Ʈ ���� �Ӽ� �� �ľ� / �Ҵ� / �ʱ�ȭ(0�� �ƴ� ����)
	//*�̺�Ʈ ���� �Ӽ� �о���̱�(���� ��ɾ� �Ҵ� �� �ʿ���)

	if (_tpword_ver >= 0x69) {
		_code_txt_pnt = wcsstr(_code_txt_buffer, event_header_prefix);
		_ev_header = new LSB_EVENT_HEADER();
		_ev_header->_recompile_from_txt(_code_txt_pnt, code);
		if (_ev_header->_elem_count != 0) {
			_ev_header->_elem_list[0]._ref_count = 0;
		}
	}
	//*���� ���� ������ 105��� ����� �Ҵ��� �ϰ� �о�;� ��
	//*�׸��� ���� �������� �ϴ� ���̹Ƿ� �Ϲ� ���ڿ� ���� �������� �ٽ� ����ؾ� �Ѵ�

	_main_inst_list = new LSB_EVENT_ARG_LIST(_attribute_list, _attribute_count, _tpword_ver);
	_code_txt_pnt = wcsstr(_code_txt_buffer, event_inst_prefix);
	_total_inst_count = Get_Txt_Count(_code_txt_pnt, event_op_type_prefix, wcslen(_code_txt_pnt));
	//*��ɾ� ���� �� �ʱ�ȭ �� ��ġ ����

	wchar_t ss_num[3]; memset(ss_num, 0, sizeof(wchar_t) * 3);
	if (_total_inst_count != 0) {
		for (unsigned int i = 0; i < _total_inst_count; i++) {
			_code_txt_pnt_2 = wcsstr(_code_txt_pnt, event_op_type_prefix) + wcslen(event_op_type_prefix);
			memcpy(ss_num, &_code_txt_pnt_2[1], sizeof(wchar_t) * 2);
			LSB_EV_OPCODE_TYPES _ev_op_tp = (LSB_EV_OPCODE_TYPES) wcstol (ss_num, NULL, 10);
			//*�̺�Ʈ ��ɾ� Ÿ�� �о���̱�
			LSB_EVENT_OP_INST* _ttp = new LSB_EVENT_OP_INST(_ev_op_tp, _attribute_list, _attribute_count, _tpword_ver);
			//*�ʱ�ȭ
			
			_code_txt_pnt = wcsstr(_code_txt_pnt_2, event_op_type_prefix);
			if (_code_txt_pnt == NULL) { _code_txt_pnt = _code_txt_buffer + wcslen(_code_txt_buffer); }
			_tm_cpy = (wchar_t*)malloc(sizeof(wchar_t) * (_code_txt_pnt - _code_txt_pnt_2 + 1));
			memset(_tm_cpy, 0, (sizeof(wchar_t) * (_code_txt_pnt - _code_txt_pnt_2 + 1)));
			memcpy(_tm_cpy, _code_txt_pnt_2, (sizeof(wchar_t) * (_code_txt_pnt - _code_txt_pnt_2)));
			//*�ʿ��� �ؽ�Ʈ�� �����ؿ���
			_ttp->_recompile_from_txt(_tm_cpy, code);
			//*�� ��ɾ �ش��ϴ� ���� �о���̱�
			_main_inst_list->Append(_ttp);
			//*����Ʈ�� �߰�
			free(_tm_cpy);
			//*������ ���� �غ�

			if (_tpword_ver >= 0x69) {
				if (_ev_op_tp == TYPE_EV_OP_CHAR)
				{
					_several_inst_count += wcslen(_ttp->_str);
					_ev_header->_several_op_count += wcslen(_ttp->_str);
					if (_ev_header->_elem_count != 0) { _ev_header->_elem_list[0]._ref_count += wcslen(_ttp->_str); }
					//*�������� �߰��� �� �̰͵� �Ű��� ��
				}
				else if ((_ev_op_tp == TYPE_EV_OP_VAR) || (_ev_op_tp == TYPE_EV_OP_HISTORY_CHAR))
				{
					_several_inst_count++;
					_ev_header->_several_op_count++;
				}
				else { 
					_several_inst_count++; 
					if ((_ev_op_tp != TYPE_EV_OP_IMG) && (_ev_op_tp != TYPE_EV_OP_ALIGN)) {
						_ev_header->_several_op_count++;
					}
					//*���� ���������� �𸣰����� �̷��� �´µ� �ϴ�
				}
			}
			//*������ ���� �� �߰�
		}
		//*�� �ʿ��� �ؽ�Ʈ �κи� �����ؼ� �Ѱ��ֱ�
		//*�� ������ŭ ���� �Ҵ��ؼ� �о���� �� �߰����ָ� �ȴ�
	}
	//*�̺�Ʈ ���� ��ɾ� �� �ľ� / �Ҵ� / �ʱ�ȭ(0�� �ƴ� ����)
	//*�̺�Ʈ ���� ��ɾ� �о���̱�
}
//*�̺�Ʈ Ŭ���� : �������� �Լ� (���� : �ش� �̺�Ʈ ���� �����Ͱ� ����ִ� �ؽ�Ʈ ������ �Ϻ�)


void LSB_EVENT::_write_as_lsb(HANDLE hNewLsb, unsigned int code)
{
	char* __s;

	unsigned int _total_ev_block_size_ofs = SetFilePointer(hNewLsb, 0, NULL, FILE_CURRENT);
	SetFilePointer(hNewLsb, sizeof(int), NULL, FILE_CURRENT);
	//*�ϴ� ��ü ���̴� ���߿� �� �� ������ ��ġ�� ����ϰ� �Ѿ��

	__s = GetAnsiStr(_tpword, code);
	_write_data(hNewLsb, (unsigned char*)__s, strlen(__s));
	free(__s);
	__s = GetAnsiStr(_ver, code);
	_write_data(hNewLsb, (unsigned char*)__s, strlen(__s));
	free(__s);
	//*���� ����Ʈ / ���� ���

	_write_int(hNewLsb, _attribute_count);
	//*���� ���� ���

	for (unsigned int i = 0; i < _attribute_count; i++) {
		_attribute_list[i]->_write_as_lsb(hNewLsb, code);
	}
	//*���� ������ ���

	if (_tpword_ver >= 0x69) {
		_ev_header->_write_as_lsb(hNewLsb, code);
	}
	//***������ ���� ������� ���

	unsigned int _total_inst_count_ofs = SetFilePointer(hNewLsb, 0, NULL, FILE_CURRENT);
	SetFilePointer(hNewLsb, sizeof(int), NULL, FILE_CURRENT);
	//*�� ��ɾ� ���� �ٽ� ����ؾ� �ϹǷ� ��ġ�� ����ϰ� �Ѿ��

	unsigned int _total_inst_count = 0;
	LSB_EVENT_OP_INST* _pnt = _main_inst_list->_dummy_start->_next;
	for (unsigned int i = 0; i < _main_inst_list->_count; i++) {
		_pnt->_write_as_lsb(hNewLsb, code, &_total_inst_count);
		_pnt = _pnt->_next;
	}
	//*����Ʈ�� ũ�⸸ŭ ���ư��鼭 �� ��ɾ� �� ���
	
	unsigned int _now_ofs = SetFilePointer(hNewLsb, 0, NULL, FILE_CURRENT);
	unsigned int _total_ev_block_size = _now_ofs - (_total_ev_block_size_ofs + sizeof(int));
	//*ó���� �Ϸ������ ��ü ũ�� ���

	SetFilePointer(hNewLsb, _total_inst_count_ofs, NULL, FILE_BEGIN);
	_write_int(hNewLsb, _total_inst_count);
	SetFilePointer(hNewLsb, _total_ev_block_size_ofs, NULL, FILE_BEGIN);
	_write_int(hNewLsb, _total_ev_block_size);
	SetFilePointer(hNewLsb, _now_ofs, NULL, FILE_BEGIN);
	//*�� ��ġ�� ����ϰ� �ڵ� ��ġ �ű�
}
//*�̺�Ʈ Ŭ���� : lsb ���Ϸ� ����ϴ� �Լ�


void LSB_EVENT::_extract_text(HANDLE hTxt)
{
	for (unsigned int i = 0; i < 1; i++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s]%s"), event_attr_prefix, _enter_raw_);
	//*�̺�Ʈ ���� ��� ���, �鿩���� 1��

	for (unsigned int i = 0; i < _attribute_count; i++) {
		_attribute_list[i]->_extract_text(hTxt);
	}
	//*�� ������ ������ �ش�

	if (_tpword_ver >= 0x69) {
		_ev_header->_extract_text(hTxt);
	}
	//*������ ���� ��� ���� �����Ѵ�

	for (unsigned int i = 0; i < 1; i++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s]%s"), event_inst_prefix, _enter_raw_);
	//*�̺�Ʈ ��ɾ� ��� ��� ���, �鿩���� 1��

	LSB_EVENT_OP_INST* _elem_pnt = _main_inst_list->_dummy_start->_next;
	for (unsigned int i = 0; i < _main_inst_list->_count; i++) {
		_elem_pnt->_extract_text(hTxt);
		//*�ؽ�Ʈ ����
		_elem_pnt = _elem_pnt->_next;
		//*����Ʈ ������ �̵�
	}
	//*���� ����Ʈ�� ��ϵ� ����ŭ ����
}
//*�̺�Ʈ Ŭ���� : �ؽ�Ʈ ���� �Լ�


void LSB_EVENT::_replace_text(LSB_TEXTS_PER_INST* txt_list_elem)
{
	//*** �̺�Ʈ ����ŭ�� �ƿ� ���� ������ �� ������ �� ���� ***//
	//*** �׷��� ��ũ��Ʈ�� �����Ӱ� ����� �߰��� �� ���� ***//
	//*** �������� text_data_prefix�� ���� ���� ������ ���� ����� ������ �� �ϴ� ***//
	//*** �� �� �Լ��� �Ⱦ��δ� ***//
}
//*�̺�Ʈ Ŭ���� : �ؽ�Ʈ ��ü �Լ�


void LSB_EVENT::_change_code_J2K()
{
	for (unsigned int i = 0; i < _attribute_count; i++) {
		_attribute_list[i]->_change_code_J2K();
	}
	//*�̺�Ʈ ���� : ���� ����Ʈ�� ��ϵ� ����ŭ �ٲٱ�

	if (_tpword_ver >= 0x69) {
		_ev_header->_change_code_J2K();
	}
	//*�̺�Ʈ ������� ������ ���� �ٲٱ�

	LSB_EVENT_OP_INST* _elem_pnt = _main_inst_list->_dummy_start->_next;
	for (unsigned int i = 0; i < _main_inst_list->_count; i++) {
		_elem_pnt->_change_code_J2K();
		_elem_pnt = _elem_pnt->_next;
		//*����Ʈ ������ �ٲ㰡�� �ٲٱ�
	}
	//*�̺�Ʈ ��ɾ� : ���� ����Ʈ�� ��ϵ� ����ŭ �ٲٱ�
}
//*�̺�Ʈ Ŭ���� : �ؽ�Ʈ �ڵ� ���� �Լ�


#define VARIABLES_DECLARE(_code_txt_buffer_) \
	wchar_t* _code_txt_pnt = (_code_txt_buffer), * _code_txt_pnt_2 = (_code_txt_buffer), * _swp;\
	wchar_t _buf_for_int[11];\
	wchar_t _buf_for_byte[5];\
	memset(_buf_for_int, 0, (sizeof(wchar_t) * 11));\
	memset(_buf_for_byte, 0, (sizeof(wchar_t) * 5));\
	wchar_t * _w_str_2, * _ww_str_2;
//*���� ���� ��ũ��

#define GET_INT_FROM_TEXT(_int_) \
	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, TEXT("[")) + wcslen(TEXT("["));\
	_w_str_2 = (wchar_t*)malloc(sizeof(wchar_t) * 11);\
	memset(_w_str_2, 0, (sizeof(wchar_t) * 11));\
	memcpy(_w_str_2, _code_txt_pnt_2, (sizeof(wchar_t) * 10));\
	(_int_) = wcstoul(_w_str_2, NULL, 16); free(_w_str_2);\
	_swp = _code_txt_pnt; _code_txt_pnt = _code_txt_pnt_2; _code_txt_pnt_2 = _swp;
//*���� ��� ��ũ��

#define GET_DEF_IDX_FROM_TEXT(_def_idx_) \
	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, ev_attr_def_idx_prefix) + wcslen(ev_attr_def_idx_prefix) + wcslen(TEXT(":"));\
	_w_str_2 = (wchar_t*)malloc(sizeof(wchar_t) * 11);\
	memset(_w_str_2, 0, (sizeof(wchar_t) * 11));\
	memcpy(_w_str_2, _code_txt_pnt_2, (sizeof(wchar_t) * 10));\
	(_def_idx_) = wcstoul(_w_str_2, NULL, 16); free(_w_str_2);
//*����Ʈ �ε��� ��� ��ũ��

#define GET_BYTE_FROM_TEXT(_byte_) \
	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, TEXT("[")) + wcslen(TEXT("["));\
	_w_str_2 = (wchar_t*)malloc(sizeof(wchar_t) * 5);\
	memcpy(_w_str_2, _code_txt_pnt_2, (sizeof(wchar_t) * 4));\
	(_byte_) = (unsigned char)wcstoul(_w_str_2, NULL, 16); free(_w_str_2);\
	_swp = _code_txt_pnt; _code_txt_pnt = _code_txt_pnt_2; _code_txt_pnt_2 = _swp;
//*����Ʈ ��� ��ũ��

#define GET_STR_FROM_TEXT(_str_) \
	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, text_prefix) + wcslen(text_prefix);\
	_code_txt_pnt = wcsstr(_code_txt_pnt_2, text_prefix);\
	(_str_) = (wchar_t*)malloc(sizeof(wchar_t) * (_code_txt_pnt - _code_txt_pnt_2 + 1));\
	memset((_str_), 0, (sizeof(wchar_t)* (_code_txt_pnt - _code_txt_pnt_2 + 1)));\
	memcpy((_str_), _code_txt_pnt_2, (sizeof(wchar_t)* (_code_txt_pnt - _code_txt_pnt_2)));\
	_code_txt_pnt += wcslen(text_prefix);
//*���ڿ� ��� ��ũ��

#define GET_IDX_FROM_TEXT(_idx_) \
	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, ev_attr_idx_prefix) + wcslen(ev_attr_idx_prefix) + wcslen(TEXT(":"));\
	_w_str_2 = (wchar_t*)malloc(sizeof(wchar_t) * 11);\
	memset(_w_str_2, 0, (sizeof(wchar_t) * 11));\
	memcpy(_w_str_2, _code_txt_pnt_2, (sizeof(wchar_t) * 10));\
	(_idx_) = wcstoul(_w_str_2, NULL, 16); free(_w_str_2);
//*�ε��� ��� ��ũ��

void LSB_EVENT_HEADER::_read_event_header(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);

	char* _s;

	_type = *(unsigned int*)lsb_buffer_pnt;
	lsb_buffer_pnt += sizeof(int);
	//*Ÿ�� ���� �б�

	_several_op_count = *(unsigned int*)lsb_buffer_pnt;
	lsb_buffer_pnt += sizeof(int);
	_unk_1 = *(unsigned int*)lsb_buffer_pnt;
	lsb_buffer_pnt += sizeof(int);
	//*�������� ���� �б�

	if (_type > 1) {
		_unk_2 = *(unsigned int*)lsb_buffer_pnt;
		lsb_buffer_pnt += sizeof(int);
		_s = _get_str(&lsb_buffer_pnt);
		_str = GetUniStr(_s, code); free(_s);
	}
	//*Ÿ���� 2�϶� Ȱ��ȭ�Ǵ� �� �б�

	_elem_count = *(unsigned int*)lsb_buffer_pnt;
	lsb_buffer_pnt += sizeof(int);
	//*���� �� �б�

	if (_elem_count != 0) {
		_elem_list = (LSB_EVH_ELEM*)malloc(sizeof(LSB_EVH_ELEM) * _elem_count);
		memset(_elem_list, 0, (sizeof(LSB_EVH_ELEM) * _elem_count));
		for (unsigned int i = 0; i < _elem_count;i++) {
			_elem_list[i]._ref_count = *(unsigned int*)lsb_buffer_pnt;
			lsb_buffer_pnt += sizeof(int);
			_s = _get_str(&lsb_buffer_pnt);
			_elem_list[i]._str = GetUniStr(_s, code); free(_s);
			_elem_list[i]._unk_2 = *(unsigned int*)lsb_buffer_pnt;
			lsb_buffer_pnt += sizeof(int);
		}
	}
	//*���� ���� ���� �Ҵ��ϰ� �о���̱�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*�̺�Ʈ ��� Ŭ���� : �о���̴� �Լ�


void LSB_EVENT_HEADER::_decompile_code(HANDLE hWrite, unsigned int code, unsigned int _indent)
{
	for (unsigned int i = 0; i < _indent; i++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s][0x%08X][0x%08X]"), event_header_prefix, _type, _unk_1);
	if (_type > 1) {
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%08X]%s%s%s"), _unk_2, text_prefix, _str, text_prefix);
	}
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _enter_raw_);
	//*�̺�Ʈ ��� �����Ƚ� ���, ������ ��·�� ������� �ϴ� ����Ѵ�
	//*�ٸ� ���⼭ ������ ��ŭ�� ������, _char_op_count�� ���߿� ��ĥ�� �޶����� _elem_count�� Ư�� Ű���� ���� ���⸸ �ϸ� ��
	//*type�� ���� _unk_2�� _str�� �����ؼ� ����Ѵ�

	wchar_t* _tp_uni;
	for (unsigned int i = 0; i < _elem_count;i++) {
		for (unsigned int j = 0; j < (_indent + 1); j++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
		//*�鿩����
		_tp_uni = Replace_Text(_elem_list[i]._str, _enter_raw_, _enter_plained_);
		//*���ڿ� ��ġ �ʿ�
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s]::[0x%08X][0x%08X]%s%s%s%s"),
			event_head_elem_prefix,
			_elem_list[i]._ref_count, _elem_list[i]._unk_2, text_prefix, _tp_uni, text_prefix,
			_enter_raw_);
		free(_tp_uni);
		//*�� ��ҵ� ���
	}
	//*������ ���� �̺�Ʈ �� �������鼭 ���
}
//*�̺�Ʈ ��� Ŭ���� : �������� �Լ�


void LSB_EVENT_HEADER::_recompile_from_txt(wchar_t* _code_txt_buffer, unsigned int code)
{
	VARIABLES_DECLARE(_code_txt_buffer_);

	_elem_count = Get_Txt_Count(_code_txt_buffer, event_head_elem_prefix, wcslen(_code_txt_buffer));
	//*���� �� ����

	GET_INT_FROM_TEXT(_type);
	GET_INT_FROM_TEXT(_unk_1);
	if (_type > 1) {
		GET_INT_FROM_TEXT(_unk_2);
		GET_STR_FROM_TEXT(_str);
	}
	//*�ʿ��� ���� ��� �����ϱ�, _type�� ���� �߰��� ���� �� �����ϱ�

	wchar_t* _inst_start_pnt = wcsstr(_code_txt_buffer, event_inst_prefix);
	wchar_t* _tm_cpy = NULL;
	wchar_t* _tmp_uni;
	//*����� ���������� ��ɾ� �������� Ȯ��

	if (_elem_count != 0) {
		_elem_list = (LSB_EVH_ELEM*)malloc(sizeof(LSB_EVH_ELEM) * _elem_count);
		memset(_elem_list, 0, (sizeof(LSB_EVH_ELEM) * _elem_count));
		for (unsigned int i = 0; i < _elem_count; i++) {
			_code_txt_pnt_2 = wcsstr(_code_txt_pnt, event_head_elem_prefix) + wcslen(event_head_elem_prefix);
			_code_txt_pnt = wcsstr(_code_txt_pnt_2, event_head_elem_prefix);
			if (_code_txt_pnt == NULL) { _code_txt_pnt = _inst_start_pnt; }
			_tm_cpy = (wchar_t*)malloc(sizeof(wchar_t) * (_code_txt_pnt - _code_txt_pnt_2 + 1));
			memset(_tm_cpy, 0, (sizeof(wchar_t) * (_code_txt_pnt - _code_txt_pnt_2 + 1)));
			memcpy(_tm_cpy, _code_txt_pnt_2, (sizeof(wchar_t) * (_code_txt_pnt - _code_txt_pnt_2)));
			//*�ʿ��� �ؽ�Ʈ�� �����ؿ���

			_elem_list[i]._recompile_from_txt(_tm_cpy, code);
			_tmp_uni = Replace_Text(_elem_list[i]._str, _enter_plained_, _enter_raw_);
			free(_elem_list[i]._str);
			_elem_list[i]._str = _tmp_uni;
			//*�ʿ��� ���� �о���̱�, ���ڿ��� ��ġ �ʿ�

			free(_tm_cpy);
			//*������ ���� �غ�
		}
	}
	//*�̺�Ʈ ���� �Ӽ� �� �ľ� / �Ҵ� / �ʱ�ȭ(0�� �ƴ� ����)
	//*�̺�Ʈ ���� �Ӽ� �о���̱�(���� ��ɾ� �Ҵ� �� �ʿ���)
}
//*�̺�Ʈ ��� Ŭ���� : �������� �Լ�


void LSB_EVENT_HEADER::_write_as_lsb(HANDLE hNewLsb, unsigned int code)
{
	char* _s;

	_write_int(hNewLsb, _type);
	//*Ÿ�� ���

	_write_int(hNewLsb, _several_op_count);
	_write_int(hNewLsb, _unk_1);
	//*�������� ���� ���

	if (_type > 1) {
		_write_int(hNewLsb, _unk_2);
		_s = GetAnsiStr(_str, code);
		_write_str(hNewLsb, _s); free(_s);
	}
	//*Ÿ�Կ� ���� ������ �� ���

	_write_int(hNewLsb, _elem_count);
	//*������ ���밪(���� ��) ���

	for (unsigned int i = 0; i < _elem_count;i++) {
		_write_int(hNewLsb, _elem_list[i]._ref_count);
		_s = GetAnsiStr(_elem_list[i]._str, code);
		_write_str(hNewLsb, _s); free(_s);
		_write_int(hNewLsb, _elem_list[i]._unk_2);
	}
	//*���� ���� ���� �߰� ���
}
//*�̺�Ʈ ��� Ŭ���� : lsb ��� �Լ�


void LSB_EVENT_HEADER::_extract_text(HANDLE hTxt)
{
	for (unsigned int i = 0; i < 1; i++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s][0x%08X][0x%08X]"), event_header_prefix, _type, _unk_1);
	if (_type > 1) {
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%08X]%s%s%s"), _unk_2, text_prefix, _str, text_prefix);
	}
	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _enter_raw_);
	//*�̺�Ʈ ��� �����Ƚ� ���, ������ ��·�� ������� �ϴ� ����Ѵ�
	//*�ٸ� ���⼭ ������ ��ŭ�� ������, _char_op_count�� ���߿� ��ĥ�� �޶����� _elem_count�� Ư�� Ű���� ���� ���⸸ �ϸ� ��
	//*type�� ���� _unk_2�� _str�� �����ؼ� ����Ѵ�

	wchar_t* _tp_uni;
	for (unsigned int i = 0; i < _elem_count; i++) {
		for (unsigned int j = 0; j < 2; j++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
		//*�鿩����
		_tp_uni = Replace_Text(_elem_list[i]._str, _enter_raw_, _enter_plained_);
		//*���ڿ� ��ġ �ʿ�
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s]::[0x%08X][0x%08X]%s%s%s%s"),
			event_head_elem_prefix,
			_elem_list[i]._ref_count, _elem_list[i]._unk_2, text_prefix, _tp_uni, text_prefix,
			_enter_raw_);
		free(_tp_uni);
		//*�� ��ҵ� ���
	}
	//*������ ���� �̺�Ʈ �� �������鼭 ���
}
//*�̺�Ʈ ��� Ŭ���� : �ؽ�Ʈ ���� �Լ�


void LSB_EVENT_HEADER::_change_code_J2K()
{
	JPHan_2_KRHan(_str);
	//*���ڿ� ��ȯ

	for (unsigned int i = 0; i < _elem_count; i++) {
		JPHan_2_KRHan(_elem_list[i]._str);
	}
	//*�� ������ ���ڿ� ��ȯ
}
//*�̺�Ʈ ��� Ŭ���� : �ؽ�Ʈ �ڵ� ���� �Լ�


void LSB_EVH_ELEM::_recompile_from_txt (wchar_t* _code_txt_buffer, unsigned int code)
{
	VARIABLES_DECLARE(_code_txt_buffer_);

	GET_INT_FROM_TEXT(_ref_count);
	GET_STR_FROM_TEXT(_str);
	GET_INT_FROM_TEXT(_unk_2);
	//*������ ����ֱ⸸ �ϸ� �ȴ�
}
//*�̺�Ʈ ��� Ŭ������ ���� ����ü : �ؽ�Ʈ �ڵ� ���� �Լ�


void LSB_EVENT_OP_INST::_read_ev_data(unsigned char** _lsb_buffer_pnt, unsigned int txt_accum_idx, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);

	if (_tpword_ver >= 0x69) {
		_unk_1 = *(unsigned int*)lsb_buffer_pnt;
		lsb_buffer_pnt += sizeof(int);
	}
	//***tpword ������ ������ ���������� ���� �ϳ� �� �о����
	//*�̰� �Ƹ� ������ ���ɼ��� ����, �̰� �ֳ� ���Ŀ� ���� ������ �� �д� ���� ������ ��

	char* __s;
	switch (_op_type)
	{
		case TYPE_EV_OP_CHAR:
		{
			_read_char_data(&lsb_buffer_pnt, txt_accum_idx, code);
			break;
			//* TYPE_EV_OP_CHAR�� �� : _read_char_data ȣ�� (_i_3, _extra_data, _str, _i) �̿�
		}
		case TYPE_EV_OP_ALIGN:
		case TYPE_EV_OP_RETURN:
		{
			if (_unk_1 != 0) {
				_unk_t2_t3._unk_1 = *(unsigned char*)lsb_buffer_pnt;
				lsb_buffer_pnt++;
				_unk_t2_t3._unk_2 = *(unsigned int*)lsb_buffer_pnt;
				lsb_buffer_pnt += sizeof(int);
				_unk_t2_t3._unk_3 = *(unsigned int*)lsb_buffer_pnt;
				lsb_buffer_pnt += sizeof(int);
			}
			//*�ϴ� ���� ���� �𸣰����ϱ� �о�鿩 �д�
			unsigned char* _n_b = _get_byte(&lsb_buffer_pnt);
			_b = *_n_b; free(_n_b);
			break;
			//* TYPE_EV_OP_ALIGN / TYPE_EV_OP_RETURN�� �� : _unk_t2_t3, _b �̿�
		}
		case TYPE_EV_OP_INDENT:
		case TYPE_EV_OP_UNDENT:
		{
			break;
			//* TYPE_EV_OP_INDENT / TYPE_EV_OP_UNDENT�� �� : �̿����� ����
		}
		case TYPE_EV_OP_EVENT:
		{
			if (_str != NULL) { free(_str); }
			__s = _get_str(&lsb_buffer_pnt);
			//*���ڿ� ���

			_decode_sharp_encoding (&__s);
			_str = GetUniStr(__s, code);
			free(__s);
			//*�����ڵ�ȭ�ϱ� ���� # + ���� 3���� �� ���ڰ��� �� ��� ansi ���ڿ��� �ٲ� ��ġ����� ��

			//*** ���߿� ����� �� ���ڿ� ��ġ�ؾ� �� _str
			break;
			//* TYPE_EV_OP_EVENT�� �� : _str �̿� (��ġ �ʿ�)
		}
		case TYPE_EV_OP_VAR:
		{
			if (_tpword_ver < 0x65) {
				if (_str != NULL) { free(_str); }
				__s = _get_str(&lsb_buffer_pnt);
				_str = GetUniStr (__s, code);
				free(__s);
				unsigned int* _n_i = _get_int(&lsb_buffer_pnt);
				_last_idx = _default_attr_idx = *_n_i; free(_n_i);
			}
			else {
				unsigned int* _n_i = _get_int(&lsb_buffer_pnt);
				_last_idx = _default_attr_idx = *_n_i; free(_n_i);
				_n_i = _get_int(&lsb_buffer_pnt);
				_i_2 = *_n_i; free(_n_i);
				if (_s != NULL) { free(_s); }
				__s = _get_str(&lsb_buffer_pnt);
				_s = GetUniStr(__s, code);
				free(__s);
				if (_tpword_ver >= 0x66) {
					if (_str != NULL) { free(_str); }
					__s = _get_str(&lsb_buffer_pnt);
					_str = GetUniStr(__s, code);
					free(__s);
				}
			}
			_ev_attr_idx_ref_list[_default_attr_idx]++;
			//*���� Ƚ�� �ݿ�
			break;
			//* TYPE_EV_OP_VAR�� �� : ver < 0x65[_str, _i �̿�], 0x65 <= ver[_i, _i_2, _s �̿�], 0x66 <= ver[_i, _i_2, _s, _str �̿�]
		}
		case TYPE_EV_OP_IMG:
		{
			unsigned int* _n_i = _get_int(&lsb_buffer_pnt);
			_i_2 = *_n_i; free(_n_i);
			_n_i = _get_int(&lsb_buffer_pnt);
			_extra_data = *_n_i; free(_n_i);
			if (_str != NULL) { free(_str); }
			__s = _get_str(&lsb_buffer_pnt);
			_str = GetUniStr(__s, code);
			free(__s);
			unsigned char* _n_b = _get_byte(&lsb_buffer_pnt);
			_b = *_n_b; free(_n_b);
			//*���� Ƚ�� �ݿ�
			if (_tpword_ver >= 0x69) {
				for (unsigned int i = 0; i < 6;i++) {
					_unk_i_list[i] = *(unsigned int*)lsb_buffer_pnt;
					lsb_buffer_pnt += sizeof(int);
				}
			}
			//***������ ���� 0x18����Ʈ �� ���ؾ��ϴµ�?
			break;
			//* TYPE_EV_OP_IMG�� �� : _i_2, _extra_data, _str, _b �̿�
		}
		case TYPE_EV_OP_HISTORY_CHAR:
		{
			unsigned int* _n_i = _get_int(&lsb_buffer_pnt);
			_i_3 = *_n_i; free(_n_i);
			_n_i = _get_int(&lsb_buffer_pnt);
			_i_2 = *_n_i; free(_n_i);
			_n_i = _get_int(&lsb_buffer_pnt);
			_last_idx = _default_attr_idx = *_n_i; free(_n_i);
			if (_str != NULL) { free(_str); }
			__s = _get_str(&lsb_buffer_pnt);
			_str = GetUniStr(__s, code);
			free(__s);
			_ev_attr_idx_ref_list[_default_attr_idx]++;
			//*���� Ƚ�� �ݿ�
			break;
			//* TYPE_EV_OP_HISTORY_CHAR�� �� : _s...�� �ƴ϶� _i_3, _i, _i_2, _str �̿�
		}
		default:
		{
			if (_str != NULL) { free(_str); }
				__s = _get_str(&lsb_buffer_pnt);
				_str = GetUniStr (__s, code);
				free(__s);
			//*** replace _str
			break;
			//* �̿��� ��� : _str �̿�
		}
	}

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//* �̺�Ʈ ���� ���� : ��� ��ɾ� Ÿ�Կ� ���ؼ� �о���̴� ��ɾ�


void LSB_EVENT_OP_INST::_read_char_data(unsigned char** _lsb_buffer_pnt, unsigned int txt_accum_idx, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);

	unsigned int* _p = _get_int(&lsb_buffer_pnt);
	_i_3 = *_p; free(_p);
	//*_i_3 �о���̱�

	_p = _get_int(&lsb_buffer_pnt);
	_extra_data = *_p; free(_p);
	//*_extra_data �о���̱�, �̰� 50�� ��� �Ӹ� �ƴ϶� 300�� �Ǵ� ��찡 ������;;
	//*�̰� ��ĥ�� ����� ������ ���� �Ǵ�

	char *__s = (char*)malloc(3);
	__s[0] = *(char*)(lsb_buffer_pnt + 1);
	__s[1] = *(char*)(lsb_buffer_pnt);
	__s[2] = 0;
	//*���� ������

	if (__s[0] == 0) { __s[0] = __s[1]; __s[1] = 0; }
	//*1����Ʈ ���ڴ� �̴�� �ϸ� �׳� 0�� �Ǽ� �ٽ� �����ؾ� �Ѵ�

	lsb_buffer_pnt += 2;
	wchar_t* __w = GetUniStr(__s, code);
	free(__s);
	//*3ĭ �̸� �Ҵ��ؼ� �о���� �� �����ڵ�� ��ȯ

	if (_str == NULL) {
		_str = __w;
		//*ó���̶�� �Ҵ��� �� �״�� �ٿ��ִ´�
	}
	else {
		wchar_t* _n_str = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(_str) + 1 + 1));
		memcpy(_n_str, _str, (sizeof(wchar_t)*wcslen(_str)));
		_n_str[wcslen(_str)] = __w[0];
		_n_str[wcslen(_str) + 1] = 0;
		free(__w); free(_str); 
		_str = _n_str;
		//*�׷��� �ʴٸ� ���� ���Ҵ� �� �ٲ�ģ��
	}
	//*_str �����ϱ�

	_p = _get_int(&lsb_buffer_pnt);
	unsigned int _attr_idx = *_p;
	free(_p);
	//*���� �Ӽ� �ε��� �� Ȯ��

	_ev_attr_idx_ref_list[_attr_idx]++;
	_last_idx = _attr_idx;
	//*���� Ƚ�� �ݿ�

	if (_default_attr_idx == 0xFFFFFFFF) { _default_attr_idx = _attr_idx; }
	//*������ �� �Ӽ� �ε��� ����

	if (_attr_idx != _default_attr_idx) {
		if (_ev_attr_info_list == NULL) {
			_ev_attr_info_list = (LSB_EV_ATTR_INFO*)malloc(sizeof(LSB_EV_ATTR_INFO));
			memset(_ev_attr_info_list, 0, sizeof(LSB_EV_ATTR_INFO));
			_ev_attr_info_list[0]._attr_idx = _attr_idx;
			_ev_attr_info_list[0]._start_txt_pos = txt_accum_idx;
			_ev_attr_info_list[0]._end_txt_pos = txt_accum_idx + 1;
			_ev_attr_info_cnt++;
		}
		//*�ƿ� ������ ���� �Ҵ��ϰ� ���� �ø�
		else {
			bool found_txt_chunk = false;
			for (unsigned int i = 0; i < _ev_attr_info_cnt;i++) {
				if ((_attr_idx == _ev_attr_info_list[i]._attr_idx)
					&& (txt_accum_idx == (_ev_attr_info_list[i]._end_txt_pos)))
				{
					_ev_attr_info_list[i]._end_txt_pos++; 
					found_txt_chunk = true; break;
				}
				//*����� �Ӽ��� ���� ���� �ؽ�Ʈ �ε��� ���ڶ��� �̾� ���� �� ���� ���� ���ڸ� �÷��ָ� �ȴ�
				//*�׷��� ������ ��� ã�ƺ�
			}
			if (!found_txt_chunk) {
				LSB_EV_ATTR_INFO* _n_il = (LSB_EV_ATTR_INFO*)malloc(sizeof(LSB_EV_ATTR_INFO) * (_ev_attr_info_cnt+1));
				memset(_n_il, 0, (sizeof(LSB_EV_ATTR_INFO) * (_ev_attr_info_cnt + 1)));
				memcpy(_n_il, _ev_attr_info_list, (sizeof(LSB_EV_ATTR_INFO) * _ev_attr_info_cnt));
				_n_il[_ev_attr_info_cnt]._attr_idx = _attr_idx;
				_n_il[_ev_attr_info_cnt]._start_txt_pos = txt_accum_idx;
				_n_il[_ev_attr_info_cnt]._end_txt_pos = txt_accum_idx + 1;
				free(_ev_attr_info_list); _ev_attr_info_list = _n_il;
				_ev_attr_info_cnt++;
			}
			//*��ã�Ҵٸ� �׳� ���� �Ҵ� �� ���� �� �߰��ϴ� �� �ۿ� ����, �׸��� ��ü �� �� �ø���
		}
		//*������ ������ ũ�⸦ �Ҵ��ϰ� �ű� �� �߰�����, �ƴϸ� �� ã�ƺ��� ���ڸ� �ø��� �ľ�
	}
	//*���� ���� ���� �⺻ �Ӽ� �ε��� ���� �ƴ� �����
	//*�ش� �ε��� �ٷ� ���� ���ڰ� �ֳ� ����,
	//*�ƴϸ� ���� �ٿ��ִ´�
	//*�Ȱ����� ���� �Ű澵 �ʿ䰡 ����

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//* �̺�Ʈ ���� ���� : �̺�Ʈ ���� char ���� �б�
//*_word_str �����͸� ���������� �߰��ϰ�, �������� ������ �о������ �ʴ´�


void LSB_EVENT_OP_INST::_decode_sharp_encoding(char** _str_addr)
{
	unsigned int _len = 0;
	unsigned int _new_len = 0;
	unsigned int _char_count = 0;
	char* _start_pos = NULL;
	char* _end_pos = NULL;
	char _tp_arr[4];				//*�ӽ� ���� �ޱ��

	if (_str_addr == NULL) { return; }
	char* _s = (*_str_addr);
	if (_s == NULL) { return; }
	//*���� �˻�

	_len = strlen(_s);
	//*���ڿ� ���� Ȯ��

	for (unsigned int i = 0; i < _len;i++) {
		if (_s[i] == '#') {
			if (i >= (_len - 4)) { break; }
			if (((_s[i+1] >= '0') && (_s[i+1] <= '9')) && ((_s[i+2] >= '0') && (_s[i+2] <= '9')) 
				&& ((_s[i+3] >= '0') && (_s[i+3] <= '9'))) 
			{ _start_pos = &_s[i]; break; }
		}
	}
	//*# + ���� 3�ڸ��� �� ������ ���۵Ǵ� ��ġ Ȯ��

	if (_start_pos == NULL) { return; }
	//*������ �׳� �����Ѵ�

	for (unsigned int i = 0; i < _len; i++) {
		if (_s[i] == '#') {
			if (i >= (_len - 4)) { break; }
			if (((_s[i + 1] >= '0') && (_s[i + 1] <= '9')) && ((_s[i + 2] >= '0') && (_s[i + 2] <= '9'))
				&& ((_s[i + 3] >= '0') && (_s[i + 3] <= '9')))
			{ _end_pos = &_s[i + 4]; i += 3; }
		}
	}
	//*# + ���� 3�ڸ��� �� ������ ������ ��ġ Ȯ��

	_char_count = (_end_pos - _start_pos) / 4;
	char* _n_tp = (char*)malloc(_char_count + (strlen(sharp_encoding_prefix) * 2) + 1);
	memset(_n_tp, 0, (_char_count + (strlen(sharp_encoding_prefix) * 2) + 1));
	memcpy(_n_tp, sharp_encoding_prefix, strlen(sharp_encoding_prefix));
	for (unsigned int i = 0; i < _char_count;i++) {
		memset(_tp_arr, 0, 4);
		memcpy(_tp_arr, (_start_pos + (i * 4) + 1), 3);
		*(unsigned char*)(&_n_tp[strlen(_n_tp)]) = (unsigned char)strtol(_tp_arr, NULL, 10);
	}
	memcpy(&_n_tp[strlen(_n_tp)], sharp_encoding_prefix, strlen(sharp_encoding_prefix));
	//*�� ���� �� �о�鿩�� ����Ʈ ��ȯ�� �ٿ��־� ansi ���ڿ� ����

	_new_len = _len - (_end_pos - _start_pos) + strlen(_n_tp);
	char* _new_s = (char*)malloc(_new_len + 1);
	memset(_new_s, 0, (_new_len + 1));
	memcpy(_new_s, _s, (_start_pos - _s));
	memcpy(_new_s + strlen(_new_s), _n_tp, strlen(_n_tp));
	memcpy(_new_s + strlen(_new_s), _end_pos, (_s + strlen(_s) - _end_pos));
	free(_s); free(_n_tp);
	(*_str_addr) = _new_s;
	//*�̷��� ��ȯ�� ���ڿ��� �ٽ� �ڸ��� �������� ������ ����� �ٿ��ְ� ��ȯ
}
//*�̺�Ʈ ���� ���� : �̺�Ʈ ��ɹ����� # + ���ڹ��ڿ��� ���ڵ��� ���� ������� ��������
//*�ϴ��� �� ���� �ص� �Ǵ� �� ������ �� ���� �Ѵ�


void LSB_EVENT_OP_INST::_decompile_code(HANDLE hWrite, unsigned int code, unsigned int _indent)
{
	for (unsigned int j = 0; j < (_indent); j++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
	//*�鿩���� ���

	wchar_t* _w_str, * _w_str_2, * _ww_str_2;

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s:%02d][0x%08X]"), event_op_type_prefix, (unsigned char)_op_type, _unk_1);
	switch (_op_type)
	{
		case TYPE_EV_OP_CHAR:
		{
			unsigned int _n_wcslen = 0;
			unsigned int _accmul_txt_pos = 0;

			if (_ev_attr_info_cnt == 0) {
				_w_str = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_str) + 1));
				memset(_w_str, 0, (sizeof(wchar_t) * (wcslen(_str) + 1)));
				memcpy(_w_str, _str, (sizeof(wchar_t) * wcslen(_str)));
			}
			//*���� �ٲ� �� ������ �״�� ������

			else {
				_w_str_2 = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_str) + 1));
				memset(_w_str_2, 0, (sizeof(wchar_t) * (wcslen(_str) + 1)));
				memcpy(_w_str_2, _str, (sizeof(wchar_t) * wcslen(_str)));
				//*�̸� �����ص�

				for (unsigned int i = 0; i < _ev_attr_info_cnt; i++) {
					_n_wcslen = wcslen(_w_str_2) + (wcslen(attr_apply_prefix) * 2) + wcslen(ev_attr_idx_prefix) + 13;
					//*�ٲ�� �� ��� ���ڿ� ���� Ȯ�� ("(��)" + "[_IDX_:0x(8�ڸ�)]"(����:13 + "_IDX_") + �״�� + "(��)")
					_w_str = (wchar_t*)malloc(sizeof(wchar_t) * (_n_wcslen + 1));
					memset(_w_str, 0, (sizeof(wchar_t) * (_n_wcslen + 1)));
					//*�Ҵ� �� ����
					memcpy(_w_str, _w_str_2, (sizeof(wchar_t) * (_ev_attr_info_list[i]._start_txt_pos + _accmul_txt_pos)));
					swprintf(_w_str + wcslen(_w_str), TEXT("%s[%s:0x%08X]"),
						attr_apply_prefix, ev_attr_idx_prefix, _ev_attr_info_list[i]._attr_idx);
					memcpy(_w_str + wcslen(_w_str),
						_w_str_2 + (_ev_attr_info_list[i]._start_txt_pos + _accmul_txt_pos),
						(sizeof(wchar_t) * (_ev_attr_info_list[i]._end_txt_pos - _ev_attr_info_list[i]._start_txt_pos)));
					swprintf(_w_str + wcslen(_w_str), TEXT("%s"), attr_apply_prefix);
					memcpy(_w_str + wcslen(_w_str),
						_w_str_2 + ((_ev_attr_info_list[i]._end_txt_pos) + _accmul_txt_pos),
						(sizeof(wchar_t) * (wcslen(_w_str_2) - ((_ev_attr_info_list[i]._end_txt_pos) + _accmul_txt_pos))));
					//*���������鼭 �߰���, �������� ����ذ��鼭 �����ؾ� ��
					_accmul_txt_pos += ((wcslen(attr_apply_prefix) * 2) + wcslen(ev_attr_idx_prefix) + 13);
					//*������ �÷���
					free(_w_str_2); _w_str_2 = _w_str;
					//*���� ���� �����ϰ� �ٲ�ġ��
				}
				//*_str�� Ȯ���� �Ӽ� ������ �̿��ؼ� �߰��߰� ���ڿ��� ��������
			}

			swprintf(_txt_buf + wcslen(_txt_buf),
				TEXT("[0x%08X][0x%08X]%s%s%s[%s:0x%08X]%s"),
				_i_3, _extra_data, text_prefix, _w_str, text_prefix, ev_attr_def_idx_prefix, _default_attr_idx, _enter_raw_);
			free(_w_str);
			break;
			//* TYPE_EV_OP_CHAR�� �� : _i_3, _extra_data, _str, _i �̿�
			//* �׵��� �ôµ� ���⼭�� �ڵ� ��ġ�� �ʿ����
		}
		case TYPE_EV_OP_ALIGN:
		case TYPE_EV_OP_RETURN:
		{
			if (_unk_1 != 0) {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%02X][0x%08X][0x%08X][0x%02X]%s"), 
					_unk_t2_t3._unk_1, _unk_t2_t3._unk_2, _unk_t2_t3._unk_3, _b, _enter_raw_);
			}
			else {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%02X]%s"), _b, _enter_raw_);
			}
			break;
			//* TYPE_EV_OP_ALIGN / TYPE_EV_OP_RETURN�� �� : _unk_t2_t3, _b �̿�
		}
		case TYPE_EV_OP_INDENT:
		case TYPE_EV_OP_UNDENT:
		{
			break;
			//* TYPE_EV_OP_INDENT / TYPE_EV_OP_UNDENT�� �� : �̿����� ����
		}
		case TYPE_EV_OP_EVENT:
		{
			_w_str_2 = _str;
			_ww_str_2 = Replace_Text(_w_str_2, hex_1_raw, hex_1_plained);
			_w_str_2 = Replace_Text(_ww_str_2, _enter_raw_, _enter_plained_); free(_ww_str_2);
			//*�ڵ� ��ȯ �� ��ġ

			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%s%s%s"), text_prefix, _w_str_2, text_prefix, _enter_raw_);
			free(_w_str_2);
			break;
			//* TYPE_EV_OP_EVENT�� �� : _str �̿� (��ġ �ʿ�)
		}
		case TYPE_EV_OP_VAR:
		{
			if (_tpword_ver < 0x65) {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%s%s[%s:0x%08X]%s"), text_prefix, _str, text_prefix, ev_attr_def_idx_prefix, _default_attr_idx, _enter_raw_);
			}
			else if (_tpword_ver >= 0x66) {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%08X]%s%s%s%s%s%s[%s:0x%08X]%s"), 
					_i_2, text_prefix, _s, text_prefix, text_prefix, _str, text_prefix, ev_attr_def_idx_prefix, _default_attr_idx, _enter_raw_);
			}
			else {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%08X]%s%s%s[%s:0x%08X]%s"), 
					_i_2, text_prefix, _s, text_prefix, ev_attr_def_idx_prefix, _default_attr_idx, _enter_raw_);
			}
			break;
			//* TYPE_EV_OP_VAR�� �� : ver < 0x65[_str, _i �̿�], 0x65 <= ver[_i, _i_2, _s �̿�], 0x66 <= ver[_i, _i_2, _s, _str �̿�]
			//* �ƹ����� ��ȯ�� �� �ʿ䰡 ���� �� ����
		}
		case TYPE_EV_OP_IMG:
		{
			if (_tpword_ver < 0x69) {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%08X][0x%08X]%s%s%s[0x%02X]%s"),
					_i_2, _extra_data, text_prefix, _str, text_prefix, _b, _enter_raw_);
			}
			else {
				swprintf(_txt_buf + wcslen(_txt_buf),
					TEXT("[0x%08X][0x%08X]%s%s%s::[0x%08X][0x%08X][0x%08X][0x%08X][0x%08X][0x%08X]::[0x%02X]%s"),
					_i_2, _extra_data, text_prefix, _str, text_prefix, 
					_unk_i_list[0], _unk_i_list[1], _unk_i_list[2], _unk_i_list[3], _unk_i_list[4], _unk_i_list[5],
					_b, _enter_raw_);
			}
			break;
			//* TYPE_EV_OP_IMG�� �� : _i_2, _extra_data, _str, _b �̿�
			//* �ƹ����� ��ȯ�� �� �ʿ䰡 ���� �� ����
			//* ������ 105 �̻��̸� ���� 6�� �߰�
		}
		case TYPE_EV_OP_HISTORY_CHAR:
		{
			swprintf(_txt_buf + wcslen(_txt_buf),
				TEXT("[0x%08X][0x%08X]%s%s%s[%s:0x%08X]%s"),
				_i_3, _i_2, text_prefix, _str, text_prefix, ev_attr_def_idx_prefix, _default_attr_idx, _enter_raw_);
			break;
			//* TYPE_EV_OP_HISTORY_CHAR�� �� : _s...�� �ƴ϶� _i_3, _i, _i_2, _str �̿�
			//* �Լ� ȣ������γ� ���̴� ��ȯ�� �ʿ䰡 ���� �� ����
		}
		default:
		{
			_w_str_2 = _str;
			_ww_str_2 = Replace_Text(_w_str_2, hex_1_raw, hex_1_plained);
			_w_str_2 = Replace_Text(_ww_str_2, _enter_raw_, _enter_plained_); free(_ww_str_2);
			//*�ڵ� ��ȯ �� ��ġ

			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%s%s%s"), text_prefix, _w_str_2, text_prefix, _enter_raw_);
			free(_w_str_2);
			break;
			//* �̿��� ��� : _str �̿�
		}
	}
}
//*�̺�Ʈ ���� Ŭ���� : �ڵ�� ����ϴ� �Լ�


void LSB_EVENT_OP_INST::_recompile_from_txt(wchar_t* _code_txt_buffer, unsigned int code)
{
	VARIABLES_DECLARE(_code_txt_buffer_);

	GET_INT_FROM_TEXT(_unk_1);
	switch (_op_type)
	{
		case TYPE_EV_OP_CHAR:
		{
			GET_INT_FROM_TEXT(_i_3);
			GET_INT_FROM_TEXT(_extra_data);
			GET_STR_FROM_TEXT(_str);
			GET_DEF_IDX_FROM_TEXT(_default_attr_idx);
			//*_i_3 / _extra_data / _str(��� ���Ե� ��) / _default_attr_idx �и�

			_set_char_data();
			//*_str���� �߰������� ������ ������ �ش�

			break;
			//* TYPE_EV_OP_CHAR�� �� : _i_3, _extra_data, _str, _i �̿�
			//* �׵��� �ôµ� ���⼭�� �ڵ� ��ġ�� �ʿ����
		}
		case TYPE_EV_OP_ALIGN:
		case TYPE_EV_OP_RETURN:
		{
			if (_unk_1 != 0) {
				GET_BYTE_FROM_TEXT(_unk_t2_t3._unk_1);
				GET_INT_FROM_TEXT(_unk_t2_t3._unk_2);
				GET_INT_FROM_TEXT(_unk_t2_t3._unk_3);
			}

			GET_BYTE_FROM_TEXT(_b);
			//*_b �и�

			break;
			//* TYPE_EV_OP_ALIGN / TYPE_EV_OP_RETURN�� �� : _unk_t2_t3, _b �̿�
		}
		case TYPE_EV_OP_INDENT:
		case TYPE_EV_OP_UNDENT:
		{
			break;
			//* TYPE_EV_OP_INDENT / TYPE_EV_OP_UNDENT�� �� : �̿����� ����
		}
		case TYPE_EV_OP_EVENT:
		{
			GET_STR_FROM_TEXT(_w_str_2);
			//*_str(Ǯ������) �и�

			_ww_str_2 = Replace_Text(_w_str_2, hex_1_plained, hex_1_raw); free(_w_str_2);
			_str = Replace_Text(_ww_str_2, _enter_plained_, _enter_raw_); free(_ww_str_2);
			//*���ڿ� ��ġ

			break;
			//* TYPE_EV_OP_EVENT�� �� : _str �̿� (��ġ �ʿ�)
		}
		case TYPE_EV_OP_VAR:
		{
			if (_tpword_ver < 0x65) {
				GET_STR_FROM_TEXT(_str);
				GET_DEF_IDX_FROM_TEXT(_default_attr_idx);
				//*_str / _default_attr_idx �и�
			}
			else if (_tpword_ver >= 0x66) {
				GET_INT_FROM_TEXT(_i_2);
				GET_STR_FROM_TEXT(_s);
				GET_STR_FROM_TEXT(_str);
				GET_DEF_IDX_FROM_TEXT(_default_attr_idx);
				//*_i_2 / _s / _str / _default_attr_idx �и�
			}
			else {
				GET_INT_FROM_TEXT(_i_2);
				GET_STR_FROM_TEXT(_s);
				GET_DEF_IDX_FROM_TEXT(_default_attr_idx);
				//*_i_2 / _s / _default_attr_idx �и�
			}

			_ev_attr_list_pnt[_default_attr_idx]->_ev_op_ref_count++;
			//*���� Ƚ�� �ݿ�
			
			break;
			//* TYPE_EV_OP_VAR�� �� : ver < 0x65[_str, _i �̿�], 0x65 <= ver[_i, _i_2, _s �̿�], 0x66 <= ver[_i, _i_2, _s, _str �̿�]
			//* �ƹ����� ��ȯ�� �� �ʿ䰡 ���� �� ����
		}
		case TYPE_EV_OP_IMG:
		{
			GET_INT_FROM_TEXT(_i_2);
			GET_INT_FROM_TEXT(_extra_data);
			GET_STR_FROM_TEXT(_str);
			if (_tpword_ver >= 0x69) {
				for (unsigned int i = 0; i < 6;i++) { GET_INT_FROM_TEXT(_unk_i_list[i]); }
			}
			GET_BYTE_FROM_TEXT(_b);
			//*_i_2 / _str / _b / _extra_data �и�
			//*������ ���󼭴� ���� 6�� �߰�

			break;
			//* TYPE_EV_OP_IMG�� �� : _i_w, _extra_data, _str, _b �̿�
			//* �ƹ����� ��ȯ�� �� �ʿ䰡 ���� �� ����
		}
		case TYPE_EV_OP_HISTORY_CHAR:
		{
			GET_INT_FROM_TEXT(_i_3);
			GET_INT_FROM_TEXT(_i_2);
			GET_STR_FROM_TEXT(_str);
			GET_DEF_IDX_FROM_TEXT(_default_attr_idx);
			//*_s...�� �ƴ϶� _i_3 / _i_2 / _str / _default_attr_idx �и�

			_ev_attr_list_pnt[_default_attr_idx]->_ev_op_ref_count++;
			//*���� Ƚ�� �ݿ�

			break;
			//* TYPE_EV_OP_HISTORY_CHAR�� �� : _s...�� �ƴ϶� _i_3, _i, _i_2, _str �̿�
			//* �Լ� ȣ������γ� ���̴� ��ȯ�� �ʿ䰡 ���� �� ����
		}
		default:
		{
			break;
			//* �̿��� ��� : �׳� �ѱ�
		}
	}
	//*�� ��쿡 ���� ��ȯ��
}
//*�̺�Ʈ ���� Ŭ���� : �������� �Լ� (���� : �ش� �̺�Ʈ ���� �����Ͱ� ����ִ� �ؽ�Ʈ ������ �Ϻ�)


void LSB_EVENT_OP_INST::_set_char_data()
{
	wchar_t* _w_str = _str, * _w_str_2 = _str;
	//*����Ǹ鼭 ���ŵ� ���� ������ ���ڿ� �����͵�

	//*** ����Ʈ �Ӽ��� �̹� ����Ǿ��� ������
	//*** ���� ��ġ�� �ʿ�� ����

	_ev_attr_info_cnt = Get_Txt_Count(_str, ev_attr_idx_prefix, wcslen(_str));
	if (_ev_attr_info_cnt == 0) { 
		_ev_attr_list_pnt[_default_attr_idx]->_ev_op_ref_count += (wcslen(_str));
		return; 
	}
	//*�ٸ� �Ӽ��� ����� Ƚ�� ���ϱ�, ������ Ƚ���� �ݿ��ϰ� ������

	_ev_attr_info_list = (LSB_EV_ATTR_INFO*)malloc(sizeof(LSB_EV_ATTR_INFO) * _ev_attr_info_cnt);
	memset(_ev_attr_info_list, 0, (sizeof(LSB_EV_ATTR_INFO) * _ev_attr_info_cnt));
	//*�Ӽ� ���� �ε��� ���� �迭 �Ҵ�

	wchar_t* _code_txt_pnt = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_str) + 1));
	memset(_code_txt_pnt, 0, (sizeof(wchar_t) * (wcslen(_str) + 1)));
	memcpy(_code_txt_pnt, _str, (sizeof(wchar_t) * wcslen(_str)));
	wchar_t* _code_txt_pnt_2 = _str, * _swp;
	unsigned int _sub_length = 0, _cp_pos_after = 0;
	//*_code_txt_pnt�� �̷������� ���� �����ؼ� �־�� �Ѵ�

	for (unsigned int i = 0; i < _ev_attr_info_cnt;i++) {

		GET_IDX_FROM_TEXT(_ev_attr_info_list[i]._attr_idx);
		//*���� �ε��� ���

		_sub_length = wcslen(attr_apply_prefix) + wcslen(TEXT("[")) + wcslen(ev_attr_idx_prefix) + wcslen(TEXT(":"));
		//*���� �� ���� Ȯ�� ("(��)" + "[" + "_IDX_" + ":")

		_ev_attr_info_list[i]._start_txt_pos = (_code_txt_pnt_2 - _code_txt_pnt) - _sub_length;
		//*�̶� _code_txt_pnt_2�� ���� �ε������� "(��)" + "[" + "_IDX_" + ":" ���� �� ���� ���̹Ƿ�
		//*���۰��� �� ���̸�ŭ ���� �ִ´�

		_cp_pos_after = _ev_attr_info_list[i]._start_txt_pos + _sub_length + 10 + wcslen(TEXT("]"));
		//*������ ��ġ Ȯ�� (���� ��ġ + "(��)" + "[" + "_IDX_" + 16���� 10�ڸ�(0x********) + ":" + "]")

		_swp = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_code_txt_pnt) - _sub_length + 1));
		memset(_swp, 0, (sizeof(wchar_t) * (wcslen(_code_txt_pnt) - _sub_length + 1)));
		memcpy(_swp, _code_txt_pnt, (sizeof(wchar_t) * _ev_attr_info_list[i]._start_txt_pos));
		memcpy((_swp + _ev_attr_info_list[i]._start_txt_pos), (_code_txt_pnt + _cp_pos_after),
			(sizeof(wchar_t) * (wcslen(_code_txt_pnt) - _cp_pos_after)));
		free(_code_txt_pnt); _code_txt_pnt = _swp;
		//*�� ���̸�ŭ ���ڿ� ���� �ٿ��� _code_txt_pnt ����
		//*������ġ�� �� ������ ������ �´�

		_code_txt_pnt_2 = wcsstr(_code_txt_pnt, attr_apply_prefix);
		_ev_attr_info_list[i]._end_txt_pos = (_code_txt_pnt_2 - _code_txt_pnt);
		//*���� �ؽ�Ʈ�� ������ ��ġ ã��

		_sub_length = wcslen(attr_apply_prefix);
		_cp_pos_after = _ev_attr_info_list[i]._end_txt_pos + _sub_length;
		//*���� �� ���� / ������ ��ġ Ȯ��

		_swp = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_code_txt_pnt) - _sub_length + 1));
		memset(_swp, 0, (sizeof(wchar_t) * (wcslen(_code_txt_pnt) - _sub_length + 1)));
		memcpy(_swp, _code_txt_pnt, (sizeof(wchar_t) * _ev_attr_info_list[i]._end_txt_pos));
		memcpy((_swp + _ev_attr_info_list[i]._end_txt_pos), (_code_txt_pnt + _cp_pos_after),
			(sizeof(wchar_t) * (wcslen(_code_txt_pnt) - _cp_pos_after)));
		free(_code_txt_pnt); _code_txt_pnt = _swp;
		//*�ٽñ� ǥ�� ����� ��ġ ����, �̹��� �� ���� ev_attr_idx_prefix��.
	}
	//*�� Ƚ����ŭ ���ư��鼭 �ٽ� ���� ���ڿ��� ������ / �ε��� ���� / ���� �迭�� �����ϱ�

	free(_str); _str = _code_txt_pnt;
	//*�̷��� ���� ���� ���ڿ��� _str�� �������ֱ�

	_idx_list = (unsigned int*)malloc(sizeof(int) * wcslen(_str));
	memset(_idx_list, 0, (sizeof(int) * wcslen(_str)));
	for (unsigned int i = 0; i < wcslen(_str); i++) { _idx_list[i] = _default_attr_idx; }
	if (_ev_attr_info_list != NULL) {
		for (unsigned int i = 0; i < _ev_attr_info_cnt; i++) {
			for (unsigned int j = _ev_attr_info_list[i]._start_txt_pos; j < _ev_attr_info_list[i]._end_txt_pos; j++) {
				_idx_list[j] = _ev_attr_info_list[i]._attr_idx;
			}
		}
	}
	//*�迭 ������ ���� �� ���ں� �ε��� ����

	for (unsigned int i = 0; i < wcslen(_str);i++) { 
		_ev_attr_list_pnt[_idx_list[i]]->_ev_op_ref_count++; 
	}
	//*����Ƚ�� �ݿ�
}
//*�̺�Ʈ ���� Ŭ���� : �̺�Ʈ ���� _str ������ ������ ���� �����ϱ�


void LSB_EVENT_OP_INST::_encode_sharp_prefix(char** _str_addr)
{
	unsigned int _len = 0;
	unsigned int _new_len = 0;
	unsigned int _char_count = 0;
	char* _start_pos = NULL;
	char* _end_pos = NULL;

	if (_str_addr == NULL) { return; }
	char* _s = (*_str_addr);
	if (_s == NULL) { return; }
	//*���� �˻�

	_len = strlen(_s);
	//*���ڿ� ���� Ȯ��

	_start_pos = strstr(_s, sharp_encoding_prefix);
	//*[#]�� ó�� �߰ߵǴ� �� Ȯ��

	if (_start_pos == NULL) { return; }
	//*������ �׳� �����Ѵ�

	_end_pos = strstr((_start_pos + strlen(sharp_encoding_prefix)), sharp_encoding_prefix);
	//*[#]�� ���߿� �߰ߵǴ� �� Ȯ��

	if (_end_pos == NULL) { return; }
	_end_pos += strlen(sharp_encoding_prefix);
	//*������ �׳� �����ϰ�, ������ [#]�� ���̸�ŭ ���ؼ� �����Ѵ�

	_char_count = (_end_pos - _start_pos) - (strlen(sharp_encoding_prefix) * 2);
	char* _n_tp = (char*)malloc((_char_count * 4) + 1);
	memset(_n_tp, 0, ((_char_count * 4) + 1));
	for (unsigned int i = 0; i < _char_count; i++) {
		sprintf(_n_tp + strlen(_n_tp), "#%03d", *(unsigned char*)(_start_pos + strlen(sharp_encoding_prefix) + i));
	}
	//*�� ���� �� �о�鿩�� ����Ʈ�� ������ �� # + ���� 3�ڸ� ���·� ����

	_new_len = _len - (_end_pos - _start_pos) + strlen(_n_tp);
	char* _new_s = (char*)malloc(_new_len + 1);
	memset(_new_s, 0, (_new_len + 1));
	memcpy(_new_s, _s, (_start_pos - _s));
	memcpy(_new_s + strlen(_new_s), _n_tp, strlen(_n_tp));
	memcpy(_new_s + strlen(_new_s), _end_pos, (_s + strlen(_s) - _end_pos));
	free(_s); free(_n_tp);
	(*_str_addr) = _new_s;
	//*�̷��� ��ȯ�� ���ڿ��� �ٽ� �ڸ��� �������� ������ ����� �ٿ��ְ� ��ȯ
}
//*�̺�Ʈ ���� ���� : �̺�Ʈ ��ɹ����� [#] ~ [#] ���̿� �ִ� ���ڿ��� # + ���ڹ��ڿ��� ���ڵ��ϱ�


void LSB_EVENT_OP_INST::_write_as_lsb(HANDLE hNewLsb, unsigned int code, unsigned int *_total_inst_count)
{
	char* __s;
	//*�ӽ� ���ڿ� / �κ� ���ڿ�

	switch (_op_type)
	{
		case TYPE_EV_OP_CHAR:
		{
			wchar_t __w[2];
			memset(__w, 0, sizeof(wchar_t) * 2);
			//*�κ� ���ڿ� �غ�

			if (_idx_list == NULL) {
				_idx_list = (unsigned int*)malloc(sizeof(int) * wcslen(_str));
				memset(_idx_list, 0, (sizeof(int) * wcslen(_str)));
				for (unsigned int i = 0; i < wcslen(_str); i++) { _idx_list[i] = _default_attr_idx; }
				if (_ev_attr_info_list != NULL) {
					for (unsigned int i = 0; i < _ev_attr_info_cnt; i++) {
						for (unsigned int j = _ev_attr_info_list[i]._start_txt_pos; j < _ev_attr_info_list[i]._end_txt_pos; j++) {
							_idx_list[j] = _ev_attr_info_list[i]._attr_idx;
						}
					}
				}
			}
			//*�迭 ������ ���� �� ���ں� �ε��� ����

			for (unsigned int i = 0; i < wcslen(_str);i++) {

				_write_byte(hNewLsb, _op_type);
				//*��ɾ� �ڵ� ���

				if (_tpword_ver >= 0x69) { _write_int(hNewLsb, _unk_1); }
				//*������ ���� �߰����� ���

				_write_int(hNewLsb, _i_3);
				//*_i_3 ���

				_write_int(hNewLsb, _extra_data);
				//*_extra_data ���

				__w[0] = _str[i];
				__s = GetAnsiStr(__w, code);
				if (__s[1] != 0) {
					_write_byte(hNewLsb, __s[1]);
					_write_byte(hNewLsb, __s[0]);
				}
				else {
					_write_data(hNewLsb, (unsigned char*)__s, 2);
				}
				free(__s);
				//*�ش� ��ġ�� ���ڸ� �ϳ� ���� ��ȯ �� 2����Ʈ�� �յڸ� �ٲ� ���
				//*1����Ʈ�� ������ �׳� ������� ����Ѵ�

				_write_int(hNewLsb, _idx_list[i]);
				//*�ε��� ���

				(*_total_inst_count)++;
				//*���� ����
			}

			return;
			//* TYPE_EV_OP_CHAR�� �� : _read_char_data ȣ�� (_i_3, _extra_data, _str, _i) �̿�
			//*���ڸ� �ϳ��� ������ ���鼭 ��ü������ �ݺ��ؼ� �����
		}
		case TYPE_EV_OP_ALIGN:
		case TYPE_EV_OP_RETURN:
		{
			_write_byte(hNewLsb, _op_type);

			if (_tpword_ver >= 0x69) { _write_int(hNewLsb, _unk_1); }
			//*������ ���� �߰����� ���

			if (_unk_1 != 0) {
				_write_byte(hNewLsb, _unk_t2_t3._unk_1);
				_write_int(hNewLsb, _unk_t2_t3._unk_2);
				_write_int(hNewLsb, _unk_t2_t3._unk_3);
			}
			//*_unk_1�� ���� �߰��� ���

			_write_byte(hNewLsb, _b);
			//*** 0�̳� 1�� �ƴҶ� Ȯ��
			//*_b ���

			break;
			//* TYPE_EV_OP_ALIGN / TYPE_EV_OP_RETURN�� �� : _unk_t2_t3, _b ���
		}
		case TYPE_EV_OP_INDENT:
		case TYPE_EV_OP_UNDENT:
		{
			_write_byte(hNewLsb, _op_type);

			if (_tpword_ver >= 0x69) { _write_int(hNewLsb, _unk_1); }
			//*������ ���� �߰����� ���

			break;
			//* TYPE_EV_OP_INDENT / TYPE_EV_OP_UNDENT�� �� : _op_type�� ���
		}
		case TYPE_EV_OP_EVENT:
		{
			_write_byte(hNewLsb, _op_type);

			if (_tpword_ver >= 0x69) { _write_int(hNewLsb, _unk_1); }
			//*������ ���� �߰����� ���

			__s = GetAnsiStr(_str, code);
			_encode_sharp_prefix(&__s);
			_write_str(hNewLsb, __s);
			free(__s);
			//*_str ���
			//*�� ���� ����� ���� ���ڵ� �� �� �ϰ� �������� ��

			break;
			//* TYPE_EV_OP_EVENT�� �� : _str ���
		}
		case TYPE_EV_OP_VAR:
		{
			_write_byte(hNewLsb, _op_type);

			if (_tpword_ver >= 0x69) { _write_int(hNewLsb, _unk_1); }
			//*������ ���� �߰����� ���

			if (_tpword_ver < 0x65) {
				__s = GetAnsiStr(_str, code);
				_write_str(hNewLsb, __s);
				free(__s);
				//*_str ���
				_write_int(hNewLsb, _default_attr_idx);
				//*_i ���
			}
			else {
				_write_int(hNewLsb, _default_attr_idx);
				//*_int ���
				_write_int(hNewLsb, _i_2);
				//*_i_2 ���
				__s = GetAnsiStr(_s, code);
				_write_str(hNewLsb, __s);
				free(__s);
				//*_s ���
				if (_tpword_ver >= 0x66) {
					__s = GetAnsiStr(_str, code);
					_write_str(hNewLsb, __s);
					free(__s);
					//*_str ���
				}
			}

			break;
			//* TYPE_EV_OP_VAR�� �� : ver < 0x65[_str, _i �̿�], 0x65 <= ver[_i, _i_2, _s �̿�], 0x66 <= ver[_i, _i_2, _s, _str �̿�]
		}
		case TYPE_EV_OP_IMG:
		{
			_write_byte(hNewLsb, _op_type);

			if (_tpword_ver >= 0x69) { _write_int(hNewLsb, _unk_1); }
			//*������ ���� �߰����� ���

			_write_int(hNewLsb, _i_2);
			//*_i_2 ���

			_write_int(hNewLsb, _extra_data);
			//*_extra_data ���

			__s = GetAnsiStr(_str, code);
			_write_str(hNewLsb, __s);
			free(__s);
			//*_str ���

			_write_byte(hNewLsb, _b);
			//*_b ���

			if (_tpword_ver >= 0x69) {
				for (unsigned int i = 0; i < 6; i++) { _write_int(hNewLsb, _unk_i_list[i]); }
			}
			//*������ ���� unk_i_list ���

			break;
			//* TYPE_EV_OP_IMG�� �� : _i_2, _extra_data, _str, _b �̿�
		}
		case TYPE_EV_OP_HISTORY_CHAR:
		{
			_write_byte(hNewLsb, _op_type);

			if (_tpword_ver >= 0x69) { _write_int(hNewLsb, _unk_1); }
			//*������ ���� �߰����� ���

			_write_int(hNewLsb, _i_3);
			//*_s...�� �ƴ϶� _i_3 ���

			_write_int(hNewLsb, _i_2);
			//*_i_2 ���

			_write_int(hNewLsb, _default_attr_idx);
			//*_i ���

			__s = GetAnsiStr(_str, code);
			_write_str(hNewLsb, __s);
			free(__s);
			//*_str ���

			break;
			//* TYPE_EV_OP_HISTORY_CHAR�� �� : _s...�� �ƴ϶� _i_3, _i, _i_2, _str �̿�
		}
		default:
		{
			_write_byte(hNewLsb, _op_type);

			__s = GetAnsiStr(_str, code);
			_write_str(hNewLsb, __s);
			free(__s);
			//*_str ���

			break;
			//* �̿��� ��� : _str �̿� (���� ���ڿ��� ��ġ �ʿ�)
		}
	}

	(*_total_inst_count)++;
	//*TYPE_EV_OP_CHAR�� ���� �����ϸ� ���� �̰��� �ٴٸ���
}
//*�̺�Ʈ ���� ���� : lsb ���Ϸ� ����ϴ� �Լ�


void LSB_EVENT_OP_INST::_extract_text(HANDLE hTxt)
{
	for (unsigned int j = 0; j < 2; j++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
	//*�鿩���� 2�� ���

	wchar_t* _w_str, * _w_str_2;
	wchar_t* _ww_str, * _ww_str_2;

	swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[%s:%02d][0x%08X]"), event_op_type_prefix, (unsigned char)_op_type, _unk_1);
	switch (_op_type)
	{
		case TYPE_EV_OP_CHAR:
		{
			unsigned int _n_wcslen = 0;
			unsigned int _accmul_txt_pos = 0;

			if (_ev_attr_info_cnt == 0) {
				_w_str = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_str) + 1));
				memset(_w_str, 0, (sizeof(wchar_t) * (wcslen(_str) + 1)));
				memcpy(_w_str, _str, (sizeof(wchar_t) * wcslen(_str)));
			}
			//*���� �ٲ� �� ������ �״�� ������

			else {
				_w_str_2 = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_str) + 1));
				memset(_w_str_2, 0, (sizeof(wchar_t) * (wcslen(_str) + 1)));
				memcpy(_w_str_2, _str, (sizeof(wchar_t) * wcslen(_str)));
				//*�̸� �����ص�

				for (unsigned int i = 0; i < _ev_attr_info_cnt; i++) {
					_n_wcslen = wcslen(_w_str_2) + (wcslen(attr_apply_prefix) * 2) + wcslen(ev_attr_idx_prefix) + 13;
					//*�ٲ�� �� ��� ���ڿ� ���� Ȯ�� ("(��)" + "[_IDX_:0x(8�ڸ�)]"(����:13 + "_IDX_") + �״�� + "(��)")
					_w_str = (wchar_t*)malloc(sizeof(wchar_t) * (_n_wcslen + 1));
					memset(_w_str, 0, (sizeof(wchar_t) * (_n_wcslen + 1)));
					//*�Ҵ� �� ����
					memcpy(_w_str, _w_str_2, (sizeof(wchar_t) * (_ev_attr_info_list[i]._start_txt_pos + _accmul_txt_pos)));
					swprintf(_w_str + wcslen(_w_str), TEXT("%s[%s:0x%08X]"),
						attr_apply_prefix, ev_attr_idx_prefix, _ev_attr_info_list[i]._attr_idx);
					memcpy(_w_str + wcslen(_w_str),
						_w_str_2 + (_ev_attr_info_list[i]._start_txt_pos + _accmul_txt_pos),
						(sizeof(wchar_t) * (_ev_attr_info_list[i]._end_txt_pos - _ev_attr_info_list[i]._start_txt_pos)));
					swprintf(_w_str + wcslen(_w_str), TEXT("%s"), attr_apply_prefix);
					memcpy(_w_str + wcslen(_w_str),
						_w_str_2 + ((_ev_attr_info_list[i]._end_txt_pos) + _accmul_txt_pos),
						(sizeof(wchar_t) * (wcslen(_w_str_2) - ((_ev_attr_info_list[i]._end_txt_pos) + _accmul_txt_pos))));
					//*���������鼭 �߰���, �������� ����ذ��鼭 �����ؾ� ��
					_accmul_txt_pos += ((wcslen(attr_apply_prefix) * 2) + wcslen(ev_attr_idx_prefix) + 13);
					//*������ �÷���
					free(_w_str_2); _w_str_2 = _w_str;
					//*���� ���� �����ϰ� �ٲ�ġ��
				}
				//*_str�� Ȯ���� �Ӽ� ������ �̿��ؼ� �߰��߰� ���ڿ��� ��������
			}

			swprintf(_txt_buf + wcslen(_txt_buf),
				TEXT("[0x%08X][0x%08X]%s%s%s[%s:0x%08X]%s"),
				_i_3, _extra_data, text_prefix, _w_str, text_prefix, ev_attr_def_idx_prefix, _default_attr_idx, _enter_raw_);
			free(_w_str);
			break;
			//* TYPE_EV_OP_CHAR�� �� : _i_3, _extra_data, _str, _i �̿�
			//* �׵��� �ôµ� ���⼭�� �ڵ� ��ġ�� �ʿ����
		}
		case TYPE_EV_OP_ALIGN:
		case TYPE_EV_OP_RETURN:
		{
			if (_unk_1 != 0) {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%02X][0x%08X][0x%08X][0x%02X]%s"),
					_unk_t2_t3._unk_1, _unk_t2_t3._unk_2, _unk_t2_t3._unk_3, _b, _enter_raw_);
			}
			else {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%02X]%s"), _b, _enter_raw_);
			}
			break;
			//* TYPE_EV_OP_ALIGN / TYPE_EV_OP_RETURN�� �� : _unk_t2_t3, _b �̿�
		}
		case TYPE_EV_OP_INDENT:
		case TYPE_EV_OP_UNDENT:
		{
			break;
			//* TYPE_EV_OP_INDENT / TYPE_EV_OP_UNDENT�� �� : �̿����� ����
		}
		case TYPE_EV_OP_EVENT:
		{
			_w_str_2 = _str;
			_ww_str_2 = Replace_Text(_w_str_2, hex_1_raw, hex_1_plained);
			_w_str_2 = Replace_Text(_ww_str_2, _enter_raw_, _enter_plained_); free(_ww_str_2);
			//*�ڵ� ��ȯ �� ��ġ

			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%s%s%s"), text_prefix, _w_str_2, text_prefix, _enter_raw_);
			free(_w_str_2);
			break;
			//* TYPE_EV_OP_EVENT�� �� : _str �̿� (��ġ �ʿ�)
		}
		case TYPE_EV_OP_VAR:
		{
			if (_tpword_ver < 0x65) {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%s%s[%s:0x%08X]%s"), text_prefix, _str, text_prefix, ev_attr_def_idx_prefix, _default_attr_idx, _enter_raw_);
			}
			else if (_tpword_ver >= 0x66) {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%08X]%s%s%s%s%s%s[%s:0x%08X]%s"),
					_i_2, text_prefix, _s, text_prefix, text_prefix, _str, text_prefix, ev_attr_def_idx_prefix, _default_attr_idx, _enter_raw_);
			}
			else {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%08X]%s%s%s[%s:0x%08X]%s"),
					_i_2, text_prefix, _s, text_prefix, ev_attr_def_idx_prefix, _default_attr_idx, _enter_raw_);
			}
			break;
			//* TYPE_EV_OP_VAR�� �� : ver < 0x65[_str, _i �̿�], 0x65 <= ver[_i, _i_2, _s �̿�], 0x66 <= ver[_i, _i_2, _s, _str �̿�]
			//* �ƹ����� ��ȯ�� �� �ʿ䰡 ���� �� ����
		}
		case TYPE_EV_OP_IMG:
		{
			if (_tpword_ver < 0x69) {
				swprintf(_txt_buf + wcslen(_txt_buf), TEXT("[0x%08X][0x%08X]%s%s%s[0x%02X]%s"),
					_i_2, _extra_data, text_prefix, _str, text_prefix, _b, _enter_raw_);
			}
			else {
				swprintf(_txt_buf + wcslen(_txt_buf),
					TEXT("[0x%08X][0x%08X]%s%s%s::[0x%08X][0x%08X][0x%08X][0x%08X][0x%08X][0x%08X]::[0x%02X]%s"),
					_i_2, _extra_data, text_prefix, _str, text_prefix,
					_unk_i_list[0], _unk_i_list[1], _unk_i_list[2], _unk_i_list[3], _unk_i_list[4], _unk_i_list[5],
					_b, _enter_raw_);
			}
			break;
			//* TYPE_EV_OP_IMG�� �� : _i_2, _extra_data, _str, _b �̿�
			//* �ƹ����� ��ȯ�� �� �ʿ䰡 ���� �� ����
			//* ������ 105 �̻��̸� ���� 6�� �߰�
		}
		case TYPE_EV_OP_HISTORY_CHAR:
		{
			swprintf(_txt_buf + wcslen(_txt_buf),
				TEXT("[0x%08X][0x%08X]%s%s%s[%s:0x%08X]%s"),
				_i_3, _i_2, text_prefix, _str, text_prefix, ev_attr_def_idx_prefix, _default_attr_idx, _enter_raw_);
			break;
			//* TYPE_EV_OP_HISTORY_CHAR�� �� : _s...�� �ƴ϶� _i_3, _i, _i_2, _str �̿�
			//* �Լ� ȣ������γ� ���̴� ��ȯ�� �ʿ䰡 ���� �� ����
		}
		default:
		{
			_w_str_2 = _str;
			_ww_str_2 = Replace_Text(_w_str_2, hex_1_raw, hex_1_plained);
			_w_str_2 = Replace_Text(_ww_str_2, _enter_raw_, _enter_plained_); free(_ww_str_2);
			//*�ڵ� ��ȯ �� ��ġ

			swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s%s%s%s"), text_prefix, _w_str_2, text_prefix, _enter_raw_);
			free(_w_str_2);
			break;
			//* �̿��� ��� : _str �̿�
		}
	}
}
//*�̺�Ʈ ���� ���� : �ؽ�Ʈ ���� �Լ�


void LSB_EVENT_OP_INST::_replace_text(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int* accum_count)
{
	if (_op_type == TYPE_EV_OP_CHAR) {

		if (is_Pure_Ascii_String(_str) || is_File_Path_String(_str)) { return; }
		//*���� ��ġ�� �ʿ� ������ ��ġ���� ����

		wchar_t* cp_str = txt_list_elem->_txt_list_per_inst[(*accum_count)++];
		wchar_t* n_str = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(cp_str) + 1));
		n_str[wcslen(cp_str)] = 0;
		memcpy(n_str, cp_str, (sizeof(wchar_t) * wcslen(cp_str)));
		if (_str != NULL) { free(_str); }
		_str = n_str;
		//*�޸� ���� �� ��ġ
		//*���⼭ 0x01, \r\n ���ڿ� ��ġ�� ���� �� �ʿ䰡 ���� �� �ϴ�

	}
	//*Ư���� char�� ����
}
//*�̺�Ʈ ���� ���� : �ؽ�Ʈ ��ü �Լ�


void LSB_EVENT_OP_INST::_change_code_J2K()
{
	JPHan_2_KRHan(_s);
	JPHan_2_KRHan(_str);
}
//*�̺�Ʈ ���� ���� : �ؽ�Ʈ �ڵ� ���� �Լ�


void LSB_EV_TXT_ATTRIBUTE::_read_var_data(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);

	unsigned int* _int;
	unsigned char* _c;
	char* __s;

	_int = _get_int(&lsb_buffer_pnt);
	_ev_op_ref_count = *_int; free(_int);
	//*�ؽ�Ʈ Ŀ�ǵ�? �о���̱�

	_int = _get_int(&lsb_buffer_pnt);
	_txt_color = *_int; free(_int);
	_int = _get_int(&lsb_buffer_pnt);
	_unk_2 = *_int; free(_int);
	_int = _get_int(&lsb_buffer_pnt);
	_unk_3 = *_int; free(_int);
	//*�𸣴� ���� 1, 2, 3

	_c = _get_byte(&lsb_buffer_pnt);
	_unk_4 = *_c; free(_c);
	_c = _get_byte(&lsb_buffer_pnt);
	_unk_5 = *_c; free(_c);
	//*�𸣴� ���� 4, 5

	_unk_6 = 0;
	if (_tpword_ver < 0x64) {
		_c = _get_byte(&lsb_buffer_pnt);
		_unk_6 = *_c; free(_c);
	}
	//*������ ���� �𸣴� �� 6

	_int = _get_int(&lsb_buffer_pnt);
	_unk_7 = *_int; free(_int);
	//*�𸣴� �� 7

	__s = _get_str(&lsb_buffer_pnt);
	_font_name = GetUniStr (__s, code);
	free(__s);
	__s = _get_str(&lsb_buffer_pnt);
	_ruby_txt = GetUniStr(__s, code);
	free(__s);
	//*�𸣴� �� 8, 9

	_unk_10 = _unk_11 = 0;
	if (_tpword_ver >= 0x64) {
		_int = _get_int(&lsb_buffer_pnt);
		_unk_10 = *_int; free(_int);
		_int = _get_int(&lsb_buffer_pnt);
		_unk_11 = *_int; free(_int);
	}
	//*������ ���� �𸣴� �� 10, 11

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*�̺�Ʈ ���� �Ӽ� ������ �б�


void LSB_EV_TXT_ATTRIBUTE::_decompile_code(HANDLE hWrite, unsigned int code, unsigned int _indent)
{
	for (unsigned int j = 0; j < (_indent); j++) { swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_); }
	//*�鿩���� ���

	swprintf(_txt_buf + wcslen(_txt_buf),
		TEXT("[%s]::[%s:0x%08X][0x%08X][0x%08X][0x%02X][0x%02X][0x%02X][0x%08X][%s]%s%s%s[%s]%s%s%s[0x%08X][0x%08X]%s"),
		refer_attr_prefix, color_prefix, _txt_color, _unk_2, _unk_3, _unk_4, _unk_5, _unk_6, _unk_7,
		font_prefix, text_prefix, _font_name, text_prefix, ruby_txt_prefix, text_prefix, _ruby_txt, text_prefix,
		_unk_10, _unk_11, _enter_raw_);
	//*11�� �� ������� ���
}
//*�̺�Ʈ ���� �Ӽ� : �������� �Լ�


void LSB_EV_TXT_ATTRIBUTE::_recompile_from_txt(wchar_t* _code_txt_buffer)
{
	wchar_t* _code_txt_pnt = _code_txt_buffer, *_code_txt_pnt_2 = _code_txt_buffer, *_swp;
	wchar_t _buf_for_int[11];
	wchar_t _buf_for_byte[5];
	memset(_buf_for_int, 0, (sizeof(wchar_t) * 11));
	memset(_buf_for_byte, 0, (sizeof(wchar_t) * 5));

	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, color_prefix) + wcslen(color_prefix) + wcslen(TEXT(":"));
	memcpy(_buf_for_int, _code_txt_pnt_2, (sizeof(wchar_t) * 10));
	_txt_color = wcstoul(_buf_for_int, NULL, 16);
	//*color

	_code_txt_pnt = wcsstr(_code_txt_pnt_2, TEXT("[")) + wcslen(TEXT("["));
	memcpy(_buf_for_int, _code_txt_pnt, (sizeof(wchar_t) * 10));
	_unk_2 = wcstoul(_buf_for_int, NULL, 16);
	//*unk_2

	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, TEXT("[")) + wcslen(TEXT("["));
	memcpy(_buf_for_int, _code_txt_pnt_2, (sizeof(wchar_t) * 10));
	_unk_3 = wcstoul(_buf_for_int, NULL, 16);
	//*unk_3

	_code_txt_pnt = wcsstr(_code_txt_pnt_2, TEXT("[")) + wcslen(TEXT("["));
	memcpy(_buf_for_byte, _code_txt_pnt, (sizeof(wchar_t) * 4));
	_unk_4 = (unsigned char)wcstoul(_buf_for_byte, NULL, 16);
	//*unk_4

	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, TEXT("[")) + wcslen(TEXT("["));
	memcpy(_buf_for_byte, _code_txt_pnt_2, (sizeof(wchar_t) * 4));
	_unk_5 = (unsigned char)wcstoul(_buf_for_byte, NULL, 16);
	//*unk_5
	
	_code_txt_pnt = wcsstr(_code_txt_pnt_2, TEXT("[")) + wcslen(TEXT("["));
	memcpy(_buf_for_byte, _code_txt_pnt, (sizeof(wchar_t) * 4));
	if (_tpword_ver < 0x64) {
		_unk_6 = (unsigned char)wcstoul(_buf_for_byte, NULL, 16);
	}
	_swp = _code_txt_pnt;
	_code_txt_pnt = _code_txt_pnt_2;
	_code_txt_pnt_2 = _swp;
	//*unk_6 (_tpword_ver < 0x64)

	_code_txt_pnt = wcsstr(_code_txt_pnt_2, TEXT("[")) + wcslen(TEXT("["));
	memcpy(_buf_for_int, _code_txt_pnt, (sizeof(wchar_t) * 10));
	_unk_7 = wcstoul(_buf_for_int, NULL, 16);
	//*unk_7

	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, font_prefix) + wcslen(font_prefix);
	_code_txt_pnt = wcsstr(_code_txt_pnt_2, text_prefix) + wcslen(text_prefix);
	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, text_prefix);
	_font_name = (wchar_t*)malloc(sizeof(wchar_t) * (_code_txt_pnt_2 - _code_txt_pnt + 1));
	memset(_font_name, 0, (sizeof(wchar_t) * (_code_txt_pnt_2 - _code_txt_pnt + 1)));
	memcpy(_font_name, _code_txt_pnt, (sizeof(wchar_t) * (_code_txt_pnt_2 - _code_txt_pnt)));
	_code_txt_pnt_2 += wcslen(text_prefix);
	_swp = _code_txt_pnt;
	_code_txt_pnt = _code_txt_pnt_2;
	_code_txt_pnt_2 = _swp;
	//*font

	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, ruby_txt_prefix) + wcslen(ruby_txt_prefix);
	_code_txt_pnt = wcsstr(_code_txt_pnt_2, text_prefix) + wcslen(text_prefix);
	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, text_prefix);
	_ruby_txt = (wchar_t*)malloc(sizeof(wchar_t) * (_code_txt_pnt_2 - _code_txt_pnt + 1));
	memset(_ruby_txt, 0, (sizeof(wchar_t) * (_code_txt_pnt_2 - _code_txt_pnt + 1)));
	memcpy(_ruby_txt, _code_txt_pnt, (sizeof(wchar_t) * (_code_txt_pnt_2 - _code_txt_pnt)));
	_code_txt_pnt_2 += wcslen(text_prefix);
	//*ruby_txt
	
	_code_txt_pnt = wcsstr(_code_txt_pnt_2, TEXT("[")) + wcslen(TEXT("["));
	memcpy(_buf_for_int, _code_txt_pnt, (sizeof(wchar_t) * 10));
	if (_tpword_ver >= 0x64) {
		_unk_10 = wcstoul(_buf_for_int, NULL, 16);
	}
	//*unk_10 (_tpword_ver >= 0x64)

	_code_txt_pnt_2 = wcsstr(_code_txt_pnt, TEXT("[")) + wcslen(TEXT("["));
	memcpy(_buf_for_int, _code_txt_pnt_2, (sizeof(wchar_t) * 10));
	if (_tpword_ver >= 0x64) {
		_unk_11 = wcstoul(_buf_for_int, NULL, 16);
	}
	//*unk_11 (_tpword_ver >= 0x64)
	//*������� �о���̸� �ȴ�
}
//*�̺�Ʈ ���� �Ӽ� : �������� �Լ� (���� : �ش� �̺�Ʈ ���� �����Ͱ� ����ִ� �ؽ�Ʈ ������ �Ϻ�)


void LSB_EV_TXT_ATTRIBUTE::_write_as_lsb(HANDLE hNewLsb, unsigned int code)
{
	char* __s;
	_write_int(hNewLsb, _ev_op_ref_count);
	_write_int(hNewLsb, _txt_color);
	_write_int(hNewLsb, _unk_2);
	_write_int(hNewLsb, _unk_3);
	_write_byte(hNewLsb, _unk_4);
	_write_byte(hNewLsb, _unk_5);

	if (_tpword_ver < 0x64) {
		_write_byte(hNewLsb, _unk_6);
	}

	_write_int(hNewLsb, _unk_7);

	__s = GetAnsiStr(_font_name, code);
	_write_str(hNewLsb, __s);
	free(__s);

	__s = GetAnsiStr(_ruby_txt, code);
	_write_str(hNewLsb, __s);
	free(__s);

	if (_tpword_ver >= 0x64) {
		_write_int(hNewLsb, _unk_10);
		_write_int(hNewLsb, _unk_11);
	}
	//*11�� �� ������� ���
}
//*�̺�Ʈ ���� �Ӽ� : lsb ���Ϸ� ����ϴ� �Լ�


void LSB_EV_TXT_ATTRIBUTE::_extract_text(HANDLE hTxt)
{
	for (unsigned int i = 0; i < 2;i++) {
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s"), _indent_);
	}
	//*�鿩���� 2��

	swprintf(_txt_buf + wcslen(_txt_buf),
		TEXT("[%s]::[%s:0x%08X][0x%08X][0x%08X][0x%02X][0x%02X][0x%02X][0x%08X][%s]%s%s%s[%s]%s%s%s[0x%08X][0x%08X]%s"),
		refer_attr_prefix, color_prefix, _txt_color, _unk_2, _unk_3, _unk_4, _unk_5, _unk_6, _unk_7,
		font_prefix, text_prefix, _font_name, text_prefix, ruby_txt_prefix, text_prefix, _ruby_txt, text_prefix,
		_unk_10, _unk_11, _enter_raw_);
	//*����� �ֱ�
}
//*�̺�Ʈ ���� ���� : �ؽ�Ʈ ���� �Լ�


void LSB_EV_TXT_ATTRIBUTE::_change_code_J2K()
{
	JPHan_2_KRHan(_font_name);
	JPHan_2_KRHan(_ruby_txt);
}
//*�̺�Ʈ ���� ���� : �ؽ�Ʈ �ڵ� ���� �Լ�
//---------------------------- �̺�Ʈ ���� Ŭ���� ----------------------------//