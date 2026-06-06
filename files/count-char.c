#include<stdio.h>
#include<stdlib.h>


int main(){

	FILE *fp;
	int count = 0;

	fp = fopen("test.txt", "r");

	if(fp == NULL)
	{
		printf("cannot open file\n");
		return 1;
	}

	char ch;

	while((ch = fgetc(fp)) != EOF)
	{

		count++;

	}

	printf("total char = %d\n", count);

	fclose(fp);

	return 0;
}

