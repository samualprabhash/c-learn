#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

	int a = 10, b = 20;

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	printf("Sum = %d\n", a + b);

	return 0;

}
