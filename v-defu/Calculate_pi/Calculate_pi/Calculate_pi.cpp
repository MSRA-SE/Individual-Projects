// 本打算写一些高精度的运算函数，最后用GLA的方法完成PI的计算，
//但失败了，原因是采用了FFT来写乘法，精度没控好，后来采用
//公式π/2=1+1/3+1/3*2/5+1/3*2/5*3/7……+1*2*3*……n/3*5*……*(2n+1)
//                    =1+1/3(1+2/5(1+……+(n-1)/(2n-1)(1+n/(2n+1))……);


#include "stdafx.h"
#include "iostream"
#include "TLfloot.h"

#ifdef _MY_TIME_CLOCK
#include <windows.h>
#define clock_t __int64
clock_t CLOCKS_PER_SEC = 0;
inline clock_t clock()
{
	__int64 result;
	if (CLOCKS_PER_SEC == 0)
	{
		QueryPerformanceFrequency((LARGE_INTEGER *)&result);
		CLOCKS_PER_SEC = (clock_t)result;
	}
	QueryPerformanceCounter((LARGE_INTEGER *)&result);
	return (clock_t)result;
}
#else
#include <time.h>
#endif

using namespace std;

void main()
{
/*	GLA 方法：  */
/*	long pi_length = 0;
	cout << "please input the length you want to calculate ot pi" << endl <<"length = ";
	cin >> pi_length;
	cout << endl;
	clock_t t0 = clock();
	long length = (pi_length + 3) / 4;
	TLfloot a, b, t, p, tmp, pi;
	a = ld_to_TL(1, length);
	print(a);
	b = RevSqrt(ld_to_TL(2, length));
	print(b);
	t = ld_to_TL(0.25, length);
	print(t);
	p = ld_to_TL(1, length);
	print(p);
	long loop_count;
	if (pi_length <= 39)
		loop_count = 1;
	else if (pi_length <= 82)
		loop_count = 2;
	else if (pi_length <= 169)
		loop_count = 3;
	else if (pi_length <= 344)
		loop_count = 4;
	else if (pi_length <= 693)
		loop_count = 5;
	else if (pi_length <= 1391)
		loop_count = 6;
	else if (pi_length <= 2788)
		loop_count = 7;
	else
	{
		loop_count = 8;
		long DLength = 5582;
		while (DLength<(long)pi_length)
		{
			DLength *= 2;//2阶收敛
			++loop_count;
		}
	}
	cout << " total times = " << loop_count << endl;
	for (long i = 0; i < loop_count; ++i)
	{
		tmp = equ(a);
		a = equ(add(a, b));
		print(a);
		a = equ(divint(a, 2));
		print(a);
		b = equ(Sqrt(Mul(b, tmp)));
		print(b);
		t = equ(sub(t, Mul(p, Mul(sub(tmp, a), sub(tmp, a)))));
		print(t);
		p = equ(mulint(p, 2));
		print(p);
		cout <<"The "<<i<<"th  " <<"calculate"<< endl;
		pi = equ(Div(Mul(add(a, b), add(a, b)), t));
		print(pi);
		pi = equ(divint(pi, 4));
		print(pi);
	}
	pi = equ(Div(Mul(add(a, b), add(a, b)), t));
	pi = equ(divint(pi, 4));
	print(pi);

	cin >> pi_length;
	
*/

/*    测试函数正确性  */
/*	TLfloot x,zz,xx;
	long double y = 3;
	int w=3;
	long double yy = 1;
	long z = 3;
	long length = 100;
	x = ld_to_TL(y, length);
	xx = ld_to_TL(yy, length);
//	print(x);
//	zz = Rev(x);
//	zz = Mul(x, xx);
//	zz = divint(x,w);
//	zz = Sqrt(x);
	zz = sub(divint( Div(xx, x),2),Div(xx, x));
	print(zz);
	cin >> z;
*/

/*    采用级数公式直接算    */
	double num_lim;
	num_lim = 0;
	long len, step, n, i;
	long *pi;
	cout << "please input the length you want to calculate of pi" << endl << "length = ";
	cin >> len;
	cout << endl;
	len += 100;
	pi = new long[len];
	len -= 100;
	clock_t t0 = clock();

	for (n = 1; n <= len; n++)     //累加确定项数.
	{
		num_lim += log10((2 * n + 1) / n);
		if (num_lim > len + 1)
			break;
	}
	num(len, n, pi);
	clock_t t1 = clock() - t0;
	cout << endl << "PI=" << pi[0] << "." << endl;  //输出计算结果。
	clock_t t2 = clock();
	step = 10;
	for (i = 1; i <= len; i++)
	{
		cout << pi[i];
		step++;
		if (step % 10 == 0)
			cout << endl;
	}
	t2 = clock() - t2;
	cout << endl;
	cout << "The time to calculate " << len << " pi is " << (t1*1.0 / CLOCKS_PER_SEC) << " seconds" << endl;
	cout << "The time to print pi is " << (t2*1.0 / CLOCKS_PER_SEC) << " seconds" << endl;
	cin >> len;
}

