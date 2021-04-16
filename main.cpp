#include "LM_Extract.h"
#include "LM_Pack.h"
#include "LM_Text.h"
#include "LM_Others.h"
#include "LM_Functions.h"
#include "LM_Script.h"


int main (int argc, char *argv[])
{
	Initialize_Tool();

	switch (argc)
	{
		case 7:
		{
			if (strcmp(argv[1], "-p") == 0) { 
				char *ExeFile = NULL; 
				int CodePage = LM_CP_JAP;
				//*����Ʈ �ɼ� ����
				for (int cdpg_idx = 2;cdpg_idx < 6;cdpg_idx += 2) {
					if (strcmp(argv[cdpg_idx], "--code") == 0) {
						if ((strcmp(argv[cdpg_idx+1], "-jap") == 0)) {
							CodePage = LM_CP_JAP;
							break;
							//*(--code �ɼ� ���� : �Ϻ���)
						}
						else if ((strcmp(argv[cdpg_idx+1], "-kor") == 0)) {
							CodePage = LM_CP_KOR;
							break;
							//*(--code �ɼ� ���� : �ѱ���)
						}
						else { goto DEF_OPER; }
						//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
					}
				}
				//*--onto �ɼ� Ȯ�� (�ε��� ��ġ�� �Ǵ��ϱ� ���� �ݺ� ����)
				for (int cdpg_idx = 2;cdpg_idx < 6;cdpg_idx += 2) {
					if (strcmp(argv[cdpg_idx], "--onto") == 0) {
						ExeFile = argv[cdpg_idx+1];
						break;
						//*(--onto �ɼ� ����)
					}
				}
				if (ExeFile == NULL) { goto DEF_OPER; }
				//*--code �ɼ� Ȯ�� (�ε��� ��ġ�� �Ǵ��ϱ� ���� �ݺ� ����)
				LM_Pack (argv[6], ExeFile, CodePage);
				break; 
			}
			//*������ ���� �Լ� (--onto, --code �ɼ� ����)
			//*exe ���� ���� ����

			else { goto DEF_OPER; }
			//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
		}

		case 6:
		{
			if (strcmp(argv[1], "-x") == 0) { 
				char *DataFile = argv[2]; 
				int CodePage = LM_CP_JAP;
				//*����Ʈ �ɼ� ����
				for (int cdpg_idx = 2;cdpg_idx < 4;cdpg_idx++) {
					if (strcmp(argv[cdpg_idx], "--code") == 0) {
						if ((strcmp(argv[cdpg_idx+1], "-jap") == 0)) {
							CodePage = LM_CP_JAP;
							break;
							//*(--code �ɼ� ���� : �Ϻ���)
						}
						else if ((strcmp(argv[cdpg_idx+1], "-kor") == 0)) {
							CodePage = LM_CP_KOR;
							break;
							//*(--code �ɼ� ���� : �ѱ���)
						}
						else { goto DEF_OPER; }
						//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
					}
				}
				//*--code �ɼ� Ȯ�� (�ε��� ��ġ�� �Ǵ��ϱ� ���� �ݺ� ����)
				LM_Extract (DataFile, argv[5], CodePage); 
				break; 
			}
			//*������ ���� �Լ� (--code �ɼ� ����)

			else { goto DEF_OPER; }
			//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
		}


		case 5:
		{
			if (strcmp(argv[1], "-p") == 0) { 
				char *ExeFile = NULL; 
				int CodePage = LM_CP_KOR;
				//*����Ʈ �ɼ� ����
				if (strcmp(argv[2], "--onto") == 0) {
					ExeFile = argv[3];
					//*(--onto �ɼ� ����)
				}
				//*--onto �ɼ� Ȯ��
				else if (strcmp(argv[2], "--code") == 0) {
					if ((strcmp(argv[3], "-jap") == 0)) {
						CodePage = LM_CP_JAP;
						//*(--code �ɼ� ���� : �Ϻ���)
					}
					else if ((strcmp(argv[3], "-kor") == 0)) {
						CodePage = LM_CP_KOR;
						//*(--code �ɼ� ���� : �ѱ���)
					}
					else { goto DEF_OPER; }
					//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
				}
				//*--code �ɼ� Ȯ��
				else { goto DEF_OPER; }
				//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
				LM_Pack (argv[4], ExeFile, CodePage);
				break;
			}
			//*������ ���� �Լ� (--onto Ȥ�� --code �ɼ� ����)
			//*--code�� ������ ~ext�� ~dat���� ���� ����
			//*--onto�� ������ exe ���� ���� ����

			else if (strcmp(argv[1], "-extt") == 0) {
				int CodePage = LM_CP_JAP;
				//*����Ʈ �ɼ� ����

				if (strcmp(argv[2], "--code") == 0) {
					if ((strcmp(argv[3], "-jap") == 0)) {
						CodePage = LM_CP_JAP;
						//*(--code �ɼ� ���� : �Ϻ���)
					}
					else if ((strcmp(argv[3], "-kor") == 0)) {
						CodePage = LM_CP_KOR;
						//*(--code �ɼ� ���� : �ѱ���)
					}
					else { goto DEF_OPER; }
					//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
				}
				//*--code �ɼ� Ȯ��
				else { goto DEF_OPER; }
				//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����

				LM_Extract_All_Script_Text(argv[4], CodePage);
				break;
			}
			//*** ���� �� lsb ���� �ϰ� ���� �Լ�

			else if (strcmp(argv[1], "-rept") == 0) {
				int CodePage = LM_CP_KOR;
				//*����Ʈ �ɼ� ����

				if (strcmp(argv[2], "--code") == 0) {
					if ((strcmp(argv[3], "-jap") == 0)) {
						CodePage = LM_CP_JAP;
						//*(--code �ɼ� ���� : �Ϻ���)
					}
					else if ((strcmp(argv[3], "-kor") == 0)) {
						CodePage = LM_CP_KOR;
						//*(--code �ɼ� ���� : �ѱ���)
					}
					else { goto DEF_OPER; }
					//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
				}
				//*--code �ɼ� Ȯ��
				else { goto DEF_OPER; }
				//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����

				LM_Replace_All_Script_Text(argv[4], CodePage);
				break;
			}
			//*** ���� �� lsb ���� �ϰ� ��ġ �Լ�

			else if (strcmp(argv[1], "-decm") == 0) {
				int CodePage = LM_CP_KOR;
				//*����Ʈ �ɼ� ����

				if (strcmp(argv[2], "--code") == 0) {
					if ((strcmp(argv[3], "-jap") == 0)) {
						CodePage = LM_CP_JAP;
						//*(--code �ɼ� ���� : �Ϻ���)
					}
					else if ((strcmp(argv[3], "-kor") == 0)) {
						CodePage = LM_CP_KOR;
						//*(--code �ɼ� ���� : �ѱ���)
					}
					else { goto DEF_OPER; }
					//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
				}
				//*--code �ɼ� Ȯ��
				else { goto DEF_OPER; }
				//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����

				LM_Decompile_All_Script(argv[4], CodePage);
				break;
			}
			//*** ���� �� ��ũ��Ʈ �ϰ� �������� �Լ�

			else { goto DEF_OPER; }
			//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
		}


		case 4:
		{
			if (strcmp(argv[1], "-x") == 0) { 
				LM_Extract (argv[2], argv[3], LM_CP_JAP); 
				break; 
			}
			//*������ ���� �Լ� (--code �ɼ� ������)

			else { goto DEF_OPER; }
			//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
		}


		case 3:
		{
			if (strcmp(argv[1], "-p") == 0) { 
				LM_Pack (argv[2], NULL, LM_CP_KOR); 
				break; 
			}
			//*������ ���� �Լ� (--onto, --code �ɼ� ������)
			//*~ext�� ~dat���� ���� ����

			else if (strcmp(argv[1], "-cvt") == 0) {
				LM_Convert_Codepage_J2K(argv[2]);
				break; 
			}
			//*** ���� �� ���� �ڵ������� �ϰ� ���� �Լ� (--code �ɼ� ������)

			else if (strcmp(argv[1], "-cvte") == 0) {
				LM_Convert_Exe_Codepage_J2K(argv[2]);
				break;
			}
			//*** exe �� ���ڿ� �ڵ������� �ϰ� ���� �Լ� (--code �ɼ� ������)

			else if (strcmp(argv[1], "-extt") == 0) {
				LM_Extract_All_Script_Text(argv[2], LM_CP_JAP);
				break;
			}
			//*** ���� �� lsb ���� �ϰ� ���� �Լ� (--code �ɼ� ������)

			else if (strcmp(argv[1], "-rept") == 0) {
				LM_Replace_All_Script_Text(argv[2], LM_CP_KOR);
				break;
			}
			//*** ���� �� lsb ���� �ϰ� ��ġ �Լ� (--code �ɼ� ������)

			else if (strcmp(argv[1], "-decm") == 0) {
				LM_Decompile_All_Script(argv[2], LM_CP_JAP);
				break;
			}
			//*** ���� �� ��ũ��Ʈ �ϰ� �������� �Լ� (--code �ɼ� ������)

			else { goto DEF_OPER; }
			//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
		}


		case 2:
		{
			if (strcmp(argv[1], "-h") == 0) { LM_Help(); break; }
			//*���� ��� �Լ�

			else { goto DEF_OPER; }
			//*�ùٸ� �ɼ��� ������ ����Ʈ ���� ����
		}


		case 1:
		default:
		{ 
DEF_OPER:
			LM_Help(); break; 
		}
		//*���� ��� �Լ�
	}

//	LSB_SCRIPT *_scr = new LSB_SCRIPT();
//	_scr->Script_Analysis(TEXT("00000001.lsb"), LM_CP_KOR);
//	_scr->Convert_Codepage_J2K();
//	_scr->Decompile_To_Code(TEXT("00000101.txt"), LM_CP_JAP);
//	_scr->Extract_Text_Data(TEXT("00000101.ext.txt"));
//	_scr->Replace_Text_Data(TEXT("00000001.ext.txt"), LM_CP_KOR);
//	_scr->Convert_Codepage_J2K();
//	_scr->Make_To_Script(TEXT("00000101_n.lsb"), LM_CP_KOR);
//	delete _scr; 

//	LM_Convert_Codepage_J2K("Output");
//	LM_Convert_Exe_Codepage_J2K("koifem_pure.exe");

//	LM_Extract("game.exe", "Output", LM_CP_JAP);
//	LM_Pack("Output_mbsn3", NULL, LM_CP_KOR);

//	LM_Decompile_All_Script("Output", LM_CP_KOR);

	Terminate_Tool();
	return 0;
}