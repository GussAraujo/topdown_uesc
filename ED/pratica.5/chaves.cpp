// Gustavo Araujo - 202210689
// João Dutterle - 202211138
// Pedro Elias - 202210359

#include <iostream>
#define TAMANHOPILHA 10000

using namespace std;

typedef struct pilha {
    char itens[TAMANHOPILHA];
    int tamanho;
} pilha;

bool empilhar(pilha *p, int obj) {
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

char topo(pilha p) {
    char val = ' ';
    if (p.tamanho > 0) val = p.itens[p.tamanho-1];
    
    return val;
}

bool complemento (char a, char b) {
    if(a == '(' && b == ')') return true;
    if(a == '[' && b == ']') return true;
    if(a == '{' && b == '}') return true;

    return false;
}

bool ehvazia(pilha p) {
    return p.tamanho ? false : true;
}

int main() {
    string express;
    while (cin >> express) {
        char simb;
        int n = 0;
        bool valid = true;
        pilha p;
        p.tamanho = 0;
        while (express.length() != n) {
        simb = express[n];
        if (simb == '[' || simb == '{' && express[n-1] != '\\') {
            empilhar(&p, simb);
        } else if (simb == ']' || simb == '}' && express[n-1] != '\\') {
            if(ehvazia(p)) valid = false;
            else {
                char top = topo(p);
                if(!complemento(top, simb)) valid = false;
                else desempilhar(&p);
            }
        }
        n++;
        }
        if (!ehvazia(p)) valid = false;

        if(valid) cout << "SIM" << endl;
        else cout << "NAO" << endl;
    }

    return 0;
}