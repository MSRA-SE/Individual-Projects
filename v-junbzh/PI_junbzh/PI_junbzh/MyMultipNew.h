#pragma once
#include "iostream"
#include "math.h"
using namespace std;

class MyMultipNew
{
public:
	int *UnitTrans(long long *x, int m)
	{
		int *z = new int[10 * m];
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

	long long *UnitReTrans(int *x, int n, int &len)
	{
		int *z = new int[n + 100];
		int m = floor(n / 10);
		long long *s = new long long[m];
		len = m;
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
		
		for (int i = 0; i < m; i++)
		{
		cout << s[i] << endl;
		}
		
		return s;
	}

	int *SimpleMultip(int a, int *x, int M)
	{
		int *s = new int[M + 1];
		int flag = 0;
		int temp = 0;

		for (int i = M-1; i >= 0; i--)
		{
			temp = x[i] * a + flag;
			flag = temp / 10;
			temp = temp % 10;
			s[i+1] = temp;
		}
		s[0] = flag;

		return s;
	}

	int *SimplePlus(int *a, int N, int *b, int M1, int M2)
	{
		int *s = new int[N];
		s = a;
		int flag = 0;
		int temp = 0;
		int j = M2 - M1 + 1;

		for (int i = M2; i >= M1; i--)
		{
			j = j - 1;
			temp = b[j] + s[i] + flag;
			/*
			if (i == M1)
			{
				cout << "bj" << b[j] << endl;
				cout << "si" << s[i] << endl;
				cout << "iiiii" << i << endl;
				cout << "mmmmm" << M1 << endl;
				cout << "jjjjj" << j << endl;
				cout << "flag" << flag << endl;
				cout << "temp" << temp << endl;
			}
			*/
			flag = temp / 10;
			temp = temp % 10;
			s[i] = temp;
		}
		if (M1 > 0)
		{
			s[M1 - 1] = s[M1 - 1] + flag;
		}
		else
		{
			cout << flag << endl;
		}
		return s;
	}

	long long *Multip(long long *x, int m, long long *y, int n, int M)
	{
		long long *a = x;// new long long[M];
		long long *b = y;// new long long[M];
		long long *answer = new long long[M];
		//a = x;
		//b = y;
		int i = 0;
		long long flag = 0;
		int N = 0;

		if (m <= n)
		{
			int *x_trans = new int[10 * n];
			int *y_trans = new int[10 * n];
			int *sum = new int[20 * n ];
			int *temp = new int[10 * n + 1];
			int multipflag = 0;
			x_trans = UnitTrans(x, n);
			y_trans = UnitTrans(y, n);

			for (int i = 0; i < 20 * n; i++)
			{
				sum[i] = 0;//!!!!!!!!!!!!!!!!!!!!!
			}

			for (int i = 10 * n-1; i >= 0; i--)
			{
				temp = SimpleMultip(y_trans[i],x_trans,10 * n);
				/*
				answer = UnitReTrans(temp, 10 * n);
				cout <<"hello"<< endl;
				cout << i << endl;
				cout << answer[0]<<endl;
				cout << answer[1] << endl;
				*/
				sum = SimplePlus(sum, 20 * n, temp, i, i + 10 * n);
			}
			/*
			temp = SimpleMultip(y_trans[0], x_trans, 10 * n);
			for (int i = 0; i < 10 * n; i++)
			{
				temp[i] = temp[i + 1];
			}

			sum = SimplePlus(sum, 20 * n - 1, temp, 0, 10 * n-1);
			*/
			//cout << "wow!!!"<<sum[0] << sum[1] << endl;
			int len;
			answer = UnitReTrans(sum, 10 * m + 10 * n - 1, len);

			for (int i = 0; i < m + n - 1; i++)
			{
				cout<<answer[i]<<" ";
			}
			cout << endl;

			for (int i = m + n - 1; i < len; i++)
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
			int *sum = new int[20 * m];
			int *temp = new int[10 * m + 1];
			int multipflag = 0;
			x_trans = UnitTrans(x,	m);
			y_trans = UnitTrans(y, m);

			for (int i = 0; i < 20 * m; i++)
			{
				sum[i] = 0;//!!!!!!!!!!!!!!!!!!!!!
			}

			for (int i = 10 * m - 1; i >= 0; i--)
			{
				temp = SimpleMultip(y_trans[i], x_trans, 10 * m);
				sum = SimplePlus(sum, 20 * m, temp, i, i + 10 * m);
			}

			int len;
			answer = UnitReTrans(sum, 10 * m + 10 * n - 1, len);
			for (int i = m + n - 1; i < len; i++)
			{
				answer[i] = 0;
			}
		}
		
		for (int i = 0; i < M; i++)
			cout << answer[i] << " ";
		cout << endl;
		
		return answer;
	}

};

