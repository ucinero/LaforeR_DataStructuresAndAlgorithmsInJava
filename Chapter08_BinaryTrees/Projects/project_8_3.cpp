// project_8_3.cpp

// tree.cpp

#include <iostream>
#include <string>
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
            cout << cData << " ";
        }
};

class Tree {
    private:
        Node* root;
    private:
        void destroy(Node* localRoot) {
            if (localRoot != nullptr) {
                destroy(localRoot->leftChild);
                destroy(localRoot->rightChild);
                delete localRoot;
            }
        }
    public:
        Tree() : root(nullptr) {}
        ~Tree() {
            destroy(root);
        }
        void setRoot(Node* rNode) {
            root = rNode;
        }
        Node* getRoot() {
            return root;
        }
        Node* buildTree(int index, string data) {
            if (index >= data.size())
                return nullptr;
            Node* mainNode   = new Node(data[index]);
            mainNode->leftChild = buildTree(index * 2 + 1, data);
            mainNode->rightChild = buildTree(index * 2 + 2, data);

            return mainNode;
        }
        void displayTree() const {
            Stack* globalStack = new Stack(2048);
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
    string s;

    cout << "Enter string: ";
    cin >> s;

    Tree* tree = new Tree();
    Node* newRoot = tree->buildTree(0, s);
    tree->setRoot(newRoot);

    tree->displayTree();

    delete tree;

    return 0;
}