#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue.h"

typedef struct GNode {
	int vDestino;
	struct GNode* next;
} GNode;

typedef struct Graph {
	int A;
	int V;
	int* grau_de_entrada;
	GNode** adj;
} Graph;

void initialize (Graph* G, int v) {
	
	G->V = v;
	G->A = 0;
	
	G->grau_de_entrada = (int*) malloc (sizeof (int) * G->V);
	G->adj = (GNode**) malloc (sizeof (GNode*) * G->V);

	for (int i = 0; i < G->V; i++) {
		G->grau_de_entrada [i] = 0;
		G->adj [i] = NULL;
	}
}

void destroy (Graph* G) {

	for (int i = 0; i < G->V; i++) {
		
		GNode* current = G->adj [i];

		while (current != NULL) {
			GNode* aux = current;
			current = current->next;
			free (aux);
		}

	}
	
	free (G->grau_de_entrada);
	free (G->adj);

	G->V = G->A = 0;
	G->adj = NULL; 
	G->grau_de_entrada = NULL;	
}

void add_edge (Graph* G, int v, int w) {

	if (v >= G->V || w >= G->V) {
		printf ("ERRO: Vértices fora dos limites do grafo!\n");
		return;
	}

	GNode* n = (GNode*) malloc (sizeof (GNode));
	
	n->vDestino = w;
	n->next = G->adj [v];
	G->adj[v] = n;

	G->A++;
	G->grau_de_entrada [w]++;
}

int topological_sort (Graph* G, int* topological_order) {
	// 3 1 2 0 -> vertices de 0 a 2, aresta 2-0
	Heap queue;
	initHeap (&queue, G->V);

	for (int i = 0; i < G->V; i++) {
		if (G->grau_de_entrada [i] == 0) {
			enqueue (&queue, i); // fila: 1 2
		}
	}

	int count = 0;

	while (!empty (&queue)) {

		int v = dequeue (&queue);	// v = 1, fila: 2 | v = 2, fila: {}  | v = 0, fila: {}
		
		topological_order [count++] = v; // {1}; | {1, 2}; | {1, 2, 0}

		for (GNode* current = G->adj [v]; current != NULL; current = current->next) { // adjacentes de 1: nulo | adjacentes de 2: 0 | adj 0: null
			
			int w = current->vDestino;	// w = 0
			G->grau_de_entrada [w]--; // degree (0)--; degree (0) == 0

			if (G->grau_de_entrada [w] == 0) {	// degree (0) == 0, entra na condição
				enqueue (&queue, w); // w = 0, fila: {0}
			}

		}
	}
	
	destroyHeap(&queue);

	if (count != G->V) { // grafo ciclico, ordenação topológica não foi possível
		return 0;
	}

	return 1;
}


int main () {

	int num_tarefas, num_dependencias;
	scanf ("%d %d", &num_tarefas, &num_dependencias);

	Graph grafo;
	initialize (&grafo, num_tarefas);

	for (int i = 0; i < num_dependencias; i++) {
		int A, B;
		scanf ("%d %d", &A, &B);

		add_edge (&grafo, A, B); // tarefa B depende da tarefa A
	}

	// Ordenação topológica - algoritmo de Kahn
	int* topological_order = (int*) malloc (sizeof (int) * grafo.V);

	if (topological_sort (&grafo, topological_order)) {
		for (int i = 0; i < grafo.V; i++)
			printf ("%d\n", topological_order [i]);
	} 

	else 
		printf ("*\n");

	free (topological_order);

	destroy (&grafo);

	return 0;
}