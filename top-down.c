#include <stdio.h>
#include <string.h>

void monstrar_menu();
int obter_opcao();
void erro(int codigo_erro);
int cadastrar_produto(char produto[1000][30], int qnt_produto, int qnt_estoque);
int adicionar_estoque(char produto[1000][30], char estoque[1000][30], int qnt, int qnt_estoque);
void consultar_estoque(char estoque[1000][30], int qnt);
int verificar_existencia(char produto[1000][30], char nome[30], int qnt);
int remove_estoque(char estoque[1000][30], int qnt);

int main(){
  char produto[1000][30], estoque[1000][30];
  int qnt_produto = 0, opcao, qnt_estoque = 0, loop = 1;
  
  while(loop){
    printf("Estoque de parafusos...\n\n");
    monstrar_menu();

    opcao = obter_opcao();

    switch (opcao) {
    case 1:
      qnt_produto = cadastrar_produto(produto, qnt_produto, qnt_estoque);
      break;
    case 2:
      consultar_estoque(estoque, qnt_estoque);
      break;
     case 3:
      qnt_estoque = adicionar_estoque(produto, estoque, qnt_produto, qnt_estoque);
      break;
    case 4:
      qnt_estoque = remove_estoque(estoque, qnt_estoque);
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
  printf("2 - Consultar Estoque\n");
  printf("3 - Adionar Produto no Estoque\n");
  printf("4 - Remover Produto no Estoque\n");
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

int cadastrar_produto(char produto[1000][30], int qnt, int qnt_estoque){
  int sair = 0, i = 0;
  char nome[30];

  qnt = 0;

  while(!sair){
    if(qnt_estoque == 1000){
      erro(1);
      return qnt;
    } else {
      printf("Digite o nome do produto: ");
      scanf("%30[^\n]s", nome);
      scanf("*[^\n]");
      scanf("%*c");

      int existe = verificar_existencia(produto, nome, qnt);

      if(existe){
        erro(2);
      } else {
        strcpy(produto[i], nome);

        printf("\nProduto adicionado: %s\n", produto[i]);
        qnt++;
      
        printf("Adicionar outro produto? (1 - nao, 0 - sim): ");
        scanf("%d", &sair);
        scanf("*[^\n]");
        scanf("%*c");

        i++;
      }
    }
  }

  return qnt;
}

int adicionar_estoque(char produto[1000][30], char estoque[1000][30], int qnt, int qnt_estoque){
  if(qnt == 0) erro(4);

  printf("\n%s\n", produto[0]);
  int total = qnt_estoque;
  for (int i = qnt_estoque, j = 0; i < (qnt_estoque + qnt); i++, j++){
    strcpy(estoque[i], produto[j]);
    total++;
  }

  return total;
}

void consultar_estoque(char estoque[1000][30], int qnt){
  if(qnt == 0) erro(5);

  printf("Estoque (%d):\n", qnt);
  for (int i = 0; i < qnt; i++){
    printf("%s\n", estoque[i]);
  }
}

int remove_estoque(char estoque[1000][30], int qnt){
  char nome[30];

  printf("Digite o nome do produto para ser removido: ");
  scanf("%30[^\n]s", nome);
  scanf("*[^\n]");
  scanf("%*c");

  for (int i = 0; i < qnt; i++){
    if(!strcmp(estoque[i], nome)) {
      strcpy(estoque[i], estoque[i+1]);
      qnt--;

      return qnt;
    }
  }

  erro(3);
  return qnt;
}

int verificar_existencia(char produto[1000][30], char nome[30], int qnt){
  int existe = 0;

  for (int i = 0; i < qnt; i++){
    if(!strcmp(produto[i], nome)) existe = 1;
  }

  return existe;
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
  case 4:
    printf("\nEstoque vazio!\n");
    break;
  }
}