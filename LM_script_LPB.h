#pragma once
#include "LM_Base.h"

//*** LPB ��ũ��Ʈ �м� �� ���� �Լ����� �����ϴ� ���


typedef struct _lpb_arg_struct
{
	wchar_t* _arg_name;							//*** ���� �̸�
	LM_SCR_ARG _arg_attr;						//*** ������ �Ӽ�
}LPB_SYS_DATA;
//*lpb ���� �ý��� ���� ����ü


class LPB_SCRIPT : public LM_BASE_SCRIPT
{
public:
	unsigned int lm_version;					//*** ��ũ��Ʈ ����
	wchar_t* _proj_name;						//*** �� ����(������Ʈ)�� �̸�
	unsigned int _resolution1_width;			//*** �ػ� �ʺ�?
	unsigned int _resolution1_height;			//*** �ػ� ����?
	unsigned int _resolution2_width;			//*** �ػ� �ʺ�?
	unsigned int _resolution2_height;			//*** �ػ� ����?
	wchar_t* _init_lsb;							//*** ���۽� ȣ���ϴ� lsb ����
	wchar_t* _exit_lsb;							//*** ����� ȣ���ϴ� lsb ����
	wchar_t* _proj_dir;							//*** ������Ʈ ���丮
	unsigned int _unk_1;						//*** �𸣴� ��
	unsigned char _flag_1;						//*** �÷���
	unsigned char _flag_2;						//*** �÷���
	wchar_t* _support_audio_format;				//*** �����ϴ� ����� ����
	unsigned char _flag_3;						//*** �÷���
	unsigned char _flag_4;						//*** �÷���
	unsigned char _flag_5;						//*** �÷���
	wchar_t* _disk_insert_prompt;				//*** ��ũ �̻��� �� ����
	wchar_t* _exit_prompt;						//*** ���� ����
	unsigned int _sys_setting_count;			//*** �ý��� ���� ����� ��
	LPB_SYS_DATA* _sys_setting_list;			//*** �ý��� ���� ����Ʈ
	unsigned int _dir_count;					//*** �� ����(������Ʈ)���� �̿�Ǵ� ���丮�� ��
	wchar_t** _dir_list;						//*** �� ���ӿ��� �̿�Ǵ� ���丮 ����Ʈ

	LPB_SCRIPT()
	{
		lm_version = 0;
		_proj_name = NULL;
		_resolution1_width = _resolution1_height = _resolution2_width = _resolution2_height = 0;
		_init_lsb = _exit_lsb = NULL;
		_proj_dir = NULL;
		_unk_1 = 0;
		_flag_1 = _flag_2 = _flag_3 = _flag_4 = _flag_5 = 0;
		_support_audio_format = NULL;
		_disk_insert_prompt = _exit_prompt = NULL;
		_sys_setting_count = 0;
		_sys_setting_list = NULL;
		_dir_count = 0;
		_dir_list = NULL;
	}
	//*������

	~LPB_SCRIPT()
	{
		if (_proj_name != NULL) { free(_proj_name); }
		if (_init_lsb != NULL) { free(_init_lsb); }
		if (_exit_lsb != NULL) { free(_exit_lsb); }
		if (_proj_dir != NULL) { free(_proj_dir); }
		if (_support_audio_format != NULL) { free(_support_audio_format); }
		if (_disk_insert_prompt != NULL) { free(_disk_insert_prompt); }
		if (_exit_prompt != NULL) { free(_exit_prompt); }

		if (_sys_setting_list != NULL) {
			for (unsigned int i = 0; i < _sys_setting_count; i++) {
				if (_sys_setting_list[i]._arg_name != NULL) { free(_sys_setting_list[i]._arg_name); }
				if (_sys_setting_list[i]._arg_attr._data != NULL) { free(_sys_setting_list[i]._arg_attr._data); }
			}
			free(_sys_setting_list);
		}

		if (_dir_list != NULL) {
			for (unsigned int i = 0; i < _dir_count; i++) {
				if (_dir_list[i] != NULL) { free(_dir_list[i]); }
			}
			free(_dir_list);
		}
	}
	//*�Ҹ���

	bool Script_Analysis(wchar_t* LpbFile, unsigned int code);
	//*lpb ������ �ҷ��� �м��ϴ� �Լ�

	void Decompile_To_Code(wchar_t* TxtFile, unsigned int code);
	//*���������ؼ� ����ϴ� �Լ�

	void Make_To_Script(wchar_t* newLpbFile, unsigned int code);
	//*lpb ���Ϸ� ����ϴ� �Լ�

	void Extract_Text_Data(wchar_t* DstTxtFile);
	//*�ؽ�Ʈ ���� �Լ�

	void Replace_Text_Data(wchar_t* SrcTxtFile, unsigned int code);
	//*�ؽ�Ʈ ��ü �Լ�

	void Convert_Codepage_J2K();
	//*�ؽ�Ʈ ����ڵ带 �Ϻ���� �ѱ۷� �ٲٴ� �Լ�
};
//*.lpb ��ũ��Ʈ Ŭ����