#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Marlin.h"

using namespace std;

void main()
{
    long N = 0;
    cout << "Please input a Number : " << endl;
    cin >> N;
    if (N < 1)
    {
        cout << "Incorrect Input" << endl;
        cout << "Press Any Key to Exit..." << endl;
        getchar();
        getchar();
        return;
    }
    calc(N);

    cout << "Press Any Key to Exit..." << endl;
    getchar();
    getchar();
}
