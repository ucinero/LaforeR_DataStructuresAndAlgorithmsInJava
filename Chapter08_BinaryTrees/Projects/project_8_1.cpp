// project_8_1.cpp

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Node;

class Stack {
    private:
        int maxSize;
        Node** stackArray;
        int top;
    public:
        Stack(int s) {
            maxSize = s;
            stackArray = new Node*[maxSize];
            top = -1;
        }
        ~Stack() {
            delete[] stackArray;
        }
        void push(Node* j) {
            stackArray[++top] = j;
        }
        Node* pop() {
            return stackArray[top--];
        }
        Node* peek() const {
            return stackArray[top];
        }
        bool isEmpty() const {
            return top == -1;
        }
        bool isFull() const {
            return top == maxSize - 1;
        }
};

class Node {
    public:
        char cData;
        Node* leftChild;
        Node* rightChild;
    public:
        Node(char cd) : cData(cd), leftChild(nullptr), rightChild(nullptr) {}
        void displayNode() const {
            cout << cData;
        }
};

class Tree {
    private:
        Node* root;
    private:
        void preOrder(Node* localRoot) const {
            if (localRoot != nullptr) {
                cout << localRoot->cData << " ";
                preOrder(localRoot->leftChild);
                preOrder(localRoot->rightChild);
            }
        }
        void inOrder(Node* localRoot) const {
            if (localRoot != nullptr) {
                inOrder(localRoot->leftChild);
                cout << localRoot->cData << " ";
                inOrder(localRoot->rightChild);
            }
        }
        void postOrder(Node* localRoot) const {
            if (localRoot != nullptr) {
                postOrder(localRoot->leftChild);
                postOrder(localRoot->rightChild);
                cout << localRoot->cData << " ";
            }
        }
        void destroy(Node* localRoot) {
            if (localRoot != nullptr) {
                destroy(localRoot->leftChild);
                destroy(localRoot->rightChild);
                delete localRoot;
            }
        }
    public:
        Tree() : root(nullptr) {}
        Tree(Node* root_Node) : root(root_Node) {}
        ~Tree() {
            destroy(root);
        }
        Node* getRoot() {
            return root;
        }
        void setRoot(Node* node) {
            root = node;
        }
        void traverse(int traverseType) const {
            switch (traverseType) {
                case 1: cout << "\nPreorder traversal: ";
                        preOrder(root);
                        break;
                case 2: cout << "\nInorder traversal: ";
                        inOrder(root);
                        break;
                case 3:
                    cout << "\nPostorder traversal: ";
                        postOrder(root);
                        break;
            }
            cout << endl;
        }
        void displayTree() const {
            Stack* globalStack = new Stack(1024);
            globalStack->push(root);
            int nBlanks = 32;
            bool isRowEmpty = false;
            cout << "......................................................" << endl;

            while (isRowEmpty == false) {
                Stack* localStack = new Stack(2048);
                isRowEmpty = true;
                for (int j = 0; j < nBlanks; j++)
                    cout << ' ';

                while (globalStack->isEmpty() == false) {
                    Node* temp = globalStack->pop();
                    if (temp != nullptr) {
                        temp->displayNode();
                        localStack->push(temp->leftChild);
                        localStack->push(temp->rightChild);

                        if (temp->leftChild != nullptr || temp->rightChild != nullptr)
                            isRowEmpty = false;
                    }
                    else {
                        cout << "--";
                        localStack->push(nullptr);
                        localStack->push(nullptr);
                    }
                    for (int j = 0; j < nBlanks * 2 - 2; j++)
                        cout << ' ';
                }
                cout << endl;
                nBlanks /= 2;
                while (localStack->isEmpty() == false)
                    globalStack->push(localStack->pop());
                delete localStack;
            }
            cout << "......................................................";
            delete globalStack;
        }
};

int main() {
    string str;

    cout << "Enter a string: ";
    cin >> str;

    if (str.empty()) {
        cout << "Empty string!" << endl;
        return 0;
    }

    reverse(str.begin(), str.end());
    int n = str.size();

    vector<Tree*> tree_vector;
    
    for (int i = 0; i < n; i++) {
        Node* newNode = new Node(str[i]);
        Tree* newTree = new Tree(newNode);
        tree_vector.push_back(newTree);
    }

    while (tree_vector.size() != 1) {
        char ch = '+';
        Node* newNode = new Node(ch);
        Tree* newTree = new Tree(newNode);

        Tree* left_tree = tree_vector.back();
        tree_vector.pop_back();

        Tree* right_tree = tree_vector.back();
        tree_vector.pop_back();

        Node* lroot = left_tree->getRoot();
        Node* rroot = right_tree->getRoot();
        newTree->getRoot()->leftChild = lroot;
        newTree->getRoot()->rightChild = rroot;

        left_tree->setRoot(nullptr);
        right_tree->setRoot(nullptr);

        tree_vector.push_back(newTree);

        delete left_tree;
        delete right_tree;
    }

    cout << "the size of tree_vector is " << tree_vector.size() << endl;
    tree_vector[0]->displayTree();

    delete tree_vector[0];

    return 0;
}