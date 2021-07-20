/*
 * Author: Truman (truman.t.kim@gmail.com)
 *
 * Example for basic diction implementation using TRIE
 */

#include <stdio.h>

#define CHAR_NUM 10   // Maximum length of a word
#define WORD_NUM 1000 // Arbitrary number of words that can be given
#define ALPH_NUM 26   // 'a' ~ 'z' (only lower case)

#define MAX_TRIE_SIZ (CHAR_NUM * WORD_NUM)
#define DEFAULT_VAL (0)

int trie[MAX_TRIE_SIZ][ALPH_NUM];
int trieCnt;
int trieData[MAX_TRIE_SIZ];
int trieDataCnt;

void initTire() {
    for (int i = 0 ; i < MAX_TRIE_SIZ ; i++) {
    // for (int i = 0 ; i < trieCnt ; i++) { for repeated TC
        trieData[i] = DEFAULT_VAL;
        for (int j = 0 ; j < ALPH_NUM ; j++) {
            trie[i][j] = 0;
        }
    }
}

void addTrie(const char *str, int data) {

    int currT = 0;
    while (*str != '\0') {
        if (!trie[currT][*str - 'a']) {
            trie[currT][*str - 'a'] = ++trieCnt;
        }
        currT = trie[currT][*str - 'a'];
        str++;
    }
    trieData[currT] = data;
    ++trieDataCnt;

    // This line below can be used for assigning ID for each record(string)
    // trieData[currT] = ++trieDataCnt;
}

int findTrie(const char *str) {

    int retVal = DEFAULT_VAL;
    int currT = 0;
    while (*str != '\0') {
        if (!trie[currT][*str - 'a']) {
            break;
        }
        currT = trie[currT][*str - 'a'];
        str++;
    }
    retVal = trieData[currT];
    return retVal;
}

void delTrie(const char *str) {

    int currT = 0;
    while (*str != '\0') {
        if (!trie[currT][*str - 'a']) {
            return;
        }
        currT = trie[currT][*str - 'a'];
        str++;
    }
    trieData[currT] = DEFAULT_VAL;
    --trieDataCnt;
}

int main() {
    char buff[CHAR_NUM + 1];
    int N;

    freopen("sample_input.txt", "r", stdin);
    setbuf(stdout, NULL);

    initTire();

    printf("-------- Add to Diction! ---------\n");
    scanf("%d", &N);
    for (int i = 1 ; i <= N ; i++) {
        scanf("%s", buff);
        addTrie(buff, 1);
        printf("(%2d) + %s\n", i, buff);
    }

    printf("------ Delete from Diction! ------\n");
    scanf("%d", &N);
    for (int i = 1 ; i <= N ; i++) {
        scanf("%s", buff);
        delTrie(buff);
        printf("(%2d) - %s\n", i, buff);
    }

    printf("-------- Search Diction! ---------\n");
    scanf("%d", &N);
    for (int i = 0 ; i < N ; i++) {
        scanf("%s", buff);
        if (findTrie(buff) == DEFAULT_VAL) {
            printf("(%2d) : %-10s (-)\n", (i+1), buff);
        } else {
            printf("(%2d) : %-10s FOUND\n", (i+1), buff);
        }
    }
    printf("----------------------------------\n");
    printf("Number of Records in Diction : %d\n", trieDataCnt);
    return 0;
}
