#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

lista_adjacencia* create_adj (int v, int peso) {
	lista_adjacencia* temp = (lista_adjacencia*) malloc (sizeof (lista_adjacencia));
	temp->vertice = v;
	temp->peso = peso;
	temp->prox = NULL;

	return temp;
}

bool createEdge (Graph* gr, int vi, int vf, int peso) {

	if (gr == NULL)
		return false;
	
	if ((vf < 0) || (vf >= gr->vertices))
		return false;
	
	if ((vi < 0) || (vf >= gr->vertices))
		return false;

}



int main () {

	


	return 0;
}