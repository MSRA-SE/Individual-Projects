#pragma once
#include "iostream"
#include "LData.h"
using namespace std;

class SimpleDiv
{
public:
	void UnitTrans(int a, long long *x, int m,int *&z)
	{
		//int *z = new int[10 * m + 1];
		long long *s = x;
		long long temp = 0;

		for (int i = 1; i < m + 1; i++)
		{
			temp = s[i - 1];
			for (int j = 10 * (i-1) + 10; j >= 10 * (i-1) + 1; j--)
			{
				z[j] = temp % 10;
				temp = temp / 10;
			}
		}
		z[0] = a;

		//return z;
	}

	void UnitReTrans(int *x, int n, long long * &s)
	{
		int *z = x;
		//long long *s = new long long[n];
		long long temp = 0;

		for (int i = 0; i < n; i++)
		{
			for (int j = 10 * i + 1; j < 10 * i + 11; j++)
			{
				temp = temp + z[j];
				temp = 10 * temp;
			}
			temp = temp / 10;
			s[i] = temp;
			temp = 0;
		}
		//return s;
	}
	LData Div(LData x, long long y, int M)
	{
		int a = x.myint;
		long long *b = x.myfloat;
		int *c = new int[10 * M + 1];
		UnitTrans(a, b, M, c);
		int *temp = new int[10 * M + 1];
		long long sum = c[0];
		int flag = 0;
		LData answer;
		/*
		for (int i = 0; i < 20; i++)
		{
			cout << "hello11111    "<<c[i] << endl;
		}
		*/
		for (int i = 0; i < 10 * M + 1; i++)
		{
			temp[i] = sum / y;
			flag = sum % y;
			sum = flag * 10 + c[i + 1];
		}
		/*
		for (int i = 0; i < 20; i++)
		{
			cout << "hello2222     "<<temp[i] << endl;
		}
		*/
		answer.myint = temp[0];
		long long *an = new long long[M];
		UnitReTrans(temp, M, an);
		answer.myfloat = an;

		delete temp;
		delete c;
		return answer;
	}

};

