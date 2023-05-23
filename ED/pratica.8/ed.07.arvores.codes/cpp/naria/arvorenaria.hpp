#ifndef _ARVORENARIA_HPP_
#define _ARVORENARIA_HPP_

#include <stdlib.h>
#include <assert.h>
#include "fila.hpp"

#define NARIA 3

typedef char obj_t;

template<class T>
class arvore{
private:
  T info;
  arvore *filhos[NARIA];
  arvore *pai;
  
public:
  arvore(T info);
  T getInfo();
  int altura();
  int profundidade();
  arvore *getPai();
  arvore *filho(uint i);
  void insereFilho(arvore *f, uint i);
  void removeFilho(uint i);
  void bfs(void function(T));
  void dfs(void function(T),bool pre=true);
};

template<class T>
arvore<T>::arvore(T info) {
  this->info = info;
  pai = NULL;
  for(int i=0; i < NARIA; i++) filhos[i] = NULL;
}

template<class T>
T arvore<T>::getInfo() {
  return info;
}

template<class T>
int arvore<T>::altura() {
  int alt=0, h, i;
  for(i=0; i < NARIA; i++) {
    if(filhos[i]!= NULL) h = filhos[i]->altura();
    else h = -1;
    if(alt <= h) alt = h+1;
  }
  return alt;
}  
     
template<class T>
int arvore<T>::profundidade() {
  int p = 0;
  
  if(pai != NULL) p = pai->profundidade() + 1;
  return p;
}

template<class T>
arvore<T> *arvore<T>::getPai() {
  return pai;
}

template<class T>
arvore<T> *arvore<T>::filho(uint i) {
  assert(i < NARIA);
  return filhos[i];
}  
  
template<class T>
void arvore<T>::insereFilho(arvore *f, uint i) {
  assert(i < NARIA);
  if(f!=NULL) f->pai = this;
  filhos[i] = f;
}

template<class T>
void arvore<T>::removeFilho(uint i) {
  int k;
  arvore<T> *f;
  assert(i < NARIA);

  f = filhos[i];
  filhos[i] = NULL;
  if(f != NULL) {
    for(k = 0; k < NARIA; k++)
      f->removeFilho(k);
    free(f);
  }
  return;
}  

template<class T>
void arvore<T>::bfs(void function(T)) {
  fila<arvore *> f;
  f.enfileirar(this);
  while(!f.ehvazia()) {
    arvore<T> *a = f.frente(); f.desenfileirar();
    for(int i=0; i<NARIA; i++) if(a->filhos[i]!=NULL) f.enfileirar(a->filhos[i]);
    function(a->info);
  }
  return;
}

template<class T>
void arvore<T>::dfs(void function(T),bool pre) {
  if(pre) function(info);
  for(int i=0; i<NARIA; i++) if(filhos[i]!=NULL) filhos[i]->dfs(function,pre);
  if(!pre) function(info);
  return;
}


#endif // _ARVORENARIA_HPP_
