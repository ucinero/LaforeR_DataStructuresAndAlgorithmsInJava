// project_10_4.cpp

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
        const int ORDER = 3;
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
            DataItem* temp = itemArray[1];
            itemArray[1] = nullptr;
            numItems--;
            return temp;
        }
        void displayNode() const {
            for (int j = 0; j < numItems; j++)
                itemArray[j]->displayItem();
            cout << "/" << endl;
        }
};

class Tree23 {
    private:
        Node* root;
    private:
        void split(Node* thisNode) {
            DataItem* itemB;
            Node* parent;
            Node* child2;
            int itemIndex;

            itemB = thisNode->removeItem();
            child2 = thisNode->disconnectChild(1);
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

            newRight->connectChild(0, child2);
        }
        void recDisplayTree(Node* thisNode, int level, int childNumber) {
            if (thisNode == nullptr)
                return;

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
    public:
        Tree23() : root(nullptr) {}
        ~Tree23() {
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

            while (!curNode->isLeaf()) {
                curNode = getNextChild(curNode, dValue);
            }

            if (curNode->isFull()) {
                Node* parent = curNode->getParent();
                if (parent != nullptr && parent->isFull()) {
                    cout << "Вставка невозможна (переполнение родителя)!" << endl;
                    return;
                }
                if (parent == nullptr && !curNode->isLeaf()) {
                    cout << "Вставка невозможна (корень полон и имеет потомков)!" << endl;
                    return;
                }
                split(curNode);
                curNode = curNode->getParent();
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
};

// ... (Классы DataItem, Node, Tree23 остаются без изменений) ...

// Вспомогательная функция для тестирования
void runTest(const string& testName, const vector<long>& valuesToInsert, const vector<long>& valuesToFind) {
    cout << "\n==================================================\n";
    cout << "ТЕСТ: " << testName << "\n";
    cout << "==================================================\n";

    Tree23 tree;
    
    // Вставка
    cout << "-> Вставка элементов: ";
    for (long val : valuesToInsert) {
        cout << val << " ";
        tree.insert(val);
    }
    cout << "\n\n";

    // Вывод дерева
    cout << "-> Структура дерева:\n";
    tree.displayTree();
    cout << "\n";

    // Поиск
    if (!valuesToFind.empty()) {
        cout << "-> Проверка поиска:\n";
        for (long key : valuesToFind) {
            int res = tree.find(key);
            if (res != -1)
                cout << "   [" << key << "] НАЙДЕН (индекс " << res << ")\n";
            else
                cout << "   [" << key << "] НЕ НАЙДЕН\n";
        }
    }
}

int main() {
    cout << "########## ТЕСТИРОВАНИЕ ДЕРЕВА 2-3 ##########\n";

    // Тест 1: Пустое дерево
    runTest("Пустое дерево (только поиск)", {}, {10, 20, 30});

    // Тест 2: Один элемент
    runTest("Один элемент (корень-лист)", {50}, {50, 40});

    // Тест 3: Заполнение корня до предела (2 элемента, без разбиения)
    runTest("Полный корень (без разбиения)", {50, 30}, {30, 50, 40});

    // Тест 4: Первое разбиение корня (3 элемента)
    // Корень разделится, 40 станет новым корнем, 30 и 50 уйдут в листья
    runTest("Первое разбиение корня", {50, 30, 40}, {30, 40, 50, 60});

    // Тест 5: Вставка в левый лист
    runTest("Вставка в левый лист", {50, 30, 40, 20}, {20, 30, 40, 50});

    // Тест 6: Разбиение левого листа (сдвиг элементов в родителе)
    runTest("Разбиение левого листа", {50, 30, 40, 20, 10}, {10, 20, 30, 40, 50});

    // Тест 7: Вставка в правый лист
    runTest("Вставка в правый лист", {50, 30, 40, 60}, {30, 40, 50, 60, 70});

    // Тест 8: Разбиение правого листа
    runTest("Разбиение правого листа", {50, 30, 40, 60, 70}, {10, 20, 30, 40, 50, 60, 70});

    // Тест 9 (ИСПРАВЛЕННЫЙ): Максимальное заполнение (8 элементов для ORDER=3)
    // Дерево 2-3 с ORDER=3 вмещает максимум 8 элементов
    runTest("Максимальное заполнение (8 элементов)", 
            {50, 30, 70, 20, 10, 80, 60, 40}, 
            {10, 20, 30, 40, 50, 60, 70, 80, 90});

    // Тест 10 (ИСПРАВЛЕННЫЙ): Попытка вставки 9-го элемента (блокировка)
    runTest("Попытка вставки 9-го элемента (блокировка)", 
            {50, 30, 70, 20, 10, 80, 60, 40, 90}, 
            {90});

    // Тест 11: Вставка с дубликатами (если разрешено логикой)
    // Проверка, что findItem найдет первое вхождение
    runTest("Вставка дубликатов", {50, 30, 40, 30}, {30, 40, 50});

    // Тест 12: Вставка отрицательных чисел
    runTest("Отрицательные числа", {-10, -20, -30, -40}, {-10, -20, -30, -40, 0});

    // Тест 13: Вставка в хаотичном порядке (проверка правильности сортировки в узлах)
    runTest("Хаотичный порядок", {90, 10, 50, 30, 70, 20, 40}, {10, 20, 30, 40, 50, 70, 90});

    cout << "\n########## ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ##########\n";
    return 0;
}