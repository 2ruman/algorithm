/*
 * Author: Truman (truman.t.kim@gmail.com)
 *
 * Example to handle big numbers exceeding maximum boundary of primitive integer type.
 */

#include <stdio.h>
#include <assert.h>

int myStrlen(const char* str) {
    int ret = 0;
    while (*str++ != '\0') ret++;
    return ret;
}

#define MAX_BN_SIZ 100
#define MAX_BN_CNT 100

typedef int* BN;

int mBnCnt;
int mBigNumbers[MAX_BN_CNT][MAX_BN_SIZ];

void init() {
    mBnCnt = 0;
}

void* bnAlloc() {
    for (int i = 0; i < MAX_BN_SIZ; i++) {
        mBigNumbers[mBnCnt][i] = 0;
    }
    return &mBigNumbers[mBnCnt++];
}

void plusBN(BN bn1, BN bn2, BN res) {

    for (int i = 0; i < MAX_BN_SIZ; i++) {
        res[i] = bn1[i] + bn2[i];
    }
    for (int i = 0; i < MAX_BN_SIZ - 1; i++) {
        if (res[i] >= 10) {
            res[i] -= 10;
            res[i + 1] += 1;
        }
    }
}

void printBN(BN bn) {
    int i = MAX_BN_SIZ - 1;
    while (i && bn[i] == 0) i--; // Skip upper digits of zero
    for (; i >= 0; i--) {
        printf("%d", bn[i]);
    }
    printf("\n");
}

void uintToBN(unsigned int num, BN res) {
    int i = 0;
    while (num) {
        res[i++] = num % 10;
        num /= 10;
    }
}

void strToBN(const char* strNum, BN res) {
    int i = myStrlen(strNum);
    while (*strNum != '\0') {
        assert(*strNum >= '0' && *strNum <= '9');
        res[--i] = *strNum++ - '0';
    }
}

void zeroizeBN(BN bn) {
    for (int i = 0; i < MAX_BN_SIZ; i++) {
        bn[i] = 0;
    }
}

int main() {

    init();

    BN res = (BN) bnAlloc();
    BN bn1 = (BN) bnAlloc();
    BN bn2 = (BN) bnAlloc();
    BN bn3 = (BN) bnAlloc();
    BN bn4 = (BN) bnAlloc();

    const char* bn1Str= "231412345213456197691872364987213649872163419237649159673049";
    const char* bn2Str= "973950978127540297324907823409709823097349872349872300023423";
    unsigned int bn3Uint = 0xFFFFFFFF;
    unsigned int bn4Uint = 923784234;
    strToBN(bn1Str, bn1);
    strToBN(bn2Str, bn2);
    uintToBN(bn3Uint, bn3);
    uintToBN(bn4Uint, bn4);
    printf("===========================================================================\n");
    printf(" BN1 : "); printBN(bn1);
    printf(" BN2 : "); printBN(bn2);
    printf(" BN3 : "); printBN(bn3);
    printf(" BN4 : "); printBN(bn4);
    printf("===========================================================================\n");
    plusBN(bn1, bn2, res);
    printf(" BN1 + BN2 = "); printBN(res);
    zeroizeBN(res);
    plusBN(bn3, bn4, res);
    printf(" BN3 + BN4 = "); printBN(res);

    return 0;
}
