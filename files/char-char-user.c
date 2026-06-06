#include<stdio.h>
#include<stdlib.h>


int main(){

	FILE *fp;

	fp = fopen("test.txt", "w");

	if(fp == NULL)
	{
		printf("cannot open file\n");
		return 1;
	}

	fputc('H', fp);
	fputc('E', fp);
	fputc('L', fp);
	fputc('L', fp);
	fputc('O', fp);

	fclose(fp);

	return 0;
}
