#include<stdio.h>
#include<stdlib.h>

int main(){


	FILE *fp;

	fp = fopen("test.txt", "a");

	fprintf(fp, "\nAppended Text");

	fclose(fp);

	return 0;
}
