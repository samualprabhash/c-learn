#include<stdio.h>
#include<stdlib.h>

struct test{

	int a;
	char b;
	double c;
};

int main(){

	struct test t1;


///  testing
///
	printf("size of Structure test is %ld\n", sizeof(t1));

	
	printf("size of t1.a is %ld\n", sizeof(t1.a));

	printf("size of t1.b is %ld\n", sizeof(t1.b));

	printf("size of t1.c is %ld\n", sizeof(t1.c));





	t1.a = 3;

	printf("The t1.a value is : %d\n", t1.a);

	t1.b = 'a';

	printf("The t1.b name is : %c\n", t1.b);

	t1.c = 2609.345;

	printf("The t1.c num is : %f\n", t1.c);


	
	printf("The t1.a value is : %d\n", t1.a);

	printf("The t1.b value is : %c\n", t1.b);

	printf("The t1.c value is : %f\n", t1.c);

	return 0;

}	
