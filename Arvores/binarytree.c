#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct node {
    struct node *left, *right;
    struct node *parent;
    T data;
} node;

node* initialize () {
    return NULL;
}

node* insert (node* root, T key) {

    if (!root) {
        root = (node*) malloc (sizeof (node));
        root->left = NULL;
        root->right = NULL;
        root->data = key;
    } 

    else {
        
        if (key < root->data)
            root->left = insert (root->left, key);
        
        else
            root->right = insert (root->right, key);
    }

    return root;
}

void freeTree (node *root) {

    if (root == NULL)
        return;

    freeTree (root->left);
    freeTree (root->right);

    free(root);
}


void exibirEmOrdem(node *pRaiz) {

    if (pRaiz != NULL) {
        exibirEmOrdem(pRaiz->left);
        printf("%i ", pRaiz->data);
        exibirEmOrdem(pRaiz->right);
    }
}

int main () {

    node *raiz = initialize();
    
    raiz = insert (raiz, 1);
    raiz = insert (raiz, 2);
    raiz = insert (raiz, 5);

    exibirEmOrdem (raiz);

    freeTree (raiz);
   
    return 0;
}