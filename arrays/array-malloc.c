#include<stdio.h>
#include<stdlib.h>

int main(){

	int i, n;

	printf("Enter size of an array : ");
	scanf("%d", &n);

	int *arr = (int *)malloc(n * sizeof(int));

	printf("Enter %d elements : ", n);

	for(i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	printf("Array elements are : ");

	for(i = 0; i < n; i++)
	{
		printf("%d\n", arr[i]);
	}

	free(arr);

	return 0;
}
