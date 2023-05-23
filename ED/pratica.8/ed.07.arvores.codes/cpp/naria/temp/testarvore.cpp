#include<iostream>
#include "../arvorenaria.hpp"

using namespace std;

void funcao(char c) {
  cout << c << " ";
  return;
}

int main(int argc, char **args) {
  arvore<char> *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
  arvore<char> *a;
  int p;
  
  d = new arvore<char>('D');
  e = new arvore<char>('E');
  d->insereFilho(e,0);
  f = new arvore<char>('F');
  e->insereFilho(f,0);
  g = new arvore<char>('G');
  d->insereFilho(g,2);
  h = new arvore<char>('H');
  g->insereFilho(h,0);
  i = new arvore<char>('I');
  h->insereFilho(i,0);
  j = new arvore<char>('J');
  g->insereFilho(j,1);
  k = new arvore<char>('K');
  j->insereFilho(k,0);
  l = new arvore<char>('L');
  j->insereFilho(l,1);
  m = new arvore<char>('M');
  g->insereFilho(m,2);
  
  a = d;
  cout << "Busca em profundidade" << endl;
  cout << "Pre: "; d->dfs(&funcao); cout << endl;
  cout << "Pos: "; d->dfs(&funcao,false); cout << endl;
  cout << endl;
  cout << "Busca em largura" << endl;
  d->bfs(&funcao); cout << endl;
  cout << endl;
  cout << "O raiz:  " << a->getInfo() << endl;
  cout << "Altura do raiz:  " << a->altura() << endl;
  cout << "Profundidade do raiz:  " << a->profundidade() << endl;
  cout << endl << " .. filhos .. " << endl;
  for(p = 0; p < NARIA; p++) {
    if(a->filho(p)) {
      a = a->filho(p);
      cout << "O filho:  " << a->getInfo() << endl;
      cout << "Altura do filho:  " << a->altura() << endl;
      cout << "Profundidade do filho:  " << a->profundidade() << endl;
      cout << endl << " .. outro .. " << endl;
      a = a->getPai();
    }
  }
  cout << "Estou no raiz  " << a->getInfo() << endl;  
  a = a->filho(2)->filho(1)->filho(0);
  cout << "Descendente  " << a->getInfo() << endl;
  cout << "Altura do descendente:  " << a->altura() << endl;
  cout << "Profundidade do descendente:  " << a->profundidade() << endl;
  
  a = a->getPai();
  cout << "Fui para o pai. Altura deste no:  " << a->altura() << endl;
  a->removeFilho(0);
  cout << "Removi o filho 0: Altura deste no:  " << a->altura() << endl;
  a->removeFilho(1);
  cout << "Removi o filho 1: Altura deste no:  " << a->altura() << endl;
  cout << "Profundidade deste no:  " <<  a->profundidade() << endl;
  
  a = d;
  a->removeFilho(1);
  a->removeFilho(0);
  delete d;
  return 0;
}
