// Gustavo Araujo - 202210689
// João Dutterle - 202211138
// Pedro Elias - 202210359

#include <iostream>
using namespace std;

struct Arvore
{
    int value;
    Arvore *left;
    Arvore *right;
};

Arvore *createNode(int value)
{
    Arvore *newNode = new Arvore;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(Arvore **raiz, int value)
{
    if (*raiz == NULL) {
        *raiz = createNode(value);
    }
    else {
        if (value <= (*raiz)->value) {
            insert(&((*raiz)->left), value);
        }
        else {
            insert(&((*raiz)->right), value);
        }
    }
}

void printInOrder(Arvore *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    printInOrder(raiz->left);
    cout << raiz->value << " ";
    printInOrder(raiz->right);
}

void printPreOrder(Arvore *root)
{
    if (root == NULL)
    {
        return;
    }

    cout << root->value << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(Arvore *root)
{
    if (root == NULL)
    {
        return;
    }

    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << root->value << " ";
}

int altura(Arvore *root) {
  int alt=-1, he, hd;
  if(root != NULL) {
    he = altura(root->left)+1;
    hd = altura(root->right)+1;
    alt = (he < hd) ? hd : he;
  }
  return alt;
}


int fator(Arvore *raiz) {
    int he = altura(raiz->left);
    int hd = altura(raiz->right);
    return he - hd;
}

bool ehBalanceada(Arvore *raiz) {
    bool bal = true;
    if (raiz != NULL) {
        bal = (abs(fator(raiz)) <= 1);
        if (bal) {
            bal = bal && ehBalanceada(raiz->left);
            bal = bal && ehBalanceada(raiz->right);
        }
    }
    return bal;
}

int main()
{
    int n, valor;

    while (cin >> n) {
        Arvore *raiz = NULL;
        for (int i = 0; i < n; i++) {
            cin >> valor;
            insert(&raiz, valor);
        }

        if (ehBalanceada(raiz))
            cout << "SIM" << endl;
        else
            cout << "NAO" << endl;
    }

    return 0;
}