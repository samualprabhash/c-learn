#include<stdio.h>
#include<stdlib.h>

int main(){
 
	int i, n;

	printf("Enter the size of an array : ");
	scanf("%d", &n);

	int arr[n], temp[n];

	printf("Enter %d elements : \n", n);

	for(i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	for(i = 0; i < n; i++)
	{
		temp[i] = arr[n - 1 - i];
	}

	printf("Reverse array values are: ");

	for(i = 0; i < n; i++)
	{
		printf("%d\n", temp[i]);
	}

	return 0;
}
