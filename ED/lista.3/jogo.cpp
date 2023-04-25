#include <iostream>

using namespace std;

class No {
  private:
    int info;
    No *prox;
  public:
    No(int info);
    void setProx(No *p);
    No* obterProx();
    int obterValor();
};

No::No(int _info) {
  this->info = _info;
  this->prox = NULL;
}

void No::setProx(No *p) {
  prox = p;
}

No* No::obterProx() {
  return prox;
}

int No::obterValor() {
  return info;
}

class Lista {
  private:
    No* cabeca;
    No* cauda;
  public:
    Lista();
    ~Lista();
    Lista(int info);
    void inserir_inicio(int info);
    void inserir_final(int info);
    void remover_ultimo();
    void remover(int info);
    void mostrar();
    bool existe(int info);
};

Lista::Lista() {
  cabeca = NULL;
  cauda = NULL;
}

Lista::Lista(int _info) {
  cabeca = new No(_info);
  cauda = cabeca;
}

Lista::~Lista() {
  delete cabeca;
}

void Lista::inserir_inicio(int _info) {
  No *novo_no = new No(_info);

  novo_no->setProx(cabeca);
  cabeca = novo_no;
}

void Lista::inserir_final(int _info) {
  No *novo_no = new No(_info);

  if (cabeca == NULL) {
    cabeca = novo_no;
    cauda = novo_no;
  } else {
    cauda->setProx(novo_no);
    cauda = novo_no;
  }
}

void Lista::remover_ultimo() {
  if(cabeca == NULL)
  {
    if(cabeca->obterProx() == NULL)
      cabeca = NULL;
    else if(cabeca->obterProx()->obterProx() == NULL)
      cabeca->setProx(NULL);
    else {
      No* ant_ant = cabeca;
      No* ant = cabeca->obterProx();
      No* corrente = cabeca->obterProx()->obterProx();

      while(corrente) {
        No* aux = ant;
        ant = corrente;
        ant_ant = aux;
        corrente = corrente->obterProx();
      }

      delete ant_ant->obterProx();
      ant_ant->setProx(NULL);
      cauda = ant_ant;
    }
  }
}

void Lista::remover(int info) {
  No* c = cabeca;
  
  if(cabeca != NULL) {
    if(c->obterProx() == NULL && c->obterValor() == info){
      c == NULL;
      return;
    } else if(cabeca->obterProx()->obterProx() == NULL){
      No* ant = cauda;
      if(c->obterValor() == info){
        c->setProx(NULL);
        delete ant;
      }
      ant->setProx(NULL);
      delete c;
    } else {
      No* ant_ant = cabeca;
      No* ant = cabeca->obterProx();
      No* corrente = cabeca->obterProx()->obterProx();

      while(c->obterValor() != info) {
        // No* aux = ant;
        // ant = corrente;
        // ant_ant = aux;
        // c = c->obterProx();
      }
    }
  }
}

void Lista::mostrar() {
  cout << "Imprimindo todos os elementos...\n";
  No* c = cabeca;

  if(cabeca == NULL)
    cout << "A lista NAO possui elementos!!\n";
  else {
    while(c) {
      cout << c->obterValor() << endl;
      c = c->obterProx();
    }
    cout << endl;
  }
}

bool Lista::existe(int info) {
  No* c = cabeca;
  
  while(c) {
    if(c->obterValor() == info)
      return true;
    c = c->obterProx();
  }
  return false;
}

int main() {
  Lista lista;

  lista.inserir_final(10);
	lista.inserir_final(20);
	lista.inserir_final(30);
	lista.inserir_final(40);
	lista.inserir_inicio(50);

  lista.mostrar();
  lista.remover(30);

  return 0;
}
