#ifndef _ARVORE_H_
#define _ARVORE_H_

#include <stdlib.h>
#include <assert.h>
#include <malloc.h>

typedef char obj_t;
typedef int boolean;
enum{falso, verdade};

typedef struct listafilhos{
  struct arvore *filho;
  struct listafilhos *prox;
} listafilhos;

typedef struct arvore{
  obj_t info;
  listafilhos *prole;
  struct arvore *pai;
} arvore;

#include "fila.h"

void iniciar(arvore *a, obj_t info);
obj_t info(arvore *a);
int altura(arvore *a);
int profundidade(arvore *a);
arvore *pai(arvore *a);
int filhos(arvore *a);
arvore *filho(arvore *a, int i);
int insereFilho(arvore *a, arvore *f);
void removeFilho(arvore *a, int i);
void dfs(arvore *a, void function(obj_t), boolean pre);
void bfs(arvore *a, void function(obj_t));

obj_t info(arvore *a) {
  obj_t ret = '\0';
  if(a!=NULL)
    ret = a->info;
  return ret;
}

void iniciar(arvore *a, obj_t info) {
  a->info = info;
  a->pai = NULL;
  a->prole = NULL;
}

int altura(arvore *a) {    
  int nfilhos;
  int alt=0, h, i;
  
  nfilhos = filhos(a);
  for(i=1; i <= nfilhos; i++) {
    h = altura(filho(a,i));
    if(alt <= h) alt = h+1;
  }
  return alt;
}  
     
int profundidade(arvore *a) {
  int p = 0;
  
  if(a->pai != NULL) p = profundidade(a->pai) + 1;
  return p;
}

arvore *pai(arvore *a) {
  return a->pai;
}

int filhos(arvore *a) {
  int k = 0;
  listafilhos *f = a->prole;
  while(f!=NULL) {
    f=f->prox;
    k++;
  }
  return k;
}

arvore *filho(arvore *a, int i) {
   int k = 1;
   arvore *filho = NULL;
   listafilhos *f = a->prole;
   while(k < i && f != NULL) {
     f = f->prox;
     k++;
   }
   if(k==i && f != NULL) filho = f->filho;
   return filho;
}  
  
int insereFilho(arvore *a, arvore *f) {
  int k = 1;
  listafilhos *fi = a->prole;
  
  if(fi == NULL) {
    a->prole = (listafilhos *) malloc(sizeof(listafilhos));
    fi = a->prole;
  } else {
    while(fi->prox != NULL) {
      fi = fi->prox;
      k++;
    }
    fi->prox = (listafilhos *) malloc(sizeof(listafilhos));
    fi = fi->prox;
    k++;
  }
  f->pai = a;
  fi->filho = f;
  return k;
}

void removeFilho(arvore *a, int i) {
  int k, nfilhos;
  arvore *f = NULL;
  listafilhos *fi, *ant;

  fi = a->prole;
  if(i == 1) {
    if(fi != NULL) {
      a->prole = fi->prox;
      f = fi->filho;
      free(fi);
    }
  } else {
    k = 1;
    while(fi!= NULL && k < (i-1)) fi = fi->prox;
    if(fi != NULL) {
      ant = fi;
      fi = fi->prox;
      if(fi != NULL) {
        ant->prox = fi->prox;
        f = fi->filho;
        free(fi);
      }
      else ant->prox = NULL;
    }
  }    
  if(f != NULL) {
    nfilhos = filhos(f);
    if(nfilhos > 0) {
      for(k = 1; k <= nfilhos; k++)
	removeFilho(f,1);
    }
    free(f);
  }
  return;
}  

void dfs(arvore *a, void function(obj_t), boolean pre) {
  if(pre) function(a->info);
  listafilhos *fi = a->prole;
  while(fi != NULL) {
    dfs(fi->filho,function,pre);
    fi = fi->prox;
  }
  if(!pre) function(a->info);
  return;
}

void bfs(arvore *a, void function(obj_t)) {
  fila *ini = NULL, *fim = NULL;
  enfileirar(&ini,&fim,a);
  while(!ehvazia(ini)) {
    arvore *v = frente(ini); desenfileirar(&ini,&fim);
    listafilhos *fi = v->prole;
    while(fi != NULL) {
      enfileirar(&ini,&fim,fi->filho);
      fi = fi->prox;
    }
    function(v->info);
  }
  return;
}
#endif // _ARVORE_H_
