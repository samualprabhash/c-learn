#include<stdio.h>
#include<stdlib.h>

int add (int num1, int num2);

int main(){

	int a, b, result;

	printf("Enter a value : ");
	scanf("%d" , &a);

	printf("Enter b value : ");
	scanf("%d", &b);

	result = add (a , b);

	printf("Sum = %d/n", result);

	return 0;
}

int add (int num1, int num2){

	int sum = num1 + num2;

	return sum;
}
