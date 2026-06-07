#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int turn = 0;

void *even(void *args)
{
	int i;

	for(i = 0; i <= 10; i += 2)
	{
		pthread_mutex_lock (&lock);

		if(turn != 0)

		pthread_cond_wait (&cond, &lock);

		printf("Even num : %d\n", i);

		turn = 1;

		pthread_cond_signal (&cond);

		pthread_mutex_unlock (&lock);

		sleep(1);
	}

	return NULL;
}

void *odd(void *args)
{
	int i;

	for(i = 1; i <= 10; i += 2)
	{
		pthread_mutex_lock(&lock);

		if(turn != 1)

		pthread_cond_wait (&cond, &lock);

		printf("odd num : %d\n", i);

		turn = 0;

		pthread_cond_signal(&cond);

		pthread_mutex_unlock(&lock);

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
