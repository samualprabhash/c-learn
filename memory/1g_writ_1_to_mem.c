#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *ptr;
    size_t size = 1024ULL * 1024 * 1024;   // 1 GB

    printf("Memory before allocation:\n");
    system("free -h");

    ptr = (char *)malloc(size);

    if(ptr == NULL)
    {
        printf("Allocation failed\n");
        return 1;
    }

    /* Touch every page so the OS actually commits memory */
    memset(ptr, 1, size);

    printf("\nMemory after allocating 1 GB:\n");
    system("free -h");


    printf("\nPress Enter to free memory...");
    getchar();
    getchar();


//if you wont free then?
    free(ptr);

    printf("\nMemory after free():\n");
    system("free -h");

    return 0;
}
