
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <time.h>
#include "Marlin.h"

using namespace std;


void calc(long N)
{
    int start = clock();

    int NumDigit = floor(N / NUM) + 1;

    double* digits1 = new double[NumDigit];

    double* digits2 = new double[NumDigit];

    thread t1(acot, 5, 16, digits1, NumDigit, N);
    thread t2(acot, 239, 4, digits2, NumDigit, N);
    t1.join();
    t2.join();

    /*
    Add these two togrther
    */
    double carry = 0;
    double digit_tmp = 0;

    for (int iter = NumDigit - 1; iter >= 0; --iter)
    {
        digit_tmp = digits1[iter] - digits2[iter] + carry;
        carry = floor(digit_tmp / BASE);
        digits1[iter] = digit_tmp - carry * BASE;
    }

    int end = clock();

    FILE* fp = fopen("pi.txt", "w");
    for (int i = 1; i < NumDigit; ++i)
    {
        // std::cout << long(digits1[i]) << endl;
        fprintf(fp, "%05d", long(digits1[i]));
    }
    fclose(fp);
    delete[] digits1;
    delete[] digits2;
    cout << "Done: Writing result to pi.txt" << endl;
    cout << "Time: " << double(end - start) / CLOCKS_PER_SEC << endl;

}




void acot(double x, double mul, double* digit, double NumDigit, long N)
{
    memset(digit, 0, NumDigit * sizeof(double));
    int MAX_ITER = N * log(BASE) / 2 / log(x);
    double den2 = x * x;

    /*
    calculate BASE / den2
    */
    double Quo_base2 = floor(BASE / den2);
    double Rem_base2 = BASE - Quo_base2 * den2;

    for (int iter = MAX_ITER; iter >= 0; --iter)
    {
        double den1 = 2 * iter + 1;
        double Quo_base1 = floor(BASE / den1);
        double Rem_base1 = BASE - Quo_base1 * den1;

        double mul_tmp = mul;
        double item = digit[0];
        double Quo1 = floor(mul_tmp / den1);
        double Quo2 = floor(item / den2);

        digit[0] = Quo1 - Quo2;

        for (int iter_next = 1; iter_next < NumDigit; ++iter_next)
        {
            double Rem1 = mul_tmp - Quo1 * den1;
            double Rem2 = item - Quo2 * den2;

            mul_tmp = Rem1 * Rem_base1;
            item = digit[iter_next] + Rem2 * Rem_base2;

            Quo1 = floor(mul_tmp / den1);
            Quo2 = floor(item / den2);

            digit[iter_next] = Quo1 + Rem1 * Quo_base1 - Quo2 - Rem2 * Quo_base2;
        }
    }

    /*
    calculate result / x
    */
    double Rem = 0;
    double Quo_base = floor(BASE / x);
    double Rem_base = BASE - Quo_base * x;

    double item = 0;
    double Quo = 0;

    for (int iter = 0; iter < NumDigit; ++iter)
    {
        item = digit[iter] + Rem * Rem_base;
        Quo = floor(item / x);
        digit[iter] = Quo + Rem * Quo_base;
        Rem = item - x * Quo;
    }
}
