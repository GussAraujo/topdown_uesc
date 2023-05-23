#ifndef _ARVOREBINARIA_HPP_
#define _ARVOREBINARIA_HPP_

#include <iostream>
// #include "fila.hpp"

template <class T>
class arvore{
private:
  T info;
  arvore *papai; // Não precisa
  arvore *filhoEsquerdo, *filhoDireito;

public:
  arvore(T info);
  T getInfo();
  int altura();
  int profundidade();
  arvore *filhoEsq();
  arvore *filhoDir();
  arvore *pai();
  void insFilhoEsq(arvore *f);
  void insFilhoDir(arvore *f);
  void remFilhoEsq();
  void remFilhoDir();
  void bfs(void function(T));
  void percPreOrdem(void function(T));
  void percOrdem(void function(T));
  void percPosOrdem(void function(T));
}; 

template <class T>
arvore<T>::arvore(T info): info(info) {
  papai = NULL; // se tiver pai
  filhoEsquerdo = NULL;
  filhoDireito = NULL;
}

template <class T>
T arvore<T>::getInfo() {
  return info;
}

template <class T>
int arvore<T>::altura() {
  int alt=0, he = 0, hd = 0;
  if(filhoEsquerdo != NULL) he = filhoEsquerdo->altura()+1;
  if(filhoDireito != NULL)  hd = filhoDireito->altura()+1;
  alt = (he < hd) ? hd : he;
  return alt;
}  

// Somente se tiver pai.
template <class T>
int arvore<T>::profundidade() {
  int pr = 0;
  if(papai != NULL) {
    pr = papai->profundidade()+1;
  }
  return pr;
}

template <class T>
arvore<T> *arvore<T>::filhoEsq() {
  return filhoEsquerdo;
}  

template <class T>
arvore<T> *arvore<T>::filhoDir() {
  return filhoDireito;
}  

// Somente se tiver pai.
template <class T>
arvore<T> *arvore<T>::pai() {
  return papai;
}

template <class T>
void arvore<T>::insFilhoEsq(arvore<T> *f) {
  filhoEsquerdo = f;
  f->papai = this;  // se tiver pai.
  return;
}

template <class T>
void arvore<T>::insFilhoDir(arvore<T> *f) {
  filhoDireito = f;
  f->papai = this; // se tiver pai
  return;
}


template <class T>
void arvore<T>::remFilhoEsq() {
  arvore<T> *f = NULL;

  f = filhoEsquerdo;
  filhoEsquerdo = NULL;
  if(f != NULL) {
    f->remFilhoEsq();
    f->remFilhoDir();
    delete f;
  }
  return;
}  

template <class T>
void arvore<T>::remFilhoDir() {
  arvore<T> *f = NULL;

  f = filhoDireito;
  filhoDireito = NULL;
  if(f != NULL) {
    f->remFilhoEsq();
    f->remFilhoDir();
    delete f;
  }
  return;
}  

template <class T>
void arvore<T>::bfs(void function(T)) {
  fila<arvore<T> *> f;
  f.enfileirar(this);
  while(!f.ehvazia()) {
    arvore<T> *a = f.frente(); f.desenfileirar();
    if(a->filhoEsquerdo!=NULL) f.enfileirar(a->filhoEsquerdo);
    if(a->filhoDireito!=NULL) f.enfileirar(a->filhoDireito);
    function(a->info);
  }
  return;
}

template <class T>
void arvore<T>::percPreOrdem(void function(T)) {
  function(info);
  if(filhoEsquerdo) filhoEsquerdo->percPreOrdem(function);
  if(filhoDireito) filhoDireito->percPreOrdem(function);
  return;
}
  
  
template <class T>
void arvore<T>::percOrdem(void function(T)) {
  if(filhoEsquerdo) filhoEsquerdo->percOrdem(function);
  function(info);
  if(filhoDireito) filhoDireito->percOrdem(function);
  return;
}
  
template <class T>
void arvore<T>::percPosOrdem(void function(T)) {
  if(filhoEsquerdo) filhoEsquerdo->percPosOrdem(function);
  if(filhoDireito) filhoDireito->percPosOrdem(function);
  function(info);
  return;
}
  

#endif // _ARVORE_HPP_
