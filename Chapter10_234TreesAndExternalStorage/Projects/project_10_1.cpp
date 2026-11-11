// project_10_1.cpp

#include <iostream>
#include <string>
#include <vector>
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
        long getMin() const {
            Node* current = root;
            if (current == nullptr)
                return 0;
            while (!current->isLeaf())
                current = current->getChild(0);
            return current->getItem(0)->dData;
        }
        void displayTree() {
            recDisplayTree(root, 0, 0);
        }
};

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ... (классы DataItem, Node, Tree234 без изменений) ...

// Вспомогательная функция для запуска теста
void runTest(const string& testName,
             const vector<long>& values,
             long expectedMin)
{
    Tree234 tree;
    for (long v : values)
        tree.insert(v);

    long actualMin = tree.getMin();

    cout << "----------------------------------------\n";
    cout << "Тест: " << testName << "\n";
    cout << "  Вставлено значений: " << values.size() << "\n";
    if (!values.empty()) {
        cout << "  Первое вставленное: " << values.front()
             << ", последнее: " << values.back() << "\n";
    }
    cout << "  Ожидаемый минимум: " << expectedMin << "\n";
    cout << "  Полученный минимум: " << actualMin << "\n";
    cout << "  Результат: "
         << (actualMin == expectedMin ? "OK ✔" : "FAIL ✘") << "\n";
}

int main() {
    cout << "========== ТЕСТЫ getMin() ==========\n";

    // 1. Пустое дерево (по контракту возвращает 0)
    runTest("Пустое дерево", {}, 0);

    // 2. Один элемент — root является листом
    runTest("Один элемент (42)", {42}, 42);

    // 3. Один элемент — отрицательный
    runTest("Один элемент (-7)", {-7}, -7);

    // 4. Два элемента: минимум вставлен первым
    runTest("Два элемента: {10, 20}", {10, 20}, 10);

    // 5. Два элемента: минимум вставлен вторым
    runTest("Два элемента: {20, 10}", {20, 10}, 10);

    // 6. Три элемента (полный узел, но ещё один корень)
    runTest("Три элемента: {30, 10, 20}", {30, 10, 20}, 10);

    // 7. Четыре элемента — первый split, появляется новый корень
    runTest("Четыре элемента: {50, 40, 60, 30}",
            {50, 40, 60, 30}, 30);

    // 8. Возрастающая последовательность 1..20
    {
        vector<long> v;
        for (long i = 1; i <= 20; ++i) v.push_back(i);
        runTest("Возрастающая 1..20", v, 1);
    }

    // 9. Убывающая последовательность 20..1
    {
        vector<long> v;
        for (long i = 20; i >= 1; --i) v.push_back(i);
        runTest("Убывающая 20..1", v, 1);
    }

    // 10. Случайный порядок
    runTest("Перемешанные {50,40,60,30,70,20,80,10}",
            {50, 40, 60, 30, 70, 20, 80, 10}, 10);

    // 11. Все отрицательные
    runTest("Все отрицательные {-1,-2,-3,-4,-5}",
            {-1, -2, -3, -4, -5}, -5);

    // 12. Смешанные знаки
    runTest("Смешанные {-10, 0, 10, -20, 20, -5}",
            {-10, 0, 10, -20, 20, -5}, -20);

    // 13. Минимум — очень маленькое число
    runTest("Очень маленькое минимум {100, 200, -999999, 50}",
            {100, 200, -999999, 50}, -999999);

    // 14. Минимум — очень большое по модулю отрицательное
    runTest("Большое по модулю {-2147483000, 5, 10, 15}",
            {-2147483000L, 5, 10, 15}, -2147483000L);

    // 15. Дубликаты (минимум = дубликат)
    runTest("Дубликаты минимума {5,5,5,10,15}", {5, 5, 5, 10, 15}, 5);

    // 16. Минимум — первое значение, остальные растут
    runTest("Минимум первый {1, 100, 200, 300, 400, 500}",
            {1, 100, 200, 300, 400, 500}, 1);

    // 17. Минимум — последнее вставленное
    runTest("Минимум последний {100, 90, 80, 70, 60, -1}",
            {100, 90, 80, 70, 60, -1}, -1);

    // 18. Большое дерево (много split'ов), минимум = -1000
    {
        vector<long> v;
        for (long i = 1000; i >= -1000; i -= 7)
            v.push_back(i);
        v.push_back(-1000);
        runTest("Большое дерево, минимум -1000", v, -1000);
    }

    // 19. Последовательные значения от -50 до 50
    {
        vector<long> v;
        for (long i = -50; i <= 50; ++i) v.push_back(i);
        runTest("Последовательность -50..50", v, -50);
    }

    // 20. Зигзаг: чередование больших и маленьких
    runTest("Зигзаг {1000, -1000, 999, -999, 500, -500}",
            {1000, -1000, 999, -999, 500, -500}, -1000);

    cout << "=====================================\n";
    return 0;
}