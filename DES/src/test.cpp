#include <stdio.h>
#include <stdlib.h>
#include "../include/DES.hpp"

int main(int argc, char const *argv[])
{
    DATA_BLOCK32 d;
    d.data[0] = 'a';
    d.data[1] = 'b';
    d.data[2] = 'c';
    d.data[3] = 'd';
    int i;

    for (i = 0; i <= 31; i++) {
        printf("%d", getBit(&d, i));
        if (i % 8 == 7)
            printf("\n");
    }

    printf("after:\n");
    
    setBit(&d, 18, 1);
    setBit(&d, 23, 1);
    setBit(&d, 29, 0);

    for (i = 0; i <= 31; i++) {
        printf("%d", getBit(&d, i));
        if (i % 8 == 7)
            printf("\n");
    }
    return 0;
}