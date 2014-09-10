#include "iostream"
#include "MyPlus.h"
#include "MyMinus.h"
//#include "MyFFT.h"
#include "MyMultipNew.h"
#include "MyMultip.h"
#include "MyDiv.h"
#include <math.h>
#include <complex>
using namespace std;
/*
int main()
{
	MyPlus plus;
	MyMinus minus;
	//MyFFT myfft;
	MyMultip mymultip;
	MyDiv div;
	MyMultipNew mymultipnew;

	int n = 200;
	int M = n / 10;
	long long flag = 0;
	long long *x = new long long[M];
	long long *y = new long long[M];
	long long *z = new long long[M];
	long long *k = new long long[M];
	long long *jjj = new long long[M];

	for (int i = 0; i < M; i++)
	{
		x[i] = 0000000000;
		y[i] = 0000000000;
		jjj[i] = 0000000000;
	}
	jjj[0] = 3000000000;
	x[0] = 9990000000;
	y[0] = 9990000000;
	/*
	z = plus.Plus(x, 2, y, 2, M);
	flag = z[M - 1];
	z[M - 1] = 0;
	for (int i = 0; i < M; i++)
	{
		cout <<z[i]<< endl;
	}

	flag = 0;
	z = minus.Minus(x, 2, y, 2, M);
	flag = z[M - 1];
	z[M - 1] = 0;
	for (int i = 0; i < M; i++)
	{
		cout << z[i] << endl;
	}
	
	
	k = mymultipnew.Multip( x, 2, y, 2, M);

	cout << "hello" << endl;
	for (int i = 0; i < M; i++)
	{
		cout << k[i] << endl;
	}
	
	/*
	k = div.Div(jjj, M);
	cout << "hello" << endl;
	for (int i = 0; i < M; i++)
	{
		cout << k[i] << endl;
	}
	*/
	/*
	int N = 8;
	std::complex<float> *a = new std::complex<float>[N];
	std::complex<float> *b = new std::complex<float>[N];
	std::complex<float> *A = new std::complex<float>[N];
	std::complex<float> *B = new std::complex<float>[N];
	std::complex<float> *C = new std::complex<float>[N];
	int *zzz = new int[N];
	for (int i = 0; i < 3; i++)
	{
		a[i] = std::complex<float>(i + 1, 0.0);
		b[i] = std::complex<float>(3 - i, 0.0);
	}
	for (int i = 3; i < N; i++)
	{
		a[i] = std::complex<float>(0.0, 0.0);
		b[i] = std::complex<float>(0.0, 0.0);
	}
	A = myfft.myFFT(a, N);
	B = myfft.myFFT(b, N);
	for (int i = 0; i < N; i++)
	{
		C[i] = A[i] * B[i];
	}
	zzz = myfft.myIFFT(C, N);
	for (int i = 0; i < N; i++)
	{
		cout << zzz[i] << endl;
	}
	
	
	system("pause");
	return 0;
}
*/