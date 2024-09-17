#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct timestamp {
    int vertice;
    int tempo_descoberta;
    int tempo_finalizacao;
} timestamp;

timestamp* timestamps;
int* visitado;
int* tempo;
bool aciclico = true;

typedef struct Node {
    int vDestino;
    struct Node* next;
} Node;

typedef struct Graph {
    int V;
    int A;
    Node** adj;
} Graph;

void inicializar(Graph* G, int v) {
    G->V = v;
    G->A = 0;

    timestamps = (timestamp*) malloc (sizeof(timestamp) * v);
    visitado = (int*) malloc (sizeof(int) * v);
    tempo = malloc (sizeof(int));

    *tempo = 0;

    G->adj = (Node**)malloc(sizeof(Node*) * G->V);
    for (int i = 0; i < G->V; i++) {
        G->adj[i] = NULL;
        visitado[i] = 0;
        timestamps[i].tempo_descoberta = 0;
        timestamps[i].tempo_finalizacao = 0;
        timestamps[i].vertice = i; 
    }
}

void destruir(Graph* G) {
    for (int i = 0; i < G->V; i++) {
        while (G->adj[i] != NULL) {
            Node* aux = G->adj[i];
            G->adj[i] = G->adj[i]->next;
            free(aux);
        }
    }

    free(G->adj);
    G->V = G->A = 0;

    free(timestamps);
    free(visitado);
    free(tempo);
}

void add_arco(Graph* G, int v, int w) {
    Node* new = (Node*) malloc (sizeof(Node));
    new->vDestino = w;
    new->next = G->adj[v];
    G->adj[v] = new;
    G->A++;
}

void DFS(Graph* G, int u) {

    visitado[u] = 1;
    (*tempo)++; 
    timestamps[u].tempo_descoberta = *tempo;

    for (Node* p = G->adj[u]; p != NULL; p = p->next) {
        int v = p->vDestino;

        if (visitado[v] == 0) {
            DFS(G, v);
        } else if (visitado[v] == 1) {
            aciclico = false;
        }
    }

    visitado[u] = 2;
    (*tempo)++;
    timestamps[u].tempo_finalizacao = *tempo;
}

void sort_timestamps (timestamp arr[], int n) {
    
	for (int i = 1; i < n; i++) {
        timestamp key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].tempo_descoberta > key.tempo_descoberta) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

int main() {

    Graph grafo;

    int v;
    scanf("%d", &v);

    inicializar (&grafo, v);

    bool fimArestas = false;

    for (int i = 0; !fimArestas; i++) {
        int x, w;
        scanf("%d,%d", &x, &w);

        if (x == 0 && w == 0) {
            fimArestas = true;
            continue;
        }

        add_arco(&grafo, x - 1, w - 1);
    }

    for (int j = 0; j < v; j++) {
        if (visitado[j] == 0) {
            DFS(&grafo, j);
        }
    }

    sort_timestamps(timestamps, v);

    for (int i = 0; i < v; i++) {
        if (timestamps[i].tempo_descoberta > 0) { 
            printf("%d [%d,%d]\n", timestamps[i].vertice + 1, timestamps[i].tempo_descoberta, timestamps[i].tempo_finalizacao);
        }
    }

    if (aciclico)
        printf("aciclico: sim\n");
    else
        printf("aciclico: nao\n");

    destruir(&grafo);

    return 0;
}