#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex>

#define PI 3.1415926

class MyFFT
{
public:
	std::complex<float> *myFFT(std::complex<float> x[], int N)
	{
		int r = floor(log(N*1.0) / log(2.0) - 0.01) + 1;
		int l = 0;//,k,i,j,m,sum,d=0;
		int k = 0;
		int i = 0;
		int j = 0;
		int m = 0;
		int sum = 0;
		int q = 0;
		int p = 0;
		std::complex<float>t(0.0, 0.0);
		std::complex<float>d(0.0, 0.0);
		std::complex<float> *w = new std::complex<float>[(N + 10)*(N / 2)];//[(N/2)+1];//[N*(N/2)];
		std::complex<float> *c = new std::complex<float>[N];
		std::complex<float> a(0, 0);
		std::complex<float> b(0, 0);

		/*for(i=2;i<=(N+5);i=i*2)
		{
		for(j=0;j<N/2;j++)
		{
		t=std::complex<float>(0,0-2.0*3.1415926*(float(j)/float(i)));
		w[i*(N/2)+j]=exp(t);//std::complex<float>((float)cos(2.0*PI*j/i),(float)(-1*sin(2.0*PI*j/i)));
		}
		/*	for(i=0;i<(N/2)+1;i++)
		{
		w[i]=std::complex<float>((float)cos(2.0*PI*i/N),(float)(-1*sin(2.0*PI*i/N)));
		}*/
		//}

		for (i = 0; i<N; i++)
		{
			//m=floor(log(i)/log(2.0))+1;
			sum = i % 2;
			k = i / 2;
			for (j = 0; j<r - 1; j++)//m-1;j++)
			{
				sum = (sum * 2) + k % 2;
				k = k / 2;
			}
			c[sum] = x[i];
		}

		for (l = 1; l <= r; l++)
		{
			m = pow(2.0, (l - 1)*1.0);
			j = int(N / pow(2.0, l));
			p = pow(2.0, l);
			while (1)
			{
				if (j == 1)
				{
					for (k = p*(j - 1); k<p*(j - 1) + m; k++)
					{
						a = c[k];
						b = c[k + m];
						t = std::complex<float>(0, 0 - 2.0*3.1415926*(float((k - p*(j - 1))) / float(p)));
						d = exp(t)*b;
						c[k] = a + d;
						c[k + m] = a - d;
						//c[k]=a+w[p*(N/2)+(k-2*(j-1))]*b;
						//c[k+m]=a-w[p*(N/2)+(k-2*(j-1))]*b;
					}
					break;
				}
				else
				{
					for (k = p*(j - 1); k<p*(j - 1) + m; k++)
					{
						a = c[k];
						b = c[k + m];
						t = std::complex<float>(0, 0 - 2.0*3.1415926*(float((k - p*(j - 1))) / float(p)));
						d = exp(t)*b;
						c[k] = a + d;
						c[k + m] = a - d;
						//c[k]=a+w[p*(N/2)+(k-2*(j-1))]*b;
						//c[k+m]=a-w[p*(N/2)+(k-2*(j-1))]*b;
					}
					j = j - 1;
				}
			}
		}

		return c;
	}

	int *myIFFT(std::complex<float> x[], int N)
	{
		int temp = 0;
		int flag = 0;
		int *z = new int[N];

		for (int i = 0; i < N; i++)
		{
			x[i] = std::complex<float>(x[i].real(), (-1)*x[i].imag());
		}

		std::complex<float> *a = new std::complex<float>[N];
		a = myFFT(x, N);

		for (int i = N - 1; i >= 0; i--)
		{
			temp = floor(a[i].real()/N + flag+0.5);
			/*
			cout <<"HELLO1:"<<a[i].real()<<endl;
			cout << "HELLO2:" << a[i].real()/N << endl;
			cout << "HELLO3:" << flag << endl;
			cout << "HELLO4:" << temp << endl;
			*/
			flag = 0;
			if (temp>9)
			{
				flag = temp / 10;
				temp = temp % 10;
				z[i] = temp;
			}
			else
			{
				z[i] = temp;
			}
		}

		return z;
	}

};
