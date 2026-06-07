#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<pthread.h>

void *even(void *args)
{
	int i;

	for(i = 0; i <= 10; i += 2)
	{
		printf("Even numbers are : %d\n", i);
		sleep(1);
	}

		return NULL;
}

void *odd(void *args)
{

	int i;

	for(i = 1; i <= 10; i += 2)
	{
		printf("Odd numbers are : %d\n", i);
		sleep(1);

	}

		return NULL;
}

int main()
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, even, NULL);

	pthread_create(&t2, NULL, odd, NULL);

	pthread_join(t1, NULL);

	pthread_join(t2, NULL);

	return 0;
}
