#include <iostream>
#define MAX 10000
using namespace std;

struct Fila
{
    int itens[MAX];
    int fim = 0;
    int ini = 0;
};
bool ehVazia(Fila *f)
{
    return f->fim == f->ini ? true : false;
}
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
    int n, vet[MAX];

    while (cin >> n && n != 0)
    {
        Fila fila1, fila2;
        int num, i = 0, tam = 0;
        char op;
        while (n != 0)
        {
            cin >> op;
            if (op == 'E')
            {
                cin >> num;
                if (num >= 5000)
                {
                    enfileirar(&fila2, num);
                }
                else
                {
                    enfileirar(&fila1, num);
                }
            }
            else if (op == 'D')
            {
                if (ehVazia(&fila1))
                {
                    vet[i] = desinfileirar(&fila2);
                    i++;
                }
                else
                {
                    vet[i] = desinfileirar(&fila1);
                    i++;
                }
            }
            n--;
            tam = i;
        }
        for(int j = 0; j < i; j++){
            cout << vet[j] << " ";
        }
        cout << endl;
    }
    return 0;
}
