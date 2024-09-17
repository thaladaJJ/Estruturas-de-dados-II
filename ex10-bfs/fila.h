#ifndef fila_h
#define fila_h

typedef int T;

typedef struct Node {
	T data;
	struct Node* prox;
} Node;

typedef struct Fila {
	Node *first, *last;
	int size;
} Fila;

void initialize (Fila* q);

void destroy (Fila* q);

void push (Fila* q, T data);

void pop (Fila *q);

T front (Fila* q);

int empty (Fila *q);

#endif