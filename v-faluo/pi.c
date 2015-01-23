#include<stdio.h>
#include <time.h>
#define ARRSIZE 2501
#define DISPCNT 2500
int main(){
	int x[ARRSIZE], z[ARRSIZE], index = 0, index0 = 0;
	int a = 1, b = 3, c, d, Run = 1, test = 10000;
	clock_t start, finish;
	double  duration = 0.0;
	start = clock();
	memset(x, 0, ARRSIZE*sizeof(int));
	memset(z, 0, ARRSIZE*sizeof(int));

	x[0] = 2;
	z[0] = 2;

	while (Run){
		d = 0;
		for (int i = ARRSIZE - 1; i >= index0; i--){
			c = z[i] * a + d;
			z[i] = c % test;
			d = c / test;
			if (z[i] != 0)
				index = i;
		}
		index0 = index;
		d = 0;
		for (int i = index0; i < ARRSIZE; i++){
			c = z[i] + d * test;
			z[i] = c / b;
			d = c % b;
		}
		Run = 0;
		for (int i = ARRSIZE - 1; i >= index0; i--){
			c = x[i] + z[i];
			x[i] = c % test;
			x[i - 1] += c / test;
			Run |= z[i];
		}
		a++;
		b += 2;
	}
	printf("%d.", x[0]);
	for (int i = 1; i < DISPCNT; i++){
		printf("%04d", x[i]);
	}
	finish = clock();
	duration = (double)(finish - start);
	printf("\n\n%f ms\n", duration);
	return 0;
}

/*#include<stdio.h>
#include <time.h>
#define ARRSIZE 716
#define DISPCNT 714
int main(){
	unsigned long long x[ARRSIZE], z[ARRSIZE];
	//x[0] = 10000000000000000000;
	//printf("%llu", x[0]);
	unsigned long long a = 1, b = 3, c, d = 0, Run = 1, Cnt = 0, test = 100000000000000;
	clock_t start, finish;
	double  duration = 0.0;
	start = clock();
	memset(x, 0, ARRSIZE*sizeof(unsigned long long));
	memset(z, 0, ARRSIZE*sizeof(unsigned long long));

	x[0] = 2;
	z[0] = 2;

	while (Run){
	d = 0;
	for (int i = ARRSIZE - 1; i >= index0; i--){
	c = z[i] * a + d;
	z[i] = c % test;
	d = c / test;
	if (z[i] != 0)
	index = i;
	}
	index0 = index;
	d = 0;
	for (int i = index0; i < ARRSIZE; i++){
	c = z[i] + d * test;
	z[i] = c / b;
	d = c % b;
	}
	Run = 0;
	for (int i = ARRSIZE - 1; i >= index0; i--){
	c = x[i] + z[i];
	x[i] = c % test;
	x[i - 1] += c / test;
	Run |= z[i];
	}
	a++;
	b += 2;
	}
	printf("%llu.", x[0]);
	for (int i = 1; i < DISPCNT; i++){
		printf("%014llu", x[i]);
	}
	finish = clock();
	duration = (double)(finish - start);
	printf("\n %f ms\n", duration);
	return 0;
}*/

