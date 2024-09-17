#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fila.h"

typedef struct Graph {
	int V;
	int A;
	int** adj;
} Graph;

typedef struct vertices_alcancados {
	int indice;
	int distancia;
} vertices;

vertices* vertices_alcancados;

void inicializa_grafo (Graph* G, int nV) {
	G->V = nV;
	G->A = 0;

	vertices_alcancados = (vertices*) malloc (sizeof (vertices) * G->V);

	G->adj = (int**) malloc (sizeof (int*) * G->V);

	for (int i = 0; i < G->V; i++) {
		
		G->adj [i] = (int*) malloc (sizeof (int) * G->V);
		
		vertices_alcancados [i].indice = -1;
		vertices_alcancados [i].distancia = 0;

		for (int j = 0; j < G->V; j++)
			G->adj [i][j] = 0;
	}
}

void destroi_grafo (Graph* G) {

	free (vertices_alcancados);

	for (int i = 0; i < G->V; i++) {
		free (G->adj [i]);
	}

	free (G->adj);

	G->V = G->A = 0;
}

void add_edge (Graph* G, int v, int w) {

	if (G->adj [v][w] == 0 && G->adj [w][v] == 0) {  // grafo não orientado, deve-se adicionar sempre as duas direções possíveis na aresta
		G->adj [v][w] = 1;
		G->adj [w][v] = 1;
		G->A++;
	}
}

void BFS (Graph* G, int vi) {

	int* vis = malloc (sizeof (int) * G->V);
	for (int v = 0; v < G->V; v++)
		vis [v] = 0;

	Fila fila;
	initialize (&fila);

	push (&fila, vi);
	vis [vi] = 1;

	int distance = 0;
	int position = 0;

	while (!empty (&fila)) {

		int size = fila.size;

		for (int i = 0; i < size; i++) {
			
			T v = front (&fila);
			pop (&fila);

			vertices_alcancados [position].indice = v + 1; // process (data)
			vertices_alcancados [position].distancia = distance;

			position++;

			for (int w = 0; w < G->V; w++) {
				
				if (G->adj [v][w] == 1 && vis [w] == 0) {
					vis [w] = 1;
					push (&fila, w);
				}
			}
		}

		distance++;
	}

	free (vis);
}

int main () {

	int v;
	scanf ("%d", &v);

	Graph grafo;
	inicializa_grafo (&grafo, v);

	bool end = false;
	int i, j;

	for (int k = 0; end != true; k++) {
		
		scanf ("%d,%d", &i, &j);

		if (i == 0 && j == 0) {
			end = true;
			continue;
		}

		add_edge (&grafo, i - 1, j - 1);
	}

	int vi;
	scanf ("%d", &vi);

	BFS (&grafo, vi - 1);

	printf ("Origem da busca: %d\n", vi);
	printf ("Vertices alcancados e distancias:\n");

	for (int k = 0; k < grafo.V; k++) {
		if (vertices_alcancados [k].indice != -1)
			printf ("%d %d\n", vertices_alcancados [k].indice, vertices_alcancados [k].distancia);
	}

	destroi_grafo (&grafo);

	return 0;
}