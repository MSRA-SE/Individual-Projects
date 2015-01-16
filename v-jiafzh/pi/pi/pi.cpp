// pi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include "SmallNum.h"
#include <time.h>

SmallNum getPI()
{
	return SmallNum::arctan(1, 5) * 16 - SmallNum::arctan(1, 239) * 4;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int maxdigit = std::atoi(argv[1]);
	if (maxdigit <= 0)
		return 0;
	SmallNum::setmaxdigit(maxdigit);

    int start = clock();
    SmallNum pi = getPI();
    int end = clock();
    pi.output(stdout);
    printf("\n\n%f seconds\n", float(end - start) / CLOCKS_PER_SEC);
    //system("pause");
	return 0;
}

