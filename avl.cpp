#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <locale>
using namespace std;


// Luigi Augusto Rovani RA 2266474
// PEDRO HENRIQUE TAGATA FERREIRA ra 1884476
// 

class AVLNode {
public:
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    AVLNode* insert(AVLNode* root, int key) {
        if (root == nullptr)
            return new AVLNode(key);

        if (key < root->key)
            root->left = insert(root->left, key);
        else if (key > root->key)
            root->right = insert(root->right, key);
        else
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);
		cout << "Balanço:  " << balance << endl;

        if (balance > 1 || balance < -1) {
            cout << "Nó desbalanceado encontrado: " << root->key << " com balanceamento " << balance << endl;
        }

        if (balance > 1 && key < root->left->key) {
            cout << "Rotação à direita em " << root->key << endl;
            return rightRotate(root);
        }

        if (balance < -1 && key > root->right->key) {
            cout << "Rotação à esquerda em " << root->key << endl;
            return leftRotate(root);
        }

        if (balance > 1 && key > root->left->key) {
            cout << "Rotação à esquerda em " << root->left->key << " e depois à direita em " << root->key << endl;
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && key < root->right->key) {
            cout << "Rotação à direita em " << root->right->key << " e depois à esquerda em " << root->key << endl;
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void printTree(AVLNode* root, int space = 0, int level_gap = 5) const {
        if (root == nullptr)
            return;

        space += level_gap;
        printTree(root->right, space);

        cout << endl;
        for (int i = level_gap; i < space; ++i)
            cout << " ";
        cout << root->key << "\n";

        printTree(root->left, space);
    }

private:
    int getHeight(AVLNode* node) const {
        return node == nullptr ? 0 : node->height;
    }

    int getBalance(AVLNode* node) const {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    AVLNode* leftRotate(AVLNode* z) {
        AVLNode* y = z->right;
        AVLNode* T2 = y->left;

        y->left = z;
        z->right = T2;

        z->height = 1 + max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    AVLNode* rightRotate(AVLNode* z) {
        AVLNode* y = z->left;
        AVLNode* T3 = y->right;

        y->right = z;
        z->left = T3;

        z->height = 1 + max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }
};

int main() {

    setlocale(LC_ALL, "");

    AVLTree tree;
    AVLNode* root = nullptr;

    int sequence[] = { 70, 60, 40, 20, 65, 50, 10, 25, 28, 27, 75, 62 };
    int n = sizeof(sequence) / sizeof(sequence[0]);

    for (int i = 0; i < n; ++i) {
        root = tree.insert(root, sequence[i]);
        cout << "Arvore depois da insercao de " << sequence[i] << ":\n";
        tree.printTree(root);
        cout << "\n--------------------------------\n";
    }

    while (true) {
		cout << "Digite um valor para inserir na árvore: " << endl;
		int valor;
		cin >> valor;

		if (cin.fail()) {
			cout << "Encerrado" << endl;
			break;
		}

        root = tree.insert(root, valor);
        tree.printTree(root);
        cout << "\n--------------------------------\n";
    }

    return 0;
}
