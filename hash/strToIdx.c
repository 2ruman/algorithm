/*
 * Author: Truman (truman.t.kim@gmail.com)
 *
 * Hash table implementation optimal for strings that are composed of
 * lower-case alphabet with the maximum length of 12-byte.
 */

#include <stdio.h>

#define MAX_LEN (12 + 1)

#define MOD 23 // Prime number enough to accommodate whole data(the number of sample data is 20)
#define DEFAULT_DATA (0)

int mSeqNum;
void init() {
    mSeqNum++;
}

// Hash table that contains data
// The sequence number is to avoid unnecessary table-reset
typedef struct _HTBL {
    unsigned long long hVal;
    int seqNum;
    int data;
} HTBL;
HTBL mHashTable[MOD];

#define CAL_HASH_KEY(hVal) ((hVal) % MOD)

unsigned int calHashKey(unsigned long long hVal, int mod) {
    return (unsigned int)(hVal % mod);
}

unsigned long long hash(const char *str) {
    unsigned long long hVal = 0;
    while (*str != '\0') {
        hVal = (hVal << 5) + (*str++ - 'a' + 1);
#if 0
        hVal = (hVal * 29) + (*str++ - 'a' + 1); // 29 is prime number to reduce hash collision
#endif
    }
    return hVal;
}

void initRow(unsigned int hKey, unsigned long long hVal) {
    mHashTable[hKey].hVal = hVal;
    mHashTable[hKey].seqNum = mSeqNum;
    mHashTable[hKey].data = DEFAULT_DATA;
}

void updateRow(unsigned int hKey, int data) {
    mHashTable[hKey].data = data;
}

int getRowData(unsigned int hKey) {
    return mHashTable[hKey].data;
}

unsigned int strToIdx(const char *str) {
    unsigned long long hVal = hash(str);
    unsigned int hKey = CAL_HASH_KEY(hVal); // int hKey = calHashKey(hVal, MOD);

    for (int i = 1 ; i < MOD ; i++) {
        // Not used at this sequence, so newly available!
        if (mHashTable[hKey].seqNum != mSeqNum) {
            initRow(hKey, hVal);
            break;
        }
        // Hit!
        else if (mHashTable[hKey].hVal == hVal) {
            break;
        }
        // Avoid collision...
        else {
            hKey = (hKey + 1) % MOD;
        }
    }
    return hKey;
}

int main() {
    int T, N;
    char str[MAX_LEN];

    freopen("sample_input.txt", "r", stdin);
    setbuf(stdout, NULL);

    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {

        scanf("%d", &N);
        init();

        for (int i = 0, data, idx; i < N; i++) {
            scanf("%s", str);
            scanf("%d", &data);
            idx = strToIdx(str);
            updateRow(idx, data);
        }

        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%s", str);
            printf("#%d - %s(%d)\n", tc, str, getRowData(strToIdx(str)));
        }
        printf("\n");
    }
    return 0;
}
