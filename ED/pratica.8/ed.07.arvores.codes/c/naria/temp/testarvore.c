#include<stdio.h>
#include<malloc.h>
#include "../arvorenaria.h"

void funcao(char c) {
  printf("%c ",c);
  return;
}

int main(int argc, char **args) {
  arvore *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
  arvore *a;
  int p;
  
  d = (arvore *) malloc(sizeof(arvore));
  iniciar(d, 'D');
  e = (arvore *) malloc(sizeof(arvore));
  iniciar(e, 'E');
  insereFilho(d,e,0);
  f = (arvore *) malloc(sizeof(arvore));
  iniciar(f, 'F');
  insereFilho(e,f,0);
  g = (arvore *) malloc(sizeof(arvore));
  iniciar(g, 'G');
  insereFilho(d,g,2);
  h = (arvore *) malloc(sizeof(arvore));
  iniciar(h, 'H');
  insereFilho(g,h,0);
  i = (arvore *) malloc(sizeof(arvore));
  iniciar(i, 'I');
  insereFilho(h,i,0);
  j = (arvore *) malloc(sizeof(arvore));
  iniciar(j, 'J');
  insereFilho(g,j,1);
  k = (arvore *) malloc(sizeof(arvore));
  iniciar(k, 'K');
  insereFilho(j,k,0);
  l = (arvore *) malloc(sizeof(arvore));
  iniciar(l, 'L');
  insereFilho(j,l,1);
  m = (arvore *) malloc(sizeof(arvore));
  iniciar(m, 'M');
  insereFilho(g,m,2);
  
  a = d;
  printf("Busca em Profundidade:\n");
  printf("Pré: "); dfs(d,funcao,verdade); printf("\n");
  printf("Pós: "); dfs(d,funcao,falso); printf("\n");
  printf("\n");
  printf("Busca em Largura:\n");
  bfs(d,funcao); printf("\n");
  printf("\n");

  printf("O raiz: %c \n",info(a));
  printf("Altura do raiz: %d \n",altura(a));
  printf("Profundidade do raiz: %d \n",profundidade(a));
  printf("\n .. filhos ..\n");
  for(p = 0; p < NARIA; p++) {
    if(filho(a,p)) {
      a = filho(a,p);
      printf("O filho: %c \n",info(a));
      printf("Altura do filho: %d \n",altura(a));
      printf("Profundidade do filho: %d \n",profundidade(a));
      printf("\n .. outro ..\n");
      a = pai(a);
    }
  }
  printf("Estou no raiz %c \n",info(a));  
  a = filho(filho(filho(a,2),1),0);
  printf("Descendente %c \n",info(a));
  printf("Altura do descendente: %d \n",altura(a));
  printf("Profundidade do descendente: %d \n",profundidade(a));
  
  a = pai(a);
  printf("Indo para o pai. altura deste no: %d \n",altura(a));
  removeFilho(a,0);
  printf("removi filho 0: Altura deste no: %d \n",altura(a));
  removeFilho(a,1);
  printf("removi filho 1: Altura deste no: %d \n",altura(a));
  printf("Profundidade deste no: %d \n", profundidade(a));
  
  a = d;
  removeFilho(a,1);
  removeFilho(a,0);
  free(d);
  return 0;
}
