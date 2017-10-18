#include <stdio.h>
#include <string.h>
#include "md5.h"


unsigned char PADDING[64] =
{
    0x80, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0
};

int X_bit[4][16] =
{
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
    { 1,  6, 11,  0,  5, 10, 15,  4,  9, 14,  3,  8, 13,  2,  7, 12 },
    { 5,  8, 11, 14,  1,  4,  7, 10, 13,  0,  3,  6,  9, 12, 15,  2 },
    { 0,  7, 14,  5, 12,  3, 10,  1,  8, 15,  6, 13,  4, 11,  2,  9 }
};

unsigned int T_table[4][16] =
{
    {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821
    },
    {
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a
    },
    {
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665
    },
    {
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    }
};

int s_bit[4][16] =
{
    { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22 },
    { 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20 },
    { 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23 },
    { 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 }
};

unsigned int F(unsigned int b, unsigned int c, unsigned int d) {
    return ((b & c) | ((~b) & d));
}
unsigned int G(unsigned int b, unsigned int c, unsigned int d) {
    return ((b & d) | (c & (~d)));
}
unsigned int H(unsigned int b, unsigned int c, unsigned int d) {
    return (b ^ c ^ d);
}
unsigned int I(unsigned int b, unsigned int c, unsigned int d) {
    return (c ^ (b | (~d)));
}

unsigned int cycleLeftShift(unsigned int num, int shiftCount) {
    return ((num << shiftCount) | (num >> (32 - shiftCount)));
}

unsigned int getXWord(unsigned char *buf, int x_bit) {
    return (buf[x_bit * 4] | (buf[x_bit * 4 + 1] << 8) |
        (buf[x_bit * 4 + 2] << 16) | (buf[x_bit * 4 + 3] << 24));
}

void onePaceCalc(TEMP_DT* tempData, int funcIdx, int paceIdx) {
    unsigned int gVal, XWord, bValAfter;
    switch(funcIdx) {
        case 0:
            gVal = F(tempData -> b, tempData -> c, tempData -> d);
            break;
        case 1:
            gVal = G(tempData -> b, tempData -> c, tempData -> d);
            break;
        case 2:
            gVal = H(tempData -> b, tempData -> c, tempData -> d);
            break;
        case 3:
            gVal = I(tempData -> b, tempData -> c, tempData -> d);
            break;
    }
    XWord = getXWord(tempData -> msgBlock, X_bit[funcIdx][paceIdx]);
    bValAfter = tempData -> b + 
        cycleLeftShift((tempData -> a + gVal + XWord + T_table[funcIdx][paceIdx]), s_bit[funcIdx][paceIdx]);
    tempData -> a = tempData -> d;
    tempData -> d = tempData -> c;
    tempData -> c = tempData -> b;
    tempData -> b = bValAfter;
}

void mdCompress(TEMP_DT* tempData) {
    unsigned int a, b, c, d;
    a = tempData -> a;
    b = tempData -> b;
    c = tempData -> c;
    d = tempData -> d;
    int funcIdx, paceIdx;
    for (funcIdx = 0; funcIdx < 4; funcIdx++)
        for (paceIdx = 0; paceIdx < 16; paceIdx++)
            onePaceCalc(tempData, funcIdx, paceIdx);
    tempData -> a += a;
    tempData -> b += b;
    tempData -> c += c;
    tempData -> d += d;
}

void tempDataBufCpy(unsigned char* buf, unsigned char* srcPtr, unsigned int len) {
    int i;
    for (i = 0; i < len; i++)
        buf[i] = srcPtr[i];
}

void count2Bits(unsigned char* countBits, unsigned int count) {
    int i;
    for (i = 0; i < 4; i++)
        countBits[i] |= (count >> (i * 8)) & 0xFF;
}

void hash(TEMP_DT* tempData, unsigned char* curPtr, unsigned int len) {
    if (len > 0)
        tempData -> count += len * 8;
    tempDataBufCpy(tempData -> msgBlock, curPtr, len);
    if (len < 64) {
        unsigned char countBits[8];
        memset(countBits, 0, 8);
        int paddingLen = (len < 56) ? 56 - len : 120 - len;
        count2Bits(countBits, (unsigned int)tempData -> count);
        count2Bits((unsigned char*)&countBits[4], (unsigned int)(tempData -> count >> 32));
        if (paddingLen <= 56) {
            tempDataBufCpy((unsigned char*)&(tempData -> msgBlock)[len],
                PADDING, paddingLen);
        } else {
            tempDataBufCpy((unsigned char*)&(tempData -> msgBlock)[len],
                PADDING, paddingLen - 56);
            mdCompress(tempData);
            tempDataBufCpy(tempData -> msgBlock, PADDING + paddingLen - 56, 56);
        }
        tempDataBufCpy((unsigned char*)&(tempData -> msgBlock)[56], countBits, 8);
    }
    mdCompress(tempData);
}

void init(TEMP_DT* tempData) {
    tempData -> a = 0x67452301;
    tempData -> b = 0xefcdab89;
    tempData -> c = 0x98badcfe;
    tempData -> d = 0x10325476;
    tempData -> count = 0;
    memset(tempData -> msgBlock, 0, 64);
}

void digestHexPrint(unsigned char* digest) {
    int i;
    for (i = 0; i < 16; i++) {
        // user mode
        printf("%01x", (digest[i] >> 4) & 0xF);
        printf("%01x", digest[i] & 0xF);
    }
}

void msgDigest(const char* string)  {
    TEMP_DT tempData;
    int notHashLen;
    int len = strlen(string);
    init(&tempData);
    while ((notHashLen = len - (tempData.count >> 3)) >= 64)
        hash(&tempData, (unsigned char*)&string[tempData.count >> 3], 64);
    hash(&tempData, (unsigned char*)&string[tempData.count >> 3], notHashLen);
    unsigned char digest[16];
    memset(digest, 0, 16);
    count2Bits(digest, tempData.a);
    count2Bits(&digest[4], tempData.b);
    count2Bits(&digest[8], tempData.c);
    count2Bits(&digest[12], tempData.d);

    digestHexPrint(digest);
}