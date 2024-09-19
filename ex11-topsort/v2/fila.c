#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void initialize_queue (Fila* q) {
	q->first = q->last = NULL;
	q->size = 0;
}

void destroy_queue (Fila* q) {
	while (!empty (q))
		pop (q);
}

void push (Fila* queue, int data) {

    Node* newNode = (Node*) malloc (sizeof(Node));
    newNode->data = data;
    newNode->prox = NULL;

    // Se a fila estiver vazia ou o novo vértice tem menor valor que o primeiro elemento
    if (queue->first == NULL || data < queue->first->data) {
        newNode->prox = queue->first;
        queue->first = newNode;
    } else {
        Node* current = queue->first;
        
        // Encontra a posição correta para inserir o novo nó (ordem crescente)
        while (current->prox != NULL && current->prox->data < data) {
            current = current->prox;
        }
        
        newNode->prox = current->prox;
        current->prox = newNode;
    }
}

T pop (Fila *q) {

	if (empty (q))
		return -1;

	
	Node* aux = q->first;
	int front = aux->data;
	q->first = q->first->prox;

	if (q->first == NULL)
		q->last = NULL;

	q->size--;
	free (aux);

	return front;
}

T front (Fila* q) {
	if (!empty (q))
		return q->first->data;
	
	return 0;
}

int empty (Fila *q) {
	return q->first == NULL;
}