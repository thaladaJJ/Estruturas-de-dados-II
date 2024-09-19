#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

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

	Fila queue;
	initialize_queue (&queue);

	for (int i = 0; i < G->V; i++) {
		if (G->grau_de_entrada [i] == 0) {
			push (&queue, i);
		}
	}

	int count = 0;

	while (!empty (&queue)) {
		
		int v = pop (&queue);
		
		topological_order [count++] = v;

		for (GNode* current = G->adj [v]; current != NULL; current = current->next) {
			
			int w = current->vDestino;
			G->grau_de_entrada [w]--;

			if (G->grau_de_entrada [w] == 0) {
				push (&queue, w);
			}

		}
	}
	
	destroy_queue (&queue);

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