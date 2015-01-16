#define _CRT_SECURE_NO_DEPRECATE

#include "Header.h"
#include <time.h>

void add(vector<int> &a, vector<int> &b, int startPos)
{
	int lena = a.size(), lenb = b.size(), last = 0;
	while (lena < lenb)
	{
		a.push_back(0);
		lena++;
	}
	for (int i = 0; i < lenb - startPos; i++)
	{
		int now = lena - i - 1;
		a[now] += b[lenb - i - 1] + last;
		if (a[now] >= MOD)
		{
			a[now] -= MOD;
			last = 1;
		}
		else     last = 0;
	}
}

void multiply(vector<int> &a, int b, int startPos)
{
	int lena = a.size(), last = 0;
	for (int i = 0; i < lena - startPos; i++)
	{
		long long now = (long long)a[lena - i - 1] * (long long)b + (long long)last;
		last = (int)(now / (long long)MOD);
		a[lena - i - 1] = (int)(now % (long long)MOD);
	}
}

void divide(vector<int> &a, int b, int startPos, int MAXN)
{
	int lena = a.size(), res = 0;
	for (int i = startPos; i < lena; i++)
	{
		long long now = (long long)a[i] + (long long)res * (long long)MOD;
		res = (int)(now % (long long)b);
		a[i] = (int)(now / (long long)b);
	}
	while (res != 0 && lena < MAXN)
	{
		long long now = (long long)res * (long long)MOD;
		res = (int)(now % (long long)b);
		a.push_back((int)(now / (long long)b));
		lena++;
	}
}

int check(vector<int> &a, int startPos)
{
	int lena = a.size();
	for (int i = startPos; i < lena; i++)
	{
		if (a[i] != 0)return i;
	}
	return -1;
}

void printAns(vector<int> &a, int n)
{
	int lena = a.size(), left = 0, perLine = 10;
	for (int i = 1; i < lena; i++)     // Decimals begin at the second digit
	{
		int now = MOD / 10;
		while (now && left < n)
		{
			printf("%d", a[i] / now % 10);
			now /= 10;
			left++;
			if (left % perLine == 0)puts("");   // 100 digits per line
		}
		if (left == n)break;
	}
	if (left % perLine)puts("");
}

void updateLength(int n, int &MAXN)
{
	MAXN = n / DIGIT + 2;   // the first digit is the interger part
	if (n % DIGIT)MAXN++;
}

int main(int argc, char *argv[])
{
	int n, MAXN = 10050 / DIGIT;
	int num = 1, den = 3, startPos = 0;

	//freopen("Pi.txt", "w", stdout);
	//scanf("%d", &n);
	//n = 100000;

	if (argc != 2)
	{
		cout << "Parameter Error!" << endl;
		return 0;
	}

	n = 0;

	int lenArgv = strlen(argv[1]);
	for (int i = 0; i < lenArgv; i++)
	if('0' <= argv[1][i] && argv[1][i] < '9')n = n * 10 + argv[1][i] - '0';
	else
	{
		cout << "Plz input a integer!" << endl;
		return 0;
	}

    clock_t begin = clock();
	//if (n <= 0) return 0;
	updateLength(n, MAXN);

	vector<int> ans, series;
	ans.push_back(2);
	series.push_back(2);
	while (1)
	{
		multiply(series, num, startPos);

		divide(series, den, startPos, MAXN);

		int nonZero = check(series, startPos);
		if (nonZero != -1)
		{
			startPos = nonZero - 1;   // nonZero must be >= 1
		}
		else
		{
			break;
		}

		num += 1;
		den += 2;
		add(ans, series, startPos);
	}
    clock_t end = clock();

	printAns(ans, n);

    cout << endl << (double)(end - begin) / CLOCKS_PER_SEC << " s." << endl;
    return 0;
}

// 1 + 1/3 + 1*2 / (3*5) + 1*2*3 / (3*5*7)