#include"create.h"
#include"calculate.h"
#include"evaluation.h"

#pragma warning (disable:4996)
#define INF 10000
#define inf 0.00001

struct timeb timeSeed;
FILE *fp;
char str[INF*INF];

int main(int argc, char *argv[])
{
	int power;
	printf("����˷��ķ���ѡ��:");
	printf("����0��ʾ'^',����1��ʾ'**'\n");
	while (scanf("%d", &power)) {
		if (power == 0 || power == 1) {
			break;
		}
		else {
			printf("Error input\n");
		}
	}

	switch (argv[1][1])
	{
	case 'n':
	{
		if ((fp = fopen("question.txt", "w")) == NULL)//�򿪲������ɹ�
		{
			printf("error\n");
			exit(1);//���������ִ��
		}
		int num = 0;
		printf("�������ɵ���Ŀ����,��Ŀ����С��1000:\n");
		while (1) {
			scanf("%d", &num);
			if (num <= INF)
				break;
			else {
				printf("Error input\n");
			}
		}
		ftime(&timeSeed);
		srand(timeSeed.time * 10000 + timeSeed.millitm);
		for (int i = 0; i<num; i++) {	//����num��ʽ�� 
			string a=create();
			char p[20] = { 0 };
			const char *p1 = a.c_str();
			int pp = 0;
			while (p1[pp] != '\0') { p[pp] = p1[pp]; pp++; }
			strcat(str, p);
		}

		for (int i = 0; i<strlen(str) - 1; i++) {
			if (power == 1) {
				if (str[i] == '^') {
					fputc('*', fp);
					fputc('*', fp);
					fputc(' ', fp);
				}
				else {
					fputc(str[i], fp);
					if (str[i] != '\n')
						fputc(' ', fp);
				}
			}
			else {
				fputc(str[i], fp);
				if (str[i] != '\n')
					fputc(' ', fp);
			}
		}
	}
		break;
	case 'c':
	{
		//���� 
		int num = 0;
		int score = 0;
		printf("������Ŀ����:\n");
		while (scanf("%d", &num)) {
			if (num>0 && num<1000)
				break;
			else {
				printf("Error input\n");
			}
		}
		ftime(&timeSeed);
		srand(timeSeed.time * 10000 + timeSeed.millitm);
		for (int i = 0; i<num; i++) {
			char suffix[1000];
			char ans[10];
			double my_answer;

			//���������Ŀ 
			string a = create();
			char p[20] = { 0 };
			const char *p1 = a.c_str();
			int pp = 0;
			while (p1[pp] != '\0') { p[pp] = p1[pp]; pp++; }
			strcat(str, p);

			printf("��%d��: ", i + 1);

			for (int i = 0; i<strlen(str); i++) {
				if (power == 1) {
					if (str[i] == '^') {
						putchar('*');
						putchar('*');
						putchar(' ');
					}
					else {
						putchar(str[i]);
						putchar(' ');
					}
				}
				else {
					putchar(str[i]);
					putchar(' ');
				}
			}

			putchar('\n');

			printf("�����(�𰸿����÷�������С����ʾ):\n");

			scanf("%s", ans);	//����𰸣�����Ϊ��/�ŵı��ʽ 

			my_answer = atof(ans);

			for (int i = 0; i<strlen(ans); i++) {
				if (ans[i] == '/') {	//�����Ϊ��ʽ 
					if (ans[0] == '-') {
						infix_to_suffix(ans + 1, suffix);
						my_answer = -1 * suffix_value(suffix);
					}
					else {
						infix_to_suffix(ans, suffix);
						my_answer = suffix_value(suffix);
					}
				}
			}


			infix_to_suffix(str, suffix);

			double right_answer = suffix_value(suffix);


			if (fabs(my_answer - right_answer)<inf) {
				printf("right!\n");
				score++;
			}

			else {
				printf("wrong!\n");
				printf("my answer is %s\n", ans);
				float_to_fraction(right_answer);

			}

			memset(str, '\0', sizeof(str));
		}

		printf("�÷�:%d / %d", score, num);
	}
		break;
	case 'e':
	{
		//��� ��ȡ�ļ��еı��ʽ��� 

		if ((fp = fopen(argv[3], "r")) == NULL)//�򿪲������ɹ�
		{
			exit(1);//���������ִ��
		}

		//���ļ��ж�ȡ
		while (fgets(str, INF, fp) != NULL) {

			char infix[INF], suffix[INF];//infix��׺���ʽ��suffix��׺���ʽ					
			str[strlen(str) - 1] = '\0';	//ɾ���س� 
			printf("%s", str);
			int l = 0;

			for (int i = 0; i<strlen(str); i++) {
				if (str[i] == ' ')	continue;
				if (str[i] != ' ') {
					if (str[i] == '*' && str[i + 1] == '*') {	//power
						i++;
						infix[l] = '^';
						l++;
					}
					else {
						infix[l] = str[i];
						l++;
					}
				}
			}
			infix[l] = '\0';
			l = 0;

			infix_to_suffix(infix, suffix);
			//printf("\n%s\n",suffix);
			double right_answer = suffix_value(suffix);
			float_to_fraction(right_answer);
			memset(infix, '\0', sizeof(infix));
			memset(suffix, '\0', sizeof(suffix));
		}
	}
		break;
	}
}
