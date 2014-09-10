#include "stdafx.h"
#include "math.h"
//#include <vector>
#define base 10000
using namespace std;
//typedef std::vector<long> Tarray;

struct TLfloot
{
	int sign = 1;
	long Exp=0;
	long length;
	long *value;     //new long[length]
};

struct Tcomplex
{
	double r;
	double i;
};

TLfloot add(TLfloot x, TLfloot y);
TLfloot sub(TLfloot x, TLfloot y);
TLfloot equ(TLfloot x);

void print(TLfloot x)
{
	for (int i = 0; i < x.length; i++)
		cout << x.value[i] << endl;
	cout << endl;
}

TLfloot zero(TLfloot x, long length)
{
	int i = 0;
	x.length = length;
	x.value = new long[x.length];
	for (i = 0; i < x.length; i++)
		x.value[i] = 0;
	return(x);
}

TLfloot regular(TLfloot x)
{
	long i = 0, k=0;
	while (!x.value[i])
	{
		k++;
		i++;
	}
	x.Exp -= k;
	for (i = 0; i < x.length-k; i++)
	{
		x.value[i] = x.value[i + k];
	}
	for (i = x.length - 1; i >= x.length - k; i--)
	{
		x.value[i] = 0;
	}
	return(x);
}

TLfloot regular_mul(TLfloot x, long len)
{
	long i = 0, k = 0;
	while (!x.value[i])
	{
		k++;
		i++;
	}
	x.Exp -= k;
	long n = x.length - k > len ? len : x.length - k;
	for (i = 0; i < n; i++)
	{
		x.value[i] = x.value[i + k];
	}
	for (i = x.length - 1; i >= n; i--)
	{
		x.value[i] = 0;
	}
	return(x);
}

TLfloot i_to_TL(long x, long length)
{
	TLfloot result;
	result = zero(result,length);
	result.Exp = (long)floor(log10(x));
	result.Exp = result.Exp % 4 == 0 ? result.Exp / 4 : (result.Exp + 3) / 4;
	for (int i = 0; i < result.Exp+1; i++)
	{
		result.value[result.Exp-i] = x % base;
		x = x / base;
	}
	result = regular(result);
	return(result);
}

TLfloot ld_to_TL(long double x, long length)
{
	TLfloot result;
	result = zero(result,length);
	long ivalue = (long)x;
	if (ivalue == x)
		result = i_to_TL(x,length);
	else
	{
		result.Exp =(long)floor(log10(x));
		result.Exp = result.Exp % 4 == 0 ? result.Exp / 4 : (result.Exp+3) / 4;
		x /= pow(10.0, result.Exp*4);
		for (int i = 0; i < result.length; i++)
		{
			if (x < 0)break;
			x *= base;
			long ivalue = long(floor(x));
			x -= ivalue;
			result.value[i] = ivalue;
		}
		result.Exp--;
	}
	result = regular(result);
	return(result);
}

TLfloot mulint(TLfloot x, int y)
{
	int carry = 0, i=0;
	long tmp;
	//x.value[x.length++] = 0;
	for (i = x.length ; i >= 0 ; i--)
	{
		tmp = x.value[i] * y+ carry;
		carry = tmp / base;
		x.value[i] = tmp % base;
	}
	if (carry)
	{
		x.length++;
		for (int j = x.length; j >= 0; j--)
			x.value[j] = x.value[j - 1];
		x.value[0] = carry;
		x.Exp++;
	}
	x = regular(x);
	return(x);
}

TLfloot divint(TLfloot x, int y)
{
	int reminder = 0;
	long tmp;
	int i = 0;
	for (i = 0; i < x.length; i++)
	{
		tmp = (x.value[i] + reminder*base) / y;
		reminder = (x.value[i] + reminder*base) % y;
		x.value[i] = tmp;
	}
	x = regular(x);
	return(x);
}

TLfloot Add_tl(TLfloot x, TLfloot y)
{
	long carry=0, i;
	long tmp;
	for (i = x.length-1; i >= 0; i--)
	{
		tmp = x.value[i] + y.value[i] + carry;
		carry = tmp / base;
		x.value[i] = tmp % base;
	}
	if (carry)
	{
		x.length++;
		for (int j = x.length; j >= 0; j--)
			x.value[j] = x.value[j - 1];
		x.value[0] = carry;
		x.Exp++;
	}
	return(x);
}

TLfloot add(TLfloot x,TLfloot y)
{
	long tmp_exp;
	TLfloot ans, tmp;
	int i;
	if (x.sign == y.sign)
	{
		if (x.Exp < y.Exp)
		{
			tmp_exp = y.Exp - x.Exp;
			tmp.Exp = y.Exp;
			if (x.length < y.length)
			{
				tmp = zero(tmp, y.length);
				for (i = 0; i < x.length && i+tmp_exp<tmp.length; i++)
				{
					tmp.value[i + tmp_exp] = x.value[i];
				}
				ans = equ(Add_tl(tmp, x));
			}
			else
			{
				tmp = zero(tmp, x.length);
				for (i = y.length; i < tmp.length; i++)
				{
					y.value[i] = 0;
				}
				for (i = 0; i < tmp.length - tmp_exp; i++)
					tmp.value[i + tmp_exp] = x.value[i];
				ans = equ(Add_tl(tmp, x));
			}
		}
		else 
		{
			tmp_exp = x.Exp - y.Exp;
			tmp.Exp = x.Exp;
			if (x.length>y.length)
			{
				tmp = zero(tmp, x.length);
				for (i = 0; i < y.length && i + tmp_exp < tmp.length; i++)
					tmp.value[i + tmp_exp] = y.value[i];
				ans = equ(Add_tl(tmp, x));
			}
			else
			{
				tmp = zero(tmp, y.length);
				for (i = x.length; i < tmp.length; i++)
					x.value[i] = 0;
				for (i = 0; i < tmp.length - tmp_exp; i++)
					tmp.value[i + tmp_exp] = y.value[i];
				ans = equ(Add_tl(tmp, x));
			}
		}	
	}
	else
	{
		y.sign = -y.sign;
		ans = sub(x, y);
	}
	return(ans);
}

TLfloot sub_tl(TLfloot x, TLfloot y)
{
	long carry, i;
	TLfloot t = equ(x);
	long tmp;
	for (i = x.length-1; i > 0; i--)
	{
		if (x.value[i] < y.value[i])
		{
			carry = 1;
			x.value[i - 1]--;
			x.value[i] = x.value[i] - y.value[i] + base;
		}
		else
		{
			carry = 0;
			x.value[i] = x.value[i] - y.value[i];
		}
	}
	if (x.value[0]>=y.value[0])
	{		
		x.value[0] = x.value[0] - y.value[0];
	}
	else
	{
		x = equ(y);
		y = equ(t);
		x.sign = -y.sign;
		x = sub_tl(x,y);		
	}		
	x = regular(x);
	return(x);
}

TLfloot sub(TLfloot x, TLfloot y)
{
	long tmp_exp;
	TLfloot ans, tmp;
	int i;
	if (y.sign == x.sign)
	{	
		if (x.Exp < y.Exp)
		{
			tmp_exp = y.Exp - x.Exp;
			tmp.Exp = y.Exp;
			if (x.length < y.length)
			{
				tmp = zero(tmp, y.length);
				for (i = 0; i < x.length && i + tmp_exp<tmp.length; i++)
				{
					tmp.value[i + tmp_exp] = x.value[i];
				}
				ans = equ(sub_tl(x, tmp));
			}
			else
			{
				tmp = zero(tmp, x.length);
				for (i = y.length; i < tmp.length; i++)
				{
					y.value[i] = 0;
				}
				for (i = 0; i < tmp.length - tmp_exp; i++)
					tmp.value[i + tmp_exp] = x.value[i];
				ans = equ(sub_tl(x, tmp));
			}
		}
		else
		{
			tmp_exp = x.Exp - y.Exp;
			tmp.Exp = x.Exp;
			if (x.length>y.length)
			{
				tmp = zero(tmp, x.length);
				for (i = 0; i < y.length && i + tmp_exp < tmp.length; i++)
					tmp.value[i + tmp_exp] = y.value[i];
				ans = equ(sub_tl(x, tmp));
			}
			else
			{
				tmp = zero(tmp, y.length);
				for (i = x.length; i < tmp.length; i++)
					x.value[i] = 0;
				for (i = 0; i < tmp.length - tmp_exp; i++)
					tmp.value[i + tmp_exp] = y.value[i];
				ans = equ(sub_tl(x, tmp));
			}
		}
	}
	else
	{
		ans.sign = x.sign;
		ans = add(x,y);
	}
	return(ans);
}

void TLF_to_Tc(TLfloot x, Tcomplex *ans, long n)
{
//	ans = new Tcomplex[n];
	int i;
	for (i = 0; i < x.length; i++)
	{
		ans[i].r = x.value[i];
		ans[i].i = 0;
	}
	for (i = x.length; i < n; ++i)
	{
		ans[i].r = 0;
		ans[i].i = 0;
	}
	//return(ans);
}

void re_order(Tcomplex *x, Tcomplex *x1, long length)
{
		int k = 0, sum=0;
		int m2, m1;
		int n = log2(length);
//		Tcomplex *x1;
		for (int i = 0; i<length; i++)
		{
			x1[i].r = 0;
			x1[i].i = 0;
		}

		for (int i = 1; i <= length; i++)
		{
			sum = 0;
			m2 = i - 1;
			for (int a = 1; a <= n; a++)
			{
				m1 = m2 % 2;
				sum = 2 * sum + m1;
				m2 = floor(m2 / 2);
			}
			x1[k].r = x[sum].r;
			x1[k].i = x[sum].i;
			k = k + 1;
		}
		//return(x1);
}

void FFT(Tcomplex *x, Tcomplex *result, long length)
{
	const double PI = 3.1415926535897932385;
	const double seta = 2.0*PI / length;
	long i, j;
	long a, b, c, xx, kb, kk;
	Tcomplex t;

	long n2 = length >> 2;
	Tcomplex *w = new Tcomplex[length];
	for (i = 0; i <length; ++i)
	{
		w[i].i = sin(seta*i);
		w[i].r = cos(seta*i);
	}
	re_order(x, result, length);
	int n = log2(length);
	for (a = 1; a <= n; a++)
	{
		b = pow(2, a - 1);
		for (c = 0; c <= b - 1; c++)
		{
			xx = c*pow(2, n - a);
			for (kk = c + 1; kk <= length; kk = kk + pow(2, a))
			{
				kb = kk + b - 1; 
				t.r = result[kb].r * w[xx].r - result[kb].i * w[xx].i;
				t.i = result[kb].r * w[xx].i + result[kb].i * w[xx].r;
				result[kb].r = result[kk - 1].r - t.r;
				result[kb].i = result[kk - 1].i - t.i;
				result[kk - 1].r = result[kk - 1].r + t.r;
				result[kk - 1].i = result[kk - 1].i + t.i;
			}
		}
	}
}

void Inv_FFT(Tcomplex *x, Tcomplex *result, long length)
{
	for (long i = 0; i < length; ++i)
		x[i].i = -x[i].i;
	FFT(x, result, length);
}

void FFT_Mul(Tcomplex *a, Tcomplex*b, long length)
{
	for (long i = 0; i < length; ++i)
	{
		double tmp = a[i].r * b[i].r - a[i].i * b[i].i;
		a[i].i = a[i].i * b[i].r + a[i].r * b[i].i;
		a[i].r = tmp;
	}
}

void Com_to_long(const Tcomplex *x, const long length_x, long *result, long length_r)
{
/*	const double tmp_rev_N = 1.0 / length_x;
	double long_base;

	long *dst = 0;
	long dstsize = 0;

	long_base = base;
	dstsize = length_r;
	dst = result;
	const double tmp_rev_base = 1.0 / long_base;

	double tmp = 0.0;

	for (long i = (length_x < dstsize ? length_x : dstsize) - 1; i >= 1; --i)
	{
		double num = x[i - 1].r*tmp_rev_N + tmp;
		tmp = floor((num + 0.499)*tmp_rev_base);
		dst[i] = (long)(num + 0.499 - tmp*long_base);
	}
	if (dstsize>0)
		dst[0] = (long)(tmp + 0.1);*/
	const double N = length_x;
	double tmp;
	long tmp_r;
	long i;
	for (i = length_x-1; i >0 ; i--)
	{
		tmp = x[i].r / N;
		tmp_r = (long) tmp + 0.499;
		result[i] += tmp_r % base;
		result[i - 1] += tmp_r / base;
	}
	result[0] += long(x[0].r / N + 0.499);
	if (result[0] >= base)
	{
		for (i = length_r - 1; i > 0; i--)
		{
			result[i] = result[i - 1];
		}
		result[0] = result[1] / base;
		result[1] = result[1] % base;
	}
}

TLfloot Mul_base_FFT(TLfloot in_x, TLfloot in_y)
{
	TLfloot ans;
	if (in_x.sign == in_y.sign)
		ans.sign = 1;
	else
		ans.sign = -1;
	long n = in_x.length + in_y.length;
	long size = in_x.length > in_y.length ? in_x.length : in_y.length;
	long length = 1;
	while (length < n) length <<= 1;
	Tcomplex *x = new Tcomplex[length];
	Tcomplex *y = new Tcomplex[length];
	Tcomplex *r_x = new Tcomplex[length];
	Tcomplex *r_y = new Tcomplex[length];
	Tcomplex *re_Inv_FFT = new Tcomplex[length];
	long *result =new long[length];
	memset(result, 0, sizeof(long)*length);
//	ans.value = new long[length];
	ans = zero(ans, size);
	TLF_to_Tc(in_x, x, length);
	TLF_to_Tc(in_y, y, length);
	FFT(x, r_x, length);
	FFT(y, r_y, length);
	FFT_Mul(r_x, r_y, length);
	Inv_FFT(r_x, re_Inv_FFT, length);
	Com_to_long(re_Inv_FFT, length, result, length);
	ans.Exp = in_x.Exp + in_y.Exp;
	long b = 0;
	while (result[b] == 0) b++;
	for (long i = 0; i < length-b; ++i)
	{
		ans.value[i] = result[i+b];
	}
	ans = regular_mul(ans,size);
	return(ans);
}

long *nor_mul(long *x, long len_x, long*y, long len_y)
{
	long len_r = len_x + len_y;
	long *r = new long[len_r];
	memset(r, 0, sizeof(long)*len_r);
	for (long i = len_x - 1; i >= 0; i--)
	{
		for (long j = len_y - 1; j >= 0; j--)
		{
			r[i + j + 1] += x[i] * y[j];
			r[i + j] += r[i + j + 1] / base;
			r[i + j + 1] = r[i + j + 1] % base;
		}
	}
	return(r);
}

TLfloot Mul(TLfloot in_x, TLfloot in_y)
{
	long *x;
	long len_x = in_x.length;
	long*y;
	long len_y = in_y.length;
	x = in_x.value;
	y = in_y.value;
	long *r ;
	r = nor_mul(x, len_x, y, len_y);
	TLfloot ans;
	ans = zero(ans, len_x + len_y);
	long b = 0;
	while (r[b] == 0) b++;
	ans.Exp = in_x.Exp + in_y.Exp + 1 - b;
	ans.length = in_x.length;
	for (long i = 0; i < len_x; ++i)
	{
		ans.value[i] = r[i+b];
	}
	ans.sign = in_x.sign == in_y.sign ? 1 : -1;
	return(ans);
}

TLfloot equ(TLfloot x)
{
	TLfloot y;
	y.Exp = x.Exp;
	y.length = x.length;
	y.sign = x.sign;
	y.value = new long[x.length];
	for (long i = 0; i < x.length; i++)
	{
		y.value[i] = x.value[i];
	}
	return(y);
}

TLfloot Rev(TLfloot x)
{
	long len = log2(x.length);
	long old_Exp = x.Exp;
	TLfloot tmp, Xn, tmp_sub, tmp_mul;
//	const TLfloot z = ld_to_TL(2.0, x.length);
	tmp=zero(tmp, x.length);
	Xn=zero(Xn, x.length);
	tmp_sub=zero(tmp_sub, x.length);
	tmp_mul=zero(tmp_mul, x.length);
	Xn.Exp = -x.Exp-1 ;
	Xn.value[0] =(long) base / x.value[0];
	for (long i = 0; i <= x.length; i++)
	{
//		print(Xn);
//		print(x);
		tmp_mul = Mul(x, Xn);
//		print(tmp_mul);
		const TLfloot z = ld_to_TL(2.0, x.length);
//		print(z);
		tmp_sub = sub(z, tmp_mul);
//		print(tmp_sub);
		Xn = Mul(Xn, tmp_sub);
//		print(Xn);
	}
	return(Xn);
}

TLfloot Div(TLfloot x, TLfloot y)
{
	TLfloot tmp;
	tmp = Rev(y);
	return(Mul(x, tmp));
}

TLfloot RevSqrt(TLfloot x)
{
	long len = log2(x.length);
	long old_Exp = x.Exp;
	TLfloot tmp, Xn, tmp_sub, tmp_mul;
	//	const TLfloot z = ld_to_TL(2.0, x.length);
	tmp = zero(tmp, x.length);
	Xn = zero(Xn, x.length);
	tmp_sub = zero(tmp_sub, x.length);
	tmp_mul = zero(tmp_mul, x.length);
	if (x.Exp % 2 == 0)
	{
		Xn.Exp = x.Exp/2;
		Xn.value[0] = (long)sqrt(x.value[0]);
	}
	else
	{
		Xn.Exp = (x.Exp - 1) / 2;
		Xn.value[0] = (long)sqrt(x.value[0])*100;
	}
	Xn = Rev(Xn);
	for (long i = 0; i <= x.length; i++)
	{
		tmp_mul = equ(Mul(x,(Mul(Xn, Xn))));
		const TLfloot z = ld_to_TL(1.0, x.length);
		tmp_sub = equ(sub(z, tmp_mul));
		tmp_mul = equ(Mul(Xn, tmp_sub));
		tmp_mul = equ(divint(tmp_mul, 2));
		Xn = equ(add(Xn, tmp_mul));
	}
	return(Xn);
}

TLfloot Sqrt(TLfloot x)
{
	return(Rev(RevSqrt(x)));
}

void num(long len, long n,long *pi)
{
	long i, j, c, d, carry;
//	long *pi;
	for (i = 0; i <= len + 3; i++)
		pi[i] = 0;
	c = 1;
	for (j = n; j >= 1; j--)                 //按公式计算。
	{
		d = 2 * j + 1;
		for (i = 0; i <= len + 2; i++)      //每位先除2j+1.
		{
			pi[i] = c / d;
			c = (c%d) * 10 + pi[i + 1];
		}
		pi[len + 3] = c / d;
		carry = 0;
		for (i = len + 3; i >= 0; i--)      //每位再乘j
		{
			pi[i] = pi[i] * j + carry;
			carry = pi[i] / 10;
			pi[i] = pi[i] % 10;
		}

		pi[0] = pi[0] + 1;
		c = pi[0];
	}
	carry = 0;
	for (i = len + 3; i >= 0; i--)     //按公式各位乘2
	{
		pi[i] = pi[i] * 2 + carry;
		carry = pi[i] / 10;
		pi[i] = pi[i] % 10;
	}
//	return (pi);
}