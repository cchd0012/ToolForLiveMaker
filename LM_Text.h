#pragma once
#include "LM_Base.h"


//*** �ؽ�Ʈ ���� �Լ��� �����ϴ� ���


void LM_Convert_Codepage_J2K(char* DataFolder);
//*** ���� �� ���� �ڵ������� �ϰ� ���� �Լ�

void LM_Convert_Exe_Codepage_J2K(char* ExeFile);
//*exe���� �ڵ������� ����� �Լ�

void LM_Extract_All_Script_Text(char *DataFolder, unsigned int code);
//*�ش� ���丮 �� ��� lsb/lpb/dat ���� �ؽ�Ʈ�� �����ϴ� �Լ�

void LM_Replace_All_Script_Text(char* DataFolder, unsigned int code);
//*�ش� ���丮 �� ��� lsb/lpb/dat ������ ��ġ�ϴ� �Լ�

void LM_Decompile_All_Script(char* DataFolder, unsigned int code);
//*�ش� ���丮 �� ��� ��ũ��Ʈ ������ ���������ϴ� �Լ�