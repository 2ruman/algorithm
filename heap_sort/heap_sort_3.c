/*
 * Author: Truman (truman.t.kim@gmail.com)
 *
 * Example for handling multi-heap
 */

#include <stdio.h>

#define DEFAULT_DATA  (-1)
#define MAX_HEAP_SIZ (100)

int minHeapCnt;
int maxHeapCnt;
int minHeap[MAX_HEAP_SIZ];
int maxHeap[MAX_HEAP_SIZ];

int minHeapCmp(int pData, int cData) {
    if (pData > cData) {
        return 1;
    }
    return 0;
}

int maxHeapCmp(int pData, int cData) {
    if (pData < cData) {
        return 1;
    }
    return 0;
}

void heapInit(int *pHeapCnt) {
    *pHeapCnt = 0;
}

int heapPeek(int heap[], int heapCnt) {
    return (heapCnt < 1) ? DEFAULT_DATA : heap[1];
}

void heapPush(int heap[], int *pHeapCnt, int data, int (*compare)(int, int)) {

    int heapCnt = ++(*pHeapCnt);
    int child = heapCnt;
    int parent = child / 2;
    int temp;

    heap[child] = data;

    while (parent && compare(heap[parent], heap[child])) {
        temp = heap[parent];
        heap[parent] = heap[child];
        heap[child] = temp;

        child = parent;
        parent = child /2;
    }
}

int heapPop(int heap[], int *pHeapCnt, int (*compare)(int, int)) {

    int retVal = heap[1];
    heap[1] = heap[(*pHeapCnt)];
    int heapCnt = --(*pHeapCnt);

    int parent = 1;
    int child = parent * 2;
    int temp;
    if (child + 1 <= heapCnt && compare(heap[child], heap[child + 1])) {
        child = child + 1;
    }

    while (child <= heapCnt && compare(heap[parent], heap[child])) {
        temp = heap[parent];
        heap[parent] = heap[child];
        heap[child] = temp;

        parent = child;
        child = parent * 2;
        if (child + 1 <= heapCnt && compare(heap[child], heap[child + 1])) {
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
        heapInit(&minHeapCnt);
        heapInit(&maxHeapCnt);

        for (int i = 0, data; i < N; i++) {
            scanf("%d", &data);
            heapPush(minHeap, &minHeapCnt, data, minHeapCmp);
            heapPush(maxHeap, &maxHeapCnt, data, maxHeapCmp);
        }

        printf("#%d", tc);
        printf(" (Peek : %d)", heapPeek(minHeap, minHeapCnt));
        for (int i = 0; i < N; i++) {
            printf(" %d", heapPop(minHeap, &minHeapCnt, minHeapCmp));

        }
        printf("\n");

        printf("#%d", tc);
        printf(" (Peek : %d)", heapPeek(maxHeap, maxHeapCnt));
        for (int i = 0; i < N; i++) {
            printf(" %d", heapPop(maxHeap, &maxHeapCnt, maxHeapCmp));
        }
        printf("\n");
    }

    return 0;
}
