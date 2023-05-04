// Gustavo Araujo - 202210689
// João Dutterle - 202211138
// Pedro Elias - 202210359

#include <iostream>
#define TAMANHOPILHA 1000

using namespace std;

typedef struct pilha {
    long long int itens[TAMANHOPILHA];
    int tamanho;
} pilha;

bool empilhar(pilha *p, long long int obj) {
    bool ret = false;
    if(p->tamanho  < TAMANHOPILHA) {
        p->itens[p->tamanho++] = obj;
        ret = true;
    }
    return ret;
}

bool desempilhar(pilha *p) {
    bool result = false;
    if(p->tamanho > 0) {
        p->tamanho--;
        result = true;
    }
    return result;
}

long long int topo(pilha p) {
    long long int val = 0;
    if (p.tamanho > 0) {
        val = p.itens[p.tamanho-1];
        return val;
    }
}

int main() {
    int n;
    string inst;

    while (cin >> n && n != 0) {
        pilha p;
        p.tamanho = 0;
        while (n != 0) {
            cin >> inst;
            if (inst == "BIPUSH") {
                long long int x;
                cin >> x; 
                empilhar(&p, x);
            } else if (inst == "ISUB") {
                long long int a = topo(p);
                desempilhar(&p);
                long long int b = topo(p);
                desempilhar(&p);
                empilhar(&p, (a - b));
            } else if (inst == "IMUL") {
                long long int a = topo(p);
                desempilhar(&p);
                long long int b = topo(p);
                desempilhar(&p);
                empilhar(&p, (a * b));
            } else if (inst == "IADD") {
                long long int a = topo(p);
                desempilhar(&p);
                long long int b = topo(p);
                desempilhar(&p);
                empilhar(&p, (a + b));
            }
            n--;
        }
        cout << topo(p) << endl;
    }

    return 0;
}
