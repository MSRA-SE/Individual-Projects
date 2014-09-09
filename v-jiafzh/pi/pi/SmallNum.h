#pragma once
#include <string.h>

class SmallNum
{
public:
	static int maxdigit;
	static int maxiter;
	static void setmaxdigit(int n)
	{
		maxiter = n;
		maxdigit = n / 4 + 1 ;
	}
	SmallNum()
	{
		data = new int[maxdigit + 1];
		memset(data, 0, sizeof(int) * (maxdigit + 1));
	}
	SmallNum(int n)
	{
		data = new int[maxdigit + 1];
		memset(data, 0, sizeof(int) * (maxdigit + 1));
		data[0] = n;
	}
	SmallNum(int *n, int count)
	{
		data = new int[maxdigit + 1];
		memset(data, 0, sizeof(int) * (maxdigit + 1));
		count = min(count, (maxdigit + 1));
		memcpy(data, n, sizeof(int) * count);
	}
	SmallNum(const SmallNum &b)
	{
		data = new int[maxdigit + 1];
		memset(data, 0, sizeof(int) * (maxdigit + 1));
		memcpy(data, b.data, sizeof(int) * (maxdigit + 1));
	}
	SmallNum operator=(const SmallNum &b) 
	{
		memcpy(data, b.data, sizeof(int) * (maxdigit + 1));
		return *this;
	}
	 SmallNum operator+(const SmallNum &b) const
	{
		SmallNum tmp;
		for (int i = maxdigit; i >= 1; i--)
		{
			tmp.data[i] += data[i] + b.data[i];
			tmp.data[i - 1] += tmp.data[i] / modl;
			tmp.data[i] %= modl;
		}
		tmp.data[0] += data[0] + b.data[0];
		return tmp;
	}
	SmallNum operator-(const SmallNum &b) const // assume a > b
	{
		SmallNum tmp;
		tmp.data[0] = data[0] - b.data[0];
		for (int i = 1; i <= maxdigit; i++)
		{
			if (data[i] < b.data[i])
			{
				int j = i - 1;
				while (tmp.data[j] == 0 && j >= 1) tmp.data[j] = modl - 1, j--;
				tmp.data[j]--;
				tmp.data[i] = data[i] + modl - b.data[i];
			}
			else
				tmp.data[i] = data[i] - b.data[i];
		}
		return tmp;
	}
	SmallNum operator*(const int b) const
	{
		SmallNum tmp;
		for (int i = 0; i <= maxdigit; i++)
			tmp.data[i] = data[i] * b;
		for (int i = maxdigit; i >= 1; i--)
		{
			tmp.data[i - 1] += tmp.data[i] / modl;
			tmp.data[i] %= modl;
		}
		return tmp;
	}
	SmallNum operator/(const int b) const
	{
		SmallNum tmp;
		int s = 0;
		for (int i = 0; i <= maxdigit; i++)
		{
			s = s * modl + data[i];
			tmp.data[i] = s / b;
			s %= b;
		}
		return tmp;
	}
	int operator[](const int i) const
	{
		return data[i];
	}
	static SmallNum arctan(int x, int y) // x/y
	{
		SmallNum s(0), b(1);
		if(y != 1) 
			b = b / y;
		if (x != 1)
			b = b * x;
		for (int i = 0; i <= maxiter; i++)
		{
			if (i % 2 == 0)
				s = s + b / (2 * i + 1);
			else
				s = s - b / (2 * i + 1);
			if (y != 1)
				b = b / (y * y);
			if (x != 1)
				b = b * (x * x);
		}
		return s;
	}
	void output(FILE *stream)
	{
		int i = 0;
		while (1)
		{
			if (i >= maxiter) break;
			if (i % 10 == 0 && i != 0)
				fprintf(stream, "\n");
			if (i % 4 == 0)
				fprintf(stream, "%d", data[i / 4 + 1] / 1000);
			else if (i % 4 == 1)
				fprintf(stream, "%d", data[i / 4 + 1] / 100 % 10);
			else if (i % 4 == 2)
				fprintf(stream, "%d", data[i / 4 + 1] / 10 % 10);
			else if (i % 4 == 3)
				fprintf(stream, "%d", data[i / 4 + 1] % 10);

			i++;
		}
	}
protected:
	template <typename _Tp> 
	_Tp max(const _Tp &a, const _Tp &b) const
	{
		if (a > b)
			return a;
		else
			return b;
	}
	template <typename _Tp>
	_Tp min(const _Tp &a, const _Tp &b) const
	{
		if (a < b)
			return a;
		else
			return b;
	}
	static const int modl = 10000;
	
private:
	int *data;

};
int SmallNum::maxdigit = 10;
int SmallNum::maxiter = 10;
