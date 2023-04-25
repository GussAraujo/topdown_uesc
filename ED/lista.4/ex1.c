#include <stdio.h>
#include <stdlib.h>

typedef int obj_t;
typedef int boolean;

typedef struct pilha {
    obj_t item;
    struct pilha *prox;
} pilha;

pilha *empilhar(pilha *p, obj_t obj) {
    pilha *cel = malloc(sizeof(pilha));
    cel->prox = p;
    cel->item = obj;
    p = cel;
    return p;
}

pilha *desempilhar(pilha *p) {
    pilha *cel = p;
    if (p) {
        printf("---> desempilhando...\n\n");
        p = p->prox;
        free(cel);
    }
    return p;
}

obj_t topo(pilha *p) {
    obj_t val = 0;
    if(p) val = p->item;
    return val;
}

void mostrar(pilha *p) {
    pilha *cel = p;
    while (cel) {
        printf("| %d |\n", cel->item);
        cel = cel->prox;
    }
    printf("\n");
}

pilha *trocar(pilha *p) {
    pilha *cel = p->prox;
    if (p && p->prox) {
        printf("---> trocando...\n\n");
        p->prox = p->prox->prox; 
        cel->prox = p;
    }
    return cel;
}

int main() {
    pilha *p;
    p = NULL;

    p = empilhar(p, 5);
    p = empilhar(p, 4);
    p = empilhar(p, 3);
    p = empilhar(p, 2);
    p = empilhar(p, 1);
    
    mostrar(p);
    p = trocar(p);
    mostrar(p);
    p = desempilhar(p);
    mostrar(p);

    return 0;
}
