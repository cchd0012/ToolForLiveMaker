#include "LM_Script_LSB.h"
#include "LM_Functions.h"


#pragma warning (disable:6031)
#pragma warning (disable:4996)

//*** lsb ��ũ��Ʈ�� ��ɾ�鸸�� ���ͼ� �����ϴ� ����


//---------------------------- if ��ɾ� ----------------------------//
LSB_INST_IF::LSB_INST_IF (LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER *_header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("Calc"))
}
//*������

void LSB_INST_IF::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Calc");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Calc"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_IF::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_IF::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	LSB_PARAMETERS* _t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	unsigned int accum_count = 0;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- if ��ɾ� ----------------------------//



//---------------------------- elif ��ɾ� ----------------------------//
LSB_INST_ELIF::LSB_INST_ELIF(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("Calc"))
}
//*������

void LSB_INST_ELIF::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Calc");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Calc"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_ELIF::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_ELIF::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	LSB_PARAMETERS* _t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	unsigned int accum_count = 0;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- elif ��ɾ� ----------------------------//



//---------------------------- else ��ɾ� ----------------------------//
LSB_INST_ELSE::LSB_INST_ELSE(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	//*�ʿ��� �з����� ����Ʈ �� : 0��
}
//*������

void LSB_INST_ELSE::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_ELSE::_extract_text_each_inst(HANDLE hTxt)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_ELSE::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- else ��ɾ� ----------------------------//



//---------------------------- label ��ɾ� ----------------------------//
LSB_INST_LABEL::LSB_INST_LABEL(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("Label"))
}
//*������

void LSB_INST_LABEL::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	char* _s;

	_data_chunks[0]._str = TEXT("Label");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[0]._data = GetUniStr (_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Label"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_LABEL::_extract_text_each_inst(HANDLE hTxt)
{
	wchar_t* _print_str;
	
	_print_str = (wchar_t*)_data_chunks[0]._data;
	if (!is_Pure_Ascii_String(_print_str) && !is_File_Path_String(_print_str)) {
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[%s]%s%s%s%s"),
			_indent_, text_data_prefix, text_prefix, _print_str, text_prefix, _enter_raw_);
	}
	//*������ �ʿ䰡 ���� ���� ���
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_LABEL::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	wchar_t* cp_txt, *n_txt;

	if (!is_Pure_Ascii_String((wchar_t*)_data_chunks[0]._data)
		&& !is_File_Path_String((wchar_t*)_data_chunks[0]._data)) {
		if (_data_chunks[0]._data != NULL) { free(_data_chunks[0]._data); }
		//*�̹� �����Ͱ� ������ ������
		cp_txt = txt_list_elem->_txt_list_per_inst[0];
		n_txt = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(cp_txt) + 1));
		n_txt[wcslen(cp_txt)] = 0;
		memcpy(n_txt, cp_txt, (sizeof(wchar_t) * wcslen(cp_txt)));
		_data_chunks[0]._data = n_txt;
		//*�޸� ���� �� ��ġ
	}
	//*������ �ʿ䰡 ���� ���� ��ġ�Ѵ�
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- label ��ɾ� ----------------------------//



//---------------------------- jump ��ɾ� ----------------------------//
LSB_INST_JUMP::LSB_INST_JUMP(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 3;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 3�� (TEXT("Script_Page"), TEXT("Target_Label_Offset"), TEXT("Calc"))
}
//*������

void LSB_INST_JUMP::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;
	char* _s;

	_data_chunks[0]._str = TEXT("Script_Page");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[0]._data = GetUniStr(_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Script_Page"))

	_data_chunks[1]._str = TEXT("Target_Label_Offset");
	_data_chunks[1]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Target_Label_Offset"))

	_data_chunks[2]._str = TEXT("Calc");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[2]._data = _pnt;
	//* ������ �о���̱� (TEXT("Calc"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_JUMP::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt = (LSB_PARAMETERS*)_data_chunks[2]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_JUMP::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	LSB_PARAMETERS* _t = (LSB_PARAMETERS*)_data_chunks[2]._data;
	unsigned int accum_count = 0;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- jump ��ɾ� ----------------------------//



//---------------------------- call ��ɾ� ----------------------------//
LSB_INST_CALL::LSB_INST_CALL(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 5;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : ��������
	//*TEXT("Script_Page"), TEXT("Target_Label_Offset"), TEXT("Result"), TEXT("Calc"), TEXT("Parameter_Count") ���� ���ڿ� ���� �޶���
	//*���� 5���� �Ҵ��� �� �ٽ� �ű�� ������ �ؾ� �� �� �ϴ�
}
//*������

void LSB_INST_CALL::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;
	char* _s;

	_data_chunks[0]._str = TEXT("Script_Page");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[0]._data = GetUniStr(_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Script_Page"))

	_data_chunks[1]._str = TEXT("Target_Label_Offset");
	_data_chunks[1]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Target_Label_Offset"))

	_data_chunks[2]._str = TEXT("Result");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[2]._data = GetUniStr(_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Result"))

	_data_chunks[3]._str = TEXT("Calc");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[3]._data = _pnt;
	//* ������ �о���̱� (TEXT("Calc"))

	_data_chunks[4]._str = TEXT("Parameter_Count");
	_data_chunks[4]._data = _get_int(&lsb_buffer_pnt);;
	//* ������ �о���̱� (TEXT("Parameter_Count"))
	
	unsigned int _param_count = *(unsigned int*)_data_chunks[4]._data;
	LSB_MAP_DATA *_n_map = _get_initialized_data_chunks (_data_chunks_count + _param_count);
	memcpy(_n_map, _data_chunks, (sizeof(LSB_MAP_DATA) * _data_chunks_count));
	for (unsigned int i = 0; i < _param_count;i++) {
		_n_map[_data_chunks_count + i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_n_map[_data_chunks_count + i]._data = _pnt;
	}
	//* ����� �� ������� �Ҵ� �� ���� �� ���� �о���̱�

	_data_chunks_count += _param_count;
	free(_data_chunks);
	_data_chunks = _n_map;
	//*�ٽ� ����

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_CALL::_extract_text_each_inst(HANDLE hTxt)
{
	unsigned int _param_cnt = *(unsigned int*)_data_chunks[4]._data;
	//*���� �� �ľ�
	for (unsigned int i = 0; i < _param_cnt; i++) {
		LSB_PARAMETERS* _pnt = (LSB_PARAMETERS*)_data_chunks[5 + i]._data;
		_pnt->_extract_text(hTxt);
		//*�з����� ����Ʈ���� ����
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_CALL::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int _param_cnt = *(unsigned int*)_data_chunks[4]._data;
	//*���� �� �ľ�
	unsigned int accum_count = 0;
	for (unsigned int i = 0; i < _param_cnt; i++) {
		LSB_PARAMETERS* _pnt = (LSB_PARAMETERS*)_data_chunks[5 + i]._data;
		_pnt->_replace_text(txt_list_elem, &accum_count);
		//*�з����� ����Ʈ���� ��ġ
	}
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- call ��ɾ� ----------------------------//



//---------------------------- exit ��ɾ� ----------------------------//
LSB_INST_EXIT::LSB_INST_EXIT(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("Calc"))
}
//*������

void LSB_INST_EXIT::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Calc");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Calc"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_EXIT::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_EXIT::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	LSB_PARAMETERS* _t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	unsigned int accum_count = 0;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- exit ��ɾ� ----------------------------//



//---------------------------- wait ��ɾ� ----------------------------//
LSB_INST_WAIT::LSB_INST_WAIT(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 2;
	if (_script_ver >= 0x6B) { _data_chunks_count++; }
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 2�� Ȥ�� 3�� (TEXT("Calc"), TEXT("Time"), ������ ���� TEXT("StopEvent"))
}
//*������

void LSB_INST_WAIT::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Calc");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Calc"))

	_data_chunks[1]._str = TEXT("Time");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[1]._data = _pnt;
	//* ������ �о���̱� (TEXT("Time"))

	if (_script_ver >= 0x6B) {
		_data_chunks[2]._str = TEXT("StopEvent");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[2]._data = _pnt;
	}
	//*������ ���� �߰��� �� ����

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_WAIT::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)

	_pnt = (LSB_PARAMETERS*)_data_chunks[1]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)

	if (_script_ver >= 0x6B) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[2]._data;
		_pnt->_extract_text(hTxt);
	}
	//*(���� ����) ���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_WAIT::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ

	_t = (LSB_PARAMETERS*)_data_chunks[1]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ

	if (_script_ver >= 0x6B) {
		_t = (LSB_PARAMETERS*)_data_chunks[2]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*(���� ����)�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- wait ��ɾ� ----------------------------//



//---------------------------- timer ��ɾ� ----------------------------//
LSB_INST_TIMER::LSB_INST_TIMER(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8);i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_TIMER::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_TIMER::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_TIMER::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- timer ��ɾ� ----------------------------//



//---------------------------- caculation function(Ư���Լ�) ��ɾ� ----------------------------//
LSB_INST_CALC_FUNC::LSB_INST_CALC_FUNC(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("Calc"))
}
//*������

void LSB_INST_CALC_FUNC::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Calc");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Calc"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_CALC_FUNC::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_CALC_FUNC::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	LSB_PARAMETERS* _t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	unsigned int accum_count = 0;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- caculation function(Ư���Լ�) ��ɾ� ----------------------------//



//---------------------------- box_new ��ɾ� ----------------------------//
LSB_INST_BOX_NEW::LSB_INST_BOX_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_BOX_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_BOX_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_BOX_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- box_new ��ɾ� ----------------------------//



//---------------------------- image_new ��ɾ� ----------------------------//
LSB_INST_IMAGE_NEW::LSB_INST_IMAGE_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_IMAGE_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_IMAGE_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_IMAGE_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- image_new ��ɾ� ----------------------------//



//---------------------------- message_new ��ɾ� ----------------------------//
LSB_INST_MESSAGE_NEW::LSB_INST_MESSAGE_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_MESSAGE_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MESSAGE_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MESSAGE_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- message_new ��ɾ� ----------------------------//



//---------------------------- particle_new ��ɾ� ----------------------------//
LSB_INST_PARTICLE_NEW::LSB_INST_PARTICLE_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_PARTICLE_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_PARTICLE_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_PARTICLE_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- particle_new ��ɾ� ----------------------------//



//---------------------------- fire_new ��ɾ� ----------------------------//
LSB_INST_FIRE_NEW::LSB_INST_FIRE_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_FIRE_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_FIRE_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_FIRE_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- fire_new ��ɾ� ----------------------------//



//---------------------------- edit_new ��ɾ� ----------------------------//
LSB_INST_EDIT_NEW::LSB_INST_EDIT_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_EDIT_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_EDIT_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_EDIT_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- edit_new ��ɾ� ----------------------------//



//---------------------------- memo_new ��ɾ� ----------------------------//
LSB_INST_MEMO_NEW::LSB_INST_MEMO_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_MEMO_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MEMO_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MEMO_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- memo_new ��ɾ� ----------------------------//



//---------------------------- map_image_new ��ɾ� ----------------------------//
LSB_INST_MAP_IMAGE_NEW::LSB_INST_MAP_IMAGE_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_MAP_IMAGE_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MAP_IMAGE_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MAP_IMAGE_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- map_image_new ��ɾ� ----------------------------//



//---------------------------- wave_new ��ɾ� ----------------------------//
LSB_INST_WAVE_NEW::LSB_INST_WAVE_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_WAVE_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_WAVE_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_WAVE_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- wave_new ��ɾ� ----------------------------//



//---------------------------- tile_new ��ɾ� ----------------------------//
LSB_INST_TILE_NEW::LSB_INST_TILE_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_TILE_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_TILE_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_TILE_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- tile_new ��ɾ� ----------------------------//



//---------------------------- slider_new ��ɾ� ----------------------------//
LSB_INST_SLIDER_NEW::LSB_INST_SLIDER_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_SLIDER_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_SLIDER_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_SLIDER_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- slider_new ��ɾ� ----------------------------//



//---------------------------- scroll_bar_new ��ɾ� ----------------------------//
LSB_INST_SCROLL_BAR_NEW::LSB_INST_SCROLL_BAR_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_SCROLL_BAR_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_SCROLL_BAR_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_SCROLL_BAR_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- scroll_bar_new ��ɾ� ----------------------------//



//---------------------------- gauge_new ��ɾ� ----------------------------//
LSB_INST_GAUGE_NEW::LSB_INST_GAUGE_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_GAUGE_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_GAUGE_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_GAUGE_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- gauge_new ��ɾ� ----------------------------//



//---------------------------- prev_menu_new ��ɾ� ----------------------------//
LSB_INST_PREV_MENU_NEW::LSB_INST_PREV_MENU_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_PREV_MENU_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_PREV_MENU_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_PREV_MENU_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- prev_menu_new ��ɾ� ----------------------------//



//---------------------------- var_new ��ɾ� ----------------------------//
LSB_INST_VAR_NEW::LSB_INST_VAR_NEW(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 4;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 4�� (TEXT("Var_Name"), TEXT("Var_Type"), TEXT("Var_Initlal_Value"), TEXT("Var_Scope_Byte"))
}
//*������

void LSB_INST_VAR_NEW::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;
	char* _s;

	_data_chunks[0]._str = TEXT("Var_Name");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[0]._data = GetUniStr (_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Var_Name"))

	_data_chunks[1]._str = TEXT("Var_Type");
	_data_chunks[1]._data = _get_byte(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Var_Type"))

	_data_chunks[2]._str = TEXT("Var_Initlal_Value");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[2]._data = _pnt;
	//* ������ �о���̱� (TEXT("Var_Initlal_Value"))

	_data_chunks[3]._str = TEXT("Var_Scope_Byte");
	_data_chunks[3]._data = _get_byte(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Var_Scope_Byte"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_VAR_NEW::_extract_text_each_inst(HANDLE hTxt)
{
	wchar_t* _print_str;
	LSB_PARAMETERS* _pnt;

	_print_str = (wchar_t*)_data_chunks[0]._data;
	if (!is_Pure_Ascii_String(_print_str) && !is_File_Path_String(_print_str)) {
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[%s]%s%s%s%s"),
			_indent_, text_data_prefix, text_prefix, _print_str, text_prefix, _enter_raw_);
	}
	//*������ �ʿ䰡 ���� ���� ���

	_pnt = (LSB_PARAMETERS*)_data_chunks[2]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_VAR_NEW::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;
	wchar_t* cp_txt, * n_txt;

	if (!is_Pure_Ascii_String((wchar_t*)_data_chunks[0]._data)
		&& !is_File_Path_String((wchar_t*)_data_chunks[0]._data)) {
		if (_data_chunks[0]._data != NULL) { free(_data_chunks[0]._data); }
		//*�̹� �����Ͱ� ������ ������
		cp_txt = txt_list_elem->_txt_list_per_inst[0];
		n_txt = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(cp_txt) + 1));
		n_txt[wcslen(cp_txt)] = 0;
		memcpy(n_txt, cp_txt, (sizeof(wchar_t) * wcslen(cp_txt)));
		_data_chunks[0]._data = n_txt;
		//*�޸� ���� �� ��ġ
		accum_count++;
	}
	//*������ �ʿ䰡 ���� ���� ��ġ�Ѵ�

	_t = (LSB_PARAMETERS*)_data_chunks[2]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- var_new ��ɾ� ----------------------------//



//---------------------------- var_delete ��ɾ� ----------------------------//
LSB_INST_VAR_DELETE::LSB_INST_VAR_DELETE(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("Var_Name"))
}
//*������

void LSB_INST_VAR_DELETE::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
//	LSB_PARAMETERS* _pnt;
	char* _s;

	_data_chunks[0]._str = TEXT("Var_Name");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[0]._data = GetUniStr(_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Var_Name"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_VAR_DELETE::_extract_text_each_inst(HANDLE hTxt)
{
	wchar_t* _print_str;

	_print_str = (wchar_t*)_data_chunks[0]._data;
	if (!is_Pure_Ascii_String(_print_str) && !is_File_Path_String(_print_str)) {
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[%s]%s%s%s%s"),
			_indent_, text_data_prefix, text_prefix, _print_str, text_prefix, _enter_raw_);
	}
	//*������ �ʿ䰡 ���� ���� ���
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_VAR_DELETE::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	wchar_t* cp_txt, * n_txt;

	if (!is_Pure_Ascii_String((wchar_t*)_data_chunks[0]._data)
		&& !is_File_Path_String((wchar_t*)_data_chunks[0]._data)) {
		if (_data_chunks[0]._data != NULL) { free(_data_chunks[0]._data); }
		//*�̹� �����Ͱ� ������ ������
		cp_txt = txt_list_elem->_txt_list_per_inst[0];
		n_txt = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(cp_txt) + 1));
		n_txt[wcslen(cp_txt)] = 0;
		memcpy(n_txt, cp_txt, (sizeof(wchar_t) * wcslen(cp_txt)));
		_data_chunks[0]._data = n_txt;
		//*�޸� ���� �� ��ġ
		accum_count++;
	}
	//*������ �ʿ䰡 ���� ���� ��ġ�Ѵ�
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- var_delete ��ɾ� ----------------------------//



//---------------------------- movie ��ɾ� ----------------------------//
LSB_INST_MOVIE::LSB_INST_MOVIE(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_MOVIE::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MOVIE::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MOVIE::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- movie ��ɾ� ----------------------------//



//---------------------------- flip ��ɾ� ----------------------------//
LSB_INST_FLIP::LSB_INST_FLIP(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 8;
	if (_script_ver >= 0x65) { _data_chunks_count++; }
	if (_script_ver >= 0x6B) { _data_chunks_count++; }
	if (_script_ver >= LM_VERSION_3) { _data_chunks_count++; }
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (TEXT("Wipe"), TEXT("Time") �� �ּ� 8��)
	//(TEXT("Wipe"), TEXT("Time"), TEXT("Reverse"), TEXT("Act"), TEXT("Parameter_Count"), [�з����͸���Ʈ ����ŭ], TEXT("Delete"), TEXT("Item_1"), TEXT("Item_2"),
	// 0x65 �̻��̸� TEXT("Source") �߰�, 0x6B �̻��̸� TEXT("StopEvent") �߰�, 0x75 �̻��̸� TEXT("DifferenceOnly") �߰�)
}
//*������

void LSB_INST_FLIP::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Wipe");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Wipe"))

	_data_chunks[1]._str = TEXT("Time");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[1]._data = _pnt;
	//* ������ �о���̱� (TEXT("Time"))

	_data_chunks[2]._str = TEXT("Reverse");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[2]._data = _pnt;
	//* ������ �о���̱� (TEXT("Reverse"))

	_data_chunks[3]._str = TEXT("Act");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[3]._data = _pnt;
	//* ������ �о���̱� (TEXT("Act"))

	_data_chunks[4]._str = TEXT("Parameter_Count");
	_data_chunks[4]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Parameter_Count"))
	
	unsigned int _param_count = *(unsigned int*)_data_chunks[4]._data;
	LSB_MAP_DATA* _n_map = _get_initialized_data_chunks(_data_chunks_count + _param_count);
	memcpy(_n_map, _data_chunks, (sizeof(LSB_MAP_DATA) * 5));
	for (unsigned int i = 0; i < _param_count; i++) {
		_n_map[5 + i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_n_map[5 + i]._data = _pnt;
	}
	//* ����� �� ������� �Ҵ� �� ���� �� ���� �о���̱�

	_data_chunks_count += _param_count;
	free(_data_chunks);
	_data_chunks = _n_map;
	//*�ٽ� ����

	_data_chunks[(5 + _param_count)]._str = TEXT("Delete");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[(5 + _param_count)]._data = _pnt;
	//* ������ �о���̱� (TEXT("Delete"))

	_data_chunks[(5 + _param_count) + 1]._str = TEXT("Item_1");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[(5 + _param_count) + 1]._data = _pnt;
	//* ������ �о���̱� (TEXT("Item_1"))

	_data_chunks[(5 + _param_count) + 2]._str = TEXT("Item_2");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[(5 + _param_count) + 2]._data = _pnt;
	//* ������ �о���̱� (TEXT("Item_2"))

	if (_script_ver >= 0x65) {
		_data_chunks[(5 + _param_count) + 3]._str = TEXT("Source");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[(5 + _param_count) + 3]._data = _pnt;
	}
	//* 0x65 �̻��̸� ������ �о���̱� (TEXT("Source"))

	if (_script_ver >= 0x6B) {
		_data_chunks[(5 + _param_count) + 4]._str = TEXT("StopEvent");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[(5 + _param_count) + 4]._data = _pnt;
	}
	//* 0x6B �̻��̸� ������ �о���̱� (TEXT("StopEvent"))

	if (_script_ver >= LM_VERSION_3) {
		_data_chunks[(5 + _param_count) + 5]._str = TEXT("DifferenceOnly");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[(5 + _param_count) + 5]._data = _pnt;
	}
	//* 0x75 �̻��̸� ������ �о���̱� (TEXT("DifferenceOnly"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_FLIP::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < 4; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ����

	unsigned int _param_count = *(unsigned int*)_data_chunks[4]._data;
	for (unsigned int i = 0; i < _param_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[5 + i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��� �� ���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ����

	for (unsigned int i = (5 + _param_count); i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��� �� ���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_FLIP::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < 4; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ

	unsigned int _param_count = *(unsigned int*)_data_chunks[4]._data;
	for (unsigned int i = 0; i < _param_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[5 + i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*���� ��� �� �з����� ����Ʈ���� ��ġ

	for (unsigned int i = (5 + _param_count); i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*������ ���� �з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- flip ��ɾ� ----------------------------//



//---------------------------- movie_stop ��ɾ� ----------------------------//
LSB_INST_MOVIE_STOP::LSB_INST_MOVIE_STOP(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 3;
	if (_script_ver >= 0x6B) { _data_chunks_count++; }
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 3�� Ȥ�� 4�� (TEXT("Target"), TEXT("Time"), TEXT("Wait"), 0x6B �̻��̸� TEXT("DifferentVer")(?) �߰�)
}
//*������

void LSB_INST_MOVIE_STOP::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Target");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Target"))

	_data_chunks[1]._str = TEXT("Time");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[1]._data = _pnt;
	//* ������ �о���̱� (TEXT("Time"))

	_data_chunks[2]._str = TEXT("Wait");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[2]._data = _pnt;
	//* ������ �о���̱� (TEXT("Wait"))

	if (_script_ver >= 0x6B) {
		_data_chunks[3]._str = TEXT("DifferentVer");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[3]._data = _pnt;
	}
	//* 0x6B �̻��̸� ������ �о���̱� (TEXT("DifferentVer")(?))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MOVIE_STOP::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < 3; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ����

	if (_script_ver >= 0x6B) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[3]._data;
		_pnt->_extract_text(hTxt);
	}
	//*������ ���� ���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MOVIE_STOP::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < 3; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ

	if (_script_ver >= 0x6B) {
		_t = (LSB_PARAMETERS*)_data_chunks[3]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*������ ���� �з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- movie_stop ��ɾ� ----------------------------//



//---------------------------- cinema ��ɾ� ----------------------------//
LSB_INST_CINEMA::LSB_INST_CINEMA(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_CINEMA::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_CINEMA::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_CINEMA::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- cinema ��ɾ� ----------------------------//



//---------------------------- get_property ��ɾ� ----------------------------//
LSB_INST_GET_PROPERTY::LSB_INST_GET_PROPERTY(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 3;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 3�� (TEXT("ObjName"), TEXT("ObjProp"), TEXT("Var_Name"))
}
//*������

void LSB_INST_GET_PROPERTY::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;
	char* _s;

	_data_chunks[0]._str = TEXT("ObjName");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("ObjName"))

	_data_chunks[1]._str = TEXT("ObjProp");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[1]._data = _pnt;
	//* ������ �о���̱� (TEXT("ObjProp"))

	_data_chunks[2]._str = TEXT("Var_Name");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[2]._data = GetUniStr (_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Var_Name"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_GET_PROPERTY::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;
	wchar_t* _print_str;

	for (unsigned int i = 0; i < 2; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)

	_print_str = (wchar_t*)_data_chunks[2]._data;
	if (!is_Pure_Ascii_String(_print_str) && !is_File_Path_String(_print_str)) {
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[%s]%s%s%s%s"),
			_indent_, text_data_prefix, text_prefix, _print_str, text_prefix, _enter_raw_);
	}
	//*������ �ʿ䰡 ���� ���� ���
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_GET_PROPERTY::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;
	wchar_t* cp_txt, * n_txt;

	for (unsigned int i = 0; i < 2; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ

	if (!is_Pure_Ascii_String((wchar_t*)_data_chunks[2]._data)
		&& !is_File_Path_String((wchar_t*)_data_chunks[2]._data)) {
		if (_data_chunks[2]._data != NULL) { free(_data_chunks[2]._data); }
		//*�̹� �����Ͱ� ������ ������
		cp_txt = txt_list_elem->_txt_list_per_inst[accum_count];
		n_txt = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(cp_txt) + 1));
		n_txt[wcslen(cp_txt)] = 0;
		memcpy(n_txt, cp_txt, (sizeof(wchar_t) * wcslen(cp_txt)));
		_data_chunks[2]._data = n_txt;
		//*�޸� ���� �� ��ġ
		accum_count++;
	}
	//*������ �ʿ䰡 ���� ���� ��ġ�Ѵ�
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- get_property ��ɾ� ----------------------------//



//---------------------------- set_property ��ɾ� ----------------------------//
LSB_INST_SET_PROPERTY::LSB_INST_SET_PROPERTY(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 3;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 3�� (TEXT("ObjName"), TEXT("ObjProp"), TEXT("Set_Value"))
}
//*������

void LSB_INST_SET_PROPERTY::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("ObjName");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("ObjName"))

	_data_chunks[1]._str = TEXT("ObjProp");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[1]._data = _pnt;
	//* ������ �о���̱� (TEXT("ObjProp"))

	_data_chunks[2]._str = TEXT("Set_Value");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[2]._data = _pnt;
	//* ������ �о���̱� (TEXT("Set_Value"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_SET_PROPERTY::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < 3; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_SET_PROPERTY::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < 3; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- set_property ��ɾ� ----------------------------//



//---------------------------- object_delete ��ɾ� ----------------------------//
LSB_INST_OBJECT_DELETE::LSB_INST_OBJECT_DELETE(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("ObjName"))
}
//*������

void LSB_INST_OBJECT_DELETE::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("ObjName");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("ObjName"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_OBJECT_DELETE::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_OBJECT_DELETE::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- object_delete ��ɾ� ----------------------------//



//---------------------------- text_inst ��ɾ� ----------------------------//
LSB_INST_TEXT_INST::LSB_INST_TEXT_INST(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 4;
	if (_script_ver >= 0x6B) { _data_chunks_count++; }
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 4�� Ȥ�� 5�� (TEXT("Event_Block"), TEXT("Unknown_1"), TEXT("Unknown_2"), TEXT("Unknown_3"), ������ ���� TEXT("Unknown_4"))
}
//*������

void LSB_INST_TEXT_INST::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;
	LSB_EVENT* _pnt_e;

	_data_chunks[0]._str = TEXT("Event_Block");
	_pnt_e = new LSB_EVENT ();
	_pnt_e->_read_event_script(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt_e;
	//* ������ �о���̱� (TEXT("Event_Block"))

	_data_chunks[1]._str = TEXT("Unknown_1");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[1]._data = _pnt;
	//* ������ �о���̱� (TEXT("Unknown_1"))

	_data_chunks[2]._str = TEXT("Unknown_2");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[2]._data = _pnt;
	//* ������ �о���̱� (TEXT("Unknown_2"))

	_data_chunks[3]._str = TEXT("Unknown_3");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[3]._data = _pnt;
	//* ������ �о���̱� (TEXT("Unknown_3"))

	if (_script_ver >= 0x6B) {
		_data_chunks[4]._str = TEXT("Unknown_4");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[4]._data = _pnt;
	}
	//* 0x6B �̻��̸� ������ �о���̱� (TEXT("Unknown_4"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_TEXT_INST::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_EVENT* _t = (LSB_EVENT*)_data_chunks[0]._data;
	_t->_extract_text(hTxt);
	//*�ؽ�Ʈ ��ɾ� �� �̺�Ʈ �������� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_TEXT_INST::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	LSB_EVENT* _n_ev = new LSB_EVENT();
	LSB_EVENT* _t = (LSB_EVENT*)_data_chunks[0]._data;
	//*�̸� �غ�

	wchar_t* _tp = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_t->_tpword) + 1));
	memset(_tp, 0, (sizeof(wchar_t) * (wcslen(_t->_tpword) + 1)));
	memcpy(_tp, _t->_tpword, (sizeof(wchar_t) * wcslen(_t->_tpword)));
	_n_ev->_tpword = _tp;
	_tp = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(_t->_ver) + 1));
	memset(_tp, 0, (sizeof(wchar_t) * (wcslen(_t->_ver) + 1)));
	memcpy(_tp, _t->_ver, (sizeof(wchar_t) * wcslen(_t->_ver)));
	_n_ev->_ver = _tp;
	_n_ev->_tpword_ver = wcstol(_tp, NULL, 10);
	//*�ʿ��� ���鸸 deep copy�� �����ؿ�

	_n_ev->_recompile_from_txt(txt_list_elem->_txt_list_per_inst[0], code);
	//*���� ���� �ؽ�Ʈ�� �����̷� ���� �ؽ�Ʈ �ϳ����̴� �߰� �ɰ��� �ٽ� �������� ��

	delete _t;
	_data_chunks[0]._data = _n_ev;
	//*�׸��� ���� �̺�Ʈ �� ���� �� �̰����� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- text_inst ��ɾ� ----------------------------//



//---------------------------- text_clear ��ɾ� ----------------------------//
LSB_INST_TEXT_CLEAR::LSB_INST_TEXT_CLEAR(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("Target"))
}
//*������

void LSB_INST_TEXT_CLEAR::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Target");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Target"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_TEXT_CLEAR::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_TEXT_CLEAR::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- text_clear ��ɾ� ----------------------------//



//---------------------------- clear_history ��ɾ� ----------------------------//
LSB_INST_CLEAR_HISTORY::LSB_INST_CLEAR_HISTORY(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	//*�ʿ��� �з����� ����Ʈ �� : 0��
}
//*������

void LSB_INST_CLEAR_HISTORY::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_CLEAR_HISTORY::_extract_text_each_inst(HANDLE hTxt)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_CLEAR_HISTORY::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- clear_history ��ɾ� ----------------------------//



//---------------------------- call_history ��ɾ� ----------------------------//
LSB_INST_CALL_HISTORY::LSB_INST_CALL_HISTORY(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 4;
	if (_script_ver >= 0x6F) { _data_chunks_count++; }
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 4�� Ȥ�� 5�� (TEXT("Target"), TEXT("Index"), TEXT("Count"), TEXT("CutBreak"), ������ ���� TEXT("FormatName"))
}
//*������

void LSB_INST_CALL_HISTORY::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Target");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Target"))

	_data_chunks[1]._str = TEXT("Index");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[1]._data = _pnt;
	//* ������ �о���̱� (TEXT("Index"))

	_data_chunks[2]._str = TEXT("Count");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[2]._data = _pnt;
	//* ������ �о���̱� (TEXT("Count"))

	_data_chunks[3]._str = TEXT("CutBreak");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[3]._data = _pnt;
	//* ������ �о���̱� (TEXT("CutBreak"))

	if (_script_ver >= 0x6F) {
		_data_chunks[4]._str = TEXT("FormatName");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[4]._data = _pnt;
	}
	//* 0x6F �̻��̸� ������ �о���̱� (TEXT("FormatName"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_CALL_HISTORY::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < 4; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)

	if (_script_ver >= 0x6F) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[4]._data;
		_pnt->_extract_text(hTxt);
	}
	//*������ ���� ���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_CALL_HISTORY::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < 4; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ

	if (_script_ver >= 0x6F) {
		_t = (LSB_PARAMETERS*)_data_chunks[4]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*������ ���� �з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- call_history ��ɾ� ----------------------------//



//---------------------------- format_history ��ɾ� ----------------------------//
LSB_INST_FORMAT_HISTORY::LSB_INST_FORMAT_HISTORY(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	if (_script_ver >= 0x6F) { _data_chunks_count++; }
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� Ȥ�� 2�� (TEXT("Name"), ������ ���� TEXT("Unknown"))
}
//*������

void LSB_INST_FORMAT_HISTORY::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Name");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Name"))

	if (_script_ver >= 0x6F) {
		_data_chunks[1]._str = TEXT("Unknown");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[1]._data = _pnt;
	}
	//* 0x6F �̻��̸� ������ �о���̱� (TEXT("Unknown"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_FORMAT_HISTORY::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)

	if (_script_ver >= 0x6F) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[1]._data;
		_pnt->_extract_text(hTxt);
	}
	//*������ ���� ���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_FORMAT_HISTORY::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ

	if (_script_ver >= 0x6F) {
		_t = (LSB_PARAMETERS*)_data_chunks[1]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*������ ���� �з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- format_history ��ɾ� ----------------------------//



//---------------------------- caption ��ɾ� ----------------------------//
LSB_INST_CAPTION::LSB_INST_CAPTION(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_CAPTION::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_CAPTION::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_CAPTION::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- caption ��ɾ� ----------------------------//



//---------------------------- cg_caption ��ɾ� ----------------------------//
LSB_INST_CG_CAPTION::LSB_INST_CG_CAPTION(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_CG_CAPTION::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_CG_CAPTION::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_CG_CAPTION::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- cg_caption ��ɾ� ----------------------------//



//---------------------------- menu ��ɾ� ----------------------------//
LSB_INST_MENU::LSB_INST_MENU(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_MENU::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MENU::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MENU::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- menu ��ɾ� ----------------------------//



//---------------------------- menu_close ��ɾ� ----------------------------//
LSB_INST_MENU_CLOSE::LSB_INST_MENU_CLOSE(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("Target"))
}
//*������

void LSB_INST_MENU_CLOSE::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Target");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Target"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MENU_CLOSE::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MENU_CLOSE::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- menu_close ��ɾ� ----------------------------//



//---------------------------- button ��ɾ� ----------------------------//
LSB_INST_BUTTON::LSB_INST_BUTTON(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_BUTTON::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_BUTTON::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_BUTTON::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- button ��ɾ� ----------------------------//



//---------------------------- comment ��ɾ� ----------------------------//
LSB_INST_COMMENT::LSB_INST_COMMENT(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("Label"))
}
//*������

void LSB_INST_COMMENT::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	char* _s;

	_data_chunks[0]._str = TEXT("Label");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[0]._data = GetUniStr(_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Label"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_COMMENT::_extract_text_each_inst(HANDLE hTxt)
{
	wchar_t* _print_str;

	_print_str = (wchar_t*)_data_chunks[0]._data;
	if (!is_Pure_Ascii_String(_print_str) && !is_File_Path_String(_print_str)) {
		swprintf(_txt_buf + wcslen(_txt_buf), TEXT("%s[%s]%s%s%s%s"),
			_indent_, text_data_prefix, text_prefix, _print_str, text_prefix, _enter_raw_);
	}
	//*������ �ʿ䰡 ���� ���� ���
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_COMMENT::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	wchar_t* cp_txt, * n_txt;

	if (!is_Pure_Ascii_String((wchar_t*)_data_chunks[0]._data)
		&& !is_File_Path_String((wchar_t*)_data_chunks[0]._data)) {
		if (_data_chunks[0]._data != NULL) { free(_data_chunks[0]._data); }
		//*�̹� �����Ͱ� ������ ������
		cp_txt = txt_list_elem->_txt_list_per_inst[accum_count];
		n_txt = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(cp_txt) + 1));
		n_txt[wcslen(cp_txt)] = 0;
		memcpy(n_txt, cp_txt, (sizeof(wchar_t) * wcslen(cp_txt)));
		_data_chunks[0]._data = n_txt;
		//*�޸� ���� �� ��ġ
		accum_count++;
	}
	//*������ �ʿ䰡 ���� ���� ��ġ�Ѵ�
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- comment ��ɾ� ----------------------------//



//---------------------------- while ��ɾ� ----------------------------//
LSB_INST_WHILE::LSB_INST_WHILE(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 2;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 2�� (TEXT("_UNK_1"), TEXT("Var_Scope"))
}
//*������

void LSB_INST_WHILE::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("_UNK_1");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("_UNK_1"))

	_data_chunks[1]._str = TEXT("Var_Scope");
	_data_chunks[1]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Var_Scope"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_WHILE::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_WHILE::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- while ��ɾ� ----------------------------//



//---------------------------- while_init ��ɾ� ----------------------------//
LSB_INST_WHILE_INIT::LSB_INST_WHILE_INIT(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("__UNK__"))
}
//*������

void LSB_INST_WHILE_INIT::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("__UNK__");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("__UNK__"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_WHILE_INIT::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_WHILE_INIT::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- while_init ��ɾ� ----------------------------//



//---------------------------- while_loop ��ɾ� ----------------------------//
LSB_INST_WHILE_LOOP::LSB_INST_WHILE_LOOP(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 2;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 2�� (TEXT("_UNK_1"), TEXT("Var_Scope"))
}
//*������

void LSB_INST_WHILE_LOOP::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("_UNK_1");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("_UNK_1"))

	_data_chunks[1]._str = TEXT("Var_Scope");
	_data_chunks[1]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Var_Scope"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_WHILE_LOOP::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_WHILE_LOOP::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- while_loop ��ɾ� ----------------------------//



//---------------------------- break ��ɾ� ----------------------------//
LSB_INST_BREAK::LSB_INST_BREAK(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 2;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 2�� (TEXT("Calc"), TEXT("Var_Scope"))
}
//*������

void LSB_INST_BREAK::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Calc");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Calc"))

	_data_chunks[1]._str = TEXT("Var_Scope");
	_data_chunks[1]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Var_Scope"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_BREAK::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_BREAK::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- break ��ɾ� ----------------------------//



//---------------------------- continue ��ɾ� ----------------------------//
LSB_INST_CONTINUE::LSB_INST_CONTINUE(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 2;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 2�� (TEXT("Calc"), TEXT("Var_Scope"))
}
//*������

void LSB_INST_CONTINUE::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Calc");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Calc"))

	_data_chunks[1]._str = TEXT("Var_Scope");
	_data_chunks[1]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Var_Scope"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_CONTINUE::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_CONTINUE::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- continue ��ɾ� ----------------------------//



//---------------------------- game_save ��ɾ� ----------------------------//
LSB_INST_GAME_SAVE::LSB_INST_GAME_SAVE(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 3;
	if (_script_ver >= 0x69) { _data_chunks_count++; }
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 3�� Ȥ�� 4��
	//*(TEXT("No"), TEXT("Script_Page"), ������ ���� TEXT("Target_Label_Offset") �߰�, TEXT("Caption"))
}
//*������

void LSB_INST_GAME_SAVE::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;
	char* _s;

	_data_chunks[0]._str = TEXT("No");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("No"))

	_data_chunks[1]._str = TEXT("Script_Page");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[1]._data = GetUniStr(_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Script_Page"))

	if (_script_ver >= 0x69) {
		_data_chunks[2]._str = TEXT("Target_Label_Offset");
		_data_chunks[2]._data = _get_int(&lsb_buffer_pnt);
		//* ������ �о���̱� (TEXT("Target_Label_Offset"))

		_data_chunks[3]._str = TEXT("Caption");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[3]._data = _pnt;
		//* ������ �о���̱� (TEXT("Caption"))
	}
	//* 0x69 �̻��̸� ������ �о���̱� (TEXT("Target_Label_Offset"), TEXT("Caption"))

	else {
		_data_chunks[2]._str = TEXT("Caption");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[2]._data = _pnt;
		//* ������ �о���̱� (TEXT("Caption"))
	}
	//* 0x69 ���̸� TEXT("Caption")�� �о���̱�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_GAME_SAVE::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)

	if (_script_ver >= 0x69) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[3]._data;
		_pnt->_extract_text(hTxt);
	}
	else {
		_pnt = (LSB_PARAMETERS*)_data_chunks[2]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_GAME_SAVE::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ

	if (_script_ver >= 0x69) {
		_t = (LSB_PARAMETERS*)_data_chunks[3]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	else {
		_t = (LSB_PARAMETERS*)_data_chunks[2]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*������ ���� �з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- game_save ��ɾ� ----------------------------//



//---------------------------- game_load ��ɾ� ----------------------------//
LSB_INST_GAME_LOAD::LSB_INST_GAME_LOAD(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("No"))
}
//*������

void LSB_INST_GAME_LOAD::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("No");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("No"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_GAME_LOAD::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_GAME_LOAD::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- game_load ��ɾ� ----------------------------//



//---------------------------- clear_load ��ɾ� ----------------------------//
LSB_INST_CLEAR_LOAD::LSB_INST_CLEAR_LOAD(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	//*�ʿ��� �з����� ����Ʈ �� : 0��
}
//*������

void LSB_INST_CLEAR_LOAD::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_CLEAR_LOAD::_extract_text_each_inst(HANDLE hTxt)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_CLEAR_LOAD::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- clear_load ��ɾ� ----------------------------//



//---------------------------- pc_reset ��ɾ� ----------------------------//
LSB_INST_PC_RESET::LSB_INST_PC_RESET(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 3;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 2�� (TEXT("Script_Page"), TEXT("Target_Label_Offset"), TEXT("All_Clear_Byte"))
}
//*������

void LSB_INST_PC_RESET::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	char* _s;

	_data_chunks[0]._str = TEXT("Script_Page");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[0]._data = GetUniStr(_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Script_Page"))

	_data_chunks[1]._str = TEXT("Target_Label_Offset");
	_data_chunks[1]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Target_Label_Offset"))

	_data_chunks[2]._str = TEXT("All_Clear_Byte");
	_data_chunks[2]._data = _get_byte(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("All_Clear_Byte"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_PC_RESET::_extract_text_each_inst(HANDLE hTxt)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_PC_RESET::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- pc_reset ��ɾ� ----------------------------//



//---------------------------- reset ��ɾ� ----------------------------//
LSB_INST_RESET::LSB_INST_RESET(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 3;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 2�� (TEXT("Script_Page"), TEXT("Target_Label_Offset"), TEXT("All_Clear_Byte"))
}
//*������

void LSB_INST_RESET::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	char* _s;

	_data_chunks[0]._str = TEXT("Script_Page");
	_s = _get_str(&lsb_buffer_pnt);
	_data_chunks[0]._data = GetUniStr(_s, code);
	free(_s);
	//* ������ �о���̱� (TEXT("Script_Page"))

	_data_chunks[1]._str = TEXT("Target_Label_Offset");
	_data_chunks[1]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Target_Label_Offset"))

	_data_chunks[2]._str = TEXT("All_Clear_Byte");
	_data_chunks[2]._data = _get_byte(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("All_Clear_Byte"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_RESET::_extract_text_each_inst(HANDLE hTxt)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_RESET::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- reset ��ɾ� ----------------------------//



//---------------------------- sound ��ɾ� ----------------------------//
LSB_INST_SOUND::LSB_INST_SOUND(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
}
//*������

void LSB_INST_SOUND::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_SOUND::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_SOUND::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- sound ��ɾ� ----------------------------//



//---------------------------- media_play ��ɾ� ----------------------------//
LSB_INST_MEDIA_PLAY::LSB_INST_MEDIA_PLAY(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 1;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 1�� (TEXT("Target"))
}
//*������

void LSB_INST_MEDIA_PLAY::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Target");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Target"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MEDIA_PLAY::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	_pnt = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MEDIA_PLAY::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	_t = (LSB_PARAMETERS*)_data_chunks[0]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- media_play ��ɾ� ----------------------------//



//---------------------------- terminate ��ɾ� ----------------------------//
LSB_INST_TERMINATE::LSB_INST_TERMINATE(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	//*�ʿ��� �з����� ����Ʈ �� : 0��
}
//*������

void LSB_INST_TERMINATE::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_TERMINATE::_extract_text_each_inst(HANDLE hTxt)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_TERMINATE::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- terminate ��ɾ� ----------------------------//



//---------------------------- do_event ��ɾ� ----------------------------//
LSB_INST_DO_EVENT::LSB_INST_DO_EVENT(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	//*�ʿ��� �з����� ����Ʈ �� : 0��
}
//*������

void LSB_INST_DO_EVENT::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_DO_EVENT::_extract_text_each_inst(HANDLE hTxt)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_DO_EVENT::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- do_event ��ɾ� ----------------------------//



//---------------------------- property_motion ��ɾ� ----------------------------//
LSB_INST_PROPERTY_MOTION::LSB_INST_PROPERTY_MOTION(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	_data_chunks_count = 6;
	if (_script_ver >= 0x6C) { _data_chunks_count++; }
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : 6�� Ȥ�� 7��
	//*(TEXT("Name"), TEXT("ObjName"), , TEXT("ObjProp"), TEXT("Value"), TEXT("Time"), TEXT("MoveType"), ������ ���� TEXT("Paused"))
}
//*������

void LSB_INST_PROPERTY_MOTION::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	_data_chunks[0]._str = TEXT("Name");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[0]._data = _pnt;
	//* ������ �о���̱� (TEXT("Name"))

	_data_chunks[1]._str = TEXT("ObjName");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[1]._data = _pnt;
	//* ������ �о���̱� (TEXT("ObjName"))

	_data_chunks[2]._str = TEXT("ObjProp");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[2]._data = _pnt;
	//* ������ �о���̱� (TEXT("ObjProp"))

	_data_chunks[3]._str = TEXT("Value");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[3]._data = _pnt;
	//* ������ �о���̱� (TEXT("Value"))

	_data_chunks[4]._str = TEXT("Time");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[4]._data = _pnt;
	//* ������ �о���̱� (TEXT("Time"))

	_data_chunks[5]._str = TEXT("MoveType");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[5]._data = _pnt;
	//* ������ �о���̱� (TEXT("MoveType"))

	if (_script_ver >= 0x6C) {
		_data_chunks[6]._str = TEXT("Paused");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[6]._data = _pnt;
	}
	//* 0x6C�̻��̸� ������ �о���̱� (TEXT("Paused"))

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_PROPERTY_MOTION::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_PROPERTY_MOTION::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;

	for (unsigned int i = 0; i < _data_chunks_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- property_motion ��ɾ� ----------------------------//



//---------------------------- save_cabinet ��ɾ� ----------------------------//
LSB_INST_SAVE_CABINET::LSB_INST_SAVE_CABINET(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks_count += 2;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���, TEXT("Name"), TEXT("Parameter_Count") �߰�)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
	//*�ű�� TEXT("Parameter_Count") ������ �ݿ��ؾ� �ϹǷ� ���� ��Ȯ�� ���� �� ����
}
//*������

void LSB_INST_SAVE_CABINET::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < (_data_chunks_count - 2); i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	_data_chunks[(_data_chunks_count - 2)]._str = TEXT("Name");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[(_data_chunks_count - 2)]._data = _pnt;
	//* ������ �о���̱� (TEXT("Name"))

	_data_chunks[(_data_chunks_count - 1)]._str = TEXT("Parameter_Count");
	_data_chunks[(_data_chunks_count - 1)]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Parameter_Count"))
	
	unsigned int _param_count = *(unsigned int*)_data_chunks[(_data_chunks_count - 1)]._data;
	LSB_MAP_DATA* _n_map = _get_initialized_data_chunks(_data_chunks_count + _param_count);
	memcpy(_n_map, _data_chunks, (sizeof(LSB_MAP_DATA) * _data_chunks_count));
	for (unsigned int i = 0; i < _param_count; i++) {
		_n_map[_data_chunks_count + i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_n_map[_data_chunks_count + i]._data = _pnt;
	}
	//* ����� �� ������� �Ҵ� �� ���� �� ���� �о���̱�

	_data_chunks_count += _param_count;
	free(_data_chunks);
	_data_chunks = _n_map;
	//*�ٽ� ����

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_SAVE_CABINET::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;
	unsigned int _tp_count = 0;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _tp_count++; }
	}
	//*�ӽ÷� ���� ���;� �Ѵ�

	for (unsigned int i = 0; i < _tp_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)

	_pnt = (LSB_PARAMETERS*)_data_chunks[_tp_count]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)

	unsigned int _param_count = *(unsigned int*)_data_chunks[(_tp_count + 1)]._data;
	for (unsigned int i = 0; i < _param_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[(_tp_count + 2) + i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� �ľ� �� ���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_SAVE_CABINET::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;
	unsigned int _tp_count = 0;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _tp_count++; }
	}
	//*�ӽ÷� ���� ���;� �Ѵ�

	for (unsigned int i = 0; i < _tp_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ

	_t = (LSB_PARAMETERS*)_data_chunks[_tp_count]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ

	unsigned int _param_count = *(unsigned int*)_data_chunks[(_tp_count + 1)]._data;
	for (unsigned int i = 0; i < _param_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[(_tp_count + 2) + i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- save_cabinet ��ɾ� ----------------------------//



//---------------------------- load_cabinet ��ɾ� ----------------------------//
LSB_INST_LOAD_CABINET::LSB_INST_LOAD_CABINET(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	_data_chunks_count = 0;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _data_chunks_count++; }
	}
	_data_chunks_count += 2;
	_data_chunks = _get_initialized_data_chunks(_data_chunks_count);
	//*�ʿ��� �з����� ����Ʈ �� : �������� (opcode���� ���� �޶���, TEXT("Name"), TEXT("Parameter_Count") �߰�)
	//*���� ���̴� ������ ���� �����µ� �׳� �����ص� �� �� ����
	//*�ű�� TEXT("Parameter_Count") ������ �ݿ��ؾ� �ϹǷ� ���� ��Ȯ�� ���� �� ����
}
//*������

void LSB_INST_LOAD_CABINET::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);
	LSB_PARAMETERS* _pnt;

	for (unsigned int i = 0; i < (_data_chunks_count - 2); i++) {
		_data_chunks[i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_data_chunks[i]._data = _pnt;
	}
	//*������ ����ŭ ���� �о���δ�

	_data_chunks[(_data_chunks_count - 2)]._str = TEXT("Name");
	_pnt = new LSB_PARAMETERS();
	_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
	_data_chunks[(_data_chunks_count - 2)]._data = _pnt;
	//* ������ �о���̱� (TEXT("Name"))

	_data_chunks[(_data_chunks_count - 1)]._str = TEXT("Parameter_Count");
	_data_chunks[(_data_chunks_count - 1)]._data = _get_int(&lsb_buffer_pnt);
	//* ������ �о���̱� (TEXT("Parameter_Count"))

	unsigned int _param_count = *(unsigned int*)_data_chunks[(_data_chunks_count - 1)]._data;
	LSB_MAP_DATA* _n_map = _get_initialized_data_chunks(_data_chunks_count + _param_count);
	memcpy(_n_map, _data_chunks, (sizeof(LSB_MAP_DATA) * _data_chunks_count));
	for (unsigned int i = 0; i < _param_count; i++) {
		_n_map[_data_chunks_count + i]._str = TEXT("__ARG__");
		_pnt = new LSB_PARAMETERS();
		_pnt->_read_parameter_list(&lsb_buffer_pnt, code);
		_n_map[_data_chunks_count + i]._data = _pnt;
	}
	//* ����� �� ������� �Ҵ� �� ���� �� ���� �о���̱�

	_data_chunks_count += _param_count;
	free(_data_chunks);
	_data_chunks = _n_map;
	//*�ٽ� ����

	(*_lsb_buffer_pnt) = lsb_buffer_pnt;
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_LOAD_CABINET::_extract_text_each_inst(HANDLE hTxt)
{
	LSB_PARAMETERS* _pnt;
	unsigned int _tp_count = 0;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _tp_count++; }
	}
	//*�ӽ÷� ���� ���;� �Ѵ�

	for (unsigned int i = 0; i < _tp_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)

	_pnt = (LSB_PARAMETERS*)_data_chunks[_tp_count]._data;
	_pnt->_extract_text(hTxt);
	//*���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)

	unsigned int _param_count = *(unsigned int*)_data_chunks[(_tp_count + 1)]._data;
	for (unsigned int i = 0; i < _param_count; i++) {
		_pnt = (LSB_PARAMETERS*)_data_chunks[(_tp_count + 2) + i]._data;
		_pnt->_extract_text(hTxt);
	}
	//*���� �ľ� �� ���� ��Ͽ��� ���ڿ��� ���ڸ� ��� ���� (���� ascii �ڵ尡 �ƴϸ� �����Ѵ�)
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_LOAD_CABINET::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	unsigned int accum_count = 0;
	LSB_PARAMETERS* _t;
	unsigned int _tp_count = 0;
	bool** property_boolean_table = _header->opcode_property_boolean_table;
	for (unsigned int i = 0; i < (_header->opcode_property_count * 0x8); i++) {
		if (property_boolean_table[_op_type][i]) { _tp_count++; }
	}
	//*�ӽ÷� ���� ���;� �Ѵ�

	for (unsigned int i = 0; i < _tp_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
	//*�з����� ����Ʈ���� ��ġ

	_t = (LSB_PARAMETERS*)_data_chunks[_tp_count]._data;
	_t->_replace_text(txt_list_elem, &accum_count);
	//*�з����� ����Ʈ���� ��ġ

	unsigned int _param_count = *(unsigned int*)_data_chunks[(_tp_count + 1)]._data;
	for (unsigned int i = 0; i < _param_count; i++) {
		_t = (LSB_PARAMETERS*)_data_chunks[(_tp_count + 2) + i]._data;
		_t->_replace_text(txt_list_elem, &accum_count);
	}
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- load_cabinet ��ɾ� ----------------------------//



//---------------------------- IFDEF ��ó�� ��ɾ� ----------------------------//
LSB_INST_MACRO_IFDEF::LSB_INST_MACRO_IFDEF(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	//*�ʿ��� �з����� ����Ʈ �� : 0��
}
//*������

void LSB_INST_MACRO_IFDEF::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MACRO_IFDEF::_extract_text_each_inst(HANDLE hTxt)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MACRO_IFDEF::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- IFDEF ��ó�� ��ɾ� ----------------------------//



//---------------------------- IFNDEF ��ó�� ��ɾ� ----------------------------//
LSB_INST_MACRO_IFNDEF::LSB_INST_MACRO_IFNDEF(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	//*�ʿ��� �з����� ����Ʈ �� : 0��
}
//*������

void LSB_INST_MACRO_IFNDEF::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MACRO_IFNDEF::_extract_text_each_inst(HANDLE hTxt)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MACRO_IFNDEF::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- IFNDEF ��ó�� ��ɾ� ----------------------------//



//---------------------------- ENDIF ��ó�� ��ɾ� ----------------------------//
LSB_INST_MACRO_ENDIF::LSB_INST_MACRO_ENDIF(LSB_INST_TYPES _op_type, unsigned int _script_ver, LSB_HEADER* _header)
	: LSB_INST_BASE(_script_ver, _header)
{
	this->_op_type = _op_type;
	//*�ʿ��� �з����� ����Ʈ �� : 0��
}
//*������

void LSB_INST_MACRO_ENDIF::_read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*���ۿ��� �о���̴� �Լ�

void LSB_INST_MACRO_ENDIF::_extract_text_each_inst(HANDLE hTxt)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� �����ϴ� �Լ�

void LSB_INST_MACRO_ENDIF::_replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code)
{
	//*���� �۾� �ʿ� ����
}
//*�ؽ�Ʈ�� ��ġ�ϴ� �Լ�
//---------------------------- ENDIF ��ó�� ��ɾ� ----------------------------//

//*********************** �� Ŭ������ �Լ� ***********************//