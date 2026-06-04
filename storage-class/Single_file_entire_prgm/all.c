#include<stdio.h>

int gb_cnt = 0;

void cnt_fun1();
void cnt_fun2();


int main()
{
	int cnt1 = 0;

	printf("main cnt1 = %d\n", cnt1);

	cnt1++;

	printf("main cnt1 after inc = %d\n", cnt1);

	cnt_fun1();
	cnt_fun2();

	printf("final gb_cnt = %d\n", gb_cnt);

	return 0;
}

void cnt_fun1()
{
	int cnt1 = 0;

	printf("local cnt1 = %d\n", cnt1);

	printf("global gb_cnt = %d\n", gb_cnt);

	gb_cnt++;

	printf("global gb_cnt after inc = %d\n", gb_cnt);
}

void cnt_fun2()
{
        int cnt1 = 0;
  
        printf("local cnt1 = %d\n", cnt1);
  
	printf("global gb_cnt = %d\n", gb_cnt);
  
        gb_cnt++;
  
        printf("global gb_cnt after inc = %d\n", gb_cnt);
}
