#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/DES.hpp"

void 
encryptWrite(DATA_BLOCK64& srcDataBlock, KEY& key, FILE *srcFp, FILE *destFp)
{
    int i = 0;
    char bufChar;
    while ((bufChar = fgetc(srcFp)) != EOF) {
        srcDataBlock.data[i] = bufChar;
        i++;
        if (i == 8) {
            DES(&key, &srcDataBlock, ENCRYPT);
            for (i = 0; i < 8; i++)
                fprintf(destFp, "%d ", (int)srcDataBlock.data[i]);

            i = 0;
        }
    }
    for (; i < 8; i++)
        srcDataBlock.data[i] = '\0';
    DES(&key, &srcDataBlock, ENCRYPT);
    for (i = 0; i < 8; i++)
        fprintf(destFp, "%d ", (int)srcDataBlock.data[i]);
}

void 
decryptWrite(DATA_BLOCK64& srcDataBlock, KEY& key, FILE *srcFp, FILE *destFp)
{
    int i = 0;
    int bufCode;
    while (fscanf(srcFp, "%d", &bufCode) != EOF) {
        srcDataBlock.data[i] = (char)bufCode;
        i++;
        if (i == 8) {
            DES(&key, &srcDataBlock, DECRYPT);
            for (i = 0; i < 8; i++)
                fputc(srcDataBlock.data[i], destFp);

            i = 0;
        }
    }
    for (; i < 8; i++)
        srcDataBlock.data[i] = '\0';
    DES(&key, &srcDataBlock, DECRYPT);
    for (i = 0; i < 8; i++)
        fputc(srcDataBlock.data[i], destFp);
}

int main(void)
{
    FILE* fp = fopen("key_64bits", "r");
    if (fp == NULL) {
        printf("Run \'./bin/key-gen\' at first!\n");
        return -1;
    }
    int i = 0;
    KEY key;
    DATA_BLOCK64 srcDataBlock;
    char buffer[9];
    while (i != 9 && (buffer[i] = fgetc(fp)) != EOF)
        i++;
    fclose(fp);
    if (i != 8) {
        printf("Error occurs when reading key of 64 bits!\n");
        return -1;
    }
    for (i = 0; i < 8; i++)
        key.data[i] = buffer[i];

    printf("Input your option:\n");
    printf("e ------ for encrypt\n");
    printf("d ------ for decrypt\n");
    char command;
    char filename[100];
    char outFilename[10];
    scanf("%c", &command);
    DES_OPT opt;
    switch(command) {
        case 'e':
        case 'd':
            opt = command == 'e' ? ENCRYPT: DECRYPT;
            strcpy(outFilename, command == 'e' ? "cipher.txt" : "plain.txt");
            printf("Input the name of the file you want to deal:\n");
            scanf("%s", filename);
            fp = fopen(filename, "r");
            if (fp == NULL) {
                printf("The filename you input does not exist!\n");
                return -1;
            }
            FILE *outfp;
            outfp = fopen(outFilename, "w");
            if (outfp == NULL) {
                printf("Error occurs when create output file!\n");
                return -1;
            }
            
            if (opt == ENCRYPT)
                encryptWrite(srcDataBlock, key, fp, outfp);
            else
                decryptWrite(srcDataBlock, key, fp, outfp);

            fclose(fp);
            fclose(outfp);
            printf("Output saved in %s\n", outFilename);
            break;
        default:
            printf("Your command is wrong!\n");
            return -1;
    }
    return 0;
}