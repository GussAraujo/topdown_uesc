#include <bits/stdc++.h>

using namespace std;

class Pilha{
    class item{
    public:
        char val;
        item *prox;

        item() { prox = NULL; }
        item(char val) : val(val) { prox = NULL; }
    };

    private:
    item *noTopo;

    public:
        void empilhar(char obj);
        void desempilhar();
        char topo();
        bool ehvazia();
        void imprimir();    
        bool validaExpressao(string exp);  
        bool complemento(char c1, char c2);
};

bool Pilha::ehvazia(){
    return (noTopo ? false : true);
}

char Pilha::topo(){
    char val = ' ';
    if (noTopo)
        val = noTopo->val;
    return val;
}

void Pilha::empilhar(char obj){
    item *noNovo = new item(obj);
    noNovo->prox = noTopo;
    noTopo = noNovo;
    return;
}

void Pilha::desempilhar(){
    item *noTemporario = noTopo;
    if (noTopo)
    {
        noTopo = noTopo->prox;
        delete noTemporario;
    }

    return;
}

void Pilha::imprimir(){
    item *noTemporario = noTopo;

    while (noTemporario != NULL)
    {
        cout << noTemporario->val << " ";
        noTemporario = noTemporario->prox;
    }
}

bool Pilha::complemento(char c1, char c2) {
    return ((c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']') || (c1 == '{' && c2 == '}'));
}


bool Pilha::validaExpressao(string exp){
  int n = 0;
    bool valid = true;
    Pilha p;

    for(char simb : exp){
        if(simb == '(' || simb == '{' || simb == '[') {
            p.empilhar(simb);
        }
        else if(simb == ')' || simb == '}' || simb == ']'){
            if(p.ehvazia()){
                valid = false;
                break;
            } else{
              char s = p.topo();
              p.desempilhar();
              if(!complemento(s, simb)){
                  valid = false;
                  break;
              }
          }
        }
        n++;
    }
    if(p.ehvazia()){
        valid = false;
    }
    return valid;
}

int main(){
    Pilha p;

    string exp1 = "{[(5x7)/5]x4-[(5x7)x2]}/(3x6)";
    string exp2 = "{2+[(16+2∧3)-4)}*3";

    if(p.validaExpressao(exp1)){
        cout << "Parentizacao correta na expressao 1" << endl;
    }else{
        cout << "Parentizacao incorreta na expressao 1" << endl;
    }

    if (p.validaExpressao(exp2)) {
        cout << "Parentizacao correta na expressao 2" << endl;
    } else {
        cout << "Parentizacao incorreta na expressao 2" << endl;
    }

    return 0;
}