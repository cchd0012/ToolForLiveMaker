#pragma once
#include "LM_Base.h"

//*** LSB ��ũ��Ʈ �м� �� ���� �Լ����� �����ϴ� ���

//*** lcm : LiveCinema108 �ڿ� (80 02) / LiveCinema112 �ڿ� (20 03)���� ����
//*** LiveCinema108 �϶��� 0x8b - �ؽ�Ʈ - 0x8b - �ؽ�Ʈ ... �̷� ���̰�
//*** LiveCinema112 �϶��� 0xa3 - �ؽ�Ʈ - 0xa3 - �ؽ�Ʈ ... �̷� ����
//*** �� ���� 0�϶��� 0xa3�� ���������� 2�϶��� 0x90�� ������ ������ ���̸�,
//*** �ؽ�Ʈ ������ ���� �� ���δ�
//*** �׷��� �̶��� �մ��� �ʴ� �� ���� �� ����
//*** lmt : LiveMotion111 �ڿ� (20 03)
//*** LiveMotion111 �϶��� 0xa3 - �ؽ�Ʈ - 0xa3 - �ؽ�Ʈ ... �̷� ����
//*** lcm�̵� lmt��	(+0x26) ��ġ�� ���Ե� ���ϸ� �ؽ�Ʈ�� ����


enum LSB_INST_TYPES
{
	TYPE_INST_IF =						0x00,
	TYPE_INST_ELIF =					0x01,
	TYPE_INST_ELSE =					0x02,

	TYPE_INST_LABEL =					0x03,
	TYPE_INST_JUMP =					0x04,

	TYPE_INST_CALL =					0x05,

	TYPE_INST_EXIT =					0x06,

	TYPE_INST_WAIT =					0x07,
	TYPE_INST_TIMER =					0x0B,

	TYPE_INST_CALC_FUNC =				0x0E,

	TYPE_INST_BOX_NEW =					0x08,
	TYPE_INST_IMAGE_NEW =				0x09,
	TYPE_INST_MESSAGE_NEW =				0x0A,
	TYPE_INST_PARTICLE_NEW =			0x24,
	TYPE_INST_FIRE_NEW =				0x25,
	TYPE_INST_EDIT_NEW =				0x2B,
	TYPE_INST_MEMO_NEW =				0x2C,
	TYPE_INST_MAP_IMAGE_NEW =			0x30,
	TYPE_INST_WAVE_NEW =				0x31,
	TYPE_INST_TILE_NEW =				0x32,
	TYPE_INST_SLIDER_NEW =				0x33,
	TYPE_INST_SCROLL_BAR_NEW =			0x34,
	TYPE_INST_GAUGE_NEW =				0x35,
	TYPE_INST_PREV_MENU_NEW =			0x38,

	TYPE_INST_VAR_NEW =					0x0F,
	TYPE_INST_VAR_DELETE =				0x10,

	TYPE_INST_MOVIE =					0x0C,
	TYPE_INST_FLIP =					0x0D,
	TYPE_INST_MOVIE_STOP =				0x15,

	TYPE_INST_CINEMA =					0x17,

	TYPE_INST_GET_PROPERTY =			0x11,
	TYPE_INST_SET_PROPERTY =			0x12,

	TYPE_INST_OBJECT_DELETE =			0x13,

	TYPE_INST_TEXT_INST =				0x14,
	TYPE_INST_TEXT_CLEAR =				0x1C,

	TYPE_INST_CLEAR_HISTORY =			0x16,
	TYPE_INST_CALL_HISTORY =			0x1D,
	TYPE_INST_FORMAT_HISTORY =			0x3A,

	TYPE_INST_CAPTION =					0x18,
	TYPE_INST_CG_CAPTION =				0x36,

	TYPE_INST_MENU =					0x19,
	TYPE_INST_MENU_CLOSE =				0x1A,
	TYPE_INST_BUTTON =					0x1E,

	TYPE_INST_COMMENT =					0x1B,

	TYPE_INST_WHILE =					0x1F,
	TYPE_INST_WHILE_INIT =				0x20,
	TYPE_INST_WHILE_LOOP =				0x21,
	TYPE_INST_BREAK =					0x22,
	TYPE_INST_CONTINUE =				0x23,

	TYPE_INST_GAME_SAVE =				0x26,
	TYPE_INST_GAME_LOAD =				0x27,
	TYPE_INST_CLEAR_LOAD =				0x2F,

	TYPE_INST_PC_RESET =				0x28,
	TYPE_INST_RESET =					0x29,

	TYPE_INST_SOUND =					0x2A,
	TYPE_INST_MEDIA_PLAY =				0x37,

	TYPE_INST_TERMINATE =				0x2D,

	TYPE_INST_DO_EVENT =				0x2E,

	TYPE_INST_PROPERTY_MOTION =			0x39,
	
	TYPE_INST_SAVE_CABINET =			0x3B,
	TYPE_INST_LOAD_CABINET =			0x3C,

	TYPE_INST_MACRO_IFDEF =				0x3D,
	TYPE_INST_MACRO_IFNDEF =			0x3E,
	TYPE_INST_MACRO_ENDIF =				0x3F,

	TYPE_INST_UNKNOWN =					0xFFFFFFFF
};
//*** ��ɾ�(instruction) Ÿ�� ������


enum LSB_OPER_TYPES
{
	TYPE_OP_ASSIGN =					0x01,		//*�� �Ҵ��ϱ�(=)
	TYPE_OP_PLUS,									//*���ϱ�(+, ��ġ �迭 / ���ڿ��� ����)
	TYPE_OP_MINUS,									//*����(-)
	TYPE_OP_MULTIPLY,								//*���ϱ�(*)
	TYPE_OP_DIVIDE,									//*������(/)
	TYPE_OP_MODULUS,								//*������(%)
	TYPE_OP_OR,										//*or(|, ��Ʈ����� ������ �� ����)
	TYPE_OP_AND,									//*and(&, ��Ʈ����� ������ �� ����)
	TYPE_OP_XOR,									//*xor(^)
	TYPE_OP_ARRAY_ACCESS,							//*�迭 ���� ������([])
	TYPE_OP_CALC_FUNC,								//*�Լ� ȣ����(())
	TYPE_OP_EQUALS,									//*��ġ(==)
	TYPE_OP_GREATER,								//*�� ������ �� ū��(>)
	TYPE_OP_LESS,									//*�� ������ �� ������(<)
	TYPE_OP_GREATER_EQUAL,							//*�� ������ ũ�ų� ������(>=)
	TYPE_OP_LESS_EQUAL,								//*�� ������ �۰ų� ������(<=)
	TYPE_OP_SHIFT_LEFT,								//*���� ����Ʈ ����(<<)
	TYPE_OP_SHIFT_RIGHT,							//*������ ����Ʈ ����(<<)
	TYPE_OP_COMBO_STRING,							//*���ڿ� �տ���(++)
	TYPE_OP_NOT_EQUALS,								//*��ġ�� �ƴ���(!=)
	TYPE_OP_UNKNOWN =					0xFFFFFFFF
};
//*** ������(operator) Ÿ�� ������


enum LSB_CALC_FUNC_TYPES
{
	TYPE_CF_IntToStr =				0x00,
	TYPE_CF_IntToHex,
	TYPE_CF_GetProp,
	TYPE_CF_SetProp,
	TYPE_CF_GetArraySize,
	TYPE_CF_Length,
	TYPE_CF_JLength,
	TYPE_CF_Copy,
	TYPE_CF_JCopy,
	TYPE_CF_Delete,
	TYPE_CF_JDelete,
	TYPE_CF_Insert,
	TYPE_CF_JInsert,
	TYPE_CF_CompareStr,
	TYPE_CF_CompareText,
	TYPE_CF_Pos,
	TYPE_CF_JPos,
	TYPE_CF_Trim,
	TYPE_CF_JTrim,
	TYPE_CF_Exists,
	TYPE_CF_Not,
	TYPE_CF_SetArray,
	TYPE_CF_FillMem,
	TYPE_CF_CopyMem,
	TYPE_CF_GetCheck,
	TYPE_CF_SetCheck,
	TYPE_CF_Random,
	TYPE_CF_GetSaveCaption,
	TYPE_CF_ArrayToString,
	TYPE_CF_StringToArray,
	TYPE_CF_IndexOfStr,
	TYPE_CF_SortStr,
	TYPE_CF_ListCompo,
	TYPE_CF_ToClientX,
	TYPE_CF_ToClientY,
	TYPE_CF_ToScreenX,
	TYPE_CF_ToScreenY,
	TYPE_CF_Int,
	TYPE_CF_Float,
	TYPE_CF_Sin,
	TYPE_CF_Cos,
	TYPE_CF_Tan,
	TYPE_CF_ArcSin,
	TYPE_CF_ArcCos,
	TYPE_CF_ArcTan_1,
	TYPE_CF_ArcTan_2,
	TYPE_CF_Hypot,
	TYPE_CF_IndexOfMenu,
	TYPE_CF_Abs,
	TYPE_CF_Fabs,
	TYPE_CF_VarExists,
	TYPE_CF_EncodeDate,
	TYPE_CF_EncodeTime,
	TYPE_CF_DecodeDate,
	TYPE_CF_DecodeTime,
	TYPE_CF_GetYear,
	TYPE_CF_GetMonth,
	TYPE_CF_GetDay,
	TYPE_CF_GetHour,
	TYPE_CF_GetMin,
	TYPE_CF_GetSec,
	TYPE_CF_GetWeek,
	TYPE_CF_GetWeekStr,
	TYPE_CF_GetWeekJStr,
	TYPE_CF_FixStr,
	TYPE_CF_GetDisplayMode,
	TYPE_CF_AddArray,
	TYPE_CF_InsertArray,
	TYPE_CF_DeleteArray,
	TYPE_CF_InPrimary,
	TYPE_CF_CopyArray,
	TYPE_CF_FileExists,
	TYPE_CF_LoadTextFile,
	TYPE_CF_LowerCase,
	TYPE_CF_UpperCase,
	TYPE_CF_ExtractFilePath,
	TYPE_CF_ExtractFileName,
	TYPE_CF_ExtractFileExt,
	TYPE_CF_IsPathDelimiter,
	TYPE_CF_AddBackSlash,
	TYPE_CF_ChangeFileExt,
	TYPE_CF_IsDelimiter,
	TYPE_CF_StringOfChar,
	TYPE_CF_StringReplace,
	TYPE_CF_AssignTemp,
	TYPE_CF_HanToZen,
	TYPE_CF_ZenToHan,
	TYPE_CF_DBCreateTable,
	TYPE_CF_DBSetActive,
	TYPE_CF_DBAddField,
	TYPE_CF_DBSetRecNo,
	TYPE_CF_DBInsert,
	TYPE_CF_DBDelete,
	TYPE_CF_DBGetInt,
	TYPE_CF_DBSetInt,
	TYPE_CF_DBGetFloat,
	TYPE_CF_DBSetFloat,
	TYPE_CF_DBGetBool,
	TYPE_CF_DBSetBool,
	TYPE_CF_DBGetStr,
	TYPE_CF_DBSetStr,
	TYPE_CF_DBRecordCount,
	TYPE_CF_DBFindFirst,
	TYPE_CF_DBFindLast,
	TYPE_CF_DBFindNext,
	TYPE_CF_DBFindPrior,
	TYPE_CF_DBLocate,
	TYPE_CF_DBLoadTsvFile,
	TYPE_CF_DBDirectGetInt,
	TYPE_CF_DBDirectSetInt,
	TYPE_CF_DBDirectGetFloat,
	TYPE_CF_DBDirectSetFloat,
	TYPE_CF_DBDirectGetBool,
	TYPE_CF_DBDirectSetBool,
	TYPE_CF_DBDirectGetStr,
	TYPE_CF_DBDirectSetStr,
	TYPE_CF_DBCopyTable,
	TYPE_CF_DBDeleteTable,
	TYPE_CF_DBInsertTable,
	TYPE_CF_DBCopy,
	TYPE_CF_DBClearTable,
	TYPE_CF_DBSort,
	TYPE_CF_DBGetActive,
	TYPE_CF_DBGetRecNo,
	TYPE_CF_DBClearRecord,
	TYPE_CF_SetWallPaper,
	TYPE_CF_Min,
	TYPE_CF_Max,
	TYPE_CF_Fmin,
	TYPE_CF_Fmax,
	TYPE_CF_GetVarType,
	TYPE_CF_GetEnabled,
	TYPE_CF_SetEnabled,
	TYPE_CF_AddDelimiter,
	TYPE_CF_ListSaveCaption,
	TYPE_CF_OpenUrl,
	TYPE_CF_Calc,
	TYPE_CF_SaveScreen,
	TYPE_CF_StrToIntDef,
	TYPE_CF_StrToFloatDef,
	TYPE_CF_GetVisible,
	TYPE_CF_SetVisible,
	TYPE_CF_GetHistoryCount,
	TYPE_CF_GetHistoryMaxCount,
	TYPE_CF_SetHistoryMaxCount,
	TYPE_CF_GetGroupIndex,
	TYPE_CF_GetSelected,
	TYPE_CF_SetSelected,
	TYPE_CF_SelectOpenFile,
	TYPE_CF_SelectSaveFile,
	TYPE_CF_SelectDirectory,
	TYPE_CF_ExtractFile,
	TYPE_CF_Chr,
	TYPE_CF_Ord,
	TYPE_CF_InCabinet,
	TYPE_CF_PushVar,
	TYPE_CF_PopVar,
	TYPE_CF_DeleteStack,
	TYPE_CF_CopyFile,
	TYPE_CF_DBGetTableCount,
	TYPE_CF_DBGetTable,
	TYPE_CF_CreateObject,
	TYPE_CF_DeleteObject,
	TYPE_CF_GetItem,
	TYPE_CF_UniqueArray,
	TYPE_CF_TrimArray,
	TYPE_CF_GetImeOpened,
	TYPE_CF_SetImeOpened,
	TYPE_CF_Alert,
	TYPE_CF_COUNT,					//*** calc_func�� �� ���� ���� ����

	TYPE_CF_UNKNOWN = 0xFFFFFFFF
};
//*** calc_func(Ư���Լ�) ������


enum LSB_EV_OPCODE_TYPES
{
	TYPE_EV_OP_CHAR =				0x01,
	TYPE_EV_OP_ALIGN =				0x02,
	TYPE_EV_OP_RETURN =				0x03,
	TYPE_EV_OP_INDENT =				0x04,
	TYPE_EV_OP_UNDENT =				0x05,
	TYPE_EV_OP_EVENT =				0x06,
	TYPE_EV_OP_VAR =				0x07,
	TYPE_EV_OP_IMG =				0x09,
	TYPE_EV_OP_HISTORY_CHAR =		0x0A,
	TYPE_EV_OP_STR =				0xFFFFFFFF
};
//*** �̺�Ʈ ��ɾ�(opcode) Ÿ�� ������



//*** Ŭ���� ���� ***//
class LSB_PARAMETERS;
class LSB_EV_TXT_ATTRIBUTE;
class LSB_EVENT_OP_INST;
class LSB_EVENT_ARG_LIST;
class LSB_EVENT;
class LSB_INST_BASE;
class LSB_HEADER;
class LSB_BODY;
class LSB_SCRIPT;
//*** Ŭ���� ���� ***//



//*Label/SetLabel/Event ������Ʈ�� Argument ������Ʈ�� ���� Ŭ�������� �Ļ��� ������ �ľ� �� �� �ϴ�
//*ParseEventBlock�� TYPE_INST_TEXT_INST �� ���� �ҷ����̴� �� �ϴ�
//*�̰͵� Argument�� ġ�� �ɵ�?
//*���� ���� �� 1�� �з����ͷ� ������ �ִ� �� ���?


typedef struct _lsb_txt_list
{
	unsigned int _line;
	unsigned int _txt_count;
	wchar_t** _txt_list_per_inst;
}LSB_TEXTS_PER_INST;
//*�� ��ɾ� �� �ؽ�Ʈ ����Ʈ�� �ش�Ǵ� ����ü

typedef struct _lsb_parameter_struct
{
	LSB_OPER_TYPES _type;							//*** �з������� ������ Ÿ��
	wchar_t* _name;									//*** �з������� �̸�
	unsigned int arg_count;							//*** ������ ��
	LM_SCR_ARG* arg_list;							//*** ���� ����Ʈ
	LSB_CALC_FUNC_TYPES _calc_func;					//*** Ư�� �Լ�
}LSB_PARAMETER;
//*** �з����� ����ü

class LSB_PARAMETERS
{
public:
	LSB_PARAMETER* _list;							//*** �з����� ����Ʈ
	unsigned int _count;							//*** �з������� ��

	LSB_PARAMETERS()
	{
		_list = NULL;
		_count = 0;
	}
	//*������

	~LSB_PARAMETERS()
	{
		_release();
	}
	//*�ı���

	void _read_parameter_list(unsigned char** _lsb_buffer_pnt, unsigned int code);
	//*�з����͸� �о���̴� �Լ�

	void _decompile_code(HANDLE hWrite, unsigned int code, unsigned int _indent);
	//*�������� �Լ�

	void _write_as_lsb(HANDLE hNewLsb, unsigned int code);
	//*lsb ���Ϸ� ����ϴ� �Լ�

	void _extract_text(HANDLE hTxt);
	//*�ؽ�Ʈ ���� �Լ�

	void _replace_text(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int* accum_count);
	//*�ؽ�Ʈ ��ü �Լ�

	void _change_code_J2K();
	//*�ؽ�Ʈ �ڵ� ���� �Լ�

	void _release();
	//*�з����͸� �����ϴ� �Լ�
};
//*** �з����� ����Ʈ Ŭ����


class LSB_EV_TXT_ATTRIBUTE
{
public:
	unsigned int _tpword_ver;						//*** ���� �̺�Ʈ ���� ����
	unsigned int _ev_op_ref_count;					//*** �� �̺�Ʈ ��ɾ�� ������ Ƚ��
	unsigned int _txt_color;						//*** �ؽ�Ʈ�� ����
	unsigned int _unk_2;							//*** �𸣴� ����
	unsigned int _unk_3;							//*** �𸣴� ����
	unsigned char _unk_4;							//*** �𸣴� ����
	unsigned char _unk_5;							//*** �𸣴� ����
	unsigned char _unk_6;							//*** �𸣴� ����
	unsigned int _unk_7;							//*** �𸣴� ����
	wchar_t* _font_name;							//*** ��Ʈ��, ������ �̸� ������ ��Ʈ�� ����Ǵ� �� ��
	wchar_t* _ruby_txt;								//*** ��� ���ڰ� ����� �� ���̴� �ؽ�Ʈ
	unsigned int _unk_10;							//*** �𸣴� ����
	unsigned int _unk_11;							//*** �𸣴� ����

	LSB_EV_TXT_ATTRIBUTE (unsigned int tpword_ver)
	{
		_tpword_ver = tpword_ver;
		_ev_op_ref_count = _txt_color = _unk_2 = _unk_3 = _unk_7 = _unk_10 = _unk_11 = 0;
		_unk_4 = _unk_5 = _unk_6 = 0;
		_font_name = _ruby_txt = NULL;
	}
	//*������

	~LSB_EV_TXT_ATTRIBUTE()
	{
		_release();
	}
	//*�ı���

	void _read_var_data(unsigned char** _lsb_buffer_pnt, unsigned int code);
	//*�̺�Ʈ ���� ���� �б�

	void _decompile_code(HANDLE hWrite, unsigned int code, unsigned int _indent);
	//*�������� �Լ�

	void _recompile_from_txt(wchar_t* _code_txt_buffer);
	//*�������� �Լ� (���� : �ش� �̺�Ʈ ���� �����Ͱ� ����ִ� �ؽ�Ʈ ������ �Ϻ�)

	void _write_as_lsb(HANDLE hNewLsb, unsigned int code);
	//*lsb ���Ϸ� ����ϴ� �Լ�

	void _extract_text(HANDLE hTxt);
	//*�ؽ�Ʈ ���� �Լ�

	void _change_code_J2K();
	//*�ؽ�Ʈ �ڵ� ���� �Լ�

	void _release()
	{
		if (_font_name != NULL) { free(_font_name); }
		if (_ruby_txt != NULL) { free(_ruby_txt); }
	}
	//*���� �Լ�
};
//*** �̺�Ʈ ���� �Ӽ� Ŭ����

typedef struct _lsb_ev_attr_info
{
	unsigned int _attr_idx;							//*�ش� �ؽ�Ʈ ������ ����� �Ӽ��� �ε���
	unsigned int _start_txt_pos;					//*����� �ؽ�Ʈ ������ ���� ����
	unsigned int _end_txt_pos;						//*����� �ؽ�Ʈ ������ �� ����
}LSB_EV_ATTR_INFO;
//*** �̺�Ʈ ���� �Ӽ� ���� �� ���̴� ����ü

typedef struct _lsb_ev_type2_type3
{
	unsigned char _unk_1;
	unsigned int _unk_2;
	unsigned int _unk_3;
}LSB_EV_TYPE2_TYPE3;
//*** _unk_1�� 0�� �ƴϰ� type�� 2�� 3�� �� ���� ����ü

class LSB_EVENT_OP_INST
{
public:
	unsigned int _tpword_ver;						//*** tpword�� ����
	unsigned int _unk_1;							//*** ���� ������ 105���� ��� �о����

	wchar_t* _s;									//*_s, _extra_data, _i�� 0x01 �� ���ȿ��� ���� ����
	unsigned int _extra_data;						//*_str�� �޶����� �� �ʹ�
	wchar_t* _str;									//*�׷��� �׿� Ưȭ�ǰ� ¥�� �� �� �ϴ�
	unsigned int _default_attr_idx;					//*�� �̺�Ʈ ��ɾ �����ϴ� �ؽ�Ʈ �Ӽ� �ε���
													//*�� TYPE_EV_OP_CHAR�� ��쿡�� �̰� �ϳ� ������� �ȵȴ�
	unsigned int _i_2;
	unsigned int _i_3;
	unsigned char _b;								//*��� ev_op�� �����Ͽ� ���� �� �ְ� ������ ���´�	

	LSB_EV_TYPE2_TYPE3 _unk_t2_t3;					//*type�� 2�� 3�� �� ���̴� �迭
	unsigned int _unk_i_list[6];					//*type�� 9�� �� ���̴� �迭

	//*** TYPE_EV_OP_CHAR ���� ���� ***//
	unsigned int _ev_attr_info_cnt;					//*�̺�Ʈ�� �ٸ��� ����Ǵ� �Ӽ� ����
	unsigned int* _ev_attr_idx_ref_list;			//*�� �̺�Ʈ �� �Ӽ��� ����Ƚ�� �����ϴ� ����
	unsigned int* _idx_list;						//*�迭 ������ ���� �� ���ں� �ε��� ����
	LSB_EV_TXT_ATTRIBUTE **_ev_attr_list_pnt;		//*�̺�Ʈ �� �Ӽ� �迭�� ����Ű�� ������, �ؽ�Ʈ�� �ݿ��� �� �ʿ�
	LSB_EV_ATTR_INFO* _ev_attr_info_list;			//*��� � �Ӽ��� �����ؾ� �ϴ��� ������ ������ �迭
	unsigned int _last_idx;							//*���������� ���� �ؽ�Ʈ�� ���� �Ӽ� �ε���
	//*���� �ٸ� ������ �󸶳� �ִ��� �Ǻ��ϱ� ���� ����
	//*** TYPE_EV_OP_CHAR ���� ���� ***//

	LSB_EV_OPCODE_TYPES _op_type;					//*** �ش� ������ ��ɾ� Ÿ��
	LSB_EVENT_OP_INST* _prev;						//*** ���� ����(����Ʈ �̿�)
	LSB_EVENT_OP_INST* _next;						//*** ���� ����(����Ʈ �̿�)

	LSB_EVENT_OP_INST (LSB_EV_OPCODE_TYPES op_type, LSB_EV_TXT_ATTRIBUTE** ev_attr_list, unsigned int ev_attr_cnt, unsigned int tpword_ver)
	{
		_tpword_ver = tpword_ver;
		_unk_1 = 0;
		_op_type = op_type;
		_prev = _next = NULL;
		_ev_attr_list_pnt = ev_attr_list;
		_ev_attr_info_cnt = 0;
		_ev_attr_idx_ref_list = (unsigned int*)malloc(sizeof(int) * ev_attr_cnt);
		memset(_ev_attr_idx_ref_list, 0, (sizeof(int) * ev_attr_cnt));
		_ev_attr_info_list = NULL;
		_idx_list = NULL;
		_last_idx = 0;

		_s = _str = NULL;
		_extra_data = _i_2 = _i_3 = 0;
		_default_attr_idx = 0xFFFFFFFF;
		_b = 0;
		memset(&_unk_t2_t3, 0, sizeof(LSB_EV_TYPE2_TYPE3));
		memset(_unk_i_list, 0, (sizeof(int) * 6));
	}
	//*������

	~LSB_EVENT_OP_INST()
	{
		_release();
	}
	//*�Ҹ���

	void _read_ev_data(unsigned char** _lsb_buffer_pnt, unsigned int txt_accum_idx, unsigned int code);
	//*��� ��ɾ� Ÿ�Կ� ���ؼ� �о���̴� ��ɾ�

	void _read_char_data(unsigned char** _lsb_buffer_pnt, unsigned int txt_accum_idx, unsigned int code);
	//*�̺�Ʈ ���� char ���� �б�

	void _decode_sharp_encoding(char **_str_addr);
	//*�̺�Ʈ ��ɹ����� # + ���ڹ��ڿ��� ���ڵ��� ���� ������� ��������

	void _decompile_code(HANDLE hWrite, unsigned int code, unsigned int _indent);
	//*�������� �Լ�

	void _recompile_from_txt(wchar_t* _code_txt_buffer, unsigned int code);
	//*�������� �Լ� (���� : �ش� �̺�Ʈ ���� �����Ͱ� ����ִ� �ؽ�Ʈ ������ �Ϻ�)

	void _set_char_data();
	//*�̺�Ʈ ���� _str ������ ������ ���� �����ϱ�

	void _encode_sharp_prefix(char** _str_addr);
	//*�̺�Ʈ ��ɹ����� [#] ~ [#] ���̿� �ִ� ���ڿ��� # + ���ڹ��ڿ��� ���ڵ��ϱ�

	void _write_as_lsb(HANDLE hNewLsb, unsigned int code, unsigned int *_total_inst_count);
	//*lsb ���Ϸ� ����ϴ� �Լ�, ��ü ī��Ʈ�� ����ؾ� ��

	void _extract_text(HANDLE hTxt);
	//*�ؽ�Ʈ ���� �Լ�

	void _replace_text(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int *accum_count);
	//*�ؽ�Ʈ ��ü �Լ�

	void _change_code_J2K();
	//*�ؽ�Ʈ �ڵ� ���� �Լ�

	void _release()
	{
		if (_s != NULL) { free(_s); }
		if (_str != NULL) { free(_str); }
		if (_ev_attr_idx_ref_list != NULL) { free(_ev_attr_idx_ref_list); }
		if (_ev_attr_info_list != NULL) { free(_ev_attr_info_list); }
		if (_idx_list != NULL) { free(_idx_list); }
	}
	//*���� �Լ�
};
//*** �̺�Ʈ ���� ���� Ŭ����

class LSB_EVENT_ARG_LIST
{
public:
	unsigned int _tpword_ver;						//*** tpword�� ����
	unsigned int _count;							//*** ����Ʈ�� ���� ������ �� ��
	LSB_EVENT_OP_INST* _dummy_start;				//*** ���� ���� ������
	LSB_EVENT_OP_INST* _dummy_end;					//*** �� ���� ������

	LSB_EVENT_ARG_LIST (LSB_EV_TXT_ATTRIBUTE** ev_attr_list, unsigned int ev_attr_cnt, unsigned int tpword_ver)
	{
		_count = 0;
		_tpword_ver = tpword_ver;
		_dummy_start = new LSB_EVENT_OP_INST(TYPE_EV_OP_STR, ev_attr_list, ev_attr_cnt, _tpword_ver);
		_dummy_end = new LSB_EVENT_OP_INST(TYPE_EV_OP_STR, ev_attr_list, ev_attr_cnt, _tpword_ver);
		_dummy_start->_next = _dummy_end;
		_dummy_end->_prev = _dummy_start;
	}
	//*������

	~LSB_EVENT_ARG_LIST()
	{
		_release();
	}
	//*�Ҹ���

	void Append (LSB_EVENT_OP_INST *_n)
	{
		if (_n == NULL) { return; }
		LSB_EVENT_OP_INST* _last = _dummy_end->_prev;
		_last->_next = _n;
		_n->_next = _dummy_end;
		_dummy_end->_prev = _n;
		_n->_prev = _last;
		_count++;
	}
	//*������� ���� �߰� �Լ� (null�� �ƴ� �͸�)
	
	void _release()
	{
		for (unsigned int i = 0; i < _count;i++) {
			LSB_EVENT_OP_INST* _d = _dummy_start->_next;
			LSB_EVENT_OP_INST* _d_n = _dummy_start->_next->_next;
			_dummy_start->_next = _d_n;
			if (_d_n != NULL) { _d_n->_prev = _dummy_start; }
			delete _d;
		}
		//*�տ������� ���ʴ�� ��� ����Ʈ ����
		delete _dummy_start;
		delete _dummy_end;
		//*���� / �� ���̸���Ʈ ����
	}
	//*���� �Լ�
};
//*** �̺�Ʈ ���� ���� ����Ʈ Ŭ����

typedef struct _lsb_evh_elem
{
	unsigned int _ref_count;						//*** �� �Ӽ� ȣ�� Ƚ��
	wchar_t* _str;									//*** ���ڿ�, �Ƹ� ��ɾ� ������ �� ������ ����, ���� ��ȯ �ʿ�
	unsigned int _unk_2;							//*** �𸣴� �� 2

	void _recompile_from_txt(wchar_t* _code_txt_buffer, unsigned int code);
	//*�������� �Լ� (���� : �ش� �̺�Ʈ ���� �����Ͱ� ����ִ� �ؽ�Ʈ ������ �Ϻ�)
}LSB_EVH_ELEM;
//*** �̺�Ʈ Ŭ���� ��� ����ü�� ����

class LSB_EVENT_HEADER
{
public:
	unsigned int _type;								//*** �̺�Ʈ ����� Ÿ��
	unsigned int _several_op_count;					//*** ȭ�鿡 ��µǴ� ���ڿ��� ���õ� ī��Ʈ
	unsigned int _unk_1;							//*** �𸣴� �� 1
	unsigned int _unk_2;							//*** �𸣴� �� 2 (Ÿ�� 2������ Ȱ��ȭ)
	wchar_t* _str;									//*** ���� �� ���ڿ�, �Լ� ��� ����? (Ÿ�� 2������ Ȱ��ȭ)
	unsigned int _elem_count;						//*** ���� ���ҵ� ����
	LSB_EVH_ELEM* _elem_list;						//*** ���� ���ҵ� ����Ʈ

	LSB_EVENT_HEADER()
	{
		_type = 0;
		_several_op_count = 0;
		_unk_1 = _unk_2 = 0;
		_str = NULL;
		_elem_count = 0;
		_elem_list = NULL;
	}
	//*������
	
	~LSB_EVENT_HEADER()
	{
		_release();
	}
	//*�Ҹ���

	void _read_event_header(unsigned char** _lsb_buffer_pnt, unsigned int code);
	//*�̺�Ʈ ����� �о���̴� �Լ�

	void _release()
	{
		if (_str != NULL) { free(_str); }
		if (_elem_list != NULL) { free(_elem_list); }
	}
	//*���� �Լ�

	void _decompile_code(HANDLE hWrite, unsigned int code, unsigned int _indent);
	//*�������� �Լ�

	void _recompile_from_txt(wchar_t* _code_txt_buffer, unsigned int code);
	//*�������� �Լ� (���� : �ش� �̺�Ʈ ���� �����Ͱ� ����ִ� �ؽ�Ʈ ������ �Ϻ�)

	void _write_as_lsb(HANDLE hNewLsb, unsigned int code);
	//*lsb ���Ϸ� ����ϴ� �Լ�

	void _extract_text(HANDLE hTxt);
	//*�ؽ�Ʈ ���� �Լ�

	void _replace_text(LSB_TEXTS_PER_INST* txt_list_elem) { ; }
	//*�ؽ�Ʈ ��ü �Լ� (��� ����)

	void _change_code_J2K();
	//*�ؽ�Ʈ �ڵ� ���� �Լ�
};
//*** �̺�Ʈ Ŭ���� ���� ���? Ŭ����, �� ������ ���� type 1�� 6�� ����Ǵ� �� ����

class LSB_EVENT
{
public:
	wchar_t* _tpword;								//*** ���� ���ڿ�(TpWord)
	wchar_t *_ver;									//*** �̺�Ʈ ��(TpWord)�� ����
	unsigned int _tpword_ver;						//*** �� ���� ����ȭ�� ��

	LSB_EVENT_HEADER* _ev_header;					//*** �̺�Ʈ ��� (������ 105 �̻��� �� ����)

	unsigned int _attribute_count;					//*** �̺�Ʈ �� �������� ��
	LSB_EV_TXT_ATTRIBUTE** _attribute_list;			//*** �̺�Ʈ �� ������ ����Ʈ

	unsigned int _total_inst_count;					//*** �̺�Ʈ �� ��ɾ���� ��
	LSB_EVENT_ARG_LIST *_main_inst_list;			//*** �ֿ� �̺�Ʈ ��ɾ� ����Ʈ

	unsigned int _several_inst_count;				//*** �� ���ں��� �ɰ��� �� ������ ����

	LSB_EVENT ()
	{
		_tpword = _ver = NULL;
		_tpword_ver = 0;
		_ev_header = NULL;
		_attribute_count = 0;
		_attribute_list = NULL;
		_total_inst_count = 0;
		_main_inst_list = NULL;
		_several_inst_count = 0;
	}
	//*������

	~LSB_EVENT()
	{
		_release();
	}
	//*�Ҹ���

	void _read_event_script(unsigned char** _lsb_buffer_pnt, unsigned int code);
	//*�̺�Ʈ ���� �о���̴� �Լ�

	void _release()
	{
		if (_tpword != NULL) { free(_tpword); }
		if (_ver != NULL) { free(_ver); }
		if (_ev_header != NULL) { delete _ev_header; }
		if (_attribute_list != NULL) {
			for (unsigned int i = 0; i < _attribute_count; i++) { delete _attribute_list[i]; }
			free(_attribute_list);
		}
		delete _main_inst_list;
	}
	//*���� �Լ�

	void _decompile_code(HANDLE hWrite, unsigned int code, unsigned int _indent);
	//*�������� �Լ�

	void _recompile_from_txt (wchar_t *_code_txt_buffer, unsigned int code);
	//*�������� �Լ� (���� : �ش� �̺�Ʈ ���� �����Ͱ� ����ִ� �ؽ�Ʈ ������ �Ϻ�)

	void _write_as_lsb(HANDLE hNewLsb, unsigned int code);
	//*lsb ���Ϸ� ����ϴ� �Լ�

	void _extract_text(HANDLE hTxt);
	//*�ؽ�Ʈ ���� �Լ�

	void _replace_text(LSB_TEXTS_PER_INST* txt_list_elem);
	//*�ؽ�Ʈ ��ü �Լ�(�� ����)

	void _change_code_J2K();
	//*�ؽ�Ʈ �ڵ� ���� �Լ�
};
//*** �̺�Ʈ �� Ŭ����


typedef struct _map_data
{
	const wchar_t* _str;
	void* _data;
}LSB_MAP_DATA;
//*** ���ڿ��� �����͸� �������ִ� ����ü

class LSB_INST_BASE
{
public:
	//---- �������� ������ ���� ----//
	LSB_MAP_DATA* _data_chunks;						//*** ���ڿ��� �� �з����� ����Ʈ �� �����͸� ���ν�Ų ����
	unsigned int _data_chunks_count;				//*** �з����� ����Ʈ�� ��
	//---- �������� ������ ���� ----//
	unsigned int _script_ver;						//*** lsb ��ũ��Ʈ�� ����
	LSB_HEADER* _header;							//*** lsb ��� ������
	unsigned int _indent;							//*** �鿩���� ĭ��?
	unsigned char _mute;							//*** ���� ����?
	unsigned char _not_update;						//*** static ����?
	unsigned int _line;								//*** �ش� ��ɾ ��ġ�� ����
	LSB_INST_TYPES _op_type;						//*** ��ɾ� Ÿ��
	//*���� ����

	LSB_INST_BASE (unsigned int script_ver, LSB_HEADER* header)
	{
		_script_ver = script_ver;
		_header = header;
		_op_type = TYPE_INST_UNKNOWN;
		_data_chunks = NULL;
		_data_chunks_count = 0;
		_indent = 0;
		_mute = 0;
		_not_update = 0;
		_line = 0;
	}
	//*������
	
	~LSB_INST_BASE()
	{ 
		if (_data_chunks != NULL) {
			for (unsigned int i = 0; i < _data_chunks_count; i++) {
				if ((wcscmp(_data_chunks[i]._str, TEXT("Result")) == 0)
					|| (wcscmp(_data_chunks[i]._str, TEXT("Script_Page")) == 0)
					|| (wcscmp(_data_chunks[i]._str, TEXT("Label")) == 0)
					|| (wcscmp(_data_chunks[i]._str, TEXT("Target_Label_Offset")) == 0)
					|| (wcscmp(_data_chunks[i]._str, TEXT("Parameter_Count")) == 0)
					|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Name")) == 0)
					|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Type")) == 0)
					|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Scope")) == 0)
					|| (wcscmp(_data_chunks[i]._str, TEXT("Var_Scope_Byte")) == 0)
					|| (wcscmp(_data_chunks[i]._str, TEXT("All_Clear_Byte")) == 0))
				{ 
					free(_data_chunks[i]._data); 
				}
				else if (wcscmp(_data_chunks[i]._str, TEXT("Event_Block")) == 0)
				{
					LSB_EVENT* _t = (LSB_EVENT*)_data_chunks[i]._data;
					delete _t;
				}
				else { 
					LSB_PARAMETERS* _t = (LSB_PARAMETERS*)_data_chunks[i]._data;
					delete _t;
				}
				//*��Ī�� ���ڿ� ���� �� 8���� ���ٸ� data���� �з����� ����Ʈ�� �ƴ� �ܼ� �������̹Ƿ� free
				//*Ȥ�� "Event_Block"�� ���ٸ� �̺�Ʈ �� ������,
				//*�̿� ���� �з����� ����Ʈ�� �����Ͽ� delete�� �����Ѵ�
			}
			free(_data_chunks);
		}
	}
	//*�ı��� (�μ��鵵 �Ű�Ἥ ������)

	LSB_MAP_DATA * _get_initialized_data_chunks (unsigned int __data_chunks_count)
	{
		LSB_MAP_DATA *__data_chunks = (LSB_MAP_DATA*)malloc(sizeof(LSB_MAP_DATA) * __data_chunks_count);
		memset(__data_chunks, 0, (sizeof(LSB_MAP_DATA) * __data_chunks_count));
		return __data_chunks;
	}
	//*�з����� ����Ʈ �ʱ�ȭ�� �� ��ȯ

	void _read_inst_data(unsigned char** _lsb_buffer_pnt, unsigned int code) {
		unsigned char* lsb_buffer_pnt = (*_lsb_buffer_pnt);

		_indent = *(unsigned int*)(lsb_buffer_pnt); lsb_buffer_pnt += sizeof(int);
		_mute = *(lsb_buffer_pnt); lsb_buffer_pnt += sizeof(char);
		_not_update = *(lsb_buffer_pnt); lsb_buffer_pnt += sizeof(char);
		_line = *(unsigned int*)(lsb_buffer_pnt); lsb_buffer_pnt += sizeof(int);
		//*���� ������ �о���̱�

		this->_read_from_buffer(&lsb_buffer_pnt, code);
		(*_lsb_buffer_pnt) = lsb_buffer_pnt;
	}
	//*������ �о���� �� ���� �Լ�

	virtual void _read_from_buffer (unsigned char** _lsb_buffer_pnt, unsigned int code) = 0;
	//*���ۿ��� �о���̴� �Լ�

	void _decompile_code(HANDLE hWrite, unsigned int offset, unsigned int code, unsigned int _indent);
	//*�������� �Լ�

	void _write_as_lsb(HANDLE hNewLsb, unsigned int code);
	//*lsb ���Ϸ� ����ϴ� �Լ�

	void _extract_text(HANDLE hTxt);
	virtual void _extract_text_each_inst(HANDLE hTxt) = 0;
	//*�ؽ�Ʈ ���� �Լ� �� �� ��ɾ�� �����ϴ� �Լ�

	void _replace_text(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code);
	virtual void _replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code) = 0;
	//*�ؽ�Ʈ ��ü �Լ� �� �� ��ɾ�� ��ü�ϴ� �Լ�

	void _change_code_J2K();
	//*�ؽ�Ʈ �ڵ� ���� �Լ�
};
//*�⺻ Ŭ����

#define DEFINE_SCRIPT_CLASS(script_class) \
class script_class : public LSB_INST_BASE \
{ \
public: \
	script_class (LSB_INST_TYPES _op_type, unsigned int script_ver, LSB_HEADER* header); \
	void _read_from_buffer(unsigned char** _lsb_buffer_pnt, unsigned int code); \
	void _extract_text_each_inst(HANDLE hTxt); \
	void _replace_text_each_inst(LSB_TEXTS_PER_INST* txt_list_elem, unsigned int code); \
}
//*��ũ��Ʈ �Լ��� ���� ����

DEFINE_SCRIPT_CLASS(LSB_INST_IF);							//*if ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_ELIF);							//*elif ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_ELSE);							//*else ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_LABEL);						//*label ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_JUMP);							//*jump ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_CALL);							//*call ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_EXIT);							//*exit ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_WAIT);							//*wait ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_TIMER);						//*timer ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_CALC_FUNC);					//*caculation function(Ư���Լ�) ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_BOX_NEW);						//*box_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_IMAGE_NEW);					//*image_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MESSAGE_NEW);					//*message_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_PARTICLE_NEW);					//*particle_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_FIRE_NEW);						//*fire_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_EDIT_NEW);						//*edit_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MEMO_NEW);						//*memo_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MAP_IMAGE_NEW);				//*map_image_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_WAVE_NEW);						//*wave_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_TILE_NEW);						//*tile_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_SLIDER_NEW);					//*slider_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_SCROLL_BAR_NEW);				//*scroll_bar_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_GAUGE_NEW);					//*gauge_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_PREV_MENU_NEW);				//*prev_menu_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_VAR_NEW);						//*var_new ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_VAR_DELETE);					//*var_delete ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MOVIE);						//*movie ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_FLIP);							//*flip ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MOVIE_STOP);					//*movie_stop ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_CINEMA);						//*cinema ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_GET_PROPERTY);					//*get_property ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_SET_PROPERTY);					//*set_property ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_OBJECT_DELETE);				//*object_delete ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_TEXT_INST);					//*text_inst ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_TEXT_CLEAR);					//*text_clear ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_CLEAR_HISTORY);				//*clear_history ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_CALL_HISTORY);					//*call_history ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_FORMAT_HISTORY);				//*format_history ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_CAPTION);						//*caption ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_CG_CAPTION);					//*cg_caption ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MENU);							//*menu ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MENU_CLOSE);					//*menu_close ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_BUTTON);						//*button ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_COMMENT);						//*comment ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_WHILE);						//*while ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_WHILE_INIT);					//*while_init ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_WHILE_LOOP);					//*while_loop ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_BREAK);						//*break ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_CONTINUE);						//*continue ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_GAME_SAVE);					//*game_save ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_GAME_LOAD);					//*game_load ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_CLEAR_LOAD);					//*clear_load ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_PC_RESET);						//*pc_reset ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_RESET);						//*reset ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_SOUND);						//*sound ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MEDIA_PLAY);					//*media_play ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_TERMINATE);					//*terminate ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_DO_EVENT);						//*do_event ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_PROPERTY_MOTION);				//*property_motion ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_SAVE_CABINET);					//*save_cabinet ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_LOAD_CABINET);					//*load_cabinet ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MACRO_IFDEF);					//*IFDEF ��ó�� ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MACRO_IFNDEF);					//*IFNDEF ��ó�� ��ɾ�
DEFINE_SCRIPT_CLASS(LSB_INST_MACRO_ENDIF);					//*ENDIF ��ó�� ��ɾ�

//*** �⺻ �ν�Ʈ���� Ŭ���� �� �Ļ� Ŭ������




class LSB_HEADER
{
public:
	unsigned int _script_ver;					//*** lsb ��ũ��Ʈ�� ����
	unsigned int opcode_count;					//*** ��ɾ� ������Ʈ�� ��? (��ü�� 0x40�� �ɵ�)
	unsigned int opcode_property_count;			//*** �ش� ��ɾ ���� �� �ִ� �Ӽ� ��? (��ü�� 0x16�ε�?)
	unsigned char** opcode_property_table;		//*** �� ��ɾ� �ڵ忡 ���� �߰� ������ ���� ���̺�
	bool** opcode_property_boolean_table;		//*** �� ���̺��� boolean ����
	//*�̰͵��� �Ƹ� �ش� ��ɾ 

	LSB_HEADER(unsigned int script_ver)
	{
		_script_ver = script_ver;
		opcode_count = opcode_property_count = 0;
		opcode_property_table = NULL;
		opcode_property_boolean_table = NULL;
	}
	//*������

	~LSB_HEADER()
	{
		if (opcode_property_table != NULL) {
			for (unsigned int i = 0; i < opcode_count; i++) { free(opcode_property_table[i]); }
			free(opcode_property_table); opcode_property_table = NULL;
		}
		if (opcode_property_boolean_table != NULL) {
			for (unsigned int i = 0; i < opcode_count; i++) { free(opcode_property_boolean_table[i]); }
			free(opcode_property_boolean_table); opcode_property_boolean_table = NULL;
		}
	}
	//*�ı���

	bool Header_Read(unsigned char* _org_pnt, unsigned char** _lsb_buffer_pnt);
	//*���ۿ��� ������ �޾ƿ���

	void _decompile_code (HANDLE hWrite);
	//*�������� �Լ�

	void _write_as_lsb(HANDLE hNewLsb);
	//*lsb ���Ϸ� ����ϴ� �Լ�
};
//*** ��� ����ü


class LSB_BODY
{
public:
	unsigned int _script_ver;					//*** lsb ��ũ��Ʈ�� ����
	LSB_HEADER* _header;						//*** lsb ��ũ��Ʈ�� ���
	unsigned int inst_list_count;				//*** ��ɾ� ������ �� ��, ��ǻ� �Լ��� ���� ����
	LSB_INST_BASE** inst_list_arr;				//*** ��ɾ� ���� ������

	LSB_BODY(unsigned int script_ver, LSB_HEADER *header)
	{
		_script_ver = script_ver;
		_header = header;
		inst_list_count = 0;
		inst_list_arr = NULL;
	}
	//*������

	~LSB_BODY()
	{
		if (inst_list_arr != NULL) {
			for (unsigned int i = 0; i < inst_list_count; i++) { 
				if (inst_list_arr[i] != NULL) { delete inst_list_arr[i]; }
			}
			delete inst_list_arr; inst_list_arr = NULL;
			//*���� �����ϰ� ����
		}
	}
	//*�ı���

	bool Body_Read(unsigned char* _org_pnt, unsigned char** _lsb_buffer_pnt, unsigned int code);
	//*���ۿ��� ������ �޾ƿ���

	void _decompile_code (HANDLE hWrite, unsigned int code);
	//*�������� �Լ�

	void _write_as_lsb(HANDLE hNewLsb, unsigned int code);
	//*lsb ���Ϸ� ����ϴ� �Լ�

	void _extract_text(HANDLE hTxt);
	//*�ؽ�Ʈ ���� �Լ�

	void _replace_text(LSB_TEXTS_PER_INST *txt_list, unsigned int txt_list_count, unsigned int code);
	//*�ؽ�Ʈ ��ü �Լ�

	void _change_code_J2K();
	//*�ؽ�Ʈ �ڵ� ���� �Լ�
};
//*** ���� ����ü


class LSB_SCRIPT : public LM_BASE_SCRIPT
{
public:
	unsigned int lm_version;					//*** ��ũ��Ʈ ����
	bool flag;									//*** ��ũ��Ʈ �÷���?
	LSB_HEADER* _header;						//*** ��� ������
	LSB_BODY* _body;							//*** ��ü ������

	LSB_SCRIPT()
	{
		lm_version = 0x00000000;
		flag = false;
		_header = NULL;
		_body = NULL;
	}
	//*������

	~LSB_SCRIPT()
	{
		if (_header != NULL) { delete _header; _header = NULL; }
		if (_body != NULL) { delete _body; _body = NULL; }
	}
	//*�Ҹ���

	bool Script_Analysis(wchar_t* LsbFile, unsigned int code);
	//*lsb ������ �ҷ��� �м��ϴ� �Լ�

	void Decompile_To_Code(wchar_t* TxtFile, unsigned int code);
	//*���������ؼ� ����ϴ� �Լ�

	void Make_To_Script(wchar_t *newLsbFile, unsigned int code);
	//*lsb ���Ϸ� ����ϴ� �Լ�

	void Extract_Text_Data(wchar_t* DstTxtFile);
	//*�ؽ�Ʈ ���� �Լ�

	void Replace_Text_Data(wchar_t* SrcTxtFile, unsigned int code);
	//*�ؽ�Ʈ ��ü �Լ�

	void Convert_Codepage_J2K();
	//*�ؽ�Ʈ ����ڵ带 �Ϻ���� �ѱ۷� �ٲٴ� �Լ�

private:
	bool LSB_Header_Analysis (wchar_t* LsbFile, unsigned char* _org_pnt, unsigned char** _lsb_buffer_pnt);
	//*��� �м� �Լ�

	bool LSB_Body_Analysis(wchar_t* LsbFile, unsigned char* _org_pnt, unsigned char** _lsb_buffer_pnt, unsigned int code);
	//*���� �м� �Լ�
};
//*** ��ũ��Ʈ ��ü�� �����ϴ� ����ü