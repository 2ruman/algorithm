/*
 * Author: Truman (truman.t.kim@gmail.com)
 *
 * Example for handling duplicated data(priority in this source)
 */

#include <stdio.h>

#define MAX_DATA_CNT 100
#define MAX_HEAP_SIZ (MAX_DATA_CNT + 1)

typedef struct _DATA {
    int id;
    int priority;
} DATA;
DATA data[MAX_DATA_CNT];
int dataCnt;

void initData() {
    dataCnt = 0;
}

// Return index of original data
int allocData(int id, int priority) {
    data[dataCnt].id = id;
    data[dataCnt].priority = priority;
    return dataCnt++;
}

int heap[MAX_HEAP_SIZ];
int heapCnt;

void heapInit() {
    heapCnt = 0;
}

int compare(int parent, int child) {
    int pDataIdx = heap[parent];
    int cDataIdx = heap[child];
    // In case that parent and child have the same priority,
    // will compare the unique value such as id.
    if (data[pDataIdx].priority < data[cDataIdx].priority
            || (data[pDataIdx].priority == data[cDataIdx].priority
                    && data[pDataIdx].id < data[cDataIdx].id)) {
        return 1; // True
    } else {
        return 0; // False
    }
}

void heapPush(int dataIdx) {

    heap[++heapCnt] = dataIdx;

    int child = heapCnt;
    int parent = child / 2;
    int temp;

    while (parent && compare(parent, child)) {
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

    if (child + 1 <= heapCnt && compare(child, child + 1)) {
        child = child + 1;
    }

    while (child <= heapCnt && compare(parent, child)) {
        temp = heap[parent];
        heap[parent] = heap[child];
        heap[child] = temp;

        parent = child;
        child = parent * 2;
        if (child + 1 <= compare(child, child + 1)) {
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
        initData();
        heapInit();

        int id, priority, dataIdx;
        for (int i = 0; i < N; i++) {
            id = i + 1;
            scanf("%d", &priority);
            dataIdx = allocData(id, priority);
            heapPush(dataIdx);
        }

        printf("#%d", tc);
        for (int i = 0; i < N; i++) {
            dataIdx = heapPop();
            id = data[dataIdx].id;
            priority = data[dataIdx].priority;

            printf(" %d(%d)", priority, id);
        }
        printf("\n");
    }

    return 0;
}
