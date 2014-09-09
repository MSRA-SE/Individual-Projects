/*
   ASE INDIVIDUAL PROJECT 
   CALCULATE THE FIRST N DIGITS OF PI
   SHILIN LIU
   2014-09-09
   V-SHILIL
*/
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<time.h>
#define base 10000
clock_t start, finish;
//calc acrtg 1/val    precise:n
void calcArctg(int n, int val, int *seq,int *res,int *midres)
{
	int valsqr,r,temp,dnp1;
	int times;
	times = 0;
	temp = base/10;
	while (temp > 0)
	{
		times++;
		temp /= 10;
	}
	//dnp1:double n+1
	valsqr = val*val;
	seq[0] = base*val;
	for (int i = 0; i < n*times; i++)
	{
		//calculate x^(2n-1)
		r = 0;
		for (int j = 0; j < n; j++)
		{
			temp = r * base + seq[j];
			seq[j] = temp / valsqr;
			r = temp % valsqr;
		}
		//calculate x^(2n-1) / (2n-1)
		r = 0;
		dnp1 = 2 * i + 1;
		for (int j = 0; j < n; j++)
		{
			temp = r * base + seq[j];
			midres[j] = temp / dnp1;
			r = temp%dnp1;
		}
		if (i % 2 == 0)
		{
			//plus
			for (int j = 0; j < n; j++)
				res[j] += midres[j];
		}
		else
		{
			//minus
			for (int j = 0; j < n; j++)
				res[j] -= midres[j];
		}
	}
}

int main(int argc, char* argv[])
{
	//Machin pi=16 arctan(1/5) -4 arctan(1/239)
	//arctan x = x- x^3/3 + x^5/5 -x^7/7 + ... + (-1)^(n-1) x^(2n-1) / (2n-1)
	int n, length, estimate;
	int *seq,*res1,*res2,*midres;
	int i,j;
	char *printres, *s;
	if (argc != 2)
	{
		printf("usage: calc n\nwhere n is the digit\n");
		return 0;
	}
		
	sscanf(argv[1],"%d", &n);
	//start = clock();
	length = n / 4 + 75;
	seq = (int *)malloc(sizeof(int)*length);
	res1 = (int *)malloc(sizeof(int)*length);
	res2 = (int *)malloc(sizeof(int)*length);
	midres = (int *)malloc(sizeof(int)*length);
	memset(seq, 0, sizeof(int)*length);
	memset(res1, 0, sizeof(int)*length);
	memset(res2, 0, sizeof(int)*length);
	calcArctg(length, 5, seq, res1,midres);
	memset(seq, 0, sizeof(int)*length);
	calcArctg(length, 239, seq, res2,midres);
	for (int i = 0; i<length; i++)
	{
		res1[i] = 16*res1[i]-4*res2[i];
	}
	
	for (int i = length - 1; i > 0; i--)
	{
		while (res1[i]>=base)
		{
			estimate = res1[i] / base;
			res1[i - 1]+=estimate;
			res1[i] -= base*estimate;
		}
		while (res1[i] < 0)
		{
			res1[i - 1]--;
			res1[i] += base;
		}
	}
	while (res1[0]>=base)
		res1[0] -= base;
	while (res1[0] < 0)
		res1[0] += base;
	//finish = clock();
	free(seq);
	free(res2);
	free(midres);
	//printf("3.\n");
	printres = (char*)malloc(sizeof(int)*(length * 4 + 10));
	s = printres;
	for (int i = 0; i < length; i++)
	{
		sprintf(s,"%04d", res1[i]);
		s += 4;
	}
	s += 4;
	s[0] = '\0';
	length = n / 10;
	char ch;
	s = printres;
	for (int i = 0; i < length; i++)
	{
		ch = s[10];
		s[10] = '\0';
		printf("%s\n", s);
		s += 10;
		s[0] = ch;
	}
	n -= length * 10;
	for (int i = 0; i < n; i++)
	{
		putchar(s[i]);
	}
	if (n>0)
		printf("\n");
	//printf("\ntime=%lfs", (double)(finish - start) / CLOCKS_PER_SEC);

	free(res1);
	free(printres);
	//system("pause");
	return 0;
}