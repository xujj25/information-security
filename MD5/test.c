#include <stdio.h>
#include "md5.h"

int main(int argc, char const *argv[])
{
    msgDigest("");
    msgDigest("a");
    msgDigest("abc");
    msgDigest("message digest");
    msgDigest("abcdefghijklmnopqrstuvwxyz");
    msgDigest("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    msgDigest("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
    return 0;
}
