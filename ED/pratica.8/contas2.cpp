#include <iostream>

template <class T>
class arvore{
private:
  T info;
  arvore *papai
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
}; 

template <class T>
arvore<T>::arvore(T info): info(info) {
  papai = NULL

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

template <class T>
arvore<T> *arvore<T>::pai() {
  return papai;
}

template <class T>
void arvore<T>::insFilhoEsq(arvore<T> *f) {
  filhoEsquerdo = f;
  f->papai = this;

  return;
}

template <class T>
void arvore<T>::insFilhoDir(arvore<T> *f) {
  filhoDireito = f;
  f->papai = this

  return;
}

int main()
{
  
  return 0;
}
