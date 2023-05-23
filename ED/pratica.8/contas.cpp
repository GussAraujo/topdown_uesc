// Gustavo Araujo - 202210689
// João Dutterle - 202211138
// Pedro Elias - 202210359

#include <iostream>
typedef string obj_t;

typedef struct arvore
{
  obj_t info;
  listafilhos *prole;
  struct arvore *pai;
} arvore;

typedef struct listafilhos
{
  struct arvore *filho;
  struct listafilhos *prox;
} listafilhos;

using namespace std;

void iniciar(arvore *a, obj_t info)
{
  a->info = info;
  a->pai = NULL;
  a->prole = NULL;
}

obj_t info(arvore *a)
{
  obj_t ret = '\0';
  if (a != NULL)
    ret = a->info;
  return ret;
}

int altura(arvore *a)
{
  int nfilhos;
  int alt = 0, h, i;
  nfilhos = filhos(a);
  for (i = 1; i <= nfilhos; i++)
  {
    h = altura(filho(a, i));
    if (alt <= h)
      alt = h + 1;
  }
  return alt;
}

int profundidade(arvore *a)
{
  int p = 0;
  if (a->pai != NULL)
    p = profundidade(a->pai) + 1;
  return p;
}

int filhos(arvore *a)
{
  int k = 0;
  listafilhos *f = a->prole;
  while (f != NULL)
  {
    f = f->prox;
    k++;
  }
  return k;
}
arvore *filho(arvore *a, int i)
{
  int k = 1;
  arvore *filho = NULL;
  listafilhos *f = a->prole;
  while (k < i && f != NULL)
  {
    f = f->prox;
    k++;
  }
  if (k == i && f != NULL)
    filho = f->filho;
  return filho;
}

int insereFilho(arvore *a, arvore *f)
{
  int k = 1;
  listafilhos *fi = a->prole;
  if (fi == NULL)
  {
    a->prole = (listafilhos *)malloc(sizeof(listafilhos));
    fi = a->prole;
  }
  else
  {
    while (fi->prox != NULL)
    {
      fi = fi->prox;
      k++;
    }
    fi->prox = (listafilhos *)malloc(sizeof(listafilhos));
    fi = fi->prox;
    k++;
  }
  f->pai = a;
  fi->filho = f;
  return k;
}

void removeFilho(arvore *a, int i)
{
  int k, nfilhos;
  arvore *f = NULL;
  listafilhos *ant, *fi = a->prole;
  if (i == 1)
  {
    if (fi != NULL)
    {
      a->prole = fi->prox;
      f = fi->filho;
      free(fi);
    }
  }
  else
  {
    k = 1;
    while (fi != NULL && k < (i - 1))
      fi = fi->prox;
    if (fi != NULL)
    {
      ant = fi;
      fi = fi->prox;
      if (fi != NULL)
      {
        ant->prox = fi->prox;
        f = fi->filho;
        free(fi);
      }
      else
        ant->prox = NULL;
    }
  }
  if (f != NULL)
  {
    nfilhos = filhos(f);
    if (nfilhos > 0)
      for (k = 1; k <= nfilhos; k++)
        removeFilho(f, 1);
    free(f);
  }
  return;
}

bool ehOperador(string valor){
  switch (valor[0]) {
  case '+':
    return true;
    break;
  case '-':
    return true;
    break;
  case '*':
    return true;
    break;
  case '/':
    return true;
    break;  
  default:
    return false;
    break;
  }
}

void construirInfixa(arvore *raiz) {
  string valor;
  cin >> valor;
  // arvore *raiz = NULL;

  if(valor == "(") {
    construirInfixa(raiz);
  } else {
    iniciar(raiz, valor);
  }

  cin >> valor;
  if (valor == "") return;
  else {
    
  }

}

int main()
{
  int n;
  string valor;

  while (cin >> n) {
    arvore *raiz = NULL;
    for (int i = 1; i < n; i++) {

    }
  }

  return 0;
}
