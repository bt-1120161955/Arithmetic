#include "create.h"


string create()	//����	
{
	string s;


	int x;	//�������� 
	int y;	//������ 
	int z;	//����� + - * / ^ 
	int w;	//�����+ - 
	int bracket;	//����
	int b_flag = 1;
	int len;	//���ʽ���� 
	int temp;

	len = rand() % 1 + 2;
	for (int i = 0; i<len; i++)
	{
		b_flag = b_flag ^ 1;
		int once = 0;	//ֻ��1������ 
		bracket = rand() % 2;	//0~1 
		x = rand() % 10 + 1;	//1~20
		y = rand() % 10 + 1;	//1~20
		z = rand() % 5;	//0~4����� 
		w = rand() % 2;	//0~1����� 
		if (x<y && z == 1) {
			temp = x;
			x = y;
			y = temp;
		}
		if (z == 4) {
			x = rand() % 4 + 1;	//1~4
			y = rand() % 2 + 1;	//1~2
		}

		if (z == 3 && once == 0) {
			do {
				y = rand() % 10 + 1;
			} while (y>4);
			once = 1;
		}

		if (b_flag&&z != 4) {
			s = s + '(';//strcat(s, "(");
		}

		char a[5];
		_itoa(x, a, 10);
		s = s + a;//strcat(s, a);

		switch (z) {
		case 0: {
			s = s + '+';//strcat(s, "+");
			break;
		}
		case 1: {
			s = s + '-';//strcat(s, "-");
			break;
		}
		case 2: {
			s = s + '*';//strcat(s, "*");
			break;
		}
		case 3: {
			s = s + '/';//strcat(s, "/");
			break;
		}
		case 4: {
			s = s + '^';//strcat(s, "^");
			break;
		}
		}

		_itoa(y, a, 10);
		s = s + a;//strcat(s, a);
		if (b_flag&&z != 4) {
			s = s + ')';//strcat(s, ")");
		}
		switch (w) {
		case 0: {
			s = s + '+';//strcat(s, "+");
			break;
		}
		case 1: {
			s = s + '-';//strcat(s, "-");
			break;
		}
		}
	
	}
	s.resize(s.length() - 1);
	s = s + '=';//str[strlen(s) - 1] = '=';
	s = s + '\n';//str[strlen(s)] = '\n';


	return s;
}
