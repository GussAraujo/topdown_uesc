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
    node *LISTA = (node *) malloc(sizeof(node));
    inicia(LISTA);
    char ch;
    int info, qnt;

    while (scanf("%d", &qnt)) {
        if (qnt == 0) break;
        while (qnt) {
            scanf(" %c %d", &ch, &info);
            if (ch == 'P') {
            insereInicio(LISTA, info);
            }
            else if (ch == 'U') {
                insereFim(LISTA, info);
            }
            qnt--;
        }
    }
    return 0;
}
