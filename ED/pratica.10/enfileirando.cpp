#include <iostream>
#define TAMANHOFILA 100000
using namespace std;

typedef struct heapfila
{
    int itens[TAMANHOFILA];
    int fim;
} heapfila;

void enfileirar(heapfila *p, int item)
{
    int i = 0;

    if (p->fim != TAMANHOFILA)
    {
        p->itens[p->fim++] = item;
        i = p->fim;
        while ((i > 1) && (p->itens[i - 1] > p->itens[i / 2 - 1]))
        {
            swap(p->itens[i - 1], p->itens[i / 2 - 1]);
            i /= 2;
        }
    }
    return;
}

int desenfileirar(heapfila *p)
{
    int i = 1, max = 1;
    int o;
    o = p->itens[0];
    p->itens[0] = p->itens[--p->fim];
    bool para = false;
    while (!para)
    {
        if (((2 * i) <= p->fim) && (p->itens[i - 1] < p->itens[2 * i - 1]))
            max = 2 * i;
        if (((2 * i + 1) <= p->fim) && (p->itens[max - i] < p->itens[2 * i]))
            max = 2 * i + 1;
        if (i != max)
        {
            int aux;
            aux = p->itens[i - 1];
            p->itens[i - 1] = p->itens[max - 1];
            p->itens[max - 1] = aux;
            i = max;
        }
        else
            para = true;
    }
    return o;
}

int main()
{
    int n = 0, val, rem;
    char op;

    while (cin >> n && n != 0)
    {
        heapfila fila;
        fila.fim = 0;

        for (int i = 0; i < n; i++)
        {
            cin >> op;
            if (op == 'E')
            {
                cin >> val;
                enfileirar(&fila, val);
                for (int j = 0; j < fila.fim; j++)
                {
                    cout << fila.itens[j] << " ";
                }
                cout << endl;
            }
            else if (op == 'D')
            {
                rem = desenfileirar(&fila);
                cout << rem << endl;
            }
        }
        cout << endl;
    }

    return 0;
}