// Gustavo Araujo - 202210689
// João Dutterle - 202211138
// Pedro Elias - 202210359

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int info;
    struct Node *prox;
};
typedef struct Node node;

void inicia(node *LISTA) {
    LISTA->prox = NULL;
}

void insereInicio(node *LISTA, int _info) {
    node *novo = (node *) malloc(sizeof(node));
    novo->info = _info;

    node *aux = LISTA->prox;
    LISTA->prox = novo;
    novo->prox = aux;
}

void insereFim(node *LISTA, int _info) {
    node *novo = (node *) malloc(sizeof(node));
    novo->info = _info;
    novo->prox = NULL;

    if(LISTA->prox == NULL)
        LISTA->prox=novo;
    else{
        node *tmp = LISTA->prox;

        while(tmp->prox != NULL){
            tmp = tmp->prox;
        }
        tmp->prox = novo;
    }
}

void exibe(node *LISTA) {
    if(LISTA->prox == NULL){
        printf("Lista vazia!\n\n");
        return;
    }

    node *tmp;
    tmp = LISTA->prox;

    while(tmp != NULL){
        printf("%d ", tmp->info);
        tmp = tmp->prox;
    }

    printf("\n");
}

void libera(node *LISTA) {
    if(LISTA->prox == NULL){
        node *proxNode, *atual;

        atual = LISTA->prox;
        while(atual != NULL){
            proxNode = atual->prox;
            free(atual);
            atual = proxNode;
        }
    }
}

int main() {
    char p;
    int info, qnt;

    while (scanf("%d", &qnt)) {
        node *LISTA = (node *) malloc(sizeof(node));
        inicia(LISTA);
        if (qnt == 0) break;
        while (qnt) {
            scanf(" %c %d", &p, &info);
            if (p == 'P') {
                insereInicio(LISTA, info);
            }
            else if (p == 'U') {
                insereFim(LISTA, info);
            }
            qnt--;
        }
        exibe(LISTA);
    }
    return 0;
}
