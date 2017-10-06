struct data_block64 {
    char data[8];
};

struct data_block32 {
    char data[4];
};

struct data_block48 {
    char data[6];
};

struct data_block56 {
    char data[7];
};

typedef struct data_block64 DATA_BLOCK64;
typedef struct data_block48 DATA_BLOCK48;
typedef struct data_block32 DATA_BLOCK32;
typedef struct data_block48 SUBKEY;
typedef struct data_block56 KEY56;
typedef struct data_block64 KEY;

enum opt{ ENCRYPT, DECRYPT };
typedef enum opt DES_OPT;

SUBKEY subkey_set[16];

int pc_1_table[56] = 
{
    57, 49, 41, 33, 25, 17, 9,
    1,  58, 50, 42, 34, 26, 18,
    10, 2,  59, 51, 43, 35, 27,
    19, 11, 3,  60, 52, 44, 36,

    63, 55, 47, 39, 31, 23, 15,
    7,  62, 54, 46, 38, 30, 22,
    14, 6,  61, 53, 45, 37, 29,
    21, 13, 5,  28, 20, 12, 4
};

int pc_2_table[48] =
{
    14, 17, 11, 24, 1,  5,
    3,  28, 15, 6,  21, 10,
    23, 19, 12, 4,  26, 8,
    16, 7,  27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int ip_table[64] = 
{
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int ip_inverse_table[64] =
{
    40, 8,  48, 16, 56, 24, 64, 32,
    39, 7,  47, 15, 55, 23, 63, 31,
    38, 6,  46, 14, 54, 22, 62, 30,
    37, 5,  45, 13, 53, 21, 61, 29,
    36, 4,  44, 12, 52, 20, 60, 28,
    35, 3,  43, 11, 51, 19, 59, 27,
    34, 2,  42, 10, 50, 18, 58, 26,
    33, 1,  41, 9,  49, 17, 57, 25
};

char s_box[8][4][16] =
{
    {
        { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
        { 0, 15, 7, 4, 15, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
        { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
        { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
    },
    {
        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
        { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
        { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
        { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
    },
    {
        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
        { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
        { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
        { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
    },
    {
        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
        { 12, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
        { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
        { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
    },
    {
        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
        { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
        { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
        { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
    },
    {
        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
        { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
        { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
        { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
    },
    {
        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
        { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
        { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
        { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
    },
    {
        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
        { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
        { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
        { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
    }
};

int p_table[32] =
{
    16, 7,  20, 21,
    29, 12, 28, 17,
    1,  15, 23, 26,
    5,  18, 31, 10,
    2,  8,  24, 14,
    32, 27, 3,  9,
    19, 13, 30, 6,
    22, 11, 4,  25
};

int e_ext_table[48] =
{
    32, 1,  2,  3,  4,  5,
    4,  5,  6,  7,  8,  9,
    8,  9,  10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

template <typename DATA_BLOCK>
char getBit(DATA_BLOCK* block, int bitIdx) {
    return ((block -> data)[bitIdx / 8] >> (bitIdx % 8)) & 1;
}

template <typename DATA_BLOCK>
void setBit(DATA_BLOCK* block, int bitIdx, char val) {
    if (val)
        (block -> data)[bitIdx / 8] |= (1 << (bitIdx % 8));
    else
        (block -> data)[bitIdx / 8] &= ~(1 << (bitIdx % 8));
}

template <typename SRC_BLOCK, typename DEST_BLOCK>
void permutation(DEST_BLOCK* destBlock, SRC_BLOCK* srcBlock, int table[]) {
    int i;
    int destBlockLen = 8 * sizeof(destBlock -> data);
    for (i = 0; i < destBlockLen; i++) {
        setBit(destBlock, i, getBit(srcBlock, table[i] - 1));
    }
}

KEY56 PC_1(KEY *key) {
    KEY56 resultKey;
    permutation(&resultKey, key, pc_1_table);
    return resultKey;
}

SUBKEY PC_2(KEY56 *key) {
    SUBKEY sk;
    permutation(&sk, key, pc_2_table);
    return sk;
}

void cycle_left_shift(KEY56 *block) {
    char temp[8];
    temp[0] = getBit(block, 8);
    temp[1] = getBit(block, 16);
    temp[2] = getBit(block, 24);
    temp[3] = getBit(block, 32);
    temp[4] = getBit(block, 40);
    temp[5] = getBit(block, 48);
    temp[6] = getBit(block, 28);
    temp[7] = getBit(block, 0);

    int i;
    for (i = 0; i < 7; i++) {
        (block -> data)[i] >>= 1;
        setBit(block, i * 8 + 7, temp[i]);
        if (i == 3)
            setBit(block, 27, temp[7]);
    }
}

void key_schedule(KEY *key, DES_OPT opt) {
    KEY56 key56 = PC_1(key);
    if (opt == ENCRYPT) {
        for (int i = 1; i <= 16; i++) {
            switch(i) {
                case 1:
                case 2:
                case 9:
                case 16:
                    cycle_left_shift(&key56);
                    break;
                default:
                    cycle_left_shift(&key56);
                    cycle_left_shift(&key56);
            }
            subkey_set[i - 1] = PC_2(&key56);
        }
    } else {
        for (int i = 1; i <= 16; i++) {
            switch(i) {
                case 1:
                case 2:
                case 9:
                case 16:
                    cycle_left_shift(&key56);
                    break;
                default:
                    cycle_left_shift(&key56);
                    cycle_left_shift(&key56);
            }
            subkey_set[16 - i] = PC_2(&key56);
        }
    }
}

DATA_BLOCK64 IP(DATA_BLOCK64 *src_data) {
    DATA_BLOCK64 resultBlock;
    permutation(&resultBlock, src_data, ip_table);
    return resultBlock;
}

DATA_BLOCK64 IP_inverse(DATA_BLOCK64 *src_data) {
    DATA_BLOCK64 resultBlock;
    permutation(&resultBlock, src_data, ip_inverse_table);
    return resultBlock;
}

DATA_BLOCK32 P_permutation(DATA_BLOCK32 *src_data) {
    DATA_BLOCK32 resultBlock;
    permutation(&resultBlock, src_data, p_table);
    return resultBlock;
}

DATA_BLOCK32 S_box_change(DATA_BLOCK48 *src_data) {
    DATA_BLOCK32 resultBlock;
    int row, col, i;
    char highBits, lowBits;
    for (i = 0; i < 8; i++) {
        row = getBit(src_data, i * 6 + 5) * 2 + getBit(src_data, i * 6);
        col = getBit(src_data, i * 6 + 4) * 8 +
              getBit(src_data, i * 6 + 3) * 4 +
              getBit(src_data, i * 6 + 2) * 2 +
              getBit(src_data, i * 6 + 1);
        if (i & 1) {
            highBits = s_box[i][row][col];
            resultBlock.data[i / 2] = (highBits << 4) + lowBits;
        } else {
            lowBits = s_box[i][row][col];
        }
    }
    return resultBlock;
}

DATA_BLOCK48 E_extension(DATA_BLOCK32 *src_data) {
    DATA_BLOCK48 resultBlock;
    permutation(&resultBlock, src_data, e_ext_table);
    return resultBlock;
}

template <typename DATA_BLOCK>
void XOR(DATA_BLOCK *destBlock, DATA_BLOCK *otherBlock) {
    int byteNum = sizeof(destBlock -> data);
    int i;
    for (i = 0; i < byteNum; i++)
        (destBlock -> data)[i] ^= (otherBlock -> data)[i];
}

DATA_BLOCK32 Feistel(DATA_BLOCK32 *right_block, SUBKEY *skey) {
    DATA_BLOCK48 extBlock = E_extension(right_block);
    XOR(&extBlock, skey);
    DATA_BLOCK32 resultBlock = S_box_change(&extBlock);
    resultBlock = P_permutation(&resultBlock);
    return resultBlock;
}

void T_iteration(DATA_BLOCK64* src_data) {
    DATA_BLOCK32 leftBlock, rightBlock, tempBlock;
    int i;
    for (i = 0; i < 4; i++) {
        leftBlock.data[i] = (src_data -> data)[i];
        rightBlock.data[i] = (src_data -> data)[i + 4];
    }
    for (i = 0; i < 16; i++) {
        tempBlock = Feistel(&rightBlock, &subkey_set[i]);
        XOR(&leftBlock, &tempBlock);
        tempBlock = rightBlock;
        rightBlock = leftBlock;
        leftBlock = tempBlock;
    }
    for (i = 0; i < 4; i++) {
        (src_data -> data)[i] = rightBlock.data[i];
        (src_data -> data)[i + 4] = leftBlock.data[i];
    }
}


void DES(KEY *key, DATA_BLOCK64* src_data, DES_OPT opt) {
    key_schedule(key, opt);
    IP(src_data);
    T_iteration(src_data);
    IP_inverse(src_data);
}
