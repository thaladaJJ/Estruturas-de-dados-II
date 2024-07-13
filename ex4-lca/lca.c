#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int rotulo;
    struct Node* parent;
} Node;

/*O Menor Ancestral Comum (LCA em inglês) de dois vétices A e B em uma árvore T é o menor nó de T (em profundidade)
que possui os nós A e B como seus descendentes. Define-se que o nó A é descendente dele próprio. 
                                                (então, caso A seja filho de B em T, B é o LCA de A e B)*/

int lca_search (int A_NODE, int B_NODE) { // imprima o Menor Ancestral Comum de A e B, A e B estão na mesma árvore.



}

int main () {
    
    int num_arvores, num_operations;
    scanf ("%d %d", &num_arvores, &num_operations);

    Node* Forest = malloc (sizeof (Node) * num_arvores);
    for (int i = 0; i < num_arvores; i++) {
        Forest[i].rotulo = i + 1;
        Forest[i].parent = NULL; 
    }

    char operation [5];

    for (int i = 0; i < num_operations; i++) {

        scanf ("%s", operation);

        if (strcmp (operation, "link") == 0) { // link A B -> A será filho de B na árvore de B

            int node_A, node_B;
            scanf ("%d %d", &node_A, &node_B);

            Forest [node_A - 1].parent = &Forest [node_B - 1];

        }

        else if (strcmp (operation, "lca") == 0) {

            int node_A, node_B;
            scanf ("%d %d", &node_A, &node_B);

            if (Forest [node_A - 1].parent == Forest [node_B - 1].parent)
                printf ("%d\n", node_A); 

        }

        else if (strcmp (operation, "cut") == 0) {



        }


    }

    free (Forest);
    
    return 0;
}