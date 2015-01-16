
#include<stdio.h>
#include<malloc.h>
#include<omp.h>
#include<time.h>
#include<string.h>

#define LOCAL
#include"MyPi.h"

ThreadPrivateData * TPD;
Number Result;


//int NumberLength = 0;
//int OutputLength = 0;


//omp_lock_t K_Lock;
int K_Obj = 0;
//static int K_Current = 0;





//****************************************************************

int SetLength(int n)
{
	NumberLength = n;
}

int NumberNew(Number * na)
{
	na->digit = (unsigned int*)malloc(sizeof(unsigned int)*NumberLength);
	if (na->digit == NULL)
	{
		printf("Malloc Error: Function 'NumberNew' ");
		exit();
	}
	
	memset(na->digit, 0, sizeof(unsigned int)*NumberLength);
	//na->NonZeroPos = NumberLength;
	na->NonZeroPos = 0;
	return NumberLength;
}

int NumberFree(Number * na)
{
	if (na->digit != NULL) free(na->digit);
}

int NumberZero(Number * na)
{
	//na->NonZeroPos = NumberLength;
	memset(na->digit, 0, sizeof(unsigned int)*NumberLength);
	na->NonZeroPos = 0;
}


// Calculate na+nb and the result will be stored in rs
int NumberAdd(Number * na, Number * nb, Number * rs)
{
	int i;
	u64 P = 0;
	int st, ed;
	st = NumberLength - 1;
	ed = MIN(na->NonZeroPos, nb->NonZeroPos) - 1;
	ed = MAX(ed, 0);
	
	for (i = st; i >= ed; i--)
	{
		//na->digit[i] = (i >= na->NonZeroPos) ? na->digit[i] : 0;
		//nb->digit[i] = (i >= nb->NonZeroPos) ? nb->digit[i] : 0;
		rs->digit[i] = ((u64)na->digit[i] + (u64)nb->digit[i] + P) % BASE;
		P = ((u64)na->digit[i] + (u64)nb->digit[i] + P) >> 32;
	}
	//rs->NonZeroPos = ed;
	//memset(rs->digit, 0, sizeof(unsigned int)*rs->NonZeroPos);
	//rs->NonZeroPos = 0;
}

// Calculate na-nb and the result will be stored in rs
int NumberMinus(Number * na, Number * nb, Number * rs)
{
	int i;
	u64 P = 0;
	unsigned int temp;
	int st, ed;
	st = NumberLength - 1;
	ed = MIN(na->NonZeroPos, nb->NonZeroPos) - 1;
	ed = MAX(ed, 0);
	for (i = st; i >= ed; i--)
	{
		//na->digit[i] = (i >= na->NonZeroPos) ? na->digit[i] : 0;
		//nb->digit[i] = (i >= nb->NonZeroPos) ? nb->digit[i] : 0;
		if ((u64)na->digit[i] >= (u64)nb->digit[i] + P)
		{
			rs->digit[i] = (u64)na->digit[i] - (u64)nb->digit[i] - P;
			P = 0;
		}
		else
		{
			rs->digit[i] = (u64)na->digit[i] + BASE - (u64)nb->digit[i] - P;
			P = 1;
		}
		//if (rs->digit[i] != 0) rs->NonZeroPos = i;
	}
	//rs->NonZeroPos = ed;
	//memset(rs->digit, 0, sizeof(unsigned int)*rs->NonZeroPos);

	//rs->NonZeroPos = 0;
	
}
// Calculate na * 10 and the result will be stored in rs
int NumberMul10(Number * na, Number * rs)
{
	int i;
	u64 P = 0;
	for (i = NumberLength - 1; i >= 0; i--)
	{
		rs->digit[i] = ((u64)na->digit[i] * 10 + P) % BASE;
		P = ((u64)na->digit[i] * 10 + P) >> 32;
	}
	return P;
}

// Calculate na/nb and the result will be stored in rs
int NumberDiv(Number *na, Number *rs, int nb)
{
	int i;
	u64 temp = 0;
	int st, ed;
	st = na->NonZeroPos;
	ed = NumberLength;

	for (i = st; i < ed; i++)
	{
		if ((u64)na->digit[i] + (temp << 32) > nb)
		{
			rs->digit[i] = ((u64)na->digit[i] + (temp << 32)) / nb;
			temp = ((u64)na->digit[i] + (temp << 32)) % nb;
		}
		else
		{
			temp = (u64)na->digit[i];
			rs->digit[i] = 0;
		}
	}
	//rs->NonZeroPos = na->NonZeroPos;
	//memset(rs->digit, 0, sizeof(unsigned int)*rs->NonZeroPos);
	//rs->NonZeroPos = 0;
}

// Set the N_th bit of na to 1 (binary)   and parameter N's range start from zero
int NumberSetBit(Number *na, int N)
{
	na->digit[N / 32] |= 1 << (31 - N % 32);
	na->NonZeroPos = MIN(na->NonZeroPos, N / 32);
	//na->NonZeroPos = 0;
}

// Set the number to 2/15
int Number2_15(Number *na)
{
	Number temp;
	NumberNew(&temp);
	NumberZero(na);
	temp.digit[0] = 2;
	NumberDiv(&temp, na, 15);
	na->digit[0] = na->digit[1];
	//na->NonZeroPos = 0;

}

// Output the digits
int NumberDump(Number *na)
{
	int i;
	Number ta, *tb;
	NumberNew(&ta);
	tb = na;

	for (i = 0; i < OutputLength; i++)
	{
		if (i % 2 == 0)
		{
			printf("%u", NumberMul10(tb, &ta));
		}
		else
		{
			printf("%u", NumberMul10(&ta, tb));
		}
		if (i % 10 == 9) printf("\n");

		//if (i % 10 == 9) printf(" ");
		//if (i % 50 == 49) printf("\n");
		//if (i % 500 == 499) printf("\n");

	}
	NumberFree(&ta);
}

int NumberDumpDebug(Number *na)
{
	int i;

	for (i = 0; i < NumberLength; i++)
	{
		printf("%12u",na->digit[i]);
	}
	printf("\n");
}


// Calculate every iterations
int BBP_K(int K)
{
	int  Tid ,i;
	Number ta, tb;

	
	//omp_set_lock(&K_Lock);
	//K = K_Current;
	//K_Current++;
	//omp_unset_lock(&K_Lock);
	

	if (K > K_Obj) return;
	if (K == K_Obj)
	{
		// sum all the result
		Tid = omp_get_thread_num();
		//printf("Sum all the result by thread %d\n",Tid);
		NumberNew(&ta);
		NumberNew(&tb);
		for (i = 0; i < ThreadsNum; i++)
		{
			
			if (i % 2 == 0)
			{
				NumberAdd(&ta, &(TPD[i].allsum), &tb);
				Number2_15(&ta);
			}
			else
			{
				NumberAdd(&tb, &(TPD[i].allsum), &ta);
				Number2_15(&tb);
			}
		}
		NumberAdd(&ta, &tb, &Result);
		NumberFree(&ta);
		NumberFree(&tb);


		return;
	}
	// else K < K_Obj   do the calculation

	Tid = omp_get_thread_num();

	NumberZero(&(TPD[Tid].tempc));

	NumberZero(&(TPD[Tid].tempa));
	NumberSetBit(&(TPD[Tid].tempa), 4 * K - 3); 
	NumberDiv(&(TPD[Tid].tempa), &(TPD[Tid].tempc), 8 * K + 1);
	
	//NumberDumpDebug(&(TPD[Tid].tempc));
	//NumberDump(&(TPD[Tid].tempc));

	NumberZero(&(TPD[Tid].tempa));
	NumberSetBit(&(TPD[Tid].tempa), 4 * K - 2);
	NumberDiv(&(TPD[Tid].tempa), &(TPD[Tid].tempb), 8 * K + 4);
	NumberMinus(&(TPD[Tid].tempc), &(TPD[Tid].tempb), &(TPD[Tid].tempa));

	NumberZero(&(TPD[Tid].tempc));
	NumberSetBit(&(TPD[Tid].tempc), 4 * K - 1);
	NumberDiv(&(TPD[Tid].tempc), &(TPD[Tid].tempb), 8 * K + 5);
	NumberMinus(&(TPD[Tid].tempa), &(TPD[Tid].tempb), &(TPD[Tid].tempc));

	NumberZero(&(TPD[Tid].tempa));
	NumberSetBit(&(TPD[Tid].tempa), 4 * K - 1);
	NumberDiv(&(TPD[Tid].tempa), &(TPD[Tid].tempb), 8 * K + 6);
	NumberMinus(&(TPD[Tid].tempc), &(TPD[Tid].tempb), &(TPD[Tid].tempa));

	NumberZero(&(TPD[Tid].tempc));
	NumberAdd(&(TPD[Tid].tempc), &(TPD[Tid].allsum), &(TPD[Tid].tempb));
	NumberAdd(&(TPD[Tid].tempb), &(TPD[Tid].tempa), &(TPD[Tid].allsum));

	//NumberDumpDebug(&(TPD[Tid].allsum));
	//NumberDump(&(TPD[Tid].allsum));

	return;
	//printf("%d\n",Tid);
}





void main(int* argc,char** argv)
{
	int i,n;
	double Time;
	//omp_set_dynamic(0);
	omp_set_num_threads(ThreadsNum);
	//ThreadNumber = omp_get_num_threads();
	//printf("%d threads will be used\n",ThreadsNum);
	//scanf_s("%d", &n);
	n = atoi(argv[1]);

	NumberLength = ((n / 3 + 1) * 10) / 32 + 1;
	NumberLength = NumberLength < 2 ? 2 : NumberLength;
	OutputLength = n;
	K_Obj = (n / 3 + 1) * 10 / 4 + 1;
	

	//K_Current = 1;

	//printf("NumberLength %d \n OutputLength %d \nK_Obj %d \n",NumberLength,OutputLength,K_Obj);

	//omp_init_lock(&K_Lock);

	TPD = (ThreadPrivateData*)malloc(sizeof(ThreadPrivateData)*ThreadsNum);
	if (TPD == NULL)
	{
		printf("Malloc Error 'TPD' \n");
		return;
	}
	for (i = 0; i < ThreadsNum; i++)
	{
		NumberNew(&(TPD[i].allsum));
		NumberNew(&(TPD[i].tempa));
		NumberNew(&(TPD[i].tempb));
		NumberNew(&(TPD[i].tempc));
	}

	NumberNew(&Result);

	clock_t t = clock();
	
#pragma omp parallel for schedule(dynamic,64)
	for (i = 1; i < K_Obj; i++)
	{
		BBP_K(i);
	}
	BBP_K(K_Obj); // sum

	Time=(double)(clock()-t) / CLOCKS_PER_SEC;


	//printf("BASE %lu \n",BASE);
	//Number2_15(&Result);
	//NumberDumpDebug(&Result);


	NumberDump(&Result);
	
	printf("Time Used %lf s \n",Time);



	//scanf_s("%d", &i);


}
