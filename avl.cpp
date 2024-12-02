#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <locale>
using namespace std;


// Luigi Augusto Rovani RA 2266474
// Lucas Vinícius Zuque de Lima RA 2268710
// Maria Julia Leandro Leal da Rocha 

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

        if (balance > 1 && key < root->left->key) {
            cout << "RSD" << root->key << endl;
            return rightRotate(root);
        }

        if (balance < -1 && key > root->right->key) {
            cout << "RSE" << root->key << endl;
            return leftRotate(root);
        }

        if (balance > 1 && key > root->left->key) {
            cout << "RDD" << root->left->key <<  endl;
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && key < root->right->key) {
            cout << "RDE" << root->right->key << endl;
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

    int getHeight(AVLNode* node) const {
        return node == nullptr ? 0 : node->height;
    }

    int getBalance(AVLNode* node) const {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

private:

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

    while (true) {
		cout << "Digite um valor para inserir na árvore: " << endl;
		int valor;
		cin >> valor;

        if (valor == 0) {
			auto balance = tree.getBalance(root);
			cout << "Bal: " << balance << endl;
            free(root);
        }

		if (cin.fail()) {
			cout << "Fim" << endl;
			free(root);
			break;
		}

        root = tree.insert(root, valor);
        cout << "\n--------------------------------\n";
    }

    return 0;
}
