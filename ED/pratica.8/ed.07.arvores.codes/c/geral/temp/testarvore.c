#include<stdio.h>
#include<malloc.h>
#include "../arvore.h"

void funcao(char c) {
  printf("%c ",c);
}

int main(int argc, char **args) {
  arvore *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
  arvore *a;
  int n, p;
  
  d = (arvore *) malloc(sizeof(arvore));
  iniciar(d, 'D');
  e = (arvore *) malloc(sizeof(arvore));
  iniciar(e, 'E');
  insereFilho(d,e);
  f = (arvore *) malloc(sizeof(arvore));
  iniciar(f, 'F');
  insereFilho(e,f);
  g = (arvore *) malloc(sizeof(arvore));
  iniciar(g, 'G');
  insereFilho(d,g);
  h = (arvore *) malloc(sizeof(arvore));
  iniciar(h, 'H');
  insereFilho(g,h);
  i = (arvore *) malloc(sizeof(arvore));
  iniciar(i, 'I');
  insereFilho(h,i);
  j = (arvore *) malloc(sizeof(arvore));
  iniciar(j, 'J');
  insereFilho(g,j);
  k = (arvore *) malloc(sizeof(arvore));
  iniciar(k, 'K');
  insereFilho(j,k);
  l = (arvore *) malloc(sizeof(arvore));
  iniciar(l, 'L');
  insereFilho(j,l);
  m = (arvore *) malloc(sizeof(arvore));
  iniciar(m, 'M');
  insereFilho(g,m);
  
  a = d;
  printf("Busca em Profundidade\n");
  printf("Pré: "); dfs(d,funcao,verdade); printf("\n");
  printf("Pós: "); dfs(d,funcao,falso); printf("\n");
  printf("\n");
  printf("Busca em Largura\n");
  bfs(d,funcao); printf("\n");
  printf("\n");
  printf("O raiz: %c \n",info(a));
  printf("Altura do raiz: %d \n",altura(a));
  printf("Profundidade do raiz: %d \n",profundidade(a));
  printf("Número de filhos do raiz: %d \n",(n=filhos(a)));
  printf("\n .. filhos ..\n");
  for(p = 1; p <= n; p++) {
    a = filho(a,p);
    printf("O filho: %c \n",info(a));
    printf("Altura do filho: %d \n",altura(a));
    printf("Profundidade do filho: %d \n",profundidade(a));
    printf("Número de filhos do filho: %d \n",filhos(a));
    printf("\n .. outro ..\n");
    a = pai(a);
  }
  printf("Estou no raiz %c \n",info(a));  
  a = filho(filho(filho(a,2),2),1);
  printf("Descendente %c \n",info(a));
  printf("Altura do descendente: %d \n",altura(a));
  printf("Profundidade do descendente: %d \n",profundidade(a));
  printf("Número de filhos do descendente: %d \n",filhos(a));
  
  a = pai(a);
  printf("Subi para o pai: %c, com altura %d\n",info(a),altura(a));
  printf("Número de filhos deste no: %d\n",filhos(a));
  removeFilho(a,1);
  printf("Removi 1: Número de filhos deste no: %d \n",filhos(a));
  removeFilho(a,1);
  printf("Removi 1: Número de filhos deste no: %d \n",filhos(a));
  printf("Altura deste no: %d \n",altura(a));
  printf("Profundidade deste no: %d \n", profundidade(a));
  
  a = d;
  removeFilho(a,2);
  removeFilho(a,1);
  free(d);
  return 0;
}
