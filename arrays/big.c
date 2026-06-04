#include<stdio.h>

int main(){

	int a,b;

	printf("Enter a value = ");
	scanf("%d", &a);

	
	printf("Enter b value = ");
	scanf("%d", &b);

	printf("The value of a is %d\n", a);
	printf("The value of b is %d\n", b);

	if( a > b ){

		printf("Big number is a %d\n",a);

	}
	else{

		printf("Big number is b %d\n",b);
	}
} 
