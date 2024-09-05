#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char byte;

typedef struct Arvore {
    int frequencia;
    byte c;
    struct Arvore *esq, *dir, *prox;
} Arvore;

typedef struct Lista {
    Arvore *inicio;
    int elementos;
} Lista;

void insereLista (Lista *l, Arvore *n);
Lista *iniciaLista (Lista *l);
void constroiLista (int tabela[], Lista *l);
int listaVazia (Lista *l);

Arvore *pop (Lista *l);
Arvore *criaArvore (Lista *l);
void calculaBits (Arvore *a, int bits, int *s);
void tabelaFrequencias (char frase[], int tabela[]);

int main () {

    byte *frase;
    int *tabela;
    tabela = calloc(256, sizeof(int));
    frase = calloc(500000, sizeof(char));

    Lista l;
    Arvore *a;

    tabelaFrequencias(frase, tabela);

    iniciaLista(&l);
    constroiLista(tabela, &l);

    a = criaArvore(&l);

    int s = 0;
    calculaBits(a, 0, &s);
    printf("%d\n", s);

    free(tabela);
    free(frase);

    return 0;
}

void tabelaFrequencias(char frase[], int tabela[]) {
    int i = 0;
    
    while (scanf("%c", &frase[i]) != EOF) {
        tabela[(int)frase[i]]++;
        i++;
    }
}

Lista *iniciaLista(Lista *l) {
    l->inicio = NULL;
    l->elementos = 0;
    return l;
}

int listaVazia(Lista *l) {
    return l->elementos == 0;
}

void insereLista(Lista *l, Arvore *n) {
    Arvore *aux;

    if (!l->inicio) {
        l->inicio = n;
    } 
    
    else if (n->frequencia < l->inicio->frequencia) {
        n->prox = l->inicio;
        l->inicio = n;
    } 
    
    else {
        
        aux = l->inicio;
        
        while (aux->prox && aux->prox->frequencia <= n->frequencia) {
            aux = aux->prox;
        }

        n->prox = aux->prox;
        aux->prox = n;
    }

    l->elementos++;
}

void constroiLista(int tabela[], Lista *l) {

    for (int i = 0; i < 256; i++) {

        if (tabela[i] != 0) {
            Arvore *novo = (Arvore *)malloc(sizeof(Arvore));

            novo->c = i;
            novo->frequencia = tabela[i];

            novo->esq = novo->dir = novo->prox = NULL;
            insereLista(l, novo);
        }
    }
}

Arvore *pop(Lista *l) {
    
    if (listaVazia(l)) {
        return NULL;
    } 
    
    else {
        Arvore *aux = l->inicio;
        l->inicio = aux->prox;
        aux->prox = NULL;
        l->elementos--;
        return aux;
    }
}

Arvore *criaArvore(Lista *l) {
    Arvore *aux1, *aux2;
    
    while (l->elementos > 1) {
        aux1 = pop(l);
        aux2 = pop(l);

        Arvore *novo = (Arvore *)malloc(sizeof(Arvore));

        novo->frequencia = aux1->frequencia + aux2->frequencia;
        novo->esq = aux1;
        novo->dir = aux2;
        novo->prox = NULL;

        insereLista(l, novo);
    }

    return l->inicio;
}

void calculaBits(Arvore *a, int bits, int *s) {
    
    if (!a->esq && !a->dir) {
        *s += (bits * a->frequencia);
    } 
    
    else {
        calculaBits(a->esq, bits + 1, s);
        calculaBits(a->dir, bits + 1, s);
    }
}