#include <iostream>

typedef struct lista {
  int ordem;
  char elem;
  struct lista * prox;
} lista;

using namespace std;

lista *remover(lista *list) {
  lista *temp = list->prox, *aux = list;
  if(list != NULL) {
    delete(aux);
    return temp;
  }
  
  return NULL;
}

void inserir(lista *list, int ord, char elemento) {
  lista *temp = new lista;
  temp->ordem = ord;
  temp->elem = elemento;
  temp->prox = NULL;

  if(list != NULL) {
    if (list->prox == NULL) {
      if (list->ordem > ord) {
        list->prox = temp;
      } else {
        lista *aux = list->prox;
        list = temp;
        list->prox = aux;
      }
    } else {
      while (ord < list->ordem) {
        list = list->prox;
      }
      temp->prox = list->prox;
      list->prox = temp;
      list->prox->prox = NULL;
    }
  } else {
    list->prox = temp;
  }
}

void listar(lista *list) {
    lista *aux = list;
    if(list != NULL) {
        while(aux != NULL) {
            cout << aux->elem << endl;
            aux = aux->prox;
        }
    }
}

int main()
{
  lista *list = NULL;

  inserir(list, 3, 'd');
  inserir(list, 2, 'c');
  inserir(list, 0, 'g');
  listar(list);
  inserir(list, 1, 'b');

  return 0;
}
