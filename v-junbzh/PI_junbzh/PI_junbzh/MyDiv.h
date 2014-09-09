#pragma once
#include "iostream"
#include "math.h"
#include "MyPlus.h"
#include "MyMinus.h"
#include "MyMultip.h"
#include "MyMultipNew.h"
using namespace std;

class MyDiv
{
public:
	long long *Div(long long *a, int M)
	{
		MyPlus plus;
		MyMinus minus;
		MyMultipNew mymultip;
		long long *x = new long long[M];
		long long *x_next = new long long[M];
		long long *temp = new long long[3*M];
		long long *unit = new long long[M];
		long long *answer = new long long[M];
		int N = ceil(log(M)/log(2));
		//cout << "kgjshkjh"<<N << endl;
		x[0] = 0010000000;
		x_next[0] = 0;
		unit[0] = 9999999999;

		for (int i = 1; i < M; i++)
		{
			x[i] = 0;
			x_next[i] = 0;
			unit[i] = 9999999999;
		}
		//cout << "NNNNNNN" << N << endl;
		int p = 1;
		int q = 1;
		for (int i = 0; i < N; i++)
		{
			cout << "MMMMMM" << i << endl;
			temp = mymultip.Multip(a, p, x, q, M);

			cout << "aaaaa" << endl;
			for (int i = 0; i < M; i++)
				cout << temp[i] << " ";
			cout << endl;

			temp = minus.Minus(unit, M, temp, p+q-1, M);
			temp[M - 1] = 0;
			temp = mymultip.Multip(temp, p+q-1, x, q, M);
			temp = plus.Plus(temp, p+2*q-1, x, q, M);
			temp[M - 1] = 0;
			q = p + 2 * q - 1;
			cout << "qqqqq" << q << endl;
			for (int j = 0; j < M; j++)
			{
				x_next[j] = temp[j];
				x[j] = x_next[j];
			}
			
		}

		return x;
	}

};

