#include"evaluation.h"
#define inf 0.00001
#define INF 10000

int gcd(long int m, long int n)
{
	while (m%n != 0) {
		int t = m%n;
		m = n;
		n = t;
	}
	return n;
}
void float_to_fraction(double x)
{
	int n = 1, m = 1, nn, mm; //分子分母 
	int sign = 1;	//存储所输入数字的符号 
	int intPart = 0;
	int common; //存储分子分母的公约数
	double d; //x存储所输入数字的小数部分 
	d = 0.0001; //指定精确度 

	sign = x / fabs(x);
	char temp[50];
	sprintf(temp, "%.4f", x);
	double y = atof(temp);

	if (fabs(x) >= 1)
		intPart = (int)(fabs(x));

	if (fabs(x)<inf) {	//x为整数 
		printf("%d\n", sign*intPart);
		return;
	}

	if (fabs(x - y)<inf) {	//x不是循环小数,假定位数为4位 
		x = y;
		x = fabs(x);
		x *= INF;
		n = (long int)x;
		m = INF;
		common = gcd(n, m);
		n /= common;
		m /= common;
		if (m != 1)
			printf("%d/%d\n", n*sign, m);
		else
			printf("%d\n", n*sign);
		return;
	}

	sprintf(temp, "%.20lf", x);

	for (int i = 0; i<strlen(temp); i++) {
		if (temp[i] == '.')
			break;
		temp[i] = '0';
	}
	x = atof(temp);
	//x为小数部分 
	if (fabs(x - 0.33333)<inf) {
		n = 1;
		m = 3;
	}
	else if (fabs(x - 0.66666)<inf) {
		n = 2;
		m = 3;
	}
	else if (fabs(x - 0.11111)<inf) {
		n = 1;
		m = 9;
	}
	else if (fabs(x - 0.22222)<inf) {
		n = 2;
		m = 9;
	}
	else if (fabs(x - 0.44444)<inf) {
		n = 4;
		m = 9;
	}
	else if (fabs(x - 0.55555)<inf) {
		n = 5;
		m = 9;
	}
	else if (fabs(x - 0.77777)<inf) {
		n = 7;
		m = 9;
	}
	else if (fabs(x - 0.88888)<inf) {
		n = 8;
		m = 9;
	}
	else if (fabs(x - 0.16666)<inf) {
		n = 1;
		m = 6;
	}
	else if (fabs(x - 0.83333)<inf) {
		n = 5;
		m = 6;
	}
	else if (fabs(x - 0.14286)<inf) {
		n = 1;
		m = 7;
	}
	else if (fabs(x - 0.28570)<inf) {
		n = 2;
		m = 7;
	}
	else if (fabs(x - 0.42857)<inf) {
		n = 3;
		m = 7;
	}
	else if (fabs(x - 0.57143)<inf) {
		n = 4;
		m = 7;
	}
	else if (fabs(x - 0.71429)<inf) {
		n = 5;
		m = 7;
	}
	else if (fabs(x - 0.85714)<inf) {
		n = 6;
		m = 7;
	}
	else {
		while (fabs(1.0*n / m - x) >= d)
		{
			if (x<1.0*n / m)
				m++;
			if (x>1.0*n / m)
				n++;
		}
		nn = n;
		mm = m;
		common = m%n;
		while (common)
		{
			m = n;
			n = common;
			common = m%n;
		}
		common = n;
		m = mm / common;
		n = nn / common;
	}
	printf("%d/%d\n", sign*(n + intPart*m), m);

}