#pragma once
#include "iostream"
using namespace std;

class SimplePlus
{
public:
	long long UnitPlus(long long x, long long y, long long &flag)
	{
		long long z = 0;
		z = x + y + flag;
		if (z > 9999999999)
		{
			flag = z / 10000000000;
			z = z % 10000000000;
		}
		else
		{
			flag = 0;
		}

		return z;
	}

	long long *Plus(long long *x, long long *y, int M,long long &flag)
	{
		long long *a = x;//new long long[M];
		long long *b = y;//new long long[M];
		long long *answer = new long long[M];

		int i = 0;
		flag = 0;

		for (i = M - 1; i >= 0; i--)
		{
			answer[i] = UnitPlus(a[i], b[i], flag);

		}

		return answer;
	}

};

