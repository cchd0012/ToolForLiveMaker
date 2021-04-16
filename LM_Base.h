#pragma once
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <vector>
#include <string>
#include <tchar.h>


//*** �⺻������ �����ϴ� ��� ����


using namespace std;

#define MZ_MAGIC				0x00505A4D
#define LV_MAGIC				0x0000766C
#define VF_MAGIC				0x00006676
#define VF_VERSION				0x00000066
//*** ��ī�̺� ���� ��

#define LM_VERSION_1			0x00000067
#define LM_VERSION_2			0x00000074
#define LM_VERSION_3			0x00000075
//*** ��ũ��Ʈ ���� ��


#define TXT_BUFF_LEN			0x400000
extern wchar_t* _txt_buf;
//*_txt_buf�� �ؽ�Ʈ ��¿� ���۴�


enum LM_SCR_TYPES
{
	TYPE_ARG_VAR = 0x00,
	TYPE_ARG_INT = 0x01,
	TYPE_ARG_FLOAT = 0x02,
	TYPE_ARG_BOOL = 0x03,
	TYPE_ARG_STR = 0x04,
	TYPE_ARG_CALC_FUNC = 0x0B,

	TYPE_ARG_UNKNOWN = 0xFFFFFFFF
};
//*** ���� (argument) Ÿ�� ������

typedef struct _lsb_arg_struct
{
	LM_SCR_TYPES _type;								//*** ������ Ÿ��
	void* _data;									//*** ���ڰ� ������ ������
}LM_SCR_ARG;
//*** ���� ����ü


typedef struct F_DESC
{
	char *FileName;
	wchar_t* FileName_uni;
	unsigned char *FileBuffer;
	unsigned int BufferSize;
	unsigned int OffsetInVF;
	bool IsCompressed;
	bool IsScrambled;
}FILE_DESC;
//*���� ����


class LM_BASE_SCRIPT
{
public:
	virtual bool Script_Analysis(wchar_t* SrciptFile, unsigned int code) = 0;
	//*��ũ��Ʈ ������ �ҷ��� �м��ϴ� �Լ�
	virtual void Decompile_To_Code(wchar_t* TxtFile, unsigned int code) = 0;
	//*���������ؼ� ����ϴ� �Լ�
	virtual void Make_To_Script(wchar_t* newLpmFile, unsigned int code) = 0;
	//*��ũ��Ʈ ���Ϸ� ����ϴ� �Լ�
	virtual void Extract_Text_Data(wchar_t* DstTxtFile) = 0;
	//*�ؽ�Ʈ ���� �Լ�
	virtual void Replace_Text_Data(wchar_t* SrcTxtFile, unsigned int code) = 0;
	//*�ؽ�Ʈ ��ü �Լ�
	virtual void Convert_Codepage_J2K() = 0;
	//*�ؽ�Ʈ ����ڵ带 �Ϻ���� �ѱ۷� �ٲٴ� �Լ�
};
//***���̽� ��ũ��Ʈ Ŭ����