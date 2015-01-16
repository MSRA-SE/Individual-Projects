#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <ctime>

using namespace std;

const int MAXDIGIT = 200000;
const int BASE = 10000;
const int LEN = 4;
int digit1[MAXDIGIT/LEN+3];
int digit2[MAXDIGIT/LEN+3];
int tmp[MAXDIGIT/LEN+3];
void addFunc(int *a, int *b, int n) {
  for (int i = n-1, f = 0; i >= 0; i--) {
    a[i] += b[i] + f;
    f = a[i]/BASE;
    a[i] -= f*BASE;
  }
}

void minusFunc(int *a, int *b, int *tmp, int n) {
  int f = 0;
  for (int i = n-1; i >= 0; i--) {
    tmp[i] = a[i] - b[i] - f;
    if (tmp[i] < 0){
      f = floor(-1*tmp[i]/(double)BASE + 1);
      tmp[i] += f*BASE;
    } else f = 0;
  }
}

void divFunc(int *a, int b, int n) {
  long long f = 0;
  for (int i = 0; i < n; i++) {
    long long c = a[i] + f*BASE;
    a[i] = c/b;//floor((c+0.0)/(b+0.0));
    f = c%b;
  }
}

void reversFunc(int* a, int f, int b, int n) {
  a[0] = floor((f+0.0)/(b+0.0));
  f = f%b;
  for (int i = 1; i < n; i++) {
    long long c = f*BASE;
    a[i] = (int)(c/b);
    f = c%b;
  }
}

void tanarcCalc(int x, int mul, int* res, int *tmp, int n, int max_);
bool unit_test(const char* file_i, const char* file_o);

int main() {
  cout << "input any number you want to calculate (<= 200000)" << endl;
  int mx_num;
  cin >> mx_num;
  int num = floor(mx_num/ LEN) + 1;
  
  memset (tmp, 0, sizeof(tmp));
  memset (digit1, 0, sizeof(digit1));
  memset (digit2, 0, sizeof(digit2));
  int start = clock();
  tanarcCalc(5, 16, tmp, digit1, num, mx_num);
  tanarcCalc(239, 4, tmp, digit2, num, mx_num);
  
  minusFunc(digit1, digit2, digit1, num);
  int end = clock();
  // FILE* fp = fopen("pi.txt", "w");
  // for (int i = 1; i < num; i++) {
  //   fprintf(fp, "%04d", long(digit1[i]));
  // }
  for (int i = 1; i < num; i++) {
    printf("%04d", long(digit1[i]));
    if (i%2 == 0)
      cout << endl;
  }
  // fclose(fp);
  cout << "DONE" << endl;
  cout << "Time: " << double(end - start) / CLOCKS_PER_SEC << endl;
  return 0;
}

void tanarcCalc(int x, int mul, int* res, int* tmp, int n, int max_) {
  double x_square = x*x;
  int iter_time = int(max_ * log(BASE) / 2 / log(x));
  //cout << "iter_time " << iter_time << endl;
  for (int i = iter_time, cur = i; i >= 0; i--) {
    int precis_num = floor((cur - i+0.0)*(n+0.0)/(cur+0.0)) + 2;
    if (precis_num > n) precis_num = n;
    reversFunc(res, mul, 2*i+1, precis_num);
    divFunc(tmp, x_square, precis_num);
    minusFunc(res, tmp, tmp, precis_num);
  }
  
  divFunc(tmp, x, n);
  
}

// bool unit_test(const char* file_i, const char* file_o)
// {
//     FILE* fp1 = fopen(file_i, "r");
//     FILE* fp2 = fopen(file_o, "r");
//     int data1 = 0;
//     int data2 = 0;
//     while (!feof(fp1))
//     {
//         fscanf(fp1, "%05d", &data1);
//         fscanf(fp2, "%05d", &data2);
//         if (data1 != data2 && !feof(fp1))
//         {
//             return false;
//             fclose(fp1);
//             fclose(fp2);
//         }
//     }
//     fclose(fp1);
//     fclose(fp2);
//     return true;
// }
