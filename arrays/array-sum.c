#include<stdio.h>
#include<stdlib.h>

int main(){

	int n,i,Sum;

	printf("Enter the size of the array : ");
	scanf("%d", &n);

	int arr[n];

	printf("Enter %d elements : \n", n);

	for(i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	for(i = 0; i < n; i++)
	{
		Sum = Sum + arr[i];
	}

	printf("Sum = %d\n", Sum);

	return 0;
}
