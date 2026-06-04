#include<stdio.h>
#include<stdlib.h>

int main(){

	int i, n;

	printf("Enter the size of an array : ");
	scanf("%d", &n);

	int arr[n];

	printf("Enter %d elements : ", n);

	for(i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	int Big = arr[0];

	for(i = 1; i < n; i++)
	{
		if(Big < arr[i])
		{
			Big = arr[i];
		}
	}

	printf("Big = %d\n", Big);
	return 0;

}
