typedef struct 
{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    unsigned long int count;
    unsigned char msgBlock[64];  /* 512 bits msg block*/

} TEMP_DT;


unsigned int F(unsigned int b, unsigned int c, unsigned int d);
unsigned int G(unsigned int b, unsigned int c, unsigned int d);
unsigned int H(unsigned int b, unsigned int c, unsigned int d);
unsigned int I(unsigned int b, unsigned int c, unsigned int d);
unsigned int cycleLeftShift(unsigned int num, int shiftCount);
unsigned int getXWord(unsigned char *buf, int x_bit);
void onePaceCalc(TEMP_DT* tempData, int funcIdx, int paceIdx);
void mdCompress(TEMP_DT* tempData);
void tempDataBufCpy(unsigned char* buf, unsigned char* srcPtr, unsigned int len);
void count2Bits(unsigned char* countBits, unsigned int count);
void hash(TEMP_DT* tempData, unsigned char* curPtr, unsigned int len);
void init(TEMP_DT* tempData);
void msgDigest(const char* string);