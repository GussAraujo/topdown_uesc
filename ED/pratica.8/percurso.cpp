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
    if (*raiz == NULL)
    {
        *raiz = createNode(value);
    }
    else
    {
        if (value < (*raiz)->value)
        {
            insert(&((*raiz)->left), value);
        }
        else
        {
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

int main()
{
    int n, valor;

    while (cin >> n)
    {
        Arvore *raiz = NULL;
        for (int i = 0; i < n; i++)
        {
            cin >> valor;
            insert(&raiz, valor);
        }
        printPreOrder(raiz);
        cout << endl;
        printPostOrder(raiz);
        cout << endl << endl;
    }

    return 0;
}
