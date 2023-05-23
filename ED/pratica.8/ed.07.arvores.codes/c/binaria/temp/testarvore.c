#include<stdio.h>
#include<malloc.h>
#include "../arvorebinaria.h"

void funcao(char c) {
  printf("%c ",c);
}

int main(int argc, char **args) {
  arvore *a, *b, *p;
  
  a = (arvore *) malloc(sizeof(arvore));
  iniciar(a, 'A');
  b = (arvore *) malloc(sizeof(arvore));
  iniciar(b, 'B');
  insFilhoEsq(a,b);
  p = b;
  b = (arvore *) malloc(sizeof(arvore));
  iniciar(b, 'C');
  insFilhoEsq(p,b);
  b = (arvore *) malloc(sizeof(arvore));
  iniciar(b, 'D');
  insFilhoDir(a,b);
  p = b;
  b = (arvore *) malloc(sizeof(arvore));
  iniciar(b, 'E');
  insFilhoEsq(p,b);
  p = b;
  b = (arvore *) malloc(sizeof(arvore));
  iniciar(b,'F');
  insFilhoEsq(p,b);
  p = filhoDir(a);
  b = (arvore *) malloc(sizeof(arvore));
  iniciar(b,'G');
  insFilhoDir(p,b);
  p = b;
  b = (arvore *) malloc(sizeof(arvore));
  iniciar(b, 'H');
  insFilhoEsq(p,b);
  b = (arvore *) malloc(sizeof(arvore));
  iniciar(b, 'I');
  insFilhoDir(p,b);
  
  p = a;
  printf("O raiz: %c \n",info(a));
  printf("Altura do raiz: %d \n",altura(a));
  printf("\n .. filhos ..\n");
  if((p = filhoEsq(a))) {
    printf("O filho: %c \n",info(p));
    printf("Altura do filho: %d \n",altura(p));
  }
  if((p = filhoDir(a))) {
    printf("\n .. outro ..\n");
    printf("O filho: %c \n",info(p));
    printf("Altura do filho: %d \n",altura(p));
  }
  printf("Estou no raiz %c \n",info(a));  
  printf("Percursos:\n");
  printf("Largura:\n"); // Somente se for definido
  bfs(a,funcao); printf("\n"); // Somente se for definido
  printf("Pré Ordem: ");
  percPreOrdem(a,funcao); printf("\n");
  printf("Ordem: ");
  percOrdem(a,&funcao); printf("\n");
  printf("Pos Ordem: ");
  percPosOrdem(a,funcao); printf("\n");
  printf("\n");
  p = filhoDir(filhoDir(a));
  printf("Descendente %c \n",info(p));
  printf("Altura do descendente: %d \n",altura(p));
  printf("Profundiade do descendente: %d\n",profundidade(p)); // somente se for definido
  remFilhoEsq(p);
  remFilhoDir(p);
  printf("Altura deste no após remover os filhos: %d \n",altura(p));
  remFilhoDir(a); // Matando tudo.
  remFilhoEsq(a);
  free(a);
  return 0;
}
