#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

//const int DIGITS = 10000;  // must: DIGITS % LEN == 0

const int LEN = 4;
const int BASE = 10000; // BASE == 10 ** LEN
const int TIMES = 14;

double get_item(double pi[], int n)
{
	double item = 0;
	for (int k = n - 1; k >= 0; k--) {
		item += pi[k] * BASE;
		pi[k] = item - floor(item / (2 * k + 1))*(2 * k + 1);
		item = floor(item / (2 * k + 1));
		if (k > 0) item *= k;

		//detect overflow
		if (item<0)
		{
			printf("overflow\n");
			getchar();
			return -1;
		}
	}
	return item;
}

void main(int argc, char* argv[])
{
    int DIGITS = atoi(argv[1]);
	clock_t start = clock();
	//cout << "input wanted digits:\n";
	//cin >> DIGITS;
	double *pi = new double[DIGITS / LEN * TIMES];
	int n = DIGITS / LEN * TIMES;
	double *result = new double[DIGITS / LEN];
	double  remainder = 0;
	for (int i = 0; i < n; i++)
		pi[i] = 2; 
	int count = 0;

	for (int i = 0; n>0; n -= TIMES, i++)
	{
		double item = get_item(pi, n);

		result[i] = remainder + floor(item / BASE);
		if (result[i] > BASE)
		{
			result[i - 1] += floor(result[i] / BASE);
			result[i] = result[i] - floor(result[i] / BASE)*BASE;
		}
		//if (i % 2 == 0)
		//	cout << endl;
		//printf("%0*.0lf", LEN, result[i]);
		//std::cout << result[i]<<std::endl;
		remainder = item - floor(item / BASE)*BASE;
	}

	clock_t end = clock();
	
	std::cout <<endl<<"time: "<< (double)(end - start) / 1000 << std::endl;

	//FILE* filePi;
	//if (!(filePi = fopen("D:\\Desktop\\Test\\testPi.txt", "w")))
	//{
	//	cout << "fail to open testPi.txt";
	//	return;
	//}
	//for (int i = 1; i < DIGITS / LEN; i++)
	//{
	//	fprintf(filePi, "%0*.0lf", LEN, result[i]);
	//}

	//fclose(filePi);

    /*getchar();
	getchar();*/
}