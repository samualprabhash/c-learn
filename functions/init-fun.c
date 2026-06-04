#include<stdio.h>
#include<stdlib.h>

	void sum(){

		int a, b, sum;

		printf("Enter a value : ");
		scanf("%d", &a);

		printf("Enter b value : ");
		scanf("%d", &b);

		sum = a + b;

		printf("Sum = %d\n", sum);
	}


void main(){

	sum();
	sum();
	sum();
}
