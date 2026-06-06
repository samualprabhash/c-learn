#include<stdio.h>
#include<stdlib.h>


int main(){

	FILE *fp;

	fp = fopen("test.txt", "r");

	if(fp == NULL)
	{
		printf("cannot open file\n");
		return 1;
	}

	char ch;

	while((ch = fgetc(fp)) != EOF)
	{

		putchar(ch);

	}

	fclose(fp);

	return 0;
}
