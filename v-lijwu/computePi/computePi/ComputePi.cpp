#include<iostream>
#include<cmath>
#include<ctime>

using namespace std;

void add(int *a, int *b, int *sum,int len){
	int carry = 0;
	for(int i = len - 1;i >= 0;i --){
		sum[i] = a[i] + b[i] + carry;
		if(sum[i] > 10000){
			sum[i] -= 10000;
			carry = 1;
		}
		else 
			carry = 0;
	}
}

void sub(int *a, int *b,int *ans, int len){
	int borrow = 0;
	for(int i = len - 1;i >= 0;i --){
		ans[i] = a[i] - b[i] - borrow;
		if(ans[i] < 0){
			ans[i] = ans[i] + 10000;
			borrow = 1;
		}
		else 
			borrow = 0;
	}
}

void divide(int *dividen, int divisor, int *ans, int len){
	int temp = 0;
	int remainder = 0;
	for (int i = 0;i < len; i ++){
		temp = dividen[i] + remainder;
		ans[i] = temp/divisor;
		remainder = (temp % divisor) * 10000;
	}
}
int main(){
	int digits;
	while(cout<<"Please enter the digits: ", cin >> digits){

		cout<<"Print directly[0] or save the result in file[1]: "<<endl;
		int choose;
		cin>>choose;
		int start = clock();

		int len = digits/4 + 1;
		int *result = new int[len];
		int *first_item = new int [len];
		int *second_item = new int [len];
		int *temp = new int [len];
		int times = (int) (digits/1.39793 + 1);
		for(int i = 0;i < len;i ++)
			result[i] = first_item[i] = second_item[i] = temp[i] = 0;

		first_item[0] = 16*5;
		second_item[0] = 239*4;

		for(int i = 1;i <= times;i ++){
			divide(first_item,5*5,first_item,len);
			divide(second_item,239*239,second_item,len);
			sub(first_item, second_item, temp,len);
			divide(temp,2*i - 1,temp,len);
			if(i % 2 == 0){
				sub(result, temp, result, len);
			}
			else 
				add(result ,temp,result,len);
		}

		int end = clock();
		
		cout<<"Time costs: "<<float(end - start) / CLOCKS_PER_SEC<<endl;
		if(choose == 1){
			cout<<"The result is in Pi_restlt.txt file"<<endl;
			FILE* fp = fopen("Pi_result.txt", "w");
			for (int i = 1; i < len; i++){
				fprintf(fp, "%04d", result[i]);
			}
			fclose(fp);
		}
		else{
			for (int i = 1; i < len; i++){
				printf("%04d", result[i]);
			}
		}
		delete [] result;
		delete [] first_item;
		delete [] second_item;
		delete [] temp;
	}
	return 0;
}