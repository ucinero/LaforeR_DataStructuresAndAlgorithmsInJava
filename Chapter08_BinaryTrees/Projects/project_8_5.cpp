// project_8_5.cpp

#include <iostream>
#include <unordered_map>
#include <string>
#include <cassert>
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
        int iData;
        Node* leftChild;
        Node* rightChild;
    public:
        Node(char cd, int id) : cData(cd), iData(id),
                                leftChild(nullptr), rightChild(nullptr) {}
        void displayNode() const {
            cout << "{" << cData << ", " << iData << "} ";
        }
};

class Tree {
    private:
        Node* root;
    private:
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
        Tree(Node* rNode) : root(rNode) {}
        ~Tree() {
            destroy(root);
        }
        Node* getRoot() const {
            return root;
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
            const int sizeStack = 2048;
            Stack* globalStack = new Stack(sizeStack);
            globalStack->push(root);
            int nBlanks = 32;
            bool isRowEmpty = false;
            cout << "......................................................" << endl;

            while (isRowEmpty == false) {
                Stack* localStack = new Stack(sizeStack);
                isRowEmpty = true;
                for (int j = 0; j < nBlanks; j++)
                    cout << ' ';

                while (globalStack->isEmpty() == false) {
                    Node* temp = globalStack->pop();
                    if (temp != nullptr) {
                        // char ch = (temp->cData == ' ') ? '*' : temp->cData;
                        cout << temp->cData << " ";
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

class PriorityQ {
    private:
        int maxSize;
        Tree** queArray;
        int nItems;
    public:
        PriorityQ(int s) {
            maxSize = s;
            queArray = new Tree*[maxSize];
            nItems = 0;
        }
        ~PriorityQ() {
            for (int i = 0; i < nItems; i++)
                delete queArray[i];
            delete[] queArray;
        }
        void insert(Tree* item) {
            int j;
            if (nItems == 0)
                queArray[nItems++] = item;
            else {
                for (j = nItems - 1; j >= 0; j--) {
                    Node* rItem = item->getRoot();
                    Node* sItem = queArray[j]->getRoot();
                    int rd = rItem->iData;
                    int sd = sItem->iData;
                    if (rd > sd)
                        queArray[j + 1] = queArray[j];
                    else
                        break;
                }
                queArray[j + 1] = item;
                nItems++;
            }
        }
        Tree* remove() {
            return queArray[--nItems];
        }
        Tree* peekMin() {
            return queArray[nItems - 1];
        }
        bool isEmpty() const {
            return nItems == 0;
        }
        bool isFull() const {
            return nItems == maxSize;
        }
        int getItems() const {
            return nItems;
        }
};

class HuffmanCoder {
    private:
        Tree* theTree;
        unordered_map<char, size_t> freq;
        unordered_map<char, string> codeTable;
    private:
        void buildFrequencyTable(const string& text) {
            for (char c : text)
                freq[c]++;
        }
        void buildTree() {
            const int maxSize = 2048;
            PriorityQ* thePQ = new PriorityQ(maxSize);

            for (const auto& [key, value] : freq) {
                Node* newNode = new Node(key, value);
                thePQ->insert(new Tree(newNode));
            }

            while (thePQ->getItems() > 1) {
                Tree* firstTree  = thePQ->remove();
                Tree* secondTree = thePQ->remove();
                int fData = firstTree->getRoot()->iData;
                int sData = secondTree->getRoot()->iData;

                int data = fData + sData;
                char ch = '*';
                Node* newNode = new Node(ch, data);
                newNode->leftChild  = firstTree->getRoot();
                newNode->rightChild = secondTree->getRoot();
                Tree* newTree = new Tree(newNode);
                thePQ->insert(newTree);
            }
            theTree = thePQ->remove();
            delete thePQ;
            // theTree->displayTree();  
    }
        void destroy() {
            delete theTree;
            theTree = nullptr;
        }
        void buildCodes(Node* localRoot, string currentCode) {
            if (localRoot == nullptr)
                return;
            if (localRoot->leftChild == nullptr && localRoot->rightChild == nullptr) {
                if (currentCode.empty())
                    codeTable[localRoot->cData] = "0";
                else
                    codeTable[localRoot->cData] = currentCode;
                return;
            }
            buildCodes(localRoot->leftChild,  currentCode + "0");
            buildCodes(localRoot->rightChild, currentCode + "1");
        }
    public:
        explicit HuffmanCoder(const string& text) : theTree(nullptr) {
            buildFrequencyTable(text);
            buildTree();
            if (theTree)
                buildCodes(theTree->getRoot(), "");
        }
        ~HuffmanCoder() {
            destroy();
        }

        HuffmanCoder(const HuffmanCoder&) = delete;
        HuffmanCoder& operator=(const HuffmanCoder&) = delete;

        Tree* getTree() const {
            return theTree;
        }
        const unordered_map<char, size_t>& getFrequencyTable() const {
            return freq;
        }
        const unordered_map<char, string>& getCodeTable() const {
            return codeTable;
        };
        string encode(const string& text) {
            string result = "";
            for (char c : text)
                result += codeTable.at(c);
            return result;
        }
        string decode(const string& encodedText) {
            string result = "";
            if (theTree == nullptr || theTree->getRoot() == nullptr)
                return result;

            Node* current = theTree->getRoot();
            if (current->leftChild == nullptr && current->rightChild == nullptr) {
                for (size_t i = 0; i < encodedText.size(); i++)
                    result += current->cData;
                return result;
            }

            for (char c : encodedText) {
                if (c == '0')
                    current = current->leftChild;
                else
                    current = current->rightChild;
                if (current->leftChild == nullptr && current->rightChild == nullptr) {
                    result += current->cData;
                    current = theTree->getRoot();
                }
            }
            return result;
        }

        void display() const {
            if (theTree)
                theTree->displayTree();
        }
};

// ... (весь ваш код классов Node, Tree, HuffmanCoder и т.д.) ...

// Вспомогательная функция для печати таблицы (для наглядности)
void printCodeTable(const unordered_map<char, string>& table) {
    cout << "  Code table:\n";
    for (const auto& [ch, code] : table) {
        cout << "   '" << ch << "' : " << code << "\n";
    }
}

void runTest(const string& testName, const string& text, bool printTree = false) {
    cout << "\n========================================\n";
    cout << "TEST: " << testName << "\n";
    cout << "Original text: \"" << text << "\"\n";

    HuffmanCoder coder(text);

    if (printTree) {
        coder.display();
        cout << "\n";
    }

    string encoded = coder.encode(text);
    string decoded = coder.decode(encoded);

    cout << "Encoded size: " << encoded.size() << " bits\n";
    
    // Если текст короткий, показываем бинарную строку
    if (encoded.size() < 100) {
        cout << "Encoded string: " << encoded << "\n";
    }

    // Проверка обратимости
    if (text == decoded) {
        cout << "Result: SUCCESS (decoded matches original)\n";
    } else {
        cout << "Result: FAILED!\n";
        cout << "Decoded text: \"" << decoded << "\"\n";
    }
}

int main() {
    cout << "=== HUFFMAN CODING TESTS ===\n";

    // 1. Базовый тест из учебника (короткое сообщение)
    runTest("Basic textbook example", "SUSIE SAYS IT IS EASY", true);

    // 2. Один уникальный символ (крайний случай: дерево из одного узла)
    runTest("Single repeated character", "AAAAAAA");

    // 3. Два уникальных символа
    runTest("Two distinct characters", "ABABABAB");

    // 4. Текст с пробелами и знаками препинания
    runTest("Punctuation and spaces", "Hello, World! C++ is fun.");

    // 5. Многострочный текст (согласно заданию: "возможно, состоящий из нескольких строк")
    runTest("Multiline text", "Line one.\nLine two.\nLine three.");

    // 6. Только пробелы (проверка, что пробел кодируется как символ)
    runTest("Only spaces", "     ");

    // 7. Длинный текст (проверка производительности и отсутствия переполнения)
    string longText = "";
    for (int i = 0; i < 100; ++i) {
        longText += "The quick brown fox jumps over the lazy dog. ";
    }
    runTest("Long text (repeated pangram)", longText);

    // 8. Текст с разными регистрами и цифрами (ASCII-разнообразие)
    runTest("Mixed case and digits", "aA1 bB2 cC3 dD4 eE5");

    // 9. Специфический случай: частоты Фибоначчи (проверка глубины дерева)
    // "A" встречается 1 раз, "B" - 1, "C" - 2, "D" - 3, "E" - 5...
    runTest("Fibonacci frequencies", "ABBCCCDDDDEEEEE");

    // 10. Пустая строка (крайний случай)
    runTest("Empty string", ""); // Раскомментируйте, чтобы проверить на прочность

    cout << "\n=== ALL TESTS FINISHED ===\n";
    return 0;
}