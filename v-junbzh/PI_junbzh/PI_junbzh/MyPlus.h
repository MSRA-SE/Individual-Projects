#pragma once
#include "iostream"
using namespace std;

class MyPlus
{
public:
	long long UnitPlus(long long x, long long y, long long &flag)
	{
		long long z = 0;
		z = x + y + flag;
		if (z > 9999999999)
		{
			flag = z/10000000000;
			z = z % 10000000000;
		}
		else
		{
			flag = 0;
		}

		return z;
	}

	long long *Plus(long long *x, int m, long long *y, int n, int M)
	{
		long long *a = x;//new long long[M];
		long long *b = y;//new long long[M];
		long long *answer = new long long[M];
		//a = x;
		//b = y;
		int i = 0;
		long long flag = 0;

		if (m <= n)
		{
			for (i = n-1; i >= 0; i--)
			{
				answer[i] = UnitPlus(a[i], b[i], flag);
			}
			for (i = m; i < M-1; i++)
			{
				answer[i] = 0;
			}
			answer[M - 1] = flag;
		}
		else
		{
			for (i = m - 1; i >= 0; i--)
			{
				answer[i] = UnitPlus(a[i], b[i], flag);
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

