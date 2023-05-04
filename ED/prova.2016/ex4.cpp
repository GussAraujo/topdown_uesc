typedef struct fila {
  int obj[100000];
  int peso;
  int inicio = 0, fim = 0;
} fila;

int enfileirar(fila *f, int valor) {  
  f->obj[f->fim++] = valor; 
  f.peso += valor;
  return f.peso;
}