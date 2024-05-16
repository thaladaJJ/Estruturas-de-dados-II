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

Node* createNode (int data, Node *parent) {

    Node *n = malloc (sizeof(Node));
    n->data = data;
    n->num_childs = 0;
    n->parent = parent;

    return n;
}

Node* findNode (Node* root, int data) {

    if (root == NULL)
        return NULL;

    if (root->data == data)
        return root;
    
    for (unsigned i = 0; i < root->num_childs; i++) {
        
        Node* found = findNode (root->childs[i], data);
        
        if (found != NULL)
            return found;
        
    }

    return NULL;
}

Node* insertNodeLink (Node* root, int a, int b) {

    if (root == NULL) {

        root = createNode (b, NULL);
        root->childs [root->num_childs] = createNode (a, root);
        root->num_childs++;

        return root;
    }

    Node* nodeB = findNode (root, b);

    if (nodeB != NULL) {
        nodeB->childs [nodeB->num_childs] = createNode(a, nodeB);
        nodeB->num_childs++;
    }

    return root;
}

Node* lca (Node* root, int a, int b) {
    
    Node* nodeA = findNode(root, a);
    Node* nodeB = findNode(root, b);

    if (nodeA == NULL || nodeB == NULL) 
        return NULL;

    int depthA = 0, depthB = 0;
    Node* tempA = nodeA;
    Node* tempB = nodeB;

    while (tempA->parent != NULL) {
        depthA++;
        tempA = tempA->parent;
    }

    while (tempB->parent != NULL) {
        depthB++;
        tempB = tempB->parent;
    }

    while (depthA > depthB) {
        nodeA = nodeA->parent;
        depthA--;
    }

    while (depthB > depthA) {
        nodeB = nodeB->parent;
        depthB--;
    }

    while (nodeA != nodeB) {
        nodeA = nodeA->parent;
        nodeB = nodeB->parent;
    }

    return nodeA;
}

void removeNode (Node* target) {
    
    if (target == NULL) 
        return;

    Node* parent = target->parent;

    if (parent != NULL) {
        
        for (unsigned i = 0; i < parent->num_childs; i++) {
           
            if (parent->childs[i] == target) {
                
                for (unsigned j = i; j < parent->num_childs - 1; j++)
                    parent->childs[j] = parent->childs[j + 1];
                
                parent->num_childs--;
                break;
            }

        }

    }

    free(target);
}

void destroyTree (Node* root) {

    if (root != NULL) {

        for (unsigned i = 0; i < root->num_childs; i++)
            destroyTree (root->childs[i]);

        free (root);
    }

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

            root = insertNodeLink (root, a_node, b_node);
        }
        
        else if (strcmp (operation, "cut") == 0 ) {
            
            int a_node;
            scanf ("%d", &a_node);

            Node *cutted_off = findNode (root, a_node);
            removeNode (cutted_off);
        }
        
        else if (strcmp (operation, "lca") == 0) {

            int a_node, b_node;
            scanf ("%d %d", &a_node, &b_node);

            if (a_node == b_node)
                printf ("%d\n", a_node);

            else {
                
                Node* ancestor = lca (root, a_node, b_node);
            
                if (ancestor != NULL)
                    printf("%d\n", ancestor->data);

            }

        }

    }

    destroyTree (root);

    return 0;
}