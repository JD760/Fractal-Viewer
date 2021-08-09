#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num = 1;

    if (*(char *)&num == 1)
    {
        printf("Little-Endian\n");
    }
    else
    {
        printf("Big-Endian\n");
    }
}