#include "LM_Others.h"
#include "LM_Functions.h"


//*** ��Ÿ �Լ��� ����� �����ϴ� ����


void LM_Help()
{
	printf ("\nToolForLiveMaker v%1.2f\n", __VERSION);
	printf ("���� : ToolForLiveMaker [option] [param]\n");
	printf ("(option�� param�� ���ٸ� 'ToolForLiveMaker -h' ����)\n\n");
	printf ("options and param:\n");
	printf ("\n\t-x ['~.exe' or '~.dat'] [--code [codepage]] [folder]\n");
	printf ("\t   �ش� exe�� dat ���Ͽ��� ������ ������ ������ ����\n");
	printf ("\t   (exe ������ �� �����͸� ������ '~_pure.exe' ������ ���� ����)\n");
	printf ("\t   (������ ������ ���� �� �ڵ� ����)\n");
	printf ("\t   (--code �ɼ� ���� �� -jap/-kor �ɼ��� �ʿ��ϸ�)\n");
	printf ("\t   (--code �ɼ� ������ �� -jap�� ������)\n");
	printf ("\t   (��� ������ ������ �ݵ�� ó���� ����)\n");
	printf ("\t   (�������� �ݵ�� �������� ����)\n");
	printf ("\n\t-p [--onto ['~.exe']] [--code [codepage]] [folder]\n");
	printf ("\t   ������ ������ �ִ� ��� ������ �����Ͽ� 'output.dat' ���Ϸ� ����\n");
	printf ("\t   (--onto �ɼ� ���� �� exe ���ϸ� ���ڰ� �ʿ��ϸ�,)\n");
	printf ("\t   (dat ������ ������ �ʰ� �ش� exe ���Ͽ� ������)\n");
	printf ("\t   (�ɼ� ������ �ÿ��� '~.exe' ���ϰ� '~.dat/~.001/... ������ ������ ����')\n");
	printf ("\t   (--code �ɼ� ���� �� -jap/-kor �ɼ��� �ʿ��ϸ�)\n");
	printf ("\t   (--code �ɼ� ������ �� -kor�� ������)\n");
	printf ("\t   (�������� �ݵ�� �������� ����)\n");
	printf ("\n\t-cvt [folder]\n");
	printf ("\t   ������ ������ �ִ� ��� ������ �ڵ��������� [�Ϻ��� -> �ѱ���] �ڵ��������� ����\n");
	printf ("\n\t-cvte ['~.exe']\n");
	printf ("\t   �ش� exe ���Ͽ��� ȣ��Ǵ� ���ڿ��� �ڵ��������� [�Ϻ��� -> �ѱ���] �ڵ��������� ����\n");
	printf ("\n\t-extt [--code [codepage]] [folder]\n");
	printf ("\t   ������ ������ �ִ� ��� lsb ������ �����ϴ� �Լ�\n");
	printf ("\t   ���� �̸��� '~.lsb'���ٸ� '~.ext.txt'�� ��µȴ�\n");
	printf ("\t   ����ڵ� �ɼ��� �Է����� ������ �Ϻ���� �����ȴ�\n");
	printf ("\n\t-rept [--code [codepage]] [folder]\n");
	printf ("\t   ������ ������ �ִ� ��� �ؽ�Ʈ ������ ������ ���� ���ϰ� ��ġ��Ű�� �Լ�\n");
	printf ("\t   '~.ext.txt'�� ���ϸ� ���� ����� �ȴ�\n");
	printf ("\t   ����ڵ� �ɼ��� �Է����� ������ �ѱ���� �����ȴ�\n");
	printf ("\n\t-decm [--code [codepage]] [folder]\n");
	printf ("\t   ������ ������ �ִ� ��� ��ũ��Ʈ ������ ���������ϴ� �Լ�\n");
	printf ("\n\t-h : ���� ��� �Լ�\n");
	printf ("\n����\n");
	printf ("\n\tToolForLiveMaker -x Game.exe --code -jap Output\n");
	printf ("\tToolForLiveMaker -s Output\n");
	printf ("\tToolForLiveMaker -p --onto Game_pure.exe --code -kor Output\n");
}
//*** ���� ��� �Լ�