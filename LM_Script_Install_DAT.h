#pragma once
#include "LM_Base.h"

//*** INSTALL.DAT ��ũ��Ʈ �м� �� ���� �Լ����� �����ϴ� ���


typedef struct _dat_attr_elem_66
{
	wchar_t* _str;
}DAT_ATTR_ELEM_66;
//*���⼭ ���� ������ 0�� �ǵ��� ��

typedef struct _dat_attr_elem_64
{
	unsigned int _int_list[8];
}DAT_ATTR_ELEM_64;

typedef struct _dat_attr_elem_not_64
{
	unsigned int _int_list[4];
}DAT_ATTR_ELEM_NOT_64;
//*(�Ƹ���) dat ������ ����ִ� �Ӽ�
//*������ ���� ����


class INSTALL_DAT_SCRIPT : public LM_BASE_SCRIPT
{
public:
	wchar_t* _Signature;
	wchar_t* _Version;
	unsigned int _Version_Int;
	unsigned int _unk_1;
	//*_Version_Int�� ��Ͽ��� �ƴϰ� ���ϰ� �ٷ�� �����̴�

	wchar_t* _Game_Title;
	wchar_t* _unk_2;
	wchar_t* _Compile_Dir;
	wchar_t* _unk_3;

	unsigned char _unk_4;
	wchar_t* _unk_5;
	unsigned char _unk_6;
	unsigned int _Attr_Count;

	wchar_t* _Execute_File_Name;
	unsigned int _unk_7;
	unsigned char _unk_8;
	unsigned char _unk_9;

	wchar_t* _Drive_Type;
	wchar_t* _unk_10;
	//*�ϴ� ���� ������ ��� �̸��� ���صд�
	//*��� (_Attr_Count + 1)��ŭ �о�鿩�� �Ѵ�

	DAT_ATTR_ELEM_64* _Attr_list_1;
	DAT_ATTR_ELEM_NOT_64* _Attr_list_2;
	//*������ ���� �� �� �ϳ��� �о���δ�

	unsigned char _unk_11;
	unsigned char _unk_12;
	//*_unk_12�� ������ ���� ����

	unsigned int _unk_13_count;
	DAT_ATTR_ELEM_66* _unk_13_list;
	//*_unk_13�� ������ ���� ����

	unsigned char _unk_14;
	unsigned char _unk_15;
	unsigned char _unk_16;
	//*_unk_14, 15, 16�� ������ ���� ����

	unsigned int _unk_17_count;
	wchar_t** _unk_17_list;
	//*_unk_17�� ������ ���� ����

	wchar_t* _unk_18;
	//*_unk_18�� ������ ���� ����

	wchar_t* _unk_19[2];
	//*_unk_19�� ������ ���� ����

	INSTALL_DAT_SCRIPT()
	{
		_Signature = _Version = NULL;
		_Version_Int = 0;
		_unk_1 = 0;
		_Game_Title = _unk_2 = _Compile_Dir = _unk_3 = NULL;
		_unk_4 = 0;
		_unk_5 = NULL;
		_unk_6 = 0;
		_Attr_Count = 0;
		_Execute_File_Name = NULL;
		_unk_7 = 0;
		_unk_8 = _unk_9 = 0;
		_Drive_Type = _unk_10 = 0;
		_Attr_list_1 = NULL;
		_Attr_list_2 = NULL;
		_unk_11 = _unk_12 = 0;
		_unk_13_count = 0;
		_unk_13_list = NULL;
		_unk_14 = _unk_15 = _unk_16 = 0;
		_unk_17_count = 0;
		_unk_17_list = NULL;
		_unk_18 = NULL;
		for (unsigned int i = 0; i < 2; i++) { _unk_19[i] = NULL; }
	}
	//*������

	~INSTALL_DAT_SCRIPT()
	{
		if (_Signature != NULL) { free(_Signature); }
		if (_Version != NULL) { free(_Version); }
		if (_Game_Title != NULL) { free(_Game_Title); }
		if (_unk_2 != NULL) { free(_unk_2); }
		if (_Compile_Dir != NULL) { free(_Compile_Dir); }
		if (_unk_3 != NULL) { free(_unk_3); }
		if (_unk_5 != NULL) { free(_unk_5); }
		if (_Attr_list_1 != NULL) { free(_Attr_list_1); }
		if (_Attr_list_2 != NULL) { free(_Attr_list_2); }
		if (_unk_13_list != NULL) { free(_unk_13_list); }
		if (_unk_17_list != NULL) { 
			for (unsigned int i = 0; i < _unk_17_count;i++) {
				if (_unk_17_list[i] != NULL) { free(_unk_17_list[i]); }
			}
			free(_unk_17_list);
		}
		if (_unk_18 != NULL) { free(_unk_18); }
		for (unsigned int i = 0; i < 2; i++) {
			if (_unk_19[i] != NULL) { free(_unk_19[i]); }
		}
	}
	//*�Ҹ���

	bool Script_Analysis(wchar_t* DatFile, unsigned int code);
	//*install.dat ������ �ҷ��� �м��ϴ� �Լ�

	void Decompile_To_Code(wchar_t* TxtFile, unsigned int code);
	//*���������ؼ� ����ϴ� �Լ�

	void Make_To_Script(wchar_t* newDatFile, unsigned int code);
	//*dat ���Ϸ� ����ϴ� �Լ�

	void Extract_Text_Data(wchar_t* DstTxtFile);
	//*�ؽ�Ʈ ���� �Լ�

	void Replace_Text_Data(wchar_t* SrcTxtFile, unsigned int code);
	//*�ؽ�Ʈ ��ü �Լ�

	void Convert_Codepage_J2K();
	//*�ؽ�Ʈ ����ڵ带 �Ϻ���� �ѱ۷� �ٲٴ� �Լ�
};
//INSTALL.DAT ��ũ��Ʈ Ŭ����