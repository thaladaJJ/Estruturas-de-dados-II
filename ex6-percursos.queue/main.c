#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct node_ {
	int data;
	struct node_ *dir, *esq;
} node;

node* inserir( node* p, int dados ) {
    
	if (p == NULL) {
		p = malloc (sizeof (node));
		if (p == NULL) 
			return NULL;

		p->data = dados;
		p->dir = p->esq = NULL;
		return p;
	}

	if (dados < p->data)
		p->esq = inserir (p->esq, dados);
	
	else if (dados > p->data)
		p->dir = inserir (p->dir, dados);

	return p;
}

void destruir( node *p ) {
    // implementar
	if (p == NULL) 
		return;
	
	destruir (p->esq);
	destruir (p->dir);

	free (p);
}

void pos_order( node *p, void (*process)(int dado) ) { // esq - dir - raiz
    // implementar
	if (p != NULL) {
		pos_order (p->esq, process);
		pos_order (p->dir, process);
		process (p->data);
	}
}

void pre_order( node *p, void (*process)(int dado) ) { // raiz - esq - direita
    // implementar
	if (p != NULL) {
		process (p->data);
		pre_order (p->esq, process);
		pre_order (p->dir, process);
	}
}

void in_order( node *p, void (*process)(int dado) ) { // esq - raiz - dir
    // implementar
	if (p != NULL) {
		in_order (p->esq, process);
		process (p->data);
		in_order (p->dir, process);
	}
}

node* findNode (node* root, int dado) {

	if (root != NULL) {

		if (root->data > dado)
			return findNode (root->esq, dado);
		
		else if (root->data < dado)
			return findNode (root->dir, dado);
		
		else
			return root;
	}

	return NULL;
}

void in_level( node *p, void (*process)(int dado) ) {
	queue q;
    // implementar
	initialize (&q);

	push (&q, &p->data);

	node* aux = p;		

	while (!empty (&q)) {
		
		int* dado = (int*) front (&q);
		pop (&q);
		process (*dado);

		aux = findNode (p, *dado);

		if (aux->esq != NULL) {
			push (&q, &aux->esq->data);
		}

		if (aux->dir != NULL) {
			push (&q, &aux->dir->data);		
		}
		
	}

	destroy (&q);
}

void print(int dado) {
	printf(" %d", dado);
}

int main() {

	int n,a;
	scanf("%d", &n);
	
	node* raiz = 0;
	
	for(int i=0;i<n; i++) {
		scanf("%d", &a);
		raiz = inserir(raiz,a);
	}
	
	printf("Pr.:");
	pre_order(raiz, print);
	printf("\n");
	printf("In.:");
	in_order(raiz, print);
	printf("\n");
	printf("Po.:");
	pos_order(raiz, print);
	printf("\n");
	printf("Ni.:");
	in_level(raiz, print);
	printf("\n");
	
	destruir(raiz);
	
	return 0;
}