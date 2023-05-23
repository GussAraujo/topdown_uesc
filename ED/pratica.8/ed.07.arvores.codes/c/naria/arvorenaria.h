#ifndef _ARVORENARIA_H_
#define _ARVORENARIA_H_

#include <stdlib.h>
#include <assert.h>

#define NARIA 3

typedef char obj_t;
typedef int boolean;
enum{falso, verdade};

typedef struct arvore{
  obj_t info;
  struct arvore *filhos[NARIA];
  struct arvore *pai;
} arvore;

#include "fila.h"

void iniciar(arvore *a, obj_t info);
obj_t info(arvore *a);
int altura(arvore *a);
int profundidade(arvore *a);
arvore *pai(arvore *a);
arvore *filho(arvore *a, uint i);
void insereFilho(arvore *a, arvore *f, uint i);
void removeFilho(arvore *a, uint i);
void bfs(arvore *a, void function(obj_t));
void dfs(arvore *a, void function(obj_t),boolean pre);

obj_t info(arvore *a) {
  obj_t ret = '\0';
  if(a!=NULL)
    ret = a->info;
  return ret;
}

void iniciar(arvore *a, obj_t info) {
  int i;
  a->info = info;
  a->pai = NULL;
  for(i=0;i<NARIA;i++) a->filhos[i] = NULL;
}

int altura(arvore *a) {    
  int alt=-1, h, i;
  if(a!=NULL) {
    for(i=0; i < NARIA; i++) {
      h = altura(filho(a,i));
      if(alt <= h) alt = h+1;
    }
  }
  return alt;
}  
     
int profundidade(arvore *a) {
  int p = 0;
  
  assert(a!=NULL);
  if(a->pai != NULL) p = profundidade(a->pai) + 1;
  return p;
}

arvore *pai(arvore *a) {
  return a->pai;
}

arvore *filho(arvore *a, uint i) {
  assert(i < NARIA);
  arvore *f=NULL;
  if(a != NULL)
    f = a->filhos[i];
  return f;
}  
  
void insereFilho(arvore *a, arvore *f, uint i) {
  assert(i < NARIA);
  assert(f != NULL); 
  assert(a != NULL);
  f->pai = a;
  a->filhos[i] = f;
}

void removeFilho(arvore *a, uint i) {
  int k;
  arvore *f = NULL;
  assert(i < NARIA);

  if(a!=NULL) {
    f = a->filhos[i];
    a->filhos[i] = NULL;
    if(f != NULL) {
      for(k = 0; k < NARIA; k++)
	removeFilho(f,k);
    }
    free(f);
  }
  return;
}  

void bfs(arvore *a, void function(obj_t)) {
  fila *ini, *fim;

  enfileirar(&ini,&fim,a);
  while(!ehvazia(ini)) {
    arvore *v = frente(ini); desenfileirar(&ini,&fim);
    for(int i = 0; i < NARIA; i++)
      if(v->filhos[i] != NULL) enfileirar(&ini,&fim,v->filhos[i]);
    function(v->info);
  }
  return;
}

void dfs(arvore *a, void function(obj_t), boolean pre) {
  if(pre) function(a->info);
  for(int i = 0; i < NARIA; i++)
    if(a->filhos[i] != NULL) dfs(a->filhos[i],function,pre);
  if(!pre) function(a->info);
  return;
}

#endif // _ARVORENARIA_H_
