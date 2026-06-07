#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int a = 10, b = 20;

void *sum (void *args)
{
	int sum = a + b;

	printf("Sum = %d\n", sum);

	return NULL;
}

void *product (void *agrs)
{
	int product = a * b;

	printf("Product = %d\n", product);

	return NULL;
}

int main()
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, sum, NULL);

	pthread_create(&t2, NULL, product, NULL);

	pthread_join(t1, NULL);

	pthread_join(t2, NULL);

	return 0;
}
