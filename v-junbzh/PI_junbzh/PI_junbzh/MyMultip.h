#pragma once
#include "iostream"
#include "MyFFT.h"
#include "math.h"
using namespace std;

class MyMultip
{

private:
	long long *a;
	long long *b;
	MyFFT myfft;

public:
	int *UnitTrans(long long *x, int m)
	{
		int *z = new int[10*m];
		long long *s = new long long[m];
		s = x;
		long long temp = 0;

		for (int i = 0; i < m; i++)
		{
			temp = s[i];
			for (int j = 10 * i + 9; j >= 10 * i; j--)
			{
				z[j] = temp % 10;
				temp = temp / 10;
			}
		}

		return z;
	}

	long long *UnitReTrans(int *x, int n)
	{
		int *z = new int[n + 100];
		int m = floor(n / 10);
		long long *s = new long long[m];
		z = x;
		long long temp = 0;

		for (int i = 0; i < m; i++)
		{
			for (int j = 10 * i; j < 10 * i + 10; j++)
			{
				temp = temp + z[j];
				temp = 10 * temp;
			}
			temp = temp / 10;
			s[i] = temp;
			temp = 0;
		}
		/*
		for (int i = 0; i < m; i++)
		{
			cout << s[i] << endl;
		}
		*/
		return s;
	}

	long long *Multip(long long *x, int m, long long *y, int n, int M)
	{
		a = new long long[M];
		b = new long long[M];
		long long *answer = new long long[M];
		a = x;
		b = y;
		int i = 0;
		long long flag = 0;
		int N = 0;

		if (m <= n)
		{
			int *x_trans = new int[10 * n];
			int *y_trans = new int[10 * n];
			x_trans = UnitTrans(x, n);
			y_trans = UnitTrans(y, n);
			N = floor(pow(2.0, ceil(log(20.0*n)/log(2.0)))+0.5);

			std::complex<float> *a1 = new std::complex<float>[N];
			std::complex<float> *b1 = new std::complex<float>[N];
			std::complex<float> *A = new std::complex<float>[N];
			std::complex<float> *B = new std::complex<float>[N];
			std::complex<float> *C = new std::complex<float>[N];
			int *z1 = new int[N];
			for (int i = 0; i < 10 * n; i++)
			{
				a1[i] = std::complex<float>(x_trans[i], 0.0);
				b1[i] = std::complex<float>(y_trans[i], 0.0);
			}
			for (int i = 10 * n; i < N; i++)
			{
				a1[i] = std::complex<float>(0.0, 0.0);
				b1[i] = std::complex<float>(0.0, 0.0);
			}
			A = myfft.myFFT(a1, N);
			B = myfft.myFFT(b1, N);
			for (int i = 0; i < N; i++)
			{
				C[i] = A[i] * B[i];
			}
			z1 = myfft.myIFFT(C, N);
			answer = UnitReTrans(z1, 10 * m + 10 * n - 1);
			for (int i = m + n - 1; i < M; i++)
			{
				answer[i] = 0;
			}
			/*
			cout << "hello" << answer[66]<< endl;
			for (int i = 0; i < M; i++)
			{
				cout << answer[i] << endl;
			}
			*/
			
		}
		else
		{
			int *x_trans = new int[10 * m];
			int *y_trans = new int[10 * m];
			x_trans = UnitTrans(x, m);
			y_trans = UnitTrans(y, m);
			N = floor(pow(2.0, ceil(log(20.0*m) / log(2.0))) + 0.5);

			std::complex<float> *a1 = new std::complex<float>[N];
			std::complex<float> *b1 = new std::complex<float>[N];
			std::complex<float> *A = new std::complex<float>[N];
			std::complex<float> *B = new std::complex<float>[N];
			std::complex<float> *C = new std::complex<float>[N];
			int *z1 = new int[N];
			for (int i = 0; i < 10 * m; i++)
			{
				a1[i] = std::complex<float>(x_trans[i], 0.0);
				b1[i] = std::complex<float>(y_trans[i], 0.0);
			}
			for (int i = 10 * n; i < N; i++)
			{
				a1[i] = std::complex<float>(0.0, 0.0);
				b1[i] = std::complex<float>(0.0, 0.0);
			}
			A = myfft.myFFT(a1, N);
			B = myfft.myFFT(b1, N);
			for (int i = 0; i < N; i++)
			{
				C[i] = A[i] * B[i];
			}
			z1 = myfft.myIFFT(C, N);
			answer = UnitReTrans(z1, 10 * m + 10 *n - 1);
			for (int i = m + n - 1; i < M; i++)
			{
				answer[i] = 0;
			}
		}

		return answer;
	}

};

