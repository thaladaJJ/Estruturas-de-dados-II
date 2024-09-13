#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
	unsigned V;
	unsigned A;
	int **adj;
} Graph;

void inicializar (Graph *g, unsigned nVertices) {
	g->V = nVertices;
	g->A = 0;
	g->adj = (int**) malloc (sizeof (int*) * g->V);

	for (unsigned v = 0; v < g->V; v++) {
		g->adj [v] = (int*) malloc (sizeof (int)*g->V);
	}

	for (unsigned i = 0; i < g->V; i++) {
		for (unsigned j = 0; j < g->V; j++) {
			g->adj [i][j] = 0;
		}
	}
}

void destroi (Graph *G) {
	
	for (unsigned v = 0; v < G->V; v++) {
		free (G->adj [v]);
	}
	
	free (G->adj);
	G->V = G->A = 0;
 }

 void add_aresta (Graph* G, unsigned v, unsigned w) {

	if (v >= G->V || w >= G->V) {
		printf ("ERRO: Vértices fora dos limites do grafo!\n");
		return;
	}

	if (G->adj [v][w] == 0) {
		G->adj [v][w] = 1;
		G->A++;
	}

	else
		printf ("Aresta (%u, %u) já existe!\n", v, w);
 }

 void dfs_private (Graph *G, int visitado [], unsigned v) {
	visitado [v] = 1;
	printf ("%u ", v);

	for (unsigned w = 0; w < G->V; w++) {
		if (G->adj [v][w] == 1 && visitado [w] == 0)
			dfs_private (G, visitado, w);
	}

 }

 void dfs (Graph *G) {

	int visitado [G->V];

	for (unsigned v = 0; v < G->V; v++) {
		visitado [v] = 0;
	}

	for (unsigned v = 0; v < G->V; v++) {
		if (visitado [v] == 0)
			dfs_private (G, visitado, v);
	}

	printf ("\n");
 }

int main () {

	unsigned v = 6;

	Graph grafo;
	inicializar (&grafo, v);

	for (int i = 0; i != -1; i++) {
		printf ("Nova aresta: ");
		
		unsigned x, w;
		scanf ("%u %u", &x, &w);

		if (x == 0 && w == 0) {
			i = -2;
			continue;
		}

		add_aresta (&grafo, x, w);
	}

 /* add_aresta (&grafo, 0, 2);
	add_aresta (&grafo, 0, 3);
	add_aresta (&grafo, 0, 5);
	add_aresta (&grafo, 1, 0);
	add_aresta (&grafo, 2, 1);
	add_aresta (&grafo, 2, 4);
	add_aresta (&grafo, 4, 1);
	add_aresta (&grafo, 4, 3);
	add_aresta (&grafo, 0, 10); saída esperada: 0 2 1 4 3 5
 */

	dfs (&grafo);

	destroi (&grafo);

	return 0;
}