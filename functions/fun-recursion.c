#include<stdio.h>
#include<stdlib.h>

void print_num(int n);

int main(){

	print_num(1);

	return 0;
}

void print_num(int n){

	if(n > 5){

	return;

	}
		printf("%d\n", n);

		print_num(n + 1);
}
