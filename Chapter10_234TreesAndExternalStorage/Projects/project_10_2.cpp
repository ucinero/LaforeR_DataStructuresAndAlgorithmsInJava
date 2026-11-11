// project_10_2.cpp

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DataItem {
    public:
        long dData;
    public:
        DataItem(long dd) : dData(dd) {}
        void displayItem() const {
            cout << "/" << dData;
        }
};

class Node {
    private:
        const int ORDER = 4;
        int numItems;
        Node* parent;
        Node** childArray = new Node*[ORDER];
        DataItem** itemArray = new DataItem*[ORDER - 1];
    public:
        Node() {
            parent = nullptr;
            for (int i = 0; i < ORDER; i++)
                childArray[i] = nullptr;
            for (int j = 0; j < ORDER - 1; j++)
                itemArray[j] = nullptr;
        }
        ~Node() {
            delete[] childArray;
            delete[] itemArray;
        }
        void connectChild(int childNum, Node* child) {
            childArray[childNum] = child;
            if (child != nullptr)
                child->parent = this;
        }
        Node* disconnectChild(int childNum) {
            Node* tempNode = childArray[childNum];
            childArray[childNum] = nullptr;
            return tempNode;
        }
        Node* getChild(int childNum) const {
            return childArray[childNum];
        }
        Node* getParent() const {
            return parent;
        }
        bool isLeaf() const {
            return (childArray[0] == nullptr) ? true : false;
        }
        int getNumItems() const {
            return numItems;
        }
        DataItem* getItem(int index) const {
            return itemArray[index];
        }
        bool isFull() const {
            return (numItems == ORDER - 1) ? true : false;
        }
        int findItem(long key) const {
            for (int j = 0; j < ORDER - 1; j++) {
                if (itemArray[j] == nullptr)
                    break;
                else if (itemArray[j]->dData == key)
                    return j;
            }
            return -1;
        }
        int insertItem(DataItem* newItem) {
            numItems++;
            long newKey = newItem->dData;

            for (int j = ORDER - 2; j >= 0; j--) {
                if (itemArray[j] == nullptr)
                    continue;
                else {
                    long itsKey = itemArray[j]->dData;
                    if (newKey < itsKey)
                        itemArray[j + 1] = itemArray[j];
                    else {
                        itemArray[j + 1] = newItem;
                        return j + 1;
                    }
                }
            }
            itemArray[0] = newItem;
            return 0;
        }
        DataItem* removeItem() {
            DataItem* temp = itemArray[numItems - 1];
            itemArray[numItems - 1] = nullptr;
            numItems--;
            return temp;
        }
        void displayNode() const {
            for (int j = 0; j < numItems; j++)
                itemArray[j]->displayItem();
        }
};

class Tree234 {
    private:
        Node* root;
    private:
        void split(Node* thisNode) {
            DataItem* itemB;
            DataItem* itemC;
            Node* parent;
            Node* child2;
            Node* child3;
            int itemIndex;

            itemC = thisNode->removeItem();
            itemB = thisNode->removeItem();
            child2 = thisNode->disconnectChild(2);
            child3 = thisNode->disconnectChild(3);
            Node* newRight = new Node();

            if (thisNode == root) {
                root = new Node();
                parent = root;
                root->connectChild(0, thisNode);
            }
            else
                parent = thisNode->getParent();

            itemIndex = parent->insertItem(itemB);
            int n = parent->getNumItems();

            for (int j = n - 1; j > itemIndex; j--) {
                Node* temp = parent->disconnectChild(j);
                parent->connectChild(j + 1, temp);
            }

            parent->connectChild(itemIndex + 1, newRight);

            newRight->insertItem(itemC);
            newRight->connectChild(0, child2);
            newRight->connectChild(1, child3);
        }
        void recDisplayTree(Node* thisNode, int level, int childNumber) {
            cout << "level = " << level << ", child = " << childNumber << " ";
            thisNode->displayNode();

            int numItems = thisNode->getNumItems();
            for (int j = 0; j < numItems + 1; j++) {
                Node* nextNode = thisNode->getChild(j);
                if (nextNode != nullptr)
                    recDisplayTree(nextNode, level + 1, j);
                else
                    return;
            }
        }
        void destroy(Node* localRoot) {
            if (localRoot != nullptr) {
                int numItems = localRoot->getNumItems();
                for (int i = 0; i <= numItems; i++) {
                    Node* tempNode = localRoot->getChild(i);
                    destroy(tempNode);
                }
                delete localRoot;
            }
        }
        void inOrder(Node* thisNode) const {
            if (thisNode != nullptr) {
                int numItems = thisNode->getNumItems();
                int i;
                for (i = 0; i < numItems; i++) {
                    inOrder(thisNode->getChild(i));
                    thisNode->getItem(i)->displayItem();
                }
                inOrder(thisNode->getChild(i));
            }
        }
    public:
        Tree234() : root(nullptr) {}
        ~Tree234() {
            destroy(root);
        }
        int find(long key) {
            if (root == nullptr)
                return -1;
            Node* curNode = root;
            int childNumber;
            while (true) {
                childNumber = curNode->findItem(key);
                if (childNumber != -1)
                    return childNumber;
                else if (curNode->isLeaf())
                    return -1;
                else
                    curNode = getNextChild(curNode, key);
            }
        }
        void insert(long dValue) {
            DataItem* tempItem = new DataItem(dValue);

            if (root == nullptr) {
                root = new Node();
                root->insertItem(tempItem);
                return;
            }

            Node* curNode = root;

            while (true) {
                if (curNode->isFull()) {
                    split(curNode);
                    curNode = curNode->getParent();
                    curNode = getNextChild(curNode, dValue);
                }
                else if (curNode->isLeaf())
                    break;
                else
                    curNode = getNextChild(curNode, dValue);
            }
            curNode->insertItem(tempItem);
        }
        Node* getNextChild(Node* theNode, long theValue) {
            int j;
            int numItems = theNode->getNumItems();
            for (j = 0; j < numItems; j++) {
                if (theValue < theNode->getItem(j)->dData)
                    return theNode->getChild(j);
            }
            return theNode->getChild(j);
        }
        void displayTree() {
            recDisplayTree(root, 0, 0);
        }
        void inorderTraversal() const {
            inOrder(root);
        }
};

// ... (Классы DataItem, Node, Tree234 с добавленным методом inorderTraversal) ...

// Вспомогательная функция для запуска тестов
void runInorderTest(const string& testName, const vector<long>& values) {
    Tree234 tree;
    for (long v : values) {
        tree.insert(v);
    }
    
    cout << "----------------------------------------\n";
    cout << "Тест: " << testName << "\n";
    cout << "Вставленные значения (" << values.size() << " шт.): ";
    for (long v : values) cout << v << " ";
    cout << "\nСимметричный обход (должен быть по возрастанию):\n  ";
    
    // Вызов нашего метода
    tree.inorderTraversal();
    
    cout << "\n";
}

int main() {
    cout << "========== ТЕСТЫ inorderTraversal() ==========\n";

    // 1. Пустое дерево
    runInorderTest("Пустое дерево", {});

    // 2. Один элемент (корень-лист)
    runInorderTest("Один элемент", {42});

    // 3. Несколько элементов без разбиения (один узел)
    runInorderTest("Один узел (3 элемента)", {30, 10, 20});

    // 4. Первое разбиение (появляется корень и 2 листа)
    runInorderTest("Первое разбиение", {50, 40, 60, 30});

    // 5. Уже упорядоченная последовательность
    runInorderTest("Возрастающая последовательность", {10, 20, 30, 40, 50});

    // 6. Обратная последовательность
    runInorderTest("Убывающая последовательность", {50, 40, 30, 20, 10});

    // 7. Перемешанные числа
    runInorderTest("Перемешанные числа", {50, 10, 90, 30, 70, 20, 80});

    // 8. Отрицательные числа
    runInorderTest("С отрицательными числами", {-10, 0, -20, 20, 10});

    // 9. С дубликатами
    runInorderTest("С дубликатами", {15, 10, 15, 20, 15, 5});

    // 10. Большое дерево (много уровней)
    vector<long> bigTree;
    for (long i = 100; i >= 1; --i) {
        bigTree.push_back(i);
    }
    runInorderTest("Большое дерево (100..1)", bigTree);

    cout << "==============================================\n";
    return 0;
}