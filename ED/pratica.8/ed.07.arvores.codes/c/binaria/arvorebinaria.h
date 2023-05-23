#ifndef _ARVOREBINARIA_H_
#define _ARVOREBINARIA_H_

#include <stdlib.h>
#include <assert.h>

typedef char obj_t;
typedef struct arvore{
  obj_t info;
  struct arvore *filhoEsquerdo, *filhoDireito;
  struct arvore *pai;
} arvore;

#include "fila.h" // Somente se quiser bfs

// Função que o usuário deve implementar para realizar os percursos

void iniciar(arvore *a, obj_t info);
obj_t info(arvore *a);
int altura(arvore *a);
int profundidade(arvore *a); // somente se tiver o ponteiro pai.
arvore *pai(arvore *a); // somente se tiver o ponteiro pai.
arvore *filhoEsq(arvore *a);
arvore *filhoDir(arvore *a);
void insFilhoEsq(arvore *a, arvore *f);
void insFilhoDir(arvore *a, arvore *f);
void remFilhoEsq(arvore *a);
void remFilhoDir(arvore *a);
void bfs(arvore *a, void function(obj_t));
void percPreOrdem(arvore *a, void function(obj_t));
void percOrdem(arvore *a, void function(obj_t));
void percPosOrdem(arvore *a, void function(obj_t));

obj_t info(arvore *a) {
  obj_t ret = '\0'; //considerando obj_t 
  if(a!=NULL)
    ret = a->info;
  return ret;
}

void iniciar(arvore *a, obj_t info) {
  a->info = info;
  a->pai = NULL; // somente se tiver o ponteiro pai
  a->filhoEsquerdo = NULL;
  a->filhoDireito = NULL;
}

int altura(arvore *a) {    
  int alt=-1, he, hd;
  if(a!=NULL) {
    he = altura(filhoEsq(a))+1;
    hd = altura(filhoDir(a))+1;
    alt = (he < hd) ? hd : he;
  }
  return alt;
}  

// Somente se tiver o ponteiro pai
int profundidade(arvore *a) {
  int p = 0;
  
  assert(a!=NULL);
  if(a->pai != NULL) p = profundidade(a->pai) + 1;
  return p;
}

// Somente se tiver o ponteiro pai
arvore *pai(arvore *a) {
  return a->pai;
}


arvore *filhoEsq(arvore *a) {
  arvore *f = NULL;
  if(a != NULL)
    f = a->filhoEsquerdo;
  return f;
}  

arvore *filhoDir(arvore *a) {
  arvore *f = NULL;
  if(a != NULL)
    f = a->filhoDireito;
  return f;
}  


void insFilhoEsq(arvore *a, arvore *f) {
  assert(a != NULL && f != NULL);  
  f->pai = a; // Somente se tiver o ponteiro pai
  a->filhoEsquerdo = f;
}

void insFilhoDir(arvore *a, arvore *f) {
  assert(a != NULL && f != NULL);  
  f->pai = a; // Somente se tiver o ponteiro pai
  a->filhoDireito = f;
}


void remFilhoEsq(arvore *a) {
  arvore *f = NULL;

  if(a!=NULL) {
    f = a->filhoEsquerdo;
    a->filhoEsquerdo = NULL;
    if(f != NULL) {
	remFilhoEsq(f);
	remFilhoDir(f);
    }
    free(f);
  }
  return;
}  

void remFilhoDir(arvore *a) {
  arvore *f = NULL;

  if(a!=NULL) {
    f = a->filhoDireito;
    a->filhoDireito = NULL;
    if(f != NULL) {
      remFilhoEsq(f);
      remFilhoDir(f);
    }
    free(f);
  }
  return;
}  

void bfs(arvore *a, void function(obj_t)) {
  if(a!=NULL) {
    fila *ini=NULL, *fim=NULL;
    enfileirar(&ini,&fim,a);
    while(!ehvazia(ini)) {
      arvore *v = frente(ini); desenfileirar(&ini,&fim);
      if(v->filhoEsquerdo != NULL) enfileirar(&ini,&fim,v->filhoEsquerdo);
      if(v->filhoDireito != NULL) enfileirar(&ini,&fim,v->filhoDireito);
      function(v->info);
    }
  }
  return;
}

void percPreOrdem(arvore *a, void function(obj_t)) {
  if(a != NULL) {
    function(a->info);
    percPreOrdem(a->filhoEsquerdo,function);
    percPreOrdem(a->filhoDireito,function);
  }
  return;
}
  
  
void percOrdem(arvore *a, void function(obj_t)) {
  if(a != NULL) {
    percOrdem(a->filhoEsquerdo,function);
    function(a->info);
    percOrdem(a->filhoDireito,function);
  }
  return;
}
  
  
void percPosOrdem(arvore *a, void function(obj_t)) {
  if(a != NULL) {
    percPosOrdem(a->filhoEsquerdo,function);
    percPosOrdem(a->filhoDireito,function);
    function(a->info);
  }
  return;
}
  

#endif // _ARVORE_H_
