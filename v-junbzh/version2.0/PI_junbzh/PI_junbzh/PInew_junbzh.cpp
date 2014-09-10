#include "iostream"
#include "stdlib.h"
#include <math.h>
#include <complex>
#include "LData.h"
#include "SimpleDiv.h"
#include "SimpleMinus.h"
#include "SimplePlus.h"
using namespace std;

int main(int args, char* argv[])
{
	int N = 0, lenArgs = strlen(argv[1]);
	for (int i = 0; i < lenArgs; i++)
		N = N * 10 + argv[1][i] - '0';
	//cout << N << endl;


	LData MyPI;
	//////////////
	//int N = 2000;
	//////////////
	int n = ceil(N/1.2);//diedai
	int M = ceil(1.1*N/10);//10 * M
	LData temp1, temp2, temp3, temp4, temp5, answer;
	LData a1, a2, a3;
	answer.myint = 0;
	answer.myfloat = new long long[M];
	a1.myint = 4;
	a1.myfloat = new long long[M];
	a2.myint = 2;
	a2.myfloat = new long long[M];
	a3.myint = 1;
	a3.myfloat = new long long[M];
	temp1.myint = 0;
	temp1.myfloat = new long long[M];
	temp2.myint = 0;
	temp2.myfloat = new long long[M];
	temp3.myint = 0;
	temp3.myfloat = new long long[M];
	temp4.myint = 0;
	temp4.myfloat = new long long[M];
	temp5.myint = 0;
	temp5.myfloat = new long long[M];

	SimpleDiv div;
	SimpleMinus minus;
	SimplePlus plus;

	long long flag = 0;
	long long flag2 = 0;
	long long flag3 = 0;
	long long flag4 = 0;

	for (int i = 0; i < M; i++)
	{
		answer.myfloat[i] = 0;
		a1.myfloat[i] = 0;
		a2.myfloat[i] = 0;
		a3.myfloat[i] = 0;
		temp1.myfloat[i] = 0;
		temp2.myfloat[i] = 0;
		temp3.myfloat[i] = 0;
		temp4.myfloat[i] = 0;
		temp5.myfloat[i] = 0;
	}

	//temp = div.Div(a1, 3, M);

	for (int i = 0; i < n; i++)
	{
		//temp1 = div.Div(a1, (8 * i + 1), M);
		div.Div(a1, (8 * i + 1), M, temp1);
		//div.Div(a2, (8 * i + 1), M, temp2);
		//temp2 = div.Div(a2, (8 * i + 4), M);
		//temp3 = div.Div(a3, (8 * i + 5), M);
		//temp4 = div.Div(a3, (8 * i + 6), M);
		div.Div(a2, (8 * i + 4), M, temp2);
		div.Div(a3, (8 * i + 5), M, temp3);
		div.Div(a3, (8 * i + 6), M, temp4);

		minus.Minus(temp1.myfloat, temp2.myfloat, M, flag2, temp5.myfloat);
		//temp5.myfloat = minus.Minus(temp5.myfloat, temp3.myfloat, M, flag3);
		//temp5.myfloat = minus.Minus(temp5.myfloat, temp4.myfloat, M, flag4);
		minus.Minus(temp5.myfloat, temp3.myfloat, M, flag3, temp5.myfloat);
		minus.Minus(temp5.myfloat, temp4.myfloat, M, flag4, temp5.myfloat);
		temp5.myint = temp1.myint - temp2.myint - temp3.myint - temp4.myint + flag2 + flag3 + flag4;
		for (int j = 0; j < i; j++)
		{
			//temp5 = div.Div(temp5, 16, M);
			div.Div(temp5, 16, M, temp5);
		}
		//answer.myfloat = plus.Plus(answer.myfloat, temp5.myfloat, M, flag);
		plus.Plus(answer.myfloat, temp5.myfloat, M, flag, answer.myfloat);
		answer.myint = answer.myint + temp5.myint + flag;


	}
	
	//cout << "hello" << endl;
	//cout << answer.myint << endl;
	long long v;
	char str1[10];
	int len = 0;
	for (int i = 0; i < ceil(N/10); i++)
	{
		v = answer.myfloat[i];
		if (v >= 1000000000)
		{
			cout << v << endl;
		}
		else
		{
			sprintf_s(str1,"%I64d",v);
			//cout <<"   " <<strlen(str1)<<endl;
			len = strlen(str1);
			for (int j = 0; j < 10 - len; j++)
			{
				cout << 0;
			}
			cout << v << endl;
		}
	}
	

	//system("pause");
	return 0;
}