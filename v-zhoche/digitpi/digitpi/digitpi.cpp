// digitpi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math.h"
#include <iostream>
#include "digitpi.h"

#define A 13591409
#define B 545140134
#define C 640320
#define K 1000000000
#define maxL 500

using namespace std;

bignum *C3div24=new bignum(2, 0, 0);

bignum::bignum()
{
	_length = 0;
	_dotpos = 0;
	_sign = 0;
}

bignum::bignum(int length, int dotpos,int sign)
{
	_length = length;
	_dotpos = dotpos;
	_sign = sign;
	data = new long long[_length];
	for (int i = 0; i < _length; i++)
		data[i] = 0;
}
/*
void bignum::copy(bignum *source)
{
	_length = source->getlength();
	_dotpos = source->getdotpos();
	_sign = source->getsign();
	data = new unsigned long long[_length];
}
*/
void bignum::setnum(long long num, int pos)
{
	data[pos] = num;
}

void bignum::setsign(int sign)
{
	_sign = sign;
}

void bignum::changelength()
{
	while ((_length >= 1)&&(data[_length - 1] == 0)) _length--;
}

int bignum::getlength()
{
	return _length;
}

int bignum::getdotpos()
{
	return _dotpos;
}

int bignum::getsign()
{
	return _sign;
}

long long bignum::getnumber(int i)
{
	return data[i];
}

void bignum::multi(bignum *src1, bignum *src2)
{
	bignum *lsrc1, *hsrc1, *lsrc2, *hsrc2;
	bignum *sumsrc1, *sumsrc2, *summulti, *multisum;
	bignum *multilow, *multihigh, *cross;

	int min = src1->getlength();
	if (min > src2->getlength()) min = src2->getlength();
	if (min < maxL)
	{
		for (int i = 0; i < src1->_length; i++)
		{
			//if (src1->data[i] != 0)
			//{
			for (int j = 0; j < src2->_length; j++)
			{
				//if (src2->data[j] != 0)
				//{
				long long temp = src1->data[i] * src2->data[j];
				if (temp >= K)
				{
					long long t = temp / K;
					data[i + j] += temp - t*K;
					data[i + j + 1] += t;
				}
				else data[i + j] += temp;
				//}
			}
			//}
		}
		for (int i = 0; i < _length - 1; i++)
		{
			long long temp = data[i] / K;
			data[i + 1] += temp;
			data[i] -= temp*K;
		}
	}
	else
	{
		int lowlength = min / 2;
		lsrc1 = new bignum(lowlength, 0, 0);
		for (int i = 0; i < lowlength; i++)
			lsrc1->setnum(src1->data[i], i);
		lsrc1->changelength();
		int highlength1 = src1->getlength() - lowlength;
		hsrc1 = new bignum(highlength1, 0, 0);
		for (int i = 0; i < highlength1; i++)
			hsrc1->setnum(src1->data[i + lowlength], i);
		
		lsrc2 = new bignum(lowlength, 0, 0);
		for (int i = 0; i < lowlength; i++)
			lsrc2->setnum(src2->data[i], i);
		lsrc2->changelength();
		int highlength2 = src2->getlength() - lowlength;
		hsrc2 = new bignum(highlength2, 0, 0);
		for (int i = 0; i < highlength2; i++)
			hsrc2->setnum(src2->data[i + lowlength], i);
		
		sumsrc1 = new bignum(highlength1 + 1, 0, 0);
		sumsrc1->add(lsrc1, hsrc1);
		sumsrc1->changelength();
		sumsrc2 = new bignum(highlength2 + 1, 0, 0);
		sumsrc2->add(lsrc2, hsrc2);
		sumsrc2->changelength();

		multilow = new bignum(2 * lowlength, 0, 0);
		multilow->multi(lsrc1, lsrc2);
		multihigh = new bignum(highlength1 + highlength2, 0, 0);
		multihigh->multi(hsrc1, hsrc2);
		summulti = new bignum(highlength1 + highlength2 + 1, 0, 0);
		summulti->add(multilow, multihigh);
		summulti->setsign(1);

		delete lsrc1;
		delete lsrc2;
		delete hsrc1;
		delete hsrc2;

		multisum = new bignum(highlength1 + highlength2 + 2, 0, 0);
		multisum->multi(sumsrc1, sumsrc2);

		delete sumsrc1;
		delete sumsrc2;

		cross = new bignum(highlength1 + highlength2 + 3, 0, 0);
		cross->add(multisum, summulti);
		cross->changelength();

		for (int i = 0; i < 2 * lowlength; i++)
			data[i] = multilow->data[i];
		for (int i = lowlength; i - lowlength < cross->getlength(); i++)
		{
			data[i] += cross->data[i - lowlength];
			if (data[i] >= K)
			{
				data[i + 1] += 1;
				data[i] -= K;
			}

		}
		for (int i = lowlength * 2; i - lowlength * 2 < multihigh->getlength(); i++)
		{
			data[i] += multihigh->data[i - lowlength * 2];
			if (data[i] >= K)
			{
				data[i + 1] += 1;
				data[i] -= K;
			}
		}
		delete multilow;
		delete multihigh;
		delete multisum;
		delete summulti;
		delete cross;
	}
		
	_dotpos = src1->_dotpos + src2->_dotpos;
	_sign = (1 - 2 * src1->_sign)*(1 - 2 * src2->_sign);
	if (_sign == 1) _sign = 0;
	else _sign = 1;
	
}

void bignum::add(bignum *src1, bignum *src2)
{
	//focus on int plus int
	int min = src1->_length;
	if (min > src2->_length) min = src2->_length;

	int max = src1->_length;
	if (max < src2->_length) max = src2->_length;

	int i;
	for (i = 0; i < min; i++)
	{
		data[i] += (1 - 2 * src1->_sign)*src1->data[i] + (1 - 2 * src2->_sign)*src2->data[i];
		if (data[i] >= 0)
		{
			if (data[i] >= K)
			{
				data[i + 1] += 1;
				data[i] -= K;
			}
		}
		else 
		{
			data[i + 1] -= 1;
			data[i] += K;
			if (data[i] < 0)
			{
				data[i + 1] -= 1;
				data[i] += K;
			}
		}
	}
	for (; i < max; i++)
	{
		if (i < src1->_length) data[i] += (1 - 2 * src1->_sign)*src1->data[i];
		if (i < src2->_length) data[i] += (1 - 2 * src2->_sign)*src2->data[i];
		if (data[i] >= 0)
		{
			if (data[i] >= K)
			{
				data[i + 1] += 1;
				data[i] -= K;
			}
		}
		else
		{
			data[i + 1] -= 1;
			data[i] += K;
			if (data[i] < 0)
			{
				data[i + 1] -= 1;
				data[i] += K;
			}
		}
	}
	i = max;
	while ((data[i] == 0)&&(i!=0)) i--;
	if (data[i] < 0)         //sum<0
	{
		_sign = 1;
		for (int j = 0; j <= i; j++)
			data[j] = -data[j];
		for (int j = 0; j < i; j++)
		{
			data[j + 1] -= 1;
			data[j] = K + data[j];
		}
	}
	else _sign = 0;
}

void computepqt(int n, bignum *p, bignum *q, bignum *t)
{
	//calculate an
	bignum *ta=new bignum(2,0,0);
	unsigned long long temp = A + ((long long)B)*n;
	ta->setnum(temp % K, 0);
	ta->setnum(temp / K, 1);
	ta->changelength();

	//calculat pn
	bignum *tp = new bignum(2, 0, 0);
	temp = (2*n-1)*(6*n-5);
	tp->setnum(temp % K, 0);
	tp->setnum(temp / K, 1);
	tp->changelength();
	bignum *tp2 = new bignum(1, 0, 0);
	tp2->setnum(6 * n - 1, 0);
	p->multi(tp, tp2);
	p->changelength();

	//calculate qn
	bignum *tq = new bignum(2, 0, 0);
	temp = n*n;
	tq->setnum(temp % K, 0);
	tq->setnum(temp / K, 1);
	tq->changelength();
	bignum *tq2 = new bignum(1, 0, 0);
	tq2->setnum(n, 0);
	bignum *tq3 = new bignum(3, 0, 0);
	tq3->multi(tq, tq2);
	tq3->changelength();
	q->multi(tq3, C3div24);
	q->changelength();

	//calculate tn
	t->multi(ta, p);
	if (n % 2 == 1) t->setsign(1);
	t->changelength();
}

void computePQT(int n, int m, bignum *p, bignum *q, bignum *t)
{
	if (n + 1 == m)
	{
		bignum *p1, *q1, *t1;
		if (n != 0)
		{
			p1 = new bignum(2, 0, 0);
			q1 = new bignum(4, 0, 0);
			t1 = new bignum(5, 0, 0);
			computepqt(n, p1, q1, t1);
		}
		else
		{
			p1 = new bignum(1, 0, 0);
			q1 = new bignum(1, 0, 0);
			t1 = new bignum(1, 0, 0);
			p1->setnum(1, 0);
			q1->setnum(1, 0);
			t1->setnum(A, 0);

		}
		*p = *p1;
		*q = *q1;
		*t = *t1;

		delete p1;
		delete q1;
		delete t1;
		return;
	}

	int mid = (n + m) / 2;

	bignum *p1,*p2,*p3;
	bignum *q1,*q2,*q3;
	bignum *t1,*t2,*t3;
	bignum *tsrc1, *tsrc2;

	p1 = new bignum();
	q1 = new bignum();
	t1 = new bignum();
	computePQT(n, mid, p1, q1, t1);

	p2 = new bignum();
	q2 = new bignum();
	t2 = new bignum();
	computePQT(mid, m, p2, q2, t2);

	p3 = new bignum(p1->getlength() + p2->getlength(), 0, 0);
	q3 = new bignum(q1->getlength() + q2->getlength(), 0, 0);

	p3->multi(p1, p2);
	p3->changelength();

	q3->multi(q1, q2);
	q3->changelength();

	tsrc1 = new bignum(t1->getlength() + q2->getlength(), 0, 0);
	tsrc2 = new bignum(p1->getlength() + t2->getlength(), 0, 0);
	tsrc1->multi(t1, q2);
	tsrc1->changelength();
	tsrc2->multi(p1, t2);
	tsrc2->changelength();

	int tmp = tsrc1->getlength();
	if (tmp < tsrc2->getlength()) tmp = tsrc2->getlength();
	t3 = new bignum(tmp + 1, 0, 0);
	t3->add(tsrc1, tsrc2);
	t3->changelength();

	delete tsrc1;
	delete tsrc2;
	delete p1;
	delete p2;
	delete q1;
	delete q2;
	delete t1;
	delete t2;

	*p = *p3;
	*q = *q3;
	*t = *t3;

	delete p3;
	delete q3;
	delete t3;

	/*
	p1 = new bignum(1,0,0);
	q1 = new bignum(2,0,0);
	t1 = new bignum(2,0,0);

	p3 = new bignum();
	q3 = new bignum();
	t3 = new bignum();

	//calculate p1, q1 ,t1
	computepqt(1,p1,q1,t1);

	for (int i = n + 2; i <= m; i++)
	{
		//calculat ai,pi and qi
		p2 = new bignum(2, 0, 0);
		q2 = new bignum(3, 0, 0);
		t2 = new bignum(4, 0, 0);
		computepqt(i, p2, q2, t2);
		if ((i - n - 2) % 2 == 0)
		{
			p3 = new bignum(p1->getlength() + p2->getlength(), 0, 0);
			q3 = new bignum(q1->getlength() + q2->getlength(), 0, 0);
			int tmp = t1->getlength() + q2->getlength();
			if (tmp < p1->getlength() + t2->getlength()) tmp = p1->getlength() + t2->getlength();
			tmp++;
			t3 = new bignum(tmp, 0, 0);

			p3->multi(p1, p2);
			p3->changelength();

			q3->multi(q1, q2);
			q3->changelength();

			tsrc1 = new bignum(t1->getlength() + q2->getlength(), 0, 0);
			tsrc2 = new bignum(p1->getlength() + t2->getlength(), 0, 0);
			tsrc1->multi(t1, q2);
			tsrc1->changelength();
			tsrc2->multi(p1, t2);
			tsrc2->changelength();
			t3->add(tsrc1, tsrc2);
			t3->changelength();

			//free
			delete tsrc1;
			delete tsrc2;
			delete p1;
			delete p2;
			delete q1;
			delete q2;
			delete t1;
			delete t2;
		}
		else
		{
			p1 = new bignum(p3->getlength() + p2->getlength(), 0, 0);
			q1 = new bignum(q3->getlength() + q2->getlength(), 0, 0);
			int tmp = t3->getlength() + q2->getlength();
			if (tmp < p3->getlength() + t2->getlength()) tmp = p3->getlength() + t2->getlength();
			tmp++;
			t1 = new bignum(tmp, 0, 0);

			p1->multi(p3, p2);
			p1->changelength();
			q1->multi(q3, q2);
			q1->changelength();

			tsrc1 = new bignum(t3->getlength() + q2->getlength(), 0, 0);
			tsrc2 = new bignum(p3->getlength() + t2->getlength(), 0, 0);
			tsrc1->multi(t3, q2);
			tsrc1->changelength();
			tsrc2->multi(p3, t2);
			tsrc2->changelength();
			t1->add(tsrc1, tsrc2);
			t1->changelength();

			//free
			delete tsrc1;
			delete tsrc2;
			delete p3;
			delete p2;
			delete q3;
			delete q2;
			delete t3;
			delete t2;
		}
	}
	if ((m - n - 2) % 2 == 0)
	{
		*p = *p3;
		*q = *q3;
		*t = *t3;
	}
	else
	{
		*p = *p1;
		*q = *q1;
		*t = *t1;
	}
	*/
	
}

void computereciprocal(bignum *q, bignum *t, bignum *ans,int N)
{
	bignum *s = new bignum(1, 0, 0);
	//s->setnum(12 * A, 0);

	bignum *s1 = new bignum(1 + q->getlength(), 0, 0);
	//s1->multi(s, q);
	s1->changelength();

	s->setnum(12, 0);
	
	bignum *s2 = new bignum(1 + t->getlength(), 0, 0);
	s2->multi(s, t);
	s2->changelength();

	int max = s1->getlength();
	if (max < s2->getlength()) max = s2->getlength();
	bignum *target = new bignum(max + 1, 0, 0);
	target->add(s1, s2);
	target->changelength();

	//guass-newton iteration
	bignum *t1 = new bignum(N + 1, N + target->getlength(), 0);
	t1->setnum((int)(K / target->getnumber(target->getlength()-1)), N);

	bignum *t2;

	while (1 == 1)
	{
		bignum *amulx = new bignum(N + target->getlength() + 1, 0, 0);
		amulx->multi(t1, target);

		bignum *trunc = new bignum(N + 2, N + 1, 0);
		for (int i = amulx->getlength() - 1; amulx->getlength() - i - 1 < N + 2; i--)
			trunc->setnum(amulx->getnumber(i), N + 1 - (amulx->getlength() - i - 1));
		trunc->setsign(1);

		bignum *two = new bignum(N + 2, N + 1, 0);
		two->setnum(2, N + 1);

		bignum *sub = new bignum(N + 3, N + 1, 0);
		sub->add(two, trunc);
		sub->changelength();

		bignum *mul = new bignum(2 * N + 3, 0, 0);
		mul->multi(sub, t1);
		mul->changelength();

		t2 = new bignum(N + 1, mul->getdotpos() - N - 1, 0);
		for (int i = mul->getlength(); mul->getlength() - i < N + 1; i--)
			t2->setnum(mul->getnumber(i-1), N - (mul->getlength() - i));

		t1->setsign(1);
		bignum *check = new bignum(N + 2, 0, 0);
		check->add(t1, t2);
		check->changelength();
		if (check->getlength() == 0) break;
		delete t1;
		t1 = t2;
	}
	*ans = *t1;
}

void computesqrt(bignum *ans,int N)
{
	bignum *t1 = new bignum(N + 1, N + 1, 0);
	t1->setnum((int)(K*sqrt((float)1.0/C)), N);

	bignum *t2;

	while (1 == 1)
	{
		bignum *s = new bignum(1, 0, 0);
		s->setnum(C, 0);

		bignum *one = new bignum(N + 2, 0, 0);
		one->multi(s, t1);

		bignum *two = new bignum(2*N + 3, 0, 0);
		two->multi(one,t1);

		
		bignum *amulx = new bignum(N + 2, N + 1, 0);
		for (int i = 2 * N + 2; i > N + 1; i--)
			amulx->setnum(two->getnumber(i), i - N - 1);
		amulx->setsign(1);

		bignum *three = new bignum(N + 2, N + 1, 0);
		three->setnum(3, N + 1);

		bignum *sub = new bignum(N + 3, N + 1, 0);
		sub->add(three, amulx);
		sub->changelength();

		bignum *mul = new bignum(2*N + 2, 0, 0);
		mul->multi(sub, t1);

		bignum *zero5 = new bignum(1, 1, 0);
		zero5->setnum(K / 2, 0);

		bignum *mulx = new bignum(2 * N + 3, 0, 0);
		mulx->multi(mul, zero5);
		
		t2 = new bignum(N + 1, N + 1, 0);
		for (int i = 2 * N + 2; i > N + 1; i--)
			t2->setnum(mulx->getnumber(i), i - N - 2);

		t1->setsign(1);
		bignum *check = new bignum(N + 2, 0, 0);
		check->add(t1, t2);
		check->changelength();
		if (check->getlength() == 0) break;
		delete t1;
		t1 = t2;
	}
	*ans = *t1;
}

void chudnovsky(int N)
{
	bignum *P = new bignum();
	bignum *Q = new bignum();
	bignum *T = new bignum();

	//calculate C3div24
	unsigned long long tmp = ((long long)C)*C/4;
	bignum *t1 = new bignum(2, 0, 0);
	t1->setnum(tmp % K, 0);
	t1->setnum(tmp / K, 1);
	t1->changelength();
	bignum *t2 = new bignum(1, 0, 0);
	t2->setnum(C/6, 0);
	C3div24->multi(t1, t2); 
	delete t1;
	delete t2;
	/*
	bignum *test1 = new bignum(2, 0, 0);
	test1->setnum(123456789, 0);
	test1->setnum(123456789, 1);
	bignum *test2 = new bignum(2, 0, 0);
	test2->setnum(123456789, 0);
	test2->setnum(123456789, 1);
	computereciprocal(test1, test2, P, (int)(N - 1) / 9 + 1);
	*/
	//computePQT
	computePQT(0,((int)(N-1)/13)+1,P,Q,T);
	//computePQT(0, 5, P, Q, T);
	//compute 1/x
	bignum *reciprocal = new bignum();
	computereciprocal(Q, T, reciprocal, (int)(N-1)/9+1);

	//compute C^(-1/2)
	bignum *sqrtc = new bignum();
	computesqrt(sqrtc,(int)(N - 1) / 9 + 1);

	int n = (int)(N - 1) / 9 + 1;
	//compute answer
	tmp = ((long long)C)*C;
	t1 = new bignum(2, 0, 0);
	t1->setnum(tmp % K, 0);
	t1->setnum(tmp / K, 1);
	
	t2 = new bignum(Q->getlength() + reciprocal->getlength(), 0, 0);
	t2->multi(Q, reciprocal);
	t2->changelength();
	bignum *t3 = new bignum(n + 1, reciprocal->getdotpos(), 0);
	for (int i = t2->getlength() - 1; t2->getlength() - 1 - i < n + 1; i--)
		t3->setnum(t2->getnumber(i), n - (t2->getlength() - 1 - i));

	delete t2;
	t2 = new bignum(n + 3, 0, 0);
	t2->multi(t3, t1);
	
	delete t3;
	t3 = new bignum(2*n + 4, 0, 0);
	t3->multi(t2, sqrtc);
	t3->changelength();

	bignum *ans = new bignum(n + 1, n + 1, 0);
	for (int i = t3->getlength() - 1; t3->getlength() - 1 - i < n + 1; i--)
		ans->setnum(t3->getnumber(i), n - (t3->getlength() - 1 - i));

	//output
	int i = n, count=0,temp=K/10;
	long long num = ans->getnumber(i);
	cout << num << ".";
	i--;
	num = ans->getnumber(i);
	while (1==1)
	{
		cout << num / temp;
		count++;
		num = num%temp;
		temp /= 10;
		if (count%10==0)
		{
			cout << endl;
		}
		if (temp == 0)
		{
			i--;
			num = ans->getnumber(i);
			temp = K / 10;
		}
		if (count == N) break;
	}
		return;
}



int main(int argc,char *argv[])
{
	int N;
	//input numbers of digit of pi
	if (argc != 2)
	{
		cout << "input the digit numbers of pi:" << endl;
		cin >> N;
	}
	else
		N = atoi(argv[1]);
	chudnovsky(N);

	return 0;
}

