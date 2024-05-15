#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 1000

typedef int T;

typedef struct Node {
    T data;
    unsigned num_childs;
    struct Node* childs [MAX];
    struct Node* parent;
} Node;

Node* insertNodeLink (Node* root, int a, int b) {

    


}

int main () {

    int num_arvores, num_operations;
    scanf ("%d %d", &num_arvores, &num_operations);
    
    Node *root = NULL;

    char operation [5];

    for (int i = 0; i < num_operations; i++) {

        scanf ("%s", operation);

        if (strcmp (operation, "link") == 0 ) {

            int a_node, b_node;
            scanf ("%d %d", &a_node, &b_node);

        
        }
        
        else if (strcmp (operation, "cut") == 0 ) {
            
            int a_node;
            scanf ("%d", &a_node);

        }
        
        else if (strcmp (operation, "lca") == 0) {

            int a_node, b_node;
            scanf ("%d %d", &a_node, &b_node);


        }


    }


    return 0;
}