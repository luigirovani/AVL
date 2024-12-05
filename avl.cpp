#include <iostream>
#include <locale>


using namespace std;

// Luigi Augusto Rovani 
// Lucas Vinícius Zuque de Lima
// Maria Julia Leandro Leal da Rocha 

template <typename T>
class AVLTree {
private:
    class AVLNode {
    public:
        T key;
        int height;
        AVLNode* left;
        AVLNode* right;

        AVLNode(T k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    AVLNode* root;

    AVLNode* insertNode(AVLNode* node, T key) {
        
        if (node == nullptr)
            return new AVLNode(key);
        
        if (key < node->key) {
            node->left = insertNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = insertNode(node->right, key);
        } else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balanceTree(node, key);
    }

    AVLNode* balanceTree(AVLNode* root, T key) {
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

    int getHeight(AVLNode* node) const {
        return node == nullptr ? 0 : node->height;
    }

    int getBalance(AVLNode* node) const {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    void clearTree(AVLNode*& node) {
        if (node == nullptr)
            return;

        clearTree(node->left);
        clearTree(node->right);

        delete node;
        node = nullptr;
    }


    void printTree(AVLNode* node, int space = 0, int level_gap = 5) const {
        if (node == nullptr)
            return;

        space += level_gap;

        printTree(node->left, space);

        cout << endl;
        for (int i = level_gap; i < space; ++i)
            cout << " ";
        cout << node->key << "\n";

        printTree(node->right, space);
    }


public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {
        clearTree(root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void insert(T key) {
        root = insertNode(root, key);
    }

    void clear() {
        clearTree(root);
        cout << "Árvore limpa!\n";
    }

    void print() const {
        if isEmpty() {
            cout << "A árvore está vazia" << endl;
            return;
        }

        printTree(root);

    }
    

    int getBalance() const {
        return getBalance(root);
    }

    T getInput() {
        cout << "Digite o valor que deseja inserir: ";
        T input;
        cin >> input;

        if (cin.fail()) {
            cerr << "Valor inválido!\nEstancie uma árvore de outro tipo\n" << endl;
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
        cout << "Digite -2 para printar a árvore.\n";
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "");
    AVLTree<int> tree;

    tree.printTip();

    while (true) {
        auto input = tree.getInput();

        if (input == 0) {
			cout << "Bal= " << tree.getBalance() << endl;
            tree.clear();
        }
        else if (input == -1) {
            break;
        }
        else if (input == -2) {
            tree.print();
        }
        else {
            tree.insert(input);
        }
    }

    cout << "Fim" << endl;
    return 0;
}
