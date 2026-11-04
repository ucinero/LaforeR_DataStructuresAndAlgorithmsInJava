// project_8_4.cpp

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Tree;

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
        int size() const {
            return top + 1;
        }
        Node* peekN(int n) {
            return stackArray[n];
        }
        void displayStack(string s) {
            cout << s;
            cout << "Stack (bottom-->top): ";
            for (int j = 0; j < size(); j++) {
                if (peekN(j) != nullptr)
                    peekN(j)->displayNode();
            }
            cout << endl;
        }
};

class ParsePost {
    private:
        Stack* theStack;
        string input;
    public:
        ParsePost(const string& s) {
            input = s;
        }
        ~ParsePost() {
            delete theStack;
        }
        Node* doParse() {
            theStack = new Stack(20);
            char ch;
            int j;
            Node* interAns;
            for (j = 0; j < input.size(); j++) {
                ch = input[j];
                if (isalpha(ch)) {
                    char operand = ch;
                    Node* newNode = new Node(operand);
                    theStack->push(newNode);
                }
                else {
                    Node* num2 = theStack->pop();
                    Node* num1 = theStack->pop();

                    interAns = new Node(ch);
                    interAns->leftChild  = num1;
                    interAns->rightChild = num2;
                    theStack->push(interAns);
                }
            }
            return interAns;
        }
};

class Tree {
    private:
        Node* root;
    private:
        void preOrder(Node* localRoot) const {
            if (localRoot != nullptr) {
                cout << localRoot->cData;
                preOrder(localRoot->leftChild);
                preOrder(localRoot->rightChild);
            }
        }
        void inOrder(Node* localRoot) const {
            if (localRoot != nullptr) {
                cout << "(";
                inOrder(localRoot->leftChild);
                cout << localRoot->cData;
                inOrder(localRoot->rightChild);
                cout << ")";
            }
        }
        void postOrder(Node* localRoot) const {
            if (localRoot != nullptr) {
                postOrder(localRoot->leftChild);
                postOrder(localRoot->rightChild);
                cout << localRoot->cData;
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
        Tree(Node* rNode) : root(rNode) {}
        ~Tree() {
            destroy(root);
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
            cout << "......................................................" << endl;
            delete globalStack;
        }
};

int main() {
    string str = "ABC+*";
    ParsePost* newPost = new ParsePost(str);
    Node* newNode = newPost->doParse();

    Tree* newTree = new Tree(newNode);

    newTree->displayTree();

    newTree->traverse(1);
    newTree->traverse(2);
    newTree->traverse(3);

    delete newTree;
    delete newPost;

    return 0;
}