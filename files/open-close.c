#include<stdio.h>
#include<stdlib.h>

int main()
{

	FILE *fp;

	fp = fopen("test.txt", "w");

	if (fp == NULL)
	{
		printf("File opened failed\n");

		return 1;
	}


	printf("File opened successfull\n");

	fclose(fp);

	return 0;
}
