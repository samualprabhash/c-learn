#include<stdio.h>
#include<stdlib.h>

int change(int x);

int main(){

	int a = 10;

	printf("before function call : %d\n", a);

	change(a);

	printf("after function call : %d\n", a);

	return 0;
}

int change(int x){

	x = 20;

	printf("Inside Function : %d\n", x);
}
