// Gustavo Araujo - 202210689
// João Dutterle - 202211138
// Pedro Elias - 202210359

#include <iostream>
#include <math.h>
#define TAMANHOPILHA 10000

using namespace std;

typedef struct pilha {
    double itens[TAMANHOPILHA];
    int tamanho;
} pilha;

bool empilhar(pilha *p, double obj) {
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

double topo(pilha p) {
    double val = 0;
    if (p.tamanho > 0) val = p.itens[p.tamanho-1];
    
    return val;
}

bool ehOperador (string op){
    if (op[0] == '+' || op[0] == '-' || op[0] == '*' || op[0] == '/' || op[0] == '^')
        return true;
    else return false;
}

double calcular(double a, double b, string op) {
    switch (op[0]) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        default:
            break;
    }

    return 0;
}

bool ehvazia(pilha p) {
    return p.tamanho ? false : true;
}

int main() {
    bool valid = true;
    pilha p;
    p.tamanho = 0;

    char simb;
    int n;
    string num;

    while (cin >> n && n != 0) {
      for (int i = 0; i < n; i++) {
        cin >> num;
        if(num.size() > 1){
            if(num[0] == '-'){
                empilhar(&p, stof(num));
            } else {
                empilhar(&p, stof(num));
            }
        } else if (!ehOperador(num)) {
          empilhar(&p, stof(num));
        } else {
          double a = topo(p);
          desempilhar(&p);
          double b = topo(p);
          desempilhar(&p);

          empilhar(&p, calcular(b, a, num));
        }
      }
      printf("%.3f\n", topo(p));
    }

    return 0;
}