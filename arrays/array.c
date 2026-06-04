#include<stdio.h>
#include<stdlib.h>

int main()
{

	int n,i;

	printf("Enter the size of the array : ");
	scanf("%d", &n);

	int arr[n];

	printf("Enter %d elements: ",n);

	for(i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	printf("Array elements are : \n");

	for(i = 0; i < n; i++)
	{
		printf("%d\n",arr[i]);
	}

	return 0;
}
