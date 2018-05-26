#include"calculate.h"
#define INF 10000




int mycmp(char a, char b) {
	if (b == '(')
		return 1;//左括号直接入栈
	else if ((b == '^') && (a == '+' || a == '-' || a == '*' || a == '/' || a == '('))
		return 1;//^优先级高于+、-、*、/、(，入栈
	else if ((b == '*' || b == '/') && (a == '+' || a == '-' || a == '('))
		return 1;//*、/优先级高于+、-、(，入栈
	else if ((b == '+' || b == '-') && (a == '('))
		return 1;//+、-优先级高于(，入栈
	else
		return 0;
}

/*中缀表达式转后缀表达式
中缀表达式之间无分割
后缀表达式操作数、操作符之间用空格分割，便于区分不同操作数*/
void infix_to_suffix(char* infix, char* suffix)
{
	stack<char>stk;
	int j = 0, i = 0;

	for (i = 0; infix[i] != '\0'; i++)
	{
		if (infix[i] >= '0'&&infix[i] <= '9')
			suffix[j++] = infix[i];
		else
		{
			if (i != 0 && infix[i - 1] >= '0'&&infix[i - 1] <= '9')
				suffix[j++] = ' ';
			if (infix[i] == ')')
			{
				while (stk.top() != '(')
				{
					suffix[j++] = stk.top();
					suffix[j++] = ' ';
					stk.pop();
				}
				stk.pop();
			}
			else if (stk.empty() || mycmp(stk.top(), infix[i]))
			{
				stk.push(infix[i]);
			}
			else
			{
				while (!stk.empty() && !mycmp(stk.top(), infix[i]))
				{
					suffix[j++] = stk.top();
					stk.pop();
					suffix[j++] = ' ';
				}
				stk.push(infix[i]);
			}
		}
	}

	if (suffix[j - 1] != ' ')
	{
		suffix[j++] = ' ';
	}

	while (!stk.empty())
	{
		suffix[j++] = stk.top();
		suffix[j++] = ' ';
		stk.pop();
	}
	suffix[j] = '\0';
}

/*后缀表达式求值*/
double suffix_value(char* suffix)
{
	stack<double>stk;
	int len = strlen(suffix);
	char ch[6] = { '+','-','*','/','^','\0' };

	double value = 0;
	int flag_f = 0;
	for (int i = 0; i<len; i++)
	{
		if (suffix[i] >= '0'&&suffix[i] <= '9')
		{
			value = value * 10 + (double)(suffix[i] - '0');
			flag_f = 0;
		}
		else if (suffix[i] == ' ' && !flag_f)
		{
			stk.push(value);
			value = 0;
		}
		else
		{
			int flag = 0;
			for (int m = 0; m<5; m++)
				if (suffix[i] == ch[m])
					flag = 1;
			if (flag)
			{
				double n1 = stk.top(); stk.pop();
				double n2 = stk.top(); stk.pop();
				switch (suffix[i])
				{
				case '+':
					n2 += n1;
					stk.push(n2);
					flag_f = 1;
					break;
				case '-':
					n2 -= n1;
					stk.push(n2);
					flag_f = 1;
					break;
				case '*':
					n2 *= n1;
					stk.push(n2);
					flag_f = 1;
					break;
				case '/':
					n2 /= n1;
					stk.push(n2);
					flag_f = 1;
					break;
				case '^':
					n2 = pow(n2, n1);
					stk.push(n2);
					flag_f = 1;
					break;
				default: break;
				}
			}

		}
	}

	return stk.top();
}