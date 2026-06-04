#include<stdio.h>
#include<stdlib.h>

void change(int *x);

int main(){

	int a = 10;

	printf("before function call : %d\n", a);

	change(&a);

	printf("after function call : %d\n", a);

	return 0;
}

void change(int *x){

	*x = 20;

	printf("Inside function : %d\n", *x);
}
