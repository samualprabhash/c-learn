#include<stdio.h>
#include<stdlib.h>

int main(){

	FILE *fp;

	char str[100];

	fp = fopen("test.txt", "r");

	fgets(str, sizeof(str), fp);

	printf("%s", str);

	fclose(fp);

}
