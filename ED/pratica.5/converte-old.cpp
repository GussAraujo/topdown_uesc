// Gustavo Araujo - 202210689
// João Dutterle - 202211138
// Pedro Elias - 202210359

#include <iostream>
#define TAMANHOPILHA 1000

using namespace std;

typedef struct pilha {
    char itens[TAMANHOPILHA];
    int tamanho;
} pilha;

bool empilhar(pilha *p, char obj) {
    bool ret = false;
    if(obj == '(' || obj == ')') return true;
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

bool ehOperador (char op){
    if (op == '+' || op == '-' || op == '*' || op == '/')
        return true;
    else return false;
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
    string express = "(A+B)-C/E+D";
    // (A(B-C)+/E)+D)

    // while (cin >> express) {
        char simb;
        int n = 0;
        pilha p;
        p.tamanho = 0;

        while (express.length() != n) {
          char aux;
          simb = express[n];
          if(ehOperador(simb)) {
            if(express[n+1] != '(' && express[n+1] != ')'){
              empilhar(&p, express[n+1]);
              empilhar(&p, simb);
              n++;
            } else {
              aux = simb;
            }
          } else if (simb == ')'){
            empilhar(&p, simb);
            empilhar(&p, aux);
          } else {
            empilhar(&p, simb);
          }
          n++;
        }
    // }

    return 0;
}