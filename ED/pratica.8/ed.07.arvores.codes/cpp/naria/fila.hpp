#ifndef __FILA_HPP__
#define __FILA_HPP__

template<class T>
class fila {
  class item {
  public:
    T val;
    item *prox;

    item() {prox = NULL;}
    item(T val): val(val) {prox = NULL;}
  };
private:
 item *ini, *fim;

public:
  fila();
  void enfileirar(T obj);
  void desenfileirar();
  T frente();
  bool ehvazia();
  int tamanho();
};

template<class T>
fila<T>::fila(): ini(NULL), fim(NULL) { }

template<class T>
void fila<T>::enfileirar(T obj) {
  item *o = new item(obj);
  o->prox = NULL;
  if(fim) fim->prox = o;
  else ini = o;
  fim = o;
  return;
}

template<class T>
void fila<T>::desenfileirar() {
  item *o = ini;
  if(ini) {
    ini = ini->prox;
    if(!ini) fim = NULL;
    delete o;
  }
  return;
}

template<class T>
T fila<T>::frente() {
  T val = T(0);
  if(ini) val = ini->val;
  return val;
}

template<class T>
bool fila<T>::ehvazia() {
  return (!ini);
}

template<class T>
int fila<T>::tamanho() {
  item *p = ini;
  int cont = 0;
  while (p) {
    p = p->prox;
    cont++;
  }
  return cont;
}

#endif // __FILA_HPP__
