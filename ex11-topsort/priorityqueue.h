#ifndef PRIORITYQ_H
#define PRIORITYQ_H

typedef int T;

typedef struct Heap {
    T* data;
    int size;
	int maxSize;
} Heap;

void initHeap (Heap *heap, int maxSize);

void destroyHeap (Heap* Heap);

void heapifyUp (Heap* pq, int index);

void heapifyDown(Heap* pq, int index);

void enqueue (Heap* pq, int value);

int dequeue (Heap* pq);

T getMin (Heap *heap);

int empty (Heap* heap);

#endif