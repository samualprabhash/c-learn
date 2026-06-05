#include<stdio.h>
#include<stdlib.h>


struct test{

	int roll : 4;
	int age : 5;
	int id : 6;
};

int main()
{
	struct test t1;

	printf("the size of the struct test is : %ld\n", sizeof(t1));

//size of operation cannot be useful for bitfiled members bcz it is bits not bytes.

	//printf("the size of the roll is : %d\n", sizeof(t1.roll));

	//printf("the size of the age is : %d\n", sizeof(t1.age));

	//printf("the size of the id is : %d\n", sizeof(t1.id));




	t1.roll = 3;

	printf("the t1.roll is %d\n", t1.roll);

	t1.age = 10;

	printf("the t1.age is %d\n", t1.age);

	t1.id = 5;

	printf("the t1.id is %d\n", t1.id);


	printf("the t1.roll is %d\n", t1.roll);
	printf("the t1.age is %d\n", t1.age);
	printf("the t1.id is %d\n", t1.id);

	return 0;
}
