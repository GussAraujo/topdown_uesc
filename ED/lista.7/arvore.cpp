#include <iostream>

using namespace std;

struct NO {
  int item;
  NO *esq;
  NO *dir;
};

class Tree {
  private:
    NO *root;
  public:
    Tree() {
      root = NULL;
    }
    void inserir(int v);
};

void Tree::inserir(int v) {
  NO *novo = new NO();
  novo->item = v;
  novo->dir = NULL;
  novo->esq = NULL;

  if (root == NULL) {
    root = novo;
  } else {
    NO *atual = root;
    NO *anterior;
    while(true) {
      anterior = atual;
      if (v <= atual->item) { // ir para esquerda
        atual = atual->esq;
        if (atual == NULL) {
          anterior->esq = novo;
          return;
        } 
      } // fim da condição ir a esquerda
      else { // ir para direita
        atual = atual->dir;
        if (atual == NULL) {
          anterior->dir = novo;
          return;
        }
      } // fim da condição ir a direita
    } // fim do laço while
  } // fim do else não raiz'
}