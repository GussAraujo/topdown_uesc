#include<iostream>
#include "../arvore.hpp"

using namespace std;

void imprimir(char c) {
  cout << c << " ";
  return;
}

int main(int argc, char **args) {
  arvore<char> *d = new arvore<char>('D');
  arvore<char> *e = new arvore<char>('E');
  arvore<char> *f = new arvore<char>('F');
  arvore<char> *g = new arvore<char>('G');
  arvore<char> *h = new arvore<char>('H');
  arvore<char> *i = new arvore<char>('I');
  arvore<char> *j = new arvore<char>('J');
  arvore<char> *k = new arvore<char>('K');
  arvore<char> *l = new arvore<char>('L');
  arvore<char> *m = new arvore<char>('M');
  arvore<char> *a;
  int n, p;
  
  d->insereFilho(e);
  e->insereFilho(f);
  d->insereFilho(g);
  g->insereFilho(h);
  h->insereFilho(i);
  g->insereFilho(j);
  j->insereFilho(k);
  j->insereFilho(l);
  g->insereFilho(m);
  
  cout << "Busca em profundidade" << endl;
  cout << "Pré: "; d->dfs(&imprimir);  cout << endl;
  cout << "Pós: "; d->dfs(&imprimir,false); cout << endl;
  cout << endl;
  cout << "Busca em largura" << endl;
  d->bfs(&imprimir); cout << endl;
  cout << endl;
  a = d;
  cout << "O raiz: " << a->getInfo() << endl;
  cout << "Altura do raiz: " << a->altura() << endl;
  cout << "Profundidade do raiz: " << a->profundidade() << endl;
  cout << "Número de filhos do raiz: " << (n=a->filhos()) << endl;
  cout << endl << " .. filhos .." << endl;
  for(p = 1; p <= n; p++) {
    a = a->filho(p);
    cout << "O filho: " << a->getInfo() << endl;
    cout << "Altura do filho: " << a->altura() << endl;
    cout << "Profundidade do filho: " << a->profundidade() << endl;
    cout << "Número de filhos do filho: " << a->filhos() << endl;
    cout << endl << " .. outro .." << endl;
    a = a->getPai();
  }
  cout << "Estou no raiz " << a->getInfo() << endl;  
  a = a->filho(2)->filho(2)->filho(1);
  cout << "Descendente " << a->getInfo() << endl;
  cout << "Altura do descendente: " << a->altura() << endl;
  cout << "Profundidade do descendente: " << a->profundidade() << endl;
  cout << "Número de filhos do descendente: " << a->filhos() << endl;
  
  a = a->getPai();
  cout << "Subi para o pai: " << a->getInfo() << " com altura " << a->altura() << endl;
  cout << "Número de filhos deste no: " << a->filhos() << endl;
  a->removeFilho(1);
  cout << "Removi 1: Número de filhos deste no: " << a->filhos() << endl;
  a->removeFilho(1);
  cout << "Removi 1: Número de filhos deste no: " << a->filhos() << endl;
  cout << "Altura deste no: " << a->altura() << endl;
  cout << "Profundidade deste no: " <<  a->profundidade() << endl;
  
  a = d;
  a->removeFilho(2);
  a->removeFilho(1);
  
  delete d;
  return 0;
}
