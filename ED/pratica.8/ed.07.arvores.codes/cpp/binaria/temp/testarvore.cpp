#include<iostream>
#include "../arvorebinaria.hpp"

using namespace std;

void funcao(char c) {
  cout << c << " ";
  return;
}

int main(int argc, char **args) {
  arvore<char> *a, *b, *p;
  
  a = new arvore<char>('A');
  b = new arvore<char>('B');
  a->insFilhoEsq(b);
  p = b;
  b = new arvore<char>('C');
  p->insFilhoEsq(b);
  b = new arvore<char>('D');
  a->insFilhoDir(b);
  p = b;
  b = new arvore<char>('E');
  p->insFilhoEsq(b);
  p = b;
  b = new arvore<char>('F');
  p->insFilhoEsq(b);
  p = a->filhoDir();
  b = new arvore<char>('G');
  p->insFilhoDir(b);
  p = b;
  b = new arvore<char>('H');
  p->insFilhoEsq(b);
  b = new arvore<char>('I');
  p->insFilhoDir(b);
  
  p = a;
  cout << "O raiz: " << a->getInfo() << endl;
  cout << "Altura do raiz: " << a->altura() << endl;
  cout << endl << " .. filhos .. " << endl;
  if((p = a->filhoEsq())) {
    cout << "O filho: " << p->getInfo() << endl;
    cout << "Altura do filho: " << p->altura() << endl;
  }
  if((p = a->filhoDir())) {
    cout << endl << " .. outro .." << endl;
    cout << "O filho: " << p->getInfo() << endl;
    cout << "Altura do filho: " << p->altura() << endl;
  }
  cout << "Estou no raiz " << a->getInfo() << endl;  
  cout << "Percursos:" << endl;
  cout << "Largura: ";
  a->bfs(funcao); cout << endl;
  cout << "Pré Ordem: ";
  a->percPreOrdem(funcao); cout << endl;
  cout << "Ordem: ";
  a->percOrdem(funcao); cout << endl;
  cout << "Pos Ordem: ";
  a->percPosOrdem(funcao); cout << endl;
  p = a->filhoDir()->filhoDir();
  cout << "Descendente " << p->getInfo() << endl;
  cout << "Altura do descendente: " << p->altura() << endl;
  cout << "Profundidade do descendente: " << p->profundidade() << endl; // só se definido
  p->remFilhoEsq();
  p->remFilhoDir();
  cout << "Removi os filhos: Altura deste no: " << p->altura() << endl;
  
  a->remFilhoDir(); // Matando tudo.
  a->remFilhoEsq();
  delete a;
  return 0;
}

