// Gustavo Araujo - 202210689
// João Dutterle - 202211138
// Pedro Elias - 202210359

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int valor;
  struct no *prox;
} No;

typedef struct {
  No *inicio;
  No *fim;
  int tam;
} Lista;

void criar_lista(Lista *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tam = 0;
}

void inserir_no_inicio(Lista *lista, int num) {
  No *novo = (No*) malloc(sizeof(No));

  novo->valor = num;
  novo->prox = lista->inicio;
  lista->inicio = novo;

  if (lista->fim == NULL)
    lista->fim = novo;

  lista->fim->prox = lista->inicio;
  lista->tam++;
}

void imprimir(Lista lista) {
  No *no = lista.inicio;
  printf("\nLista tam %d: ", lista.tam);
  if(no) {
    do {
      printf("%d ", no->valor);
      no = no->prox;
    } while (no != lista.inicio);   
    printf("\nInicio: %d\n", no->valor);
  }
  printf("\n");
}

No* matar(Lista *lista, int num) {
  No *aux, *remover = NULL;

  if (lista->inicio) {
    if(lista->inicio == lista->fim && lista->inicio->valor == num) {
      remover = lista->inicio;
      lista->inicio = NULL;
      lista->fim = NULL;
      lista->tam--;
    } else if (lista->inicio->valor == num) {
      remover = lista->inicio;
      lista->inicio = remover->prox;
      lista->fim->prox = lista->inicio;
      lista->tam--;
    } else {
      aux = lista->inicio;
      while (aux->prox != lista->inicio && aux->prox->valor != num) {
        aux = aux->prox;
      }
      if (aux->prox->valor == num) {
        if (lista->fim == aux->prox) {
          remover = aux->prox;
          aux->prox = remover->prox;
          lista->fim = aux;
        } else {
          remover = aux->prox;
          aux->prox = remover->prox;
        }
        lista->tam--;
      }
    }
  }


  return remover;
}

No* escolha(Lista lista, int ordem) {
  No *no = lista.inicio;
  No *aux = lista.inicio;
  int j = 1;

  if(no) {
    do {
      if(aux->valor != 1) j = 0;
      for (int i = 0; i < ordem - j; i++) {
        aux = aux->prox;
      }
      aux = matar(&lista, aux->valor);
    } while (lista.tam != 1);
  }

  return aux->prox;
}

int main() {
  No *result;

  int ordem, qnt;

  while (scanf("%d %d", &qnt, &ordem)) {
    Lista lista;
    criar_lista(&lista);
    for (int i = qnt; i > 0; i--) {
      inserir_no_inicio(&lista, i);
    }
    result = escolha(lista, ordem);
    printf("%d\n", result->valor);
  }

  return 0;
}
