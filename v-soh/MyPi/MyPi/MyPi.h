#define BASE 0x100000000
#define ThreadsNum 8
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)>(y)?(y):(x))

typedef unsigned long long u64;

typedef struct Number
{
	unsigned int * digit;
	int NonZeroPos;
} Number;

typedef struct ThreadPrivateData
{
	Number tempa;
	Number tempb;
	Number tempc;
	Number allsum;
	int IsFinished;
} ThreadPrivateData;

/*
#ifndef LOCAL
extern int NumberLength = 0;
extern int OutputLength = 0;

#else

#endif
*/

#pragma once

#ifdef LOCAL
#define MY_CPP_UNITTESTAPP_EXPORT __declspec(dllexport)
#else
#define MY_CPP_UNITTESTAPP_EXPORT extern
#endif

MY_CPP_UNITTESTAPP_EXPORT int SetLength(int n);
MY_CPP_UNITTESTAPP_EXPORT int NumberNew(Number * na);
MY_CPP_UNITTESTAPP_EXPORT int NumberFree(Number * na);
MY_CPP_UNITTESTAPP_EXPORT int NumberZero(Number * na);
MY_CPP_UNITTESTAPP_EXPORT int NumberAdd(Number * na, Number * nb, Number * rs);
MY_CPP_UNITTESTAPP_EXPORT int NumberMinus(Number * na, Number * nb, Number * rs);
MY_CPP_UNITTESTAPP_EXPORT int NumberMul10(Number * na, Number * rs);
MY_CPP_UNITTESTAPP_EXPORT int NumberDiv(Number *na, Number *rs, int nb);
MY_CPP_UNITTESTAPP_EXPORT int NumberSetBit(Number *na, int N);
MY_CPP_UNITTESTAPP_EXPORT int Number2_15(Number *na);
MY_CPP_UNITTESTAPP_EXPORT int NumberDump(Number *na);
MY_CPP_UNITTESTAPP_EXPORT int NumberDumpDebug(Number *na);
MY_CPP_UNITTESTAPP_EXPORT int BBP_K(int K);

MY_CPP_UNITTESTAPP_EXPORT int NumberLength;
MY_CPP_UNITTESTAPP_EXPORT int OutputLength;