/*
 * Author: Truman (truman.t.kim@gmail.com)
 *
 * Example for basic heap-sort implementation (a.k.a priority queue, pq)
 */

#include <stdio.h>

#define MAX_HEAP_SIZ 100

int heap[MAX_HEAP_SIZ];
int heapCnt;

void heapInit() {
    heapCnt = 0;
}

void heapPush(int data) {

    heap[++heapCnt] = data;

    int child = heapCnt;
    int parent = child / 2;
    int temp;

    while (parent && heap[parent] < heap[child]) {
        temp = heap[parent];
        heap[parent] = heap[child];
        heap[child] = temp;

        child = parent;
        parent = child /2;
    }
}

int heapPop() {
    int retVal = heap[1];
    heap[1] = heap[heapCnt--];
    // You can empty the leaf node but it's not necessary,
    // since the heap sufficiently can be managed only by heap count.

    int parent = 1;
    int child = parent * 2;
    int temp;

    if (child + 1 <= heapCnt && heap[child] < heap[child + 1]) {
        child = child + 1;
    }

    while (child <= heapCnt && heap[parent] < heap[child]) {
        temp = heap[parent];
        heap[parent] = heap[child];
        heap[child] = temp;

        parent = child;
        child = parent * 2;
        if (child + 1 <= heapCnt && heap[child] < heap[child + 1]) {
            child = child + 1;
        }
    }
    return retVal;
}

int main() {
    int T, N;

    freopen("sample_input.txt", "r", stdin);
    setbuf(stdout, NULL);

    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);
        heapInit();

        for (int i = 0, data; i < N; i++) {
            scanf("%d", &data);
            heapPush(data);
        }

        printf("#%d", tc);
        for (int i = 0; i < N; i++) {
            printf(" %d", heapPop());
        }
        printf("\n");
    }

    return 0;
}
