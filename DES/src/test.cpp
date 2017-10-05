#include <stdio.h>
#include <stdlib.h>
#include "../include/DES.hpp"

int main(int argc, char const *argv[])
{
    DATA_BLOCK64 srcData;
    srcData.data[0] = 'a';
    srcData.data[1] = 'b';
    srcData.data[2] = 'c';
    srcData.data[3] = 'd';
    srcData.data[4] = 'e';
    srcData.data[5] = 'f';
    srcData.data[6] = 'g';
    srcData.data[7] = 'h';

    KEY key;
    key.data[0] = 'a';
    key.data[1] = 'b';
    key.data[2] = 'c';
    key.data[3] = 'd';
    key.data[4] = 'e';
    key.data[5] = 'f';
    key.data[6] = 'g';
    key.data[7] = 'h';

    int i;
    DES(&key, &srcData, ENCRYPT);
    DES(&key, &srcData, ENCRYPT);
    DES(&key, &srcData, ENCRYPT);
    DES(&key, &srcData, ENCRYPT);

    for (i = 0; i < 8; i++)
        printf("%c", srcData.data[i]);
    printf("\n");

    DES(&key, &srcData, DECRYPT);
    DES(&key, &srcData, DECRYPT);
    DES(&key, &srcData, DECRYPT);
    DES(&key, &srcData, DECRYPT);

    for (i = 0; i < 8; i++)
        printf("%c", srcData.data[i]);
    printf("\n");


    return 0;
}