#include <stdio.h>
#include <stdlib.h>

typedef struct adjacencia {
	int vertice; // vertice destino (final)
	int peso;    // peso associado a aresta que leva ao vértice de destino
	struct adjacencia* prox;
} lista_adjacencia;

typedef struct vertice {
	lista_adjacencia* head;
} Vertice;

typedef struct graph {
	int vertices;
	int arestas;
	Vertice* adj;	// um ponteiro para o arranjo de vértices
} Graph;

Graph* createGraph (int v) {
	Graph* g = (Graph*) malloc (sizeof (Graph));
	g->vertices = v;
	g->arestas = 0;
	g->adj = (Vertice*) malloc (v* sizeof(Vertice));	// aloco os v vértices do arranjo

	for (int i = 0;	i < v; i++)
		g->adj[i].head = NULL;

	return g;
}

int main () {


	printf ("Hello, Graphs!\n");	

	return 0;
}