#include "my.h"


int global_count;


int main()
{
	int result, pro;
	int a = 10;
	int b = 20;

	result = sum(a, b);

	pro = product(a, b);

	printf("Sum = %d\n", result);

	printf("product = %d\n", pro);


	global_count++;

	printf("In main function global counter value is : %d\n", global_count);

	return 0;
} 
