#include <iostream>
#define MAX 10000
using namespace std;

struct Fila
{
    int itens[MAX];
    int fim = 0;
    int ini = 0;
};

void enfileirar(Fila *f, int item)
{
    if (f->fim == MAX)
    {
        cout << "fila cheia" << endl;
        return;
    }

    f->itens[f->fim] = item;
    f->fim++;
}

int desinfileirar(Fila *f)
{
    if (f->fim == f->ini)
    {
        cout << "Fila vaiza" << endl;
        return 0;
    }
    f->ini++;
    return f->itens[f->ini - 1];
}

void listarFila(Fila *fila)
{
    if (fila->ini == fila->fim)
    {
        cout << "*" << std::endl;
        return;
    }
    for (int i = fila->ini; i < fila->fim; i++)
    {
        cout << fila->itens[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n;

    while (cin >> n && n != 0)
    {
        Fila fila;
        int num;
        char op;
        while (n != 0)
        {
            cin >> op;
            if (op == 'E')
            {
                cin >> num;
                enfileirar(&fila, num);
                listarFila(&fila);
            }
            else if (op == 'D')
            {
                desinfileirar(&fila);
                listarFila(&fila);
            }
            n--;
        }
    }
    return 0;
}
