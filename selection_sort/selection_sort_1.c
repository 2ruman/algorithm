/*
 * Author: Truman (truman.t.kim@gmail.com)
 *
 * Basic implementation of selection sort
 */

#include <stdio.h>

#define MAX_NUM_CNT 100
int num[MAX_NUM_CNT];

void selectionSort(int data[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (data[j] < data[i]) {
                // Swap
                int temp = data[j];
                data[j] = data[i];
                data[i] = temp;
            }
        }
    }
}

void dump(int data[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main() {
    int T, N;

    freopen("sample_input.txt", "r", stdin);
    setbuf(stdout, NULL);

    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);

        for (int i = 0; i < N; i++) {
            scanf("%d", &num[i]);
        }
        selectionSort(num, N);
        printf("#%d ", tc);
        dump(num, N);
    }

    return 0;
}
