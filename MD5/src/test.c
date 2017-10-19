#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "md5.h"


/* testcases:
MD5 test suite:
MD5 ("") = d41d8cd98f00b204e9800998ecf8427e
MD5 ("a") = 0cc175b9c0f1b6a831c399e269772661
MD5 ("abc") = 900150983cd24fb0d6963f7d28e17f72
MD5 ("message digest") = f96b697d7cb7938d525a2f31aaf161d0
MD5 ("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
MD5 ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") =
d174ab98d277d9f5a5611c2c9f419d9f
MD5 ("12345678901234567890123456789012345678901234567890123456789012345678901234567890") = 57edf4a22be3c955ac49da2e2107b67a
*/
int main(int argc, char const *argv[])
{
    int size, index;
    char inputChar;
    char* buffer;
    printf("Please input buffer size: ");
    scanf("%d", &size);
    buffer = (char*)malloc(60);
    printf("PLease input the string you want to do message digesting:\n");
    fgets(buffer, 60, stdin);  // clear the input buffer before the user input
    free(buffer);
    buffer = (char*)malloc(size);
    while ((inputChar = getchar()) != EOF && inputChar != '\n' && index != size - 1)
        buffer[index++] = inputChar;
    buffer[index] = '\0';
    printf("Result:\n");
    msgDigest(buffer);
    printf("\n");
    free(buffer);
    return 0;
}
