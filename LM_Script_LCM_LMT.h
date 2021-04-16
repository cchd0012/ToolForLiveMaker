#pragma once
#include "LM_Base.h"

//*** LCM/LMT ��ũ��Ʈ �м� �� ���� �Լ����� �����ϴ� ���


typedef struct _lcm_lmt_type_type_info_1
{
	unsigned int _int_list[6];
	unsigned char _char_list[2];
}LCM_LMT_TILE_INFO_1;
//*lcm/lmt ���� ���� ����ü 1(TILE)

typedef struct _lcm_lmt_type_0_info_2
{
	double _double_list[2];
	unsigned char _char_1;
	unsigned int _int_list[2];
	unsigned char _char_2;
}LCM_LMT_TILE_INFO_2;
//*lcm/lmt ���� ���� ����ü 2(TILE)

typedef struct _lcm_lmt_type_2_info
{
	unsigned int _int_list_1[4];
	unsigned char _char_list[2];
	unsigned int _int_list_2[12];
}LCM_LMT_BOX_INFO;
//*lcm/lmt ���� ���� ����ü 3(BOX)
//*���⿡ _int_list_2[0]~[5]��°�� x, y ��ġ/�ʺ�,����/��½� �ʺ�,���̰� �ִ� �� �ϴ�

typedef struct _lcm_lmt_type_4_info
{
	unsigned int _int_list[4];
	unsigned char _char_list[2];
}LCM_LMT_SOUND_INFO;
//*lcm/lmt ���� ���� ����ü 4(SOUND)

typedef struct _lcm_lmt_unk_65
{
	unsigned int _int_list[8];
	unsigned char _char_list[2];
}LCM_LMT_UNK_65;
//*lcm/lmt ���� ���� ����ü 3 (ver >= 0x65)

typedef struct _lcm_lmt_unk_69
{
	double _double_list[2];
	unsigned char _char;
}LCM_LMT_UNK_69;
//*lcm/lmt ���� ���� ����ü 3 (ver >= 0x69)

typedef struct _lcm_lmt_unk_6d
{
	unsigned int _int_list[4];
}LCM_LMT_UNK_6D;
//*lcm/lmt ���� ���� ����ü 4 (ver >= 0x6D)

typedef struct _lcm_lmt_unk_6e
{
	double _double_list[2];
}LCM_LMT_UNK_6E;
//*lcm/lmt ���� ���� ����ü 5 (ver >= 0x6E)

typedef struct _lcm_lmt_unk_not_6e
{
	unsigned int _int_list[2];
}LCM_LMT_UNK_NOT_6E;
//*lcm/lmt ���� ���� ����ü 6 (ver < 0x6E, type 0������)


class LCM_LMT_SCRIPT_ELEM
{
public:
	unsigned int _Version;						//*** lcm/lmt ��ũ��Ʈ�� ����
	unsigned char _elem_type;					//*** ����
	unsigned int _unk_2[6];						//*** ����
	unsigned char _unk_3[3];					//*** ����

	wchar_t *_unk_3_1;							//*** ���� 0x71 �̻�
	
	LCM_LMT_TILE_INFO_1 *_elem_info_0_1;		//*** _elem_type�� 0�� ��, 1��
	LCM_LMT_UNK_6E* _unk_4_1;					//*** ���� 0x6E �̻�, _elem_type�� 0�� ��
	LCM_LMT_UNK_NOT_6E* _unk_4_2;				//*** ���� 0x6E �̸�, _elem_type�� 0�� ��
	LCM_LMT_TILE_INFO_2* _elem_info_0_2;		//*** _elem_type�� 0�� ��, 2��
	LCM_LMT_BOX_INFO* _elem_info_2;			//*** _elem_type�� 2�� ��
	LCM_LMT_SOUND_INFO* _elem_info_4;			//*** _elem_type�� 4�� ��
	LCM_LMT_UNK_65 *_unk_5;						//*** ���� 0x65 �̻�
	LCM_LMT_UNK_69* _unk_6;						//*** ���� 0x69 �̻�
	LCM_LMT_UNK_6D* _unk_7;						//*** ���� 0x6D �̻�
	wchar_t* _SrcFile;							//*** �ҽ��� �Ǵ� ����

	LCM_LMT_SCRIPT_ELEM(unsigned int Version)
	{
		_Version = Version;
		_elem_type = 0;
		memset(_unk_2, 0, (sizeof(int) * 6));
		memset(_unk_3, 0, (sizeof(char) * 3));
		_unk_3_1 = NULL;
		_elem_info_0_1 = NULL;
		_unk_4_1 = NULL;
		_unk_4_2 = NULL;
		_elem_info_0_2 = NULL;
		_elem_info_2 = NULL;
		_elem_info_4 = NULL;
		_unk_5 = NULL;
		_unk_6 = NULL;
		_unk_7 = NULL;
		_SrcFile = NULL;
	}
	//*������

	~LCM_LMT_SCRIPT_ELEM()
	{
		if (_elem_info_0_1 != NULL) { free(_elem_info_0_1); }
		if (_unk_3_1 != NULL) { free(_unk_3_1); }
		if (_unk_4_1 != NULL) { free(_unk_4_1); }
		if (_unk_4_2 != NULL) { free(_unk_4_2); }
		if (_elem_info_0_2 != NULL) { free(_elem_info_0_2); }
		if (_elem_info_2 != NULL) { free(_elem_info_2); }
		if (_elem_info_4 != NULL) { free(_elem_info_4); }
		if (_unk_5 != NULL) { free(_unk_5); }
		if (_unk_6 != NULL) { free(_unk_6); }
		if (_unk_7 != NULL) { free(_unk_7); }
		if (_SrcFile != NULL) { free(_SrcFile); }
	}
	//*�Ҹ���

	void _read_from_buffer(unsigned char** _lcm_lmt_buffer_pnt, unsigned int code);
	//*���ۿ��� �о���̴� �Լ�

	void _decompile_code(HANDLE hWrite, unsigned int code);
	//*�������� �Լ�

	void _write_as_lcm_or_lmt(HANDLE hNew_Lcm_Lmt, unsigned int code);
	//*lcm/lmt ���Ϸ� ����ϴ� �Լ�
};
//*�� ��ũ��Ʈ���� ���ҷ� ���̴� Ŭ����


class LCM_LMT_SCRIPT : public LM_BASE_SCRIPT
{
public:
	wchar_t* _Signature;
	wchar_t* _Version;
	unsigned int _Width;
	unsigned int _Height;
	unsigned int _unk_1[4];
	unsigned char _unk_2;
	unsigned int _elem_count;
	LCM_LMT_SCRIPT_ELEM** _elem_list;

	LCM_LMT_SCRIPT()
	{
		_Signature = NULL;
		_Version = NULL;
		_Width = _Height = 0;
		memset(_unk_1, 0, (sizeof(int) * 4));
		_unk_2 = 0;
		_elem_count = 0;
		_elem_list = NULL;
	}
	//*������

	~LCM_LMT_SCRIPT()
	{
		if (_Signature != NULL) { free(_Signature); }
		if (_Version != NULL) { free(_Version); }
		if (_elem_count != 0) {
			for (unsigned int i = 0; i < _elem_count;i++) {
				if (_elem_list[i] != NULL) { delete _elem_list[i]; }
			}
			free(_elem_list);
		}
	}
	//*�Ҹ���

	bool Script_Analysis(wchar_t* Lcm_Lmt_File, unsigned int code);
	//*lcm/lmt ������ �ҷ��� �м��ϴ� �Լ�

	void Decompile_To_Code(wchar_t* TxtFile, unsigned int code);
	//*���������ؼ� ����ϴ� �Լ�

	void Make_To_Script(wchar_t* new_Lcm_Lmt_File, unsigned int code);
	//*lsb ���Ϸ� ����ϴ� �Լ�

	void Extract_Text_Data(wchar_t* DstTxtFile);
	//*�ؽ�Ʈ ���� �Լ�

	void Replace_Text_Data(wchar_t* SrcTxtFile, unsigned int code);
	//*�ؽ�Ʈ ��ü �Լ�

	void Convert_Codepage_J2K();
	//*�ؽ�Ʈ ����ڵ带 �Ϻ���� �ѱ۷� �ٲٴ� �Լ�
};
//*.lcm/*.lmt ��ũ��Ʈ Ŭ����