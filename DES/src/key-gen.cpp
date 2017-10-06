#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/DES.hpp"

void gen_odd_parity(char *c) {
    char temp = *c;
    int i, count = 0;
    for (i = 0; i < 7; i++) {
        if (temp & 1)
            count++;
        temp >>= 1;
    }
    if (count & 1)
        *c += (1 << 7);
}

int main() {
    KEY key;
    int i;
    srand((unsigned)time(NULL));
    for (i = 0; i < 8; i++) {
        key.data[i] = (char)(rand() % 128);
        gen_odd_parity(&key.data[i]);
    }        
        
    FILE *fp;
    fp = fopen("key_64bits", "w");
    if (fp != NULL) {
        for (i = 0; i < 8; i++)
            fputc(key.data[i], fp);
        fclose(fp);
    }

    printf("Finished key generation, the key was saved in file \"key_64bits\"\n");

    return 0;
}