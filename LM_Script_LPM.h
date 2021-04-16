#pragma once
#include "LM_Base.h"

//*** LPM ��ũ��Ʈ �м� �� ���� �Լ����� �����ϴ� ���


typedef struct _Lpm_Item_Arg
{
	wchar_t* _str[5];
	unsigned int _int;
}LPM_ITEM_ARG;
//*������ Ŭ������ ���� ���� �����ε�?


class LPM_ITEM
{
public:
	unsigned int _Version;								//*��ư Ŭ�������� ���� ������
	unsigned int _Left;									//*���̳ʸ� �� "width"�� ����
	unsigned int _Top;									//*���̳ʸ� �� "height"�� ����
	wchar_t* _Src;										//*���̳ʸ� �� "src"�� ����
	unsigned char _unk_2;								//*���̳ʸ� �� "unk2"�� ����
	wchar_t* _Name;										//*���̳ʸ� �� "name"�� ����
	wchar_t* _Src_Selected;								//*���̳ʸ� �� "src_selected"�� ����
	wchar_t* _unk_3;									//*�������� ���� ���̳ʸ����� ����
	wchar_t* _unk_4;
	wchar_t* _unk_5;
	wchar_t* _unk_6[2];
	wchar_t* _unk_7;
	wchar_t* _unk_8;
	wchar_t* _unk_9;
	wchar_t* _unk_10[2];
	unsigned int _unk_11;
	unsigned int _unk_12;
	wchar_t* _unk_13;
	LPM_ITEM_ARG _unk_14;
	wchar_t* _unk_15;
	wchar_t* _unk_16;

	LPM_ITEM (unsigned int Version)
	{
		_Version = Version;
		_Left = _Top = 0;
		_unk_2 = 0;
		_Name = _Src_Selected = NULL;
		_unk_3 = _unk_4 = _unk_5 = NULL;
		memset(_unk_6, 0, (sizeof(wchar_t*) * 2));
		_unk_7 = _unk_8 = _unk_9 = NULL;
		memset(_unk_10, 0, (sizeof(wchar_t*) * 2));
		_unk_11 = _unk_12 = 0;
		_unk_13 = NULL;
		memset(&_unk_14, 0, sizeof(LPM_ITEM_ARG));
		_unk_15 = _unk_16 = NULL;
	}
	//*������

	~LPM_ITEM()
	{
		if (_Name != NULL) { free(_Name); }
		if (_Src_Selected != NULL) { free(_Src_Selected); }
		if (_unk_3 != NULL) { free(_unk_3); } if (_unk_4 != NULL) { free(_unk_4); } if (_unk_5 != NULL) { free(_unk_5); }
		for (unsigned int i = 0; i < 2;i++) { 
			if (_unk_6[i] != NULL) { free(_unk_6[i]); }
		}
		if (_unk_7 != NULL) { free(_unk_7); } if (_unk_8 != NULL) { free(_unk_8); } if (_unk_9 != NULL) { free(_unk_9); }
		for (unsigned int i = 0; i < 2; i++) {
			if (_unk_10[i] != NULL) { free(_unk_10[i]); }
		}
		if (_unk_13 != NULL) { free(_unk_13); }
		for (unsigned int i = 0; i < 5; i++) {
			if (_unk_14._str[i] != NULL) { free(_unk_14._str[i]); }
		}
		if (_unk_15 != NULL) { free(_unk_15); } if (_unk_16 != NULL) { free(_unk_16); }
	}
	//*�Ҹ���

	void _read_from_buffer(unsigned char** _lpm_buffer_pnt, unsigned int code);
	//*���ۿ��� �о���̴� �Լ�

	void _decompile_code(HANDLE hWrite, unsigned int code);
	//*�������� �Լ�

	void _write_as_lpm(HANDLE hNewLpm, unsigned int code);
	//*lpm ���Ϸ� ����ϴ� �Լ�

	void _change_code_J2K();
	//*�ؽ�Ʈ �ڵ� ���� �Լ�
};
//*lpm ��ũ��Ʈ���� Item�� �����Ǵ� Ŭ����
//*xml�� ���̳ʸ��� ���� �����ǵ��� ¥�°� �ʹ� �����


class LPM_BUTTON
{
public:
	unsigned int _Version;
	unsigned int _item_count;
	LPM_ITEM** _item_list;

	LPM_BUTTON()
	{
		_Version = 0;
		_item_count = 0;
		_item_list = NULL;
	}
	//*������

	~LPM_BUTTON()
	{
		if (_item_list != NULL) {
			for (unsigned int i = 0; i < _item_count;i++) {
				if (_item_list[i] != NULL) { delete _item_list[i]; }
			}
			free (_item_list);
		}
	}
	//*�Ҹ���

	void _read_from_buffer(unsigned char** _lpm_buffer_pnt, unsigned int code);
	//*���ۿ��� �о���̴� �Լ�

	void _decompile_code(HANDLE hWrite, unsigned int code);
	//*�������� �Լ�

	void _write_as_lpm(HANDLE hNewLpm, unsigned int code);
	//*lpm ���Ϸ� ����ϴ� �Լ�

	void _change_code_J2K();
	//*�ؽ�Ʈ �ڵ� ���� �Լ�
};
//*lpm ��ũ��Ʈ���� Button�� �����Ǵ� Ŭ����


class LPM_PREVMENU
{
public:
	wchar_t* _Signature;
	wchar_t* _Version;
	unsigned int _Width;
	unsigned int _Height;
	LPM_BUTTON* _Button;

	LPM_PREVMENU()
	{
		_Signature = _Version = NULL;
		_Width = _Height = 0;
		_Button = new LPM_BUTTON();
	}
	//*������

	~LPM_PREVMENU()
	{
		if (_Signature != NULL) { free(_Signature); }
		if (_Version != NULL) { free(_Version); }
		if (_Button != NULL) { delete _Button; }
	}
	//*�Ҹ���

	void _read_from_buffer(unsigned char** _lpm_buffer_pnt, unsigned int code);
	//*���ۿ��� �о���̴� �Լ�

	void _decompile_code(HANDLE hWrite, unsigned int code);
	//*�������� �Լ�

	void _write_as_lpm(HANDLE hNewLpm, unsigned int code);
	//*lpm ���Ϸ� ����ϴ� �Լ�

	void _change_code_J2K();
	//*�ؽ�Ʈ �ڵ� ���� �Լ�
};
//*lpm ��ũ��Ʈ���� PrevMenu�� �����Ǵ� Ŭ����
//* �ٵ� lpm�� xml������ ��쵵 �ְ� ���̳ʸ��� �Ǿ��ִ� ��쵵 �־ ��쿡 ���� ������ �� �� �ϴ�
//* xml������ ���� �ƿ� ���������� �Ǿ������� �ǵ� �ʿ䰡 ����


class LPM_SCRIPT : public LM_BASE_SCRIPT
{
public:
	bool _is_xml_script;						//*** xml �������� �Ǻ��ϴ� ����
	wchar_t* _Lpm_Buffer;						//*** xml �����̶�� �׳� ���� �о�鿩 ������
	LPM_PREVMENU *_PrevMenu;					//*** lpm ��ũ��Ʈ�� ����� PrevMenu Ŭ����

	LPM_SCRIPT()
	{
		_is_xml_script = false;
		_Lpm_Buffer = NULL;
		_PrevMenu = NULL;
	}
	//*������

	~LPM_SCRIPT()
	{
		if (_Lpm_Buffer != NULL) { free (_Lpm_Buffer); }
		if (_PrevMenu != NULL) { delete _PrevMenu; }
	}
	//*�Ҹ���

	bool Script_Analysis(wchar_t* LpmFile, unsigned int code);
	//*lpm ������ �ҷ��� �м��ϴ� �Լ�

	void Decompile_To_Code(wchar_t* TxtFile, unsigned int code);
	//*���������ؼ� ����ϴ� �Լ�

	void Make_To_Script(wchar_t* newLpmFile, unsigned int code);
	//*lpm ���Ϸ� ����ϴ� �Լ�

	void Extract_Text_Data(wchar_t* DstTxtFile);
	//*�ؽ�Ʈ ���� �Լ�

	void Replace_Text_Data(wchar_t* SrcTxtFile, unsigned int code);
	//*�ؽ�Ʈ ��ü �Լ�

	void Convert_Codepage_J2K();
	//*�ؽ�Ʈ ����ڵ带 �Ϻ���� �ѱ۷� �ٲٴ� �Լ�
	
private:
	bool _analysis_as_xml(wchar_t* LpmFile, unsigned int code);
	//*xml�� ��� �м��ϴ� �Լ�
	
	bool _analysis_as_binary(wchar_t* LpmFile, unsigned int code);
	//*�������Ϸ� ��� �м��ϴ� �Լ�
};
//*.lpm ��ũ��Ʈ Ŭ����
//*xml�� �Ǿ� ������ �ƿ� �м��� �� �ʿ䰡 ����