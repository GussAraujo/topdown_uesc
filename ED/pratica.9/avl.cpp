// Gustavo Araujo - 202210689
// João Dutterle - 202211138
// Pedro Elias - 202210359

#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node *insert(Node *root, int value)
{
    if (root == nullptr)
    {
        Node *newNode = new Node;
        newNode->data = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (value <= root->data)
    {
        root->left = insert(root->left, value);
    }
    else
    {
        root->right = insert(root->right, value);
    }

    return root;
}

void preOrderTraversal(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    cout << root->data << " ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void insertLeft(Node *node, int value)
{
    Node *newNode = new Node;
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    node->left = newNode;
}

void insertRight(Node *node, int value)
{
    Node *newNode = new Node;
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    node->right = newNode;
}

void rotateRight(Node **root)
{
    Node *p = (*root)->left;
    (*root)->left = p->right;
    p->right = (*root);
    (*root) = p;
}

void rotateLeft(Node **root)
{
    Node *p = (*root)->right;
    (*root)->right = p->left;
    p->left = (*root);
    (*root) = p;
}

int calculateHeight(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int alt = 0, he = 0, hd = 0;
    if (node->left != NULL)
        he = calculateHeight(node->left) + 1;
    if (node->right != NULL)
        hd = calculateHeight(node->right) + 1;
    alt = (he < hd) ? hd : he;
    return alt;
}

int fator(Node *raiz)
{
    int he = calculateHeight(raiz->left);
    int hd = calculateHeight(raiz->right);
    return he - hd;
}

bool ehBalanceada(Node *raiz)
{
    bool bal = true;
    if (raiz != NULL)
    {
        bal = (abs(fator(raiz)) <= 1);
        if (bal)
        {
            bal = bal && ehBalanceada(raiz->left);
            bal = bal && ehBalanceada(raiz->right);
        }
    }
    return bal;
}

void balancear(Node **raiz)
{
    if ((*raiz) != NULL)
    {
        while (!ehBalanceada(*raiz))
        {
            balancear(&((*raiz)->left));
            balancear(&((*raiz)->right));
            int fd = fator((*raiz));
            if (fd > 1)
            {
                if (fator((*raiz)->left) < 0)
                {
                    rotateLeft(&((*raiz)->left));
                    rotateRight(raiz);
                }
                else
                {
                    rotateRight(raiz);
                }
            }
            if (fd < -1)
            {
                if (fator((*raiz)->right) > 0)
                {
                    rotateRight(&((*raiz)->right));
                    rotateLeft(raiz);
                }
                else
                {
                    rotateLeft(raiz);
                }
            }
        }
    }
}

void freeTree(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main()
{
    int n;
    while (cin >> n)
    {
        Node *root = nullptr;
        for (int i = 0; i < n; i++)
        {
            int value;
            cin >> value;
            root = insert(root, value);
            balancear(&root);
        }
        preOrderTraversal(root);
        cout << endl;

        freeTree(root);
    }

    return 0;
}
