#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node *left, *right;
    char rotulo;
} Node;

Node* initializeTree (char rotulo) {
    Node* root = malloc (sizeof (Node));
    if (root == NULL)
        return NULL;

    root->rotulo = rotulo;
    root->left = root->right = NULL;

    return root;
}

void traversal_pos_order (Node* root) {
    if (root != NULL) {
        traversal_pos_order (root->left);
        traversal_pos_order (root->right);
        printf ("%c", root->rotulo);
    }
}

void destroyTree (Node *root) {

    if (root != NULL) {
        destroyTree (root->left);
        destroyTree (root->right);
        free (root);
    }

}

int findPosition (char* inOrder, char rotulo, int start, int end) {
    
    for (int i = start; i <= end; i++) {
        if (inOrder[i] == rotulo)
            return i;
    }

    return -1;
}

Node* buildTree (char* preOrder, char* inOrder, int inOrderStart, int inOrderEnd, int* preOrderIndex) {
    
    if (inOrderStart > inOrderEnd)
        return NULL;

    Node* root = initializeTree (preOrder [*preOrderIndex]);
    (*preOrderIndex)++;

    if (inOrderStart == inOrderEnd)
        return root;

    int inOrderIndex = findPosition (inOrder, root->rotulo, inOrderStart, inOrderEnd);

    root->left = buildTree(preOrder, inOrder, inOrderStart, inOrderIndex - 1, preOrderIndex);
    root->right = buildTree(preOrder, inOrder, inOrderIndex + 1, inOrderEnd, preOrderIndex);

    return root;
}

int main () {

    int num_casos;
    scanf ("%d", &num_casos);

    // pre ordem -> raiz-sub arvore esquerda-sub arvore direita
    // in ordem ->  sub arvore esquerda-raiz-sub arvore direita
    // pos ordem -> sub arvore esquerda-sub arvore direita-raiz

    for (int i = 0; i < num_casos; i++) {
        
        int num_nodes;
        char preOrder_string [53];
        char inOrder_string [53];
        scanf ("%d %s %s", &num_nodes, preOrder_string, inOrder_string);

        int preOrderIndex = 0;
        Node* root = buildTree (preOrder_string, inOrder_string, 0, num_nodes - 1, &preOrderIndex);

        traversal_pos_order (root);
        printf ("\n");
        destroyTree (root);
    }


    return 0;
}