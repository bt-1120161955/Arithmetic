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
	printf("输入乘方的符号选择:");
	printf("输入0表示'^',输入1表示'**'\n");
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
		if ((fp = fopen("question.txt", "w")) == NULL)//打开操作不成功
		{
			printf("error\n");
			exit(1);//结束程序的执行
		}
		int num = 0;
		printf("输入生成的题目数量,题目数量小于1000:\n");
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
		for (int i = 0; i<num; i++) {	//生成num个式子 
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
		//答题 
		int num = 0;
		int score = 0;
		printf("输入题目数量:\n");
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

			//随机生成题目 
			string a = create();
			char p[20] = { 0 };
			const char *p1 = a.c_str();
			int pp = 0;
			while (p1[pp] != '\0') { p[pp] = p1[pp]; pp++; }
			strcat(str, p);

			printf("第%d题: ", i + 1);

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

			printf("输入答案(答案可以用分数或者小数表示):\n");

			scanf("%s", ans);	//输入答案，可能为带/号的表达式 

			my_answer = atof(ans);

			for (int i = 0; i<strlen(ans); i++) {
				if (ans[i] == '/') {	//输入答案为分式 
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

		printf("得分:%d / %d", score, num);
	}
		break;
	case 'e':
	{
		//求解 读取文件中的表达式求解 

		if ((fp = fopen(argv[3], "r")) == NULL)//打开操作不成功
		{
			exit(1);//结束程序的执行
		}

		//从文件中读取
		while (fgets(str, INF, fp) != NULL) {

			char infix[INF], suffix[INF];//infix中缀表达式，suffix后缀表达式					
			str[strlen(str) - 1] = '\0';	//删除回车 
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
