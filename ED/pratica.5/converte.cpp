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

bool empilhar(pilha *p, char obj) {
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

bool ehOperador (char op){
    if (op == '+' || op == '-' || op == '*' || op == '/')
        return true;
    else return false;
}

int prioridade(char c, char t){
    int pc, pt;
  
    if(c == '^')
      pc = 4;
    else if(c == '*' || c == '/')
      pc = 2;
    else if(c == '+' || c == '-')
      pc = 1;
    else if(c == '(')
      pc = 4;
  
    if(t == '^')
      pt = 3;
    else if(t == '*' || t == '/')
      pt = 2;
    else if(t == '+' || t == '-')
      pt = 1;
    else if(t == '(')
      pt = 0;
  
    return (pc > pt);
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
      char simb, t;
      int n = 0;
      pilha p;
      p.tamanho = 0;

      empilhar(&p, '(');
      do {
        simb = express[n];
        if(simb >= 'A' && simb <= 'Z') {
          cout << simb;
        }
        else if (simb == '(') empilhar(&p, simb);
        else if (simb == ')' || simb == '\0'){
          do {
            t = topo(p);
            desempilhar(&p);
            if (t != '(') {
              cout << t;
            }
          } while (t != '(');
        } else if (ehOperador(simb)) {
          while (1) {
            t = topo(p);
            desempilhar(&p);
            if (prioridade(simb, t)) {
              empilhar(&p, t);
              empilhar(&p, simb);
              break;
            } else {
              cout << t;
            }
          }
        }
        n++;
      } while (simb != '\0');
      cout << endl;
    }

    return 0;
}