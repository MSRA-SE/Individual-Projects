#pragma once
#include "iostream"
using namespace std;

class SimpleMinus
{
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

	long long *Minus(long long *x, long long *y, int M ,long long &flag)
	{
		long long *a = x;// new long long[M];
		long long *b = y;// new long long[M];
		long long *answer = new long long[M];

		int i = 0;
		flag = 0;

		for (i = M - 1; i >= 0; i--)
		{
			answer[i] = UnitMinus(a[i], b[i], flag);

		}
		//answer[M - 1] = flag;

		return answer;
	}

};

