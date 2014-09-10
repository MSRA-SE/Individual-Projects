#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<cstring>
#include<string>
#include<algorithm>

const int MOD = 1000000000;
const int DIGIT = 9;

using namespace std;

void add(vector<int> &a, vector<int> &b, int startPos);

void multiply(vector<int> &a, int b, int startPos);

void divide(vector<int> &a, int b, int startPos, int MAXN);

int check(vector<int> &a, int startPos);

void printAns(vector<int> &a, int n);

void updateLength(int n, int &MAXN);