#include <stdlib.h>
#include "queue.h"

void initialize(queue *q) {
    // implementar
    q->first = q->last = NULL;
}

void destroy(queue *q) {
    while(!empty(q))
        pop(q);
}

void* front(queue *q) {
    if(!empty(q))
        return q->first->data;
    return 0;
}

void push(queue *q, void* data) {
    // implementar

    qnode* new_node = (qnode*) malloc (sizeof (qnode));
    if (new_node == NULL) 
        return;

    new_node->data = (int*) data;
    new_node->next = NULL;

    if (empty (q)) {
        q->first = q->last = new_node;
    } else {
        q->last->next = new_node;
        q->last = new_node;
    }
}

void pop(queue *q) {
    // implementar

    if (empty (q))
        return;
    
    qnode* temp = q->first;
    q->first = q->first->next;

    if (q->first == NULL) {
        q->last = NULL;
    }
    
    free (temp);
}

int empty(queue *q) {
    return q->first == 0;
}