#include <bits/stdc++.h>
#define TAMANHOFILA 1000
typedef int obj_t;

using namespace std;

typedef struct Fila{
    obj_t itens[TAMANHOFILA];
    int inicio, fim;
    bool cheia, vazia;
}fila;

bool enfileirar(fila *p, obj_t obj) {
    bool ret = false;
    if(!p->cheia){
        p->itens[p->fim++] = obj;
        if(p->fim == TAMANHOFILA) p->fim = 0;
        if(p->inicio == p->fim) p->cheia = true;
        p->vazia=false;
        ret = true;
    }
    return ret;
}

bool desenfileirar(fila *p) {
    bool ret = false;
    obj_t max = 0;
    int posicaoMax = -1;
    int aux = 0;

    // Se a fila não for vazia
    if (!p->vazia) {
        // procura o maior valor e seu indice
        for(int i = p->inicio; i != p->fim; i = (i+1) % TAMANHOFILA){
            if(p->itens[i] > max){
                max = p->itens[i];
                posicaoMax = i;
            } 
        }
        // entra se indice for diferente de -1 (0 é um indice válido), ou seja, achou um um 'val'
        if(posicaoMax != -1) {
            // verifica se a fila só tem 1 elemento e remove ele
            if (posicaoMax == 0 && p->fim == 1) {
                p->vazia = true;
                p->cheia = false;
                p->inicio++;
            // se tiver mais que 1 elemento
            } else {
                // vai empurrar os elementos anteriores até chegar no indice encontrado e subsitui-lo tbm
                for(int i = 0; i < posicaoMax; i++){
                    if(i == 0) {
                        aux = p->itens[i+1];
                        p->itens[i+1] = p->itens[i];    
                    } else {
                        int aux2 = aux;
                        aux = p->itens[i+1];
                        p->itens[i+1] = aux2;
                    }
                }
                if (p->inicio == p->fim) p->vazia = true;
                p->cheia = false;
                ret = true;
                p->inicio++;
            }
        }
    }
   
    return ret;
}

void imprimir(fila *p){
    if (!p->vazia) {
        int i = p->inicio;
        do {
            cout << p->itens[i] << " ";
            i = (i + 1) % TAMANHOFILA;
        } while (i != p->fim);
        cout << endl;
    } else {
        cout << "*" << endl;
    }
}

int main(){
    int n;
    obj_t val;
    char opcao;

    while(cin >> n && n != 0){
        fila p;
        p.inicio = 0;
        p.fim = 0;
        p.cheia = false;
        p.vazia = true;
        int i = 0;
        while(i < n){
            cin >> opcao;

            switch (opcao){
            case 'E':
                // enfileira o 'val'
                cin >> val;
                enfileirar(&p, val);
                imprimir(&p);
                break;
            case 'D':
                // desenfileira o maior 'val' da fila
                desenfileirar(&p);
                imprimir(&p);
                break;
            default:
                break;
            }
            i++;
        }
        cout << endl;
    }


    return 0;
}