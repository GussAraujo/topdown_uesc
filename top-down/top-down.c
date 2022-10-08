#include <stdio.h>
#include <string.h>

#define QNT_MAX_PROD 1000
#define TAM_NOME 30

void monstrar_menu();
int obter_opcao();
void erro(int codigo_erro);

int cadastrar_produto(char produto[QNT_MAX_PROD][TAM_NOME], int qnt_produto, int estoque[QNT_MAX_PROD]);
void adicionar_estoque(char produto[QNT_MAX_PROD][TAM_NOME], int qnt, int estoque[QNT_MAX_PROD]);
void remove_estoque(char produtos[QNT_MAX_PROD][TAM_NOME], int qnt, int estoque[QNT_MAX_PROD]);
void consultar_estoque(char produto[QNT_MAX_PROD][TAM_NOME], int qnt, int estoque[QNT_MAX_PROD]);

int verificar_existencia(char produto[QNT_MAX_PROD][TAM_NOME], char nome[TAM_NOME], int qnt);

int main(){
  char produto[QNT_MAX_PROD][TAM_NOME], estoque[QNT_MAX_PROD];
  int qnt_produto = 0, loop = 1, opcao;
  
  while(loop){
    printf("Estoque de parafusos...\n\n");
    monstrar_menu();

    opcao = obter_opcao();

    switch (opcao) {
    case 1:
      qnt_produto = cadastrar_produto(produto, qnt_produto, estoque);
      break;
    case 2:
      adicionar_estoque(produto, qnt_produto, estoque);
      break;
    case 3:
      remove_estoque(produto, qnt_produto, estoque);
      break;
    case 4:
      consultar_estoque(produto, qnt_produto, estoque);
      break;
    case 5:
      loop = 0;
      break;
    default:
      printf("Numero invalido...");
      break;
    }
  }

  return 0;
}

void monstrar_menu(){
  printf("Selecione uma opcao:\n");
  printf("1 - Cadastrar Produto\n");
  printf("2 - Adionar Produto no Estoque\n");
  printf("3 - Remover Produto no Estoque\n");
  printf("4 - Consultar Estoque\n");
  printf("5 - Sair\n");
}

int obter_opcao(){
  int resposta;
  
  printf("\nDigitar opcao: ");
  scanf("%d", &resposta);
  scanf("*[^\n]");
  scanf("%*c");
  
  system("clear || cls");

  return resposta;
}

int cadastrar_produto(char produto[QNT_MAX_PROD][TAM_NOME], int qnt, int estoque[QNT_MAX_PROD]){
  int sair = 1, i = 0, existe;
  char nome[TAM_NOME];

  while(sair){
    if(qnt == QNT_MAX_PROD){
      erro(1);
      return qnt;
    }

    obter_produto(nome);
    existe = verificar_existencia(produto, nome, qnt);

    if(existe != -1){
      erro(2);
      continue;
    } 

    strcpy(produto[i], nome);

    estoque[qnt] = 0;
    qnt++;
  
    printf("Adicionar outro produto? (0 - nao, 1 - sim): ");
    scanf("%d", &sair);
    scanf("*[^\n]");
    scanf("%*c");

    i++;
    system("clear || cls");
  }

  return qnt;
}

void obter_produto(char *nome){
  printf("\nDigite o produto: ");
  scanf("%30[^\n]s", nome);
  scanf("*[^\n]");
  scanf("%*c");
}

void adicionar_estoque(char produto[QNT_MAX_PROD][TAM_NOME], int qnt, int estoque[QNT_MAX_PROD]){
  int existe, qnt_item = 0;
  char nome[TAM_NOME];

  printf("Digite o nome do produto: ");
  scanf("%30[^\n]s", nome);
  scanf("*[^\n]");
  scanf("%*c");

  existe = verificar_existencia(produto, nome, qnt);

  if(existe != -1){
    printf("\nDigite a quantidade para adicionar: ");
    scanf("%d", &qnt_item);
    
    estoque[existe] += qnt_item;

    return;
  }
  
  erro(3);
  return;
}

void remove_estoque(char produto[QNT_MAX_PROD][TAM_NOME], int qnt, int estoque[QNT_MAX_PROD]){
  char nome[TAM_NOME];
  int existe, qnt_item = 0;

  printf("Digite o nome do produto: ");
  scanf("%30[^\n]s", nome);
  scanf("*[^\n]");
  scanf("%*c");

  existe = verificar_existencia(produto, nome, qnt);

  if(existe != -1){
    printf("\nDigite a quantidade para retirar: ");
    scanf("%d", &qnt_item);
    
    estoque[existe] -= qnt_item;

    return;
  }
  
  erro(3);
  return;
}

void consultar_estoque(char produto[QNT_MAX_PROD][TAM_NOME], int qnt, int estoque[QNT_MAX_PROD]){
  system("clear || cls");
  printf("------------------Relatório-----------------\n");
  printf("   %s    %10s\n", "Produto", "Quantidade");

  for(int i = 0; i < qnt; i++){
    printf("\n%d: %s    %10d", i+1, produto[i], estoque[i]);
  }

  printf("\n------------------Relatório-----------------\n");
}

int verificar_existencia(char produto[QNT_MAX_PROD][TAM_NOME], char nome[TAM_NOME], int qnt){
  for (int i = 0; i < qnt; i++){
    if(!strcmp(produto[i], nome)) return i;
  }
  return -1;
}

void erro(int codigo_erro){
  switch (codigo_erro)
  {
  case 1:
    printf("\nNao eh possivel cadastrar:");
    printf("\nLimite do estoque alcancado!");
    break;
   case 2:
    printf("\nProduto ja cadastrado!\n");
    break;
  case 3:
    printf("\nProduto nao cadastrado!\n");
    break;
  case 4:
    printf("\nProduto nao encontrado!\n");
    break;
  case 5:
    printf("\nEstoque vazio!\n");
    break;
  }
}