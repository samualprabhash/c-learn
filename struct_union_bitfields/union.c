#include<stdio.h>
#include<stdlib.h>


union test{

	int a;
	char b;
	double c;
};


int main()
{

	union test t1;

	printf("the size of the union is %ld\n", sizeof(t1));

	t1.a = 3;

	printf("the t1.a value is : %d\n", t1.a);

	t1.b = 's';

	printf("the t1.b name is : %c\n", t1.b);

	t1.c = 2345.600;

	printf("the t1.c num is : %f\n", t1.c);




	printf("the t1.a value is : %d\n", t1.a);

	printf("the t1.b value is : %c\n", t1.b);

	printf("the t1.c value is : %f\n", t1.c);




	printf("the size of a is : %ld\n", sizeof(t1.a));

	printf("the size of b is : %ld\n", sizeof(t1.b));

	printf("the size of c is : %ld\n", sizeof(t1.c));

	return 0;
}
