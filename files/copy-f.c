#include<stdio.h>
#include<stdlib.h>

int main(){

	FILE *src, *dst;

	char ch;

	src = fopen("test.txt", "r");

	dst = fopen("copy.txt", "w"); 

	while((ch = fgetc(src)) != EOF)
	{
		fputc(ch, dst);
	}

	fclose(src);
	fclose(dst);

	return 0;

}
