#pragma once
#include "iostream"
using namespace std;

class MyMinus
{
private:
	long long *answer;
public:
	long long UnitMinus(long long x, long long y, long long &flag)
	{
		long long z = 0;
		z = x - y + flag;
		if (z >= 0)
		{
			flag = 0;
		}
		else
		{
			z = 10000000000 + x - y + flag;
			flag = -1;
		}

		return z;
	}

	long long *Minus(long long *x, int m, long long *y, int n, int M)
	{
		//cout << "HHH"<< M << endl;
		long long *a = x;// new long long[M];
		long long *b = y;// new long long[M];
		long long *answer = new long long[M];


		//a = x;
		//b = y;
		int i = 0;
		long long flag = 0;

		if (m <= n)
		{
			for (i = n - 1; i >= 0; i--)
			{
				answer[i] = UnitMinus(a[i], b[i], flag);
				//answer[i] = UnitMinus(x[i], y[i], flag);
			}
			for (i = m; i < M - 1; i++)
			{
				answer[i] = 0;
			}
			answer[M - 1] = flag;
		}
		else
		{
			for (i = m - 1; i >= 0; i--)
			{
				answer[i] = UnitMinus(a[i], b[i], flag);
				//answer[i] = UnitMinus(x[i], y[i], flag);
			}
			for (i = n; i < M - 1; i++)
			{
				answer[i] = 0;
			}
			answer[M - 1] = flag;
		}

		return answer;
	}

};

