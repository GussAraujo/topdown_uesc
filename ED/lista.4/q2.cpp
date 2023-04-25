#include <iostream>
using namespace std;

template <class T>
class Pilha
{
    class item
    {
    public:
        T val;
        item *prox;

        item() {
            prox = NULL;
        }
        item(T val) : val(val) {
            prox = NULL;
        }
    };

private:
    item *noTopo;

public:
    Pilha();
    void empilhar(T obj);
    void desempilhar();
    T topo();
    bool ehvazia();
    int tamanho();
    bool estaCheio();
    void imprimir();
    void obterStrings();
    void stringValida(string val);
};

template <class T>
Pilha<T>::Pilha()
{
    noTopo = NULL;
}

template <class T>
bool Pilha<T>::estaCheio()
{
    item *no;

    try
    {
        no = new item;
        delete no;
        return false;
    }
    catch (bad_alloc exception)
    {
        return true;
    }
}

template <class T>
void Pilha<T>::imprimir()
{
    item *noTemporario = noTopo;

    while (noTemporario != NULL)
    {
        cout << noTemporario->val << " ";
        noTemporario = noTemporario->prox;
    }
}

template <class T>
void Pilha<T>::empilhar(T obj)
{
    item *noNovo = new item(obj);
    noNovo->prox = noTopo;
    noTopo = noNovo;
    return;
}

template <class T>
void Pilha<T>::desempilhar()
{
    item *noTemporario = noTopo;
    if (noTopo)
    {
        noTopo = noTopo->prox;
        delete noTemporario;
    }

    return;
}

template <class T>
T Pilha<T>::topo()
{
    T val = 0;
    if (noTopo)
        val = noTopo->val;
    return val;
}

template <class T>
bool Pilha<T>::ehvazia()
{
    return (noTopo ? false : true);
}

template <class T>
int Pilha<T>::tamanho()
{
    item *p = noTopo;
    int cont = 0;
    while (p)
    {
        p = p->prox;
        cont++;
    }
    return cont;
}

template <class T>
void Pilha<T>::obterStrings()
{
    item *aux = noTopo;
    string value;

    while (aux)
    {
        stringValida(aux->val);
        aux = aux->prox;
    }

}

template <class T>
void Pilha<T>::stringValida(string val)
{
    int tam = val.length() / 2, cont = 0;
    char vet[tam];
    char vet2[tam];
    bool segundoVetor = false;
    for (int i = 0, x = 0; i < val.length(); i++)
    {
        if (segundoVetor)
        {
            vet2[x] = val[i];
            x++;
        }
        if (val[i] != 'C')
        {
            vet[i] = val[i];
        }
        else if (val[i] == 'C')
        {
            segundoVetor = true;
        }
    }

    for (int i = 0, x = tam - 1; i < tam; i++, x--)
    {
        if (vet[x] == vet2[i])
            cont++;
    }

    if (cont == tam)
    {
        cout << "String valida!\n";
    }
    else
    {
        cout << "String invalida!\n";
    }
}

int main()
{
    Pilha<string> p;
    // p.empilhar("AAAAABBCBBAAAAA");
    p.empilhar("ABBCBBA");
    p.obterStrings();
    return 0;
}
