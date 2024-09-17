#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void initialize (Fila* q) {
	q->first = q->last = NULL;
	q->size = 0;
}

void destroy (Fila* q) {
	while (!empty (q))
		pop (q);
}

void push (Fila* q, T data) {
	
	Node* n = (Node*) malloc (sizeof (Node));
	if (n == NULL)
		return;
	
	n->data = data;
	n->prox = NULL;

	if (empty (q)) {
		q->first = q->last = n;
	}

	else {
		q->last->prox = n;
		q->last = n;
	}

	q->size++;
}

void pop (Fila *q) {

	if (empty (q))
		return;
	
	Node* aux = q->first;
	q->first = q->first->prox;

	if (q->first == NULL)
		q->last = NULL;

	q->size--;
	free (aux);
}

T front (Fila* q) {
	if (!empty (q))
		return q->first->data;
	
	return 0;
}

int empty (Fila *q) {
	return q->first == NULL;
}