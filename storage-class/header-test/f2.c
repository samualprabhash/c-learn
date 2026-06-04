#include "my.h"


int sum(int a, int b)
{
	int sum;

	sum = a + b;


	global_count++;

	printf("In sum function the global count is : %d\n", global_count);

	return sum; 
} 
