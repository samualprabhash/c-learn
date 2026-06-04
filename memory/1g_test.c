#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *ptr;

    ptr = (char *)malloc(1024 * 1024 * 1024);  // 1 GB

    if(ptr == NULL)
    {
        printf("Memory allocation failed\n");
	sleep(100);
    }
    else
    {
        printf("1 GB memory allocated successfully\n");
	sleep(100);
        free(ptr);
    }


    return 0;
}
