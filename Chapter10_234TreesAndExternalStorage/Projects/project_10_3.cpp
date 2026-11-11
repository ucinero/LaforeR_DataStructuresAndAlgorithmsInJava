// project_10_3.cpp

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
            cout << "/" << endl;
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
        void inOrderToArray(Node* thisNode, long* array, int& index) const {
            if (thisNode != nullptr) {
                int numItems = thisNode->getNumItems();
                for (int i = 0; i < numItems; i++) {
                    inOrderToArray(thisNode->getChild(i), array, index);
                    array[index] = thisNode->getItem(i)->dData;
                    index++;
                }
                inOrderToArray(thisNode->getChild(numItems), array, index);
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
        void sort(long* array, int size) const {
            if (size == 0)
                return;
            Tree234 tempTree;
            for (int i = 0; i < size; i++)
                tempTree.insert(array[i]);
            int index = 0;
            tempTree.inOrderToArray(tempTree.root, array, index);
        }
};

#include <iostream>

// ... (Классы DataItem, Node, Tree234 с добавленным методом sort) ...

// Вспомогательная функция для запуска тестов
void runSortTest(const string& testName, vector<long> inputArray) {
    cout << "----------------------------------------\n";
    cout << "Тест: " << testName << "\n";
    
    // Вывод исходного массива
    cout << "Исходный массив: [";
    for (size_t i = 0; i < inputArray.size(); ++i) {
        cout << inputArray[i] << (i < inputArray.size() - 1 ? ", " : "");
    }
    cout << "]\n";

    // Создаем дерево и вызываем сортировку
    // Передаем указатель на данные вектора и его размер
    Tree234 tree;
    if (!inputArray.empty()) {
        tree.sort(inputArray.data(), inputArray.size());
    }

    // Вывод отсортированного массива
    cout << "После sort():  [";
    for (size_t i = 0; i < inputArray.size(); ++i) {
        cout << inputArray[i] << (i < inputArray.size() - 1 ? ", " : "");
    }
    cout << "]\n";

    // Проверка
    bool isSorted = std::is_sorted(inputArray.begin(), inputArray.end());
    cout << "Результат: " << (isSorted ? "OK ✔ (массив отсортирован)" : "FAIL ✘ (нарушен порядок)") << "\n";
}

int main() {
    cout << "========== ТЕСТЫ sort() ==========\n";

    // 1. Пустой массив
    runSortTest("Пустой массив", {});

    // 2. Один элемент
    runSortTest("Один элемент", {42});

    // 3. Уже отсортированный массив
    runSortTest("Уже отсортирован (1..5)", {1, 2, 3, 4, 5});

    // 4. Отсортированный по убыванию (обратный порядок)
    runSortTest("Обратный порядок (5..1)", {5, 4, 3, 2, 1});

    // 5. Случайный порядок
    runSortTest("Случайный порядок", {50, 10, 90, 30, 70, 20, 80});

    // 6. С отрицательными числами
    runSortTest("С отрицательными числами", {10, -5, 0, -20, 15, -10});

    // 7. С дубликатами
    runSortTest("С дубликатами", {5, 1, 5, 3, 1, 2, 5});

    // 8. Четное количество элементов
    runSortTest("Четное количество", {8, 3, 7, 1, 4, 6});

    // 9. Два элемента (проверка минимального размера для ветвления)
    runSortTest("Два элемента (10, 5)", {10, 5});

    // 10. Большой массив
    vector<long> bigArray;
    for (long i = 50; i >= -50; --i) {
        bigArray.push_back(i);
    }
    runSortTest("Большой массив (50..-50)", bigArray);

    cout << "===================================\n";
    return 0;
}