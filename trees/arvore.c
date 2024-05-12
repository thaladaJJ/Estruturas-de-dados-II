#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node *left, *right;
} Node;

Node* initializeTree () {

    return NULL;
}

Node* createNode (int data) {

    Node* n = malloc (sizeof (Node));
    n->value = data;
    n->left = n->right = NULL;

    return n;
}

Node* insertNode (Node* root, int data) {

    if (root == NULL)
        return createNode (data);
    
    else {
        
        if (data < root->value)
            root->left = insertNode (root->left, data);

        else
            root->right = insertNode (root->right, data);
        
        return root;
    }
}

void destroyTree (Node* root) {

    if (root != NULL) {
        
        destroyTree (root->left);
        destroyTree (root->right);
        
        free (root);
    }

}

void inorder_traversal(Node* root) {
    
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->value);
        inorder_traversal(root->right);
    }

}

void preorder_traversal(Node* root) {
    
    if (root != NULL) {
        printf("%d ", root->value);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }

}

void postorder_traversal(Node* root) {
    
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->value);
    }

}

int main () {

    Node* root = initializeTree ();

    for (int i = 0; i < 5; i++) {

        int value = 0;

        printf ("Valor a inserir na arvore: ");
        scanf ("%d", &value);

        root = insertNode (root, value);
    }
    printf ("\n");

    printf ("Valor na raiz: %d\n", root->value);
    printf ("%p %p\n", root->left, root->right);
    printf("\n");

    printf("Percurso in-order: ");
    inorder_traversal (root);
    printf("\n");

    printf("Percurso pre-order: ");
    preorder_traversal (root);
    printf("\n");

    printf("Percurso post-order: ");
    postorder_traversal (root);
    printf("\n");

    destroyTree (root); 

    return 0;
}