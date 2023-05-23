#ifndef __FILA_H__
#define __FILA_H__
#include <malloc.h>

typedef arvore* fobj_t;
typedef int bool;
enum{false,true};

typedef struct fila {
  fobj_t item;
  struct fila *prox;
} fila;

void enfileirar(fila **inicio, fila **fim, fobj_t obj);
bool desenfileirar(fila **inicio, fila **fim);
fobj_t frente(fila *inicio);
bool ehvazia(fila *inicio);
int tamanho(fila *inicio);

void enfileirar(fila **inicio, fila **fim, fobj_t obj) {
  fila *o = malloc(sizeof(fila));
  o->item = obj;
  o->prox = NULL;
  if(*fim) (*fim)->prox = o;
  else (*inicio) = o;
  (*fim) = o;
  return;
}


bool desenfileirar(fila **inicio, fila **fim) {
  bool ret = false;
  fila *o = (*inicio);
  if(*inicio) {
    *inicio = (*inicio)->prox;
    if(!*inicio) (*fim) = NULL;
    free(o);
    ret = true;
  }
  return ret;
}

fobj_t frente(fila *inicio) {
  fobj_t o = 0;
  if(inicio) o = inicio->item;
  return o;
}

bool ehvazia(fila *inicio) {
  return (!inicio);
}

int tamanho(fila *inicio) {
  int cont = 0;
  while(inicio) {
    inicio = inicio->prox;
    cont++;
  }
  return cont;
}

#endif // __FILA_H__
