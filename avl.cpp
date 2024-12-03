#include <iostream>
#include <locale>
using namespace std;

// Luigi Augusto Rovani RA 2266474
// Lucas Vinícius Zuque de Lima RA 2268710
// Maria Julia Leandro Leal da Rocha 

template <typename T>
class AVLNode {
public:
    T key;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(T k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class AVLTree {
public:
    AVLNode<T>* insert(AVLNode<T>* root, T key) {
        if (root == nullptr)
            return new AVLNode<T>(key);

        if (key < root->key)
            root->left = insert(root->left, key);
        else if (key > root->key)
            root->right = insert(root->right, key);
        else
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        return balanceTree(root, key);
    }

    void clearTree(AVLNode<T>*& root) {
        if (root == nullptr)
            return;

        clearTree(root->left);
        clearTree(root->right);

        delete root;
        root = nullptr;
    }

    void printTree(AVLNode<T>* root, int space = 0, int level_gap = 5) const {
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

    int getBalance(AVLNode<T>* node) const {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

private:
    int getHeight(AVLNode<T>* node) const {
        return node == nullptr ? 0 : node->height;
    }

    AVLNode<T>* balanceTree(AVLNode<T>* root, T key) {
        int balance = getBalance(root);

        if (balance > 1 && key < root->left->key) {
            cout << "RSD " << root->key << endl;
            return rightRotate(root);
        }

        if (balance < -1 && key > root->right->key) {
            cout << "RSE " << root->key << endl;
            return leftRotate(root);
        }

        if (balance > 1 && key > root->left->key) {
            cout << "RDD " << root->left->key << endl;
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && key < root->right->key) {
            cout << "RDE " << root->right->key << endl;
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* z) {
        AVLNode<T>* y = z->right;
        AVLNode<T>* T2 = y->left;

        y->left = z;
        z->right = T2;

        z->height = 1 + max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    AVLNode<T>* rightRotate(AVLNode<T>* z) {
        AVLNode<T>* y = z->left;
        AVLNode<T>* T3 = y->right;

        y->right = z;
        z->left = T3;

        z->height = 1 + max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }
};

int main() {
    setlocale(LC_ALL, "");

    AVLTree<int> tree;
    AVLNode<int>* root = nullptr;

    cout << "Use:\n 0 para obter o balanço e limpar a árvore \n -1 para sair \n -2 para printar a árvore" << endl;

    while (true) {

        cout << "\nDigite o valor que deseja inserir: ";
        int valor;
        cin >> valor;

        if (valor == 0) {
			cout << "Bal: " << tree.getBalance(root) << endl;
            tree.clearTree(root);
            cout << "Árvore limpa!\n";
        } else if (valor == -2) {
            tree.printTree(root);
		} else if (cin.fail() or valor == -1) {
            break;
        } else {
            root = tree.insert(root, valor);
        }
    }

    cout << "Fim" << endl;

    return 0;
}
