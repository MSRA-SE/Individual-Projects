#include "MyPlus.h"
#include "iostream"
using namespace std;


int MyPlus::Plus(int x, int y)
{
	a = x;
	b = y;
	answer = x + y;

	return answer;
}


MyPlus::~MyPlus(void)
{
}
