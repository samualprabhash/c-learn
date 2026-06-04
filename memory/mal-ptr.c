#include<stdio.h>
#include<stdlib.h>

int main(){

	int *ptr1;
	int *ptr2;
	
// here no addr is assinged to ptrs.	
	printf(" addrs of ptr1 %d\n", ptr1);
	printf(" addrs of ptr2 %d\n", ptr2);
	

	ptr1 = malloc(100);


// here only ptr1 ddr is assinged .	
	printf(" addrs of ptr1 %d\n", ptr1);
	printf(" addrs of ptr2 %d\n", ptr2);
	
// enterin value into address
	*ptr1= 5;


// since pt2 not got memory, we can not insert data into ptr2
// if you try to insert data, then segmentaion fault may come, may not if addrss is falling in your range.
// but you get randaom data.
//	*ptr2= 8;
	
	printf(" value at ptr1 %d\n", *ptr1);
}
