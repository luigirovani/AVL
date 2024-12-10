// Luigi Augusto Rovani 
// Lucas Vinícius Zuque de Lima
// Maria Julia Leandro Leal da Rocha 

#include <iostream>
#include <memory>
#include <algorithm>
#include <typeinfo>
#include <limits>
#include <locale>


using namespace std;

template <typename T>
class AVLTree {
private:
    class Node {
    public:
        T key;
        int height;
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        Node(T k)
            : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    using NodePtr = unique_ptr<Node>;
    NodePtr root;

    NodePtr insertNode(NodePtr node, T key) {
        if (!node)
            return make_unique<Node>(key);

        if (key < node->key) {
            node->left = insertNode(move(node->left), key);
        }
        else if (key > node->key) {
            node->right = insertNode(move(node->right), key);
        }
        else {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balanceTree(move(node), key);
    }

    NodePtr balanceTree(NodePtr node, T key) {
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) {
            cout << "RSD " << node->key << endl;
            return rightRotate(move(node));
        }

        if (balance > 1 && key > node->left->key) {
            cout << "RDD " << node->left->key << endl;
            node->left = leftRotate(move(node->left));
            return rightRotate(move(node));
        }

        if (balance < -1 && key > node->right->key) {
            cout << "RSE " << node->key << endl;
            return leftRotate(move(node));
        }

        if (balance < -1 && key < node->right->key) {
            cout << "RDE " << node->right->key << endl;
            node->right = rightRotate(move(node->right));
            return leftRotate(move(node));
        }

        return node;
    }

    NodePtr leftRotate(NodePtr z) {
        auto y = move(z->right);
        z->right = move(y->left);
        y->left = move(z);

        y->left->height = 1 + max(getHeight(y->left->left), getHeight(y->left->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    NodePtr rightRotate(NodePtr z) {
        auto y = move(z->left);
        z->left = move(y->right);
        y->right = move(z);

        y->right->height = 1 + max(getHeight(y->right->left), getHeight(y->right->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    int getHeight(const NodePtr& node) const {
        return node ? node->height : 0;
    }

    int getBalance(const NodePtr& node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void printTree(const NodePtr& node, int space = 0, int level_gap = 5) const {
        if (!node)
            return;

        space += level_gap;

        printTree(node->right, space);

        cout << endl;
        for (int i = level_gap; i < space; ++i)
            cout << " ";
        cout << node->key << "\n";

        printTree(node->left, space);
    }

public:
    AVLTree() : root(nullptr) {}

    bool isEmpty() const {
        return !root;
    }

    void print() const {
        if (isEmpty()) {
            cout << "A árvore está vazia" << endl;
            return;
        }
        printTree(root);
    }

    int getBalance() const {
        return getBalance(root);
    }

    void insert(T key) {
        root = insertNode(move(root), key);
    }

    void clear() {
        root.reset();
        cout << "Árvore Limpa!\n";
    }

    T getInput() {
        T input;
        cin >> input;

        if (cin.fail()) {
            cerr << "Valor inválido!\nCrie uma árvore com outro tipo de dado.\n" << endl;
            printTip();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return getInput();
        }

        cout << endl;
        return input;
    }

    void printTip() const {
        cout << "Digite um valor do tipo <" << typeid(T).name() << "> para inserir na árvore.\n";
        cout << "Digite 0 para limpar a árvore.\n";
        cout << "Digite -1 para sair.\n";
        cout << "Digite -2 para imprimir a árvore.\n";
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "");
    AVLTree<int> tree;

    while (true) {
        auto input = tree.getInput();

        if (input > 0)
            tree.insert(input);
        else if (input == 0) {
            cout << "Bal = " << tree.getBalance() << endl;
            tree.clear();
        }
        else if (input == -1)
            break;
        else if (input == -2)
            tree.print();
        else
            tree.printTip();
    }

    cout << "Fim" << endl;
    return 0;
}
