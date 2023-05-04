#include <iostream>

using namespace std;

typedef struct vetor {
  int key = 0;
  int address[100000];
} vetor;

void inserir(vetor vet, int x) {
  vet->address[vet->key++] = x;
}

int main(int argc, char const *argv[])
{
  vetor vet;
  inserir(vet, 10);

  return 0;
}
