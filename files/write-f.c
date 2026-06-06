#include<stdio.h>
#include<stdlib.h>

int main()
{

	FILE *fp;

	fp = fopen("test.txt", "w");

	if (fp == NULL)
	{
		printf("File not opened\n");

		return 1;
	}

	printf("File opened\n");

	fprintf(fp, "Hello world\n");

	fclose(fp);

	return 0;
} 
