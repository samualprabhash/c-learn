#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

	int a,b,temp;

	a = 20;
	b = 30;

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	printf("Before Swapping a = %d and b = %d\n",a, b);

	temp = a;
	a = b;
	b = temp;

	printf("After Swapping a = %d and b = %d\n",a, b);

	return 0;
}
