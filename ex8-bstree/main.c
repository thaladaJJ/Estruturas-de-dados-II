#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _bst {
    struct _bst* l;
    struct _bst* r;
    char* str;
} bst;

bst* get(bst* root, char* str) {
    // implementar iterativo! retornando NULL caso não encontre a str

    bst* aux = root;

    while (aux != NULL) {

        int cmp = strcmp (aux->str, str);

        if (cmp == 0)
            return aux;
        
        else if (cmp > 0)
            aux = aux->l;
        
        else
            aux = aux->r;

    }

    return NULL;
}

bst* put(bst* root, char* str) {
    if(root) {
        int cmp = strcmp(root->str, str);
        if(cmp > 0)
            root->l = put(root->l,str);
        else if (cmp < 0)
            root->r = put(root->r,str);
        return root;
    } else {
        bst* novo = (bst*)malloc(sizeof(bst));
        novo->str = (char*)malloc(sizeof(char)*(strlen(str)+1));
        strcpy(novo->str,str);
        novo->l = novo->r = NULL;
        return novo;
    }
}

bst* max(bst* root) {
    // implementar

    if (root == NULL)
        return NULL;

    bst* aux = root;

    while (aux->r != NULL) {
        aux = aux->r;
    }

    return aux;
}

bst* min(bst* root) {
    // implementar

    if (root == NULL)
        return NULL;

    bst* aux = root;

    while (aux->l != NULL) {
        aux = aux->l;
    }

    return aux;
}

bst* rem(bst* root, char* str) {
    // implementar recursivo, não esqueça de remover o espaço da string!

    if (root == NULL) {
        return NULL;
    }

    int cmp = strcmp (root->str, str);

    if (cmp > 0) {
        root->l = rem (root->l, str);
    } 
    
    else if (cmp < 0) {
        root->r = rem (root->r, str);
    } 
    
    else {
        
        if (root->l == NULL) {
            
            bst* temp = root->r;
            free (root->str);
            free (root);

            return temp;
        } 
        
        else if (root->r == NULL) {
            
            bst* temp = root->l;
            free (root->str);
            free (root);

            return temp;
        } 
        
        else {

            bst* temp = min (root->r);
            free (root->str);
            root->str = strdup (temp->str);
            root->r = rem (root->r, temp->str);
        }
    }

    return root;
}

void del(bst* root) {
    if(root) {
        del(root->l);
        del(root->r);
        free(root->str);
        free(root);
    }
}

int main() {

    char comando[2], palavra[255];

    bst* raiz = NULL;

    while(scanf("%s", comando) != EOF) {
        scanf("%s", palavra);
        if( comando[0] == 'P' ) 
            raiz = put(raiz,palavra);
        else if( comando[0] == 'R' ) 
            raiz = rem(raiz,palavra);
        else if( comando[0] == 'G' ) {
            bst* result = get(raiz,palavra);
            if( result )
                printf("%s encontrada\n", result->str);
            else
                printf("%s nao foi encontrada\n", palavra);
        }
    }

    del(raiz);

    return 0;
}