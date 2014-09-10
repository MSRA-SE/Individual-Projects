#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <time.h>

using namespace std;
const long LEN = 5;
// long DIGITS = 30005L;
const long BASE = 100000; // BASE == 10 ** LEN
const long TIMES = 20;

double get_item(double* pi, int n)
{
    double item = 0;
    double tmp;
    for (long k = n - 1; k >= 0; k--) {
        long den = 2 * k + 1;
        item += pi[k] * BASE;
        tmp = floor(item / den);
        pi[k] = item - tmp * den;
        item = tmp;
        
        if (k > 0) item = k * item;
    }
    return item;
}

void main()
{
    long DIGITS = 0;
    cout << "Please input a Number : " << endl;
    cin >> DIGITS;
    if (DIGITS < 1)
    {
        cout << "Incorrect Input" << endl;
        cout << "Press Any Key to Exit..." << endl;
        getchar();
        getchar();
        return;
    }
    DIGITS += LEN;
    int start = clock();

    double* pi = new double[DIGITS / LEN * TIMES];
    long n = DIGITS / LEN * TIMES;
    double* result = new double[DIGITS / LEN];

    for (int i = 0; i < n; i++) pi[i] = 2; // BASE / 5 == 2.000
    int m = 0;
    for (double remainder = 0; m < DIGITS / LEN; m++) {
        double item = get_item(pi, n);
        n -= TIMES;
        result[m] = remainder + floor(item / BASE);
        // cout << m << " : " << result[m] << endl;

        int p = m;
        double tmp;
        while (floor(result[p] / BASE) > 0)
        {
            tmp = floor(result[p] / BASE);
            result[p - 1] += tmp;
            result[p] = result[p] - BASE * tmp;
            p--;
        }

        remainder = item - floor(item / BASE) * BASE;

    }
    int end = clock();

    FILE* fp = fopen("pi.txt", "w");
    long len = DIGITS / LEN;
    for (int i = 1; i < len; ++i)
    {
        // std::cout << long(digits1[i]) << endl;
        fprintf(fp, "%05d", long(result[i]));
    }
    fclose(fp);
    delete[]pi;
    delete[]result;
    

     cout << float(end - start) / CLOCKS_PER_SEC << endl;
     cout << "Press Any Key to Exit..." << endl;
     getchar();
     getchar();
}