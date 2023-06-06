#include <iostream>

using namespace std;

int pai(int index) {
    return (index - 1) / 2;
}

int filhoEsquerda(int index) {
    return (2 * index) + 1;
}

int filhoDireita(int index) {
    return (2 * index) + 2;
}

void maxHeapify(int heap[], int tamanho, int index) {
    int maior = index;
    int esquerda = filhoEsquerda(index);
    int direita = filhoDireita(index);

    if (esquerda < tamanho && heap[esquerda] > heap[maior])
        maior = esquerda;

    if (direita < tamanho && heap[direita] > heap[maior])
        maior = direita;

    if (maior != index)
    {
        swap(heap[index], heap[maior]);
        maxHeapify(heap, tamanho, maior);
    }
}

void imprimirHeap(const int heap[], int tamanho) {
    if (tamanho == 0)
    {
        cout << "A heap estÃ¡ vazia!" << endl;
        return;
    }

    for (int i = 0; i < tamanho; i++)
    {
        cout << heap[i] << " ";
    }
    cout << endl;
}

int main() {
    int n = 0;

    while (cin >> n)
    {
        int heap[n];
        for (int i = 0; i < n; i++)
        {
            cin >> heap[i];
        }
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            maxHeapify(heap, n, i);
        }

        imprimirHeap(heap, n);
    }

    return 0;
}