#ifndef _ARVORE_HPP_
#define _ARVORE_HPP_
#include "fila.hpp"


template<class T>
class listafilhos;

template<class T>
class arvore{
private:
  T info;
  listafilhos<T> *prole;
  arvore *pai;
  
public:
  arvore(T info);
  T getInfo();
  int altura();
  int profundidade();
  arvore *getPai();
  int filhos();
  arvore *filho(int i);
  int insereFilho(arvore *f);
  void removeFilho(int i);  
  void dfs(void function(T), bool pre=true);
  void bfs(void function(T));
};

template<class T>
class listafilhos{
  friend class arvore<T>;
private:
  arvore<T> *filho;
  listafilhos *prox;
  listafilhos(arvore<T> *f);
};

template<class T>
listafilhos<T>::listafilhos(arvore<T> *f) {
  filho = f;
  prox = NULL;
}

template<class T>
arvore<T>::arvore(T info) {
  this->info = info;
  this->pai = NULL;
  this->prole = NULL;
}

template<class T>
T arvore<T>::getInfo() {
  return info;
}

template<class T>
int arvore<T>::altura() {
  int nfilhos;
  int alt=0, h, i;
  
  nfilhos = filhos();
  for(i=1; i <= nfilhos; i++) {
    h = filho(i)->altura();
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
int arvore<T>::filhos() {
  int k = 0;
  listafilhos<T> *f = prole;
  while(f!=NULL) {
    f=f->prox;
    k++;
  }
  return k;
}

template<class T>
arvore<T> *arvore<T>::filho(int i) {
   int k = 1;
   listafilhos<T> *f = prole;
   while(k < i && f != NULL) {
     f = f->prox;
     k++;
   }
   return f->filho;
}  
  
template<class T>
int arvore<T>::insereFilho(arvore<T> *f) {
  int k = 1;
  listafilhos<T> *fi = prole;
  
  if(fi == NULL) {
    prole = new listafilhos(f);
    fi = prole;
  } else {
    while(fi->prox != NULL) {
      fi = fi->prox;
      k++;
    }
    fi->prox = new listafilhos(f);
    fi = fi->prox;
    k++;
  }
  f->pai = this;
  return k;
}

template<class T>
void arvore<T>::removeFilho(int i) {
  int k, nfilhos;
  listafilhos<T> *fi, *ant;
  arvore *f;

  fi = prole;
  if(i == 1) {
    if(fi != NULL) {
      prole = fi->prox;
      f = fi->filho;
      delete fi;
    }
  } else {
    k = 1;
    while(fi!= NULL && k < (i-1)) fi = fi->prox;
    ant = fi;
    fi = fi->prox;
    if(fi != NULL) {
      ant->prox = fi->prox;
      f = fi->filho;
      delete fi;
    }
    else ant->prox = NULL;
  }    
  if(f != NULL) {
    nfilhos = f->filhos();
    if(nfilhos > 0) {
      for(k = 1; k <= nfilhos; k++)
	f->removeFilho(1);
    }
    delete f;
  }
  return;
}  

template<class T>
void arvore<T>::dfs(void function(T), bool pre) {
  if(pre) function(info);
  listafilhos<T> *fi = prole;
  while(fi != NULL) {
    fi->filho->dfs(function,pre);
    fi = fi->prox;
  }
  if(!pre) function(info);
  return;
}

template<class T>
void arvore<T>::bfs(void function(T)) {
  fila<arvore<T> *> f;
  f.enfileirar(this);
  while(!f.ehvazia()) {
    arvore<T> *a = f.frente(); f.desenfileirar();
    listafilhos<T> *fi = a->prole;
    while(fi != NULL) {
      f.enfileirar(fi->filho);
      fi=fi->prox;
    }
    function(a->info);
  }
  return;
}

#endif // _ARVORE_HPP_
