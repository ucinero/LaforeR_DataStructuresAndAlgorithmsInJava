// tree.cpp

#include <iostream>
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
        int iData;
        double dData;
        Node* leftChild;
        Node* rightChild;
    public:
        Node() : leftChild(nullptr), rightChild(nullptr) {}
        void displayNode() const {
            cout << "{" << iData << ", " << dData << "} ";
        }
};

class Tree {
    private:
        Node* root;
    private:
        Node* getSuccessor(Node* delNode) {
            Node* successorParent = delNode;
            Node* successor = delNode;
            Node* current = delNode->rightChild;

            while (current != nullptr) {
                successorParent = successor;
                successor = current;
                current = current->leftChild;
            }

            if (successor != delNode->rightChild) {
                successorParent->leftChild = successor->rightChild;
                successor->rightChild = delNode->rightChild;
            }

            return successor;
        }
        void preOrder(Node* localRoot) const {
            if (localRoot != nullptr) {
                cout << localRoot->iData << " ";
                preOrder(localRoot->leftChild);
                preOrder(localRoot->rightChild);
            }
        }
        void inOrder(Node* localRoot) const {
            if (localRoot != nullptr) {
                inOrder(localRoot->leftChild);
                cout << localRoot->iData << " ";
                inOrder(localRoot->rightChild);
            }
        }
        void postOrder(Node* localRoot) const {
            if (localRoot != nullptr) {
                postOrder(localRoot->leftChild);
                postOrder(localRoot->rightChild);
                cout << localRoot->iData << " ";
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
        ~Tree() {
            destroy(root);
        }
        Node* find(int key) const {
            Node* current = root;
            while (current->iData != key) {
                if (key < current->iData)
                    current = current->leftChild;
                else
                    current = current->rightChild;
                if (current == nullptr)
                    return nullptr;
            }
            return current;
        }
        void insert(int id, double dd) {
            Node* newNode = new Node();
            newNode->iData = id;
            newNode->dData = dd;
            if (root == nullptr)
                root = newNode;
            else {
                Node* current = root;
                Node* parent;
                while (true) {
                    parent = current;
                    if (id < current->iData) {
                        current = current->leftChild;
                        if (current == nullptr) {
                            parent->leftChild = newNode;
                            return;
                        }
                    }
                    else {
                        current = current->rightChild;
                        if (current == nullptr) {
                            parent->rightChild = newNode;
                            return;
                        }
                    }
                }
            }
        }
        bool Delete(int key) {
            Node* current = root;
            Node* parent = root;
            bool isLeftChild = true;

            while (current->iData != key) {
                parent = current;
                if (key < current->iData) {
                    isLeftChild = true;
                    current = current->leftChild;
                }
                else {
                    isLeftChild = false;
                    current = current->rightChild;
                }
                if (current == nullptr)
                    return false;
            }

            if (current->leftChild == nullptr && current->rightChild == nullptr) {
                if (current == root)
                    root = nullptr;
                else if (isLeftChild)
                    parent->leftChild = nullptr;
                else
                    parent->rightChild = nullptr;
            }
            else if (current->rightChild == nullptr) {
                if (current == root)
                    root = current->leftChild;
                else if (isLeftChild)
                    parent->leftChild = current->leftChild;
                else
                    parent->rightChild = current->leftChild;
            }
            else if (current->leftChild == nullptr) {
                if (current == root)
                    root = current->rightChild;
                else if (isLeftChild)
                    parent->leftChild = current->rightChild;
                else
                    parent->rightChild = current->rightChild;
            }
            else {
                Node* successor = getSuccessor(current);
                if (current == root)
                    root = successor;
                else if (isLeftChild)
                    parent->leftChild = successor;
                else
                    parent->rightChild = successor;
                successor->leftChild = current->leftChild;
            }
            return true;
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
            Stack* globalStack = new Stack(100);
            globalStack->push(root);
            int nBlanks = 32;
            bool isRowEmpty = false;
            cout << "......................................................" << endl;

            while (isRowEmpty == false) {
                Stack* localStack = new Stack(100);
                isRowEmpty = true;
                for (int j = 0; j < nBlanks; j++)
                    cout << ' ';

                while (globalStack->isEmpty() == false) {
                    Node* temp = reinterpret_cast<Node*>(globalStack->pop());
                    if (temp != nullptr) {
                        cout << temp->iData;
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
    int value;
    char choice;

    Tree* theTree = new Tree();

    theTree->insert(50, 1.5);
    theTree->insert(25, 1.2);
    theTree->insert(75, 1.7);
    theTree->insert(12, 1.5);
    theTree->insert(37, 1.2);
    theTree->insert(43, 1.7);
    theTree->insert(30, 1.5);
    theTree->insert(33, 1.2);
    theTree->insert(87, 1.7);
    theTree->insert(93, 1.5);
    theTree->insert(97, 1.5);

    while (true) {
        cout << "Enter first letter of show, "
             << "insert, find, delete or traverse: ";
        cin >> choice;

        switch(choice) {
            case 's': {
                theTree->displayTree();
                break; }
            case 'i': {
                cout << "Enter value to insert: ";
                cin >> value;
                theTree->insert(value, value + 0.9);
                break; }
            case 'f': {
                cout << "Enter value to find: ";
                cin >> value;
                Node* found = theTree->find(value);
                if (found != nullptr) {
                    cout << "Found: ";
                    found->displayNode();
                    cout << endl;
                }
                else
                    cout << "Could not find " << value << endl;
                break; }
            case 'd': {
                cout << "Enter value to delete: ";
                cin >> value;
                bool isDeleted = theTree->Delete(value);
                if (isDeleted)
                    cout << "Deleted " << value << endl;
                else
                    cout << "Could not delete " << value << endl;
                break; }
            case 't': {
                cout << "Enter type 1, 2 or 3: ";
                cin >> value;
                theTree->traverse(value);
                break; }
            default:
                cout << "Invalid entry" << endl;
        }
    }

    delete theTree;
    return 0;
}