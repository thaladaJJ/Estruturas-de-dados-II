#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue.h"

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void initHeap (Heap *heap, int maxSize) {
	heap->data = (T*) malloc (sizeof (T) * maxSize);
	heap->maxSize = maxSize;
    heap->size = 0;
}

void destroyHeap (Heap* heap) {
	
	if (heap != NULL)
		free (heap->data);
	
	heap->size = 0;
}

// "Sobe" o elemento recém-inserido para manter a propriedade do heap
void heapifyUp (Heap* pq, int index) {
    
    if (index && pq->data [(index - 1) / 2] > pq->data [index]) {
        swap(&pq->data [(index - 1) / 2], &pq->data [index]);
        heapifyUp(pq, (index - 1) / 2);
    }
}

void enqueue (Heap* pq, int value) {
    if (pq->size == pq->maxSize) {
        printf("Fila de prioridade cheia!\n");
        return;
    }

    pq->data[pq->size++] = value;
    heapifyUp(pq, pq->size - 1);
}

// "desce" o elemento após a remoção para manter a propriedade do heap
void heapifyDown(Heap* pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->data[left] < pq->data[smallest])
        smallest = left;

    if (right < pq->size && pq->data[right] < pq->data[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&pq->data[index], &pq->data[smallest]);
        heapifyDown(pq, smallest);
    }
}

int dequeue (Heap* pq) {
    
    if (pq->size == 0) {
        printf("Fila vazia.\n");
        return -1;
    }

    int item = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    heapifyDown(pq, 0);
    return item;
}


T getMin (Heap *heap) {

    if (heap->size == 0) {
        printf("Heap está vazio!\n");
        return -1;
    }

    return heap->data[0];
}

int empty (Heap* heap) {
	return heap->size == 0;
}