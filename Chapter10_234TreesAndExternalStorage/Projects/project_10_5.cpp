// project_10_5.cpp

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class DataItem {
    public:
        long dData;
    public:
        DataItem(long dd) : dData(dd) {}
        DataItem() : dData(0) {}
        ~DataItem() = default;
        void displayItem() {
            cout << "/" << dData;
        }
};

class Node {
    private:
        static const int ORDER = 3;
        int numItems;
        Node* parent;
        Node** childArray;
        DataItem** itemArray;
    public:
        Node() : numItems(0), parent(nullptr) {
            childArray = new Node*[ORDER];
            itemArray = new DataItem*[ORDER - 1];
            for (int i = 0; i < ORDER; i++)
                childArray[i] = nullptr;
            for (int j = 0; j < ORDER - 1; j++)
                itemArray[j] = nullptr;
        }
        ~Node() {
            for (int i = 0; i < numItems; i++)
                delete itemArray[i];
            for (int i = 0; i <= numItems; i++)
                delete childArray[i];
            delete[] itemArray;
            delete[] childArray;
        }
        void connectChild(int childNum, Node* child) {
            if (childNum < 0 || childNum >= ORDER) return;
            childArray[childNum] = child;
            if (child != nullptr)
                child->parent = this;
        }
        Node* disconnectChild(int childNum) {
            if (childNum < 0 || childNum >= ORDER) return nullptr;
            Node* tempNode = childArray[childNum];
            childArray[childNum] = nullptr;
            return tempNode;
        }
        Node* getChild(int childNum) {
            if (childNum < 0 || childNum >= ORDER) return nullptr;
            return childArray[childNum];
        }
        Node* getParent() {
            return parent;
        }
        bool isLeaf() {
            return childArray[0] == nullptr;
        }
        int getNumItems() {
            return numItems;
        }
        DataItem* getItem(int index) {
            return itemArray[index];
        }
        bool isFull() {
            return numItems == ORDER - 1;
        }
        int findItem(long key) {
            for (int j = 0; j < ORDER - 1; j++) {
                if (itemArray[j] == nullptr)
                    break;
                else if (itemArray[j]->dData == key)
                    return j;
            }
            return - 1;
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
        void displayNode() {
            for (int j = 0; j < numItems; j++)
                itemArray[j]->displayItem();
            cout << "/" << endl;
        }
        int findChildPos(Node* child) {
            if (child == nullptr)
                return -1;
            for (int i = 0; i < ORDER; i++)
                if (childArray[i] == child)
                    return i;
            return -1;
        }
};

class Tree234 {
    private:
        Node* root;
    private:
        void recDisplayTree(Node* thisNode, int level, int childNumber) {
            cout << "level = " << level << " child = " << childNumber << " ";
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
        void sort(DataItem** array) {
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2 - i; j++)
                    if (array[j]->dData > array[j + 1]->dData)
                        swap(array[j], array[j + 1]);
        }
        void swap(DataItem*& left, DataItem*& right) {
            DataItem* temp = left;
            left = right;
            right = temp;
        }
        void split(Node* thisNode, DataItem* thisItem) {
            DataItem* item0 = thisNode->removeItem();
            DataItem* item1 = thisNode->removeItem();
            DataItem* allItems[3] { item0, item1, thisItem };
            sort(allItems);
            DataItem* leftItem   = allItems[0];
            DataItem* middleItem = allItems[1];
            DataItem* rightItem  = allItems[2];

            Node* leftNode   = new Node();
            Node* middleNode = new Node();
            Node* rightNode  = new Node();
            leftNode->insertItem(leftItem);
            middleNode->insertItem(middleItem);
            rightNode->insertItem(rightItem);

            if (thisNode == root && root->isLeaf()) {   
                thisNode->insertItem(middleItem);          
                thisNode->connectChild(0, leftNode);
                thisNode->connectChild(1, rightNode);
                return;
            } 
            else {
                Node* parent = thisNode->getParent();
                if (parent == nullptr) {
                    Node* newRoot = new Node();
                    newRoot->insertItem(middleItem);
                    newRoot->connectChild(0, thisNode);
                    newRoot->connectChild(1, rightNode);

                    thisNode->insertItem(leftItem);
                    root = newRoot;
                    return;
                }
                int childPos = parent->findChildPos(thisNode);
                if (childPos == -1) {
                    cout << "ERROR: Child not found in parent!" << endl;
                    delete thisItem;
                    return;
                }
                if (childPos == 0) {
                    if (!parent->isFull()) {
                        parent->insertItem(rightItem);
                        thisNode->insertItem(leftItem);
                        thisNode->insertItem(middleItem);

                        Node* newNode = new Node();
                        parent->connectChild(2, parent->disconnectChild(1));
                        parent->connectChild(1, newNode);
                        parent->connectChild(0, thisNode);
                    } else {
                        // split(parent, rightItem);
                        // parent = thisNode->getParent();
                        // childPos = parent->findChildPos(thisNode);

                        DataItem* tempRightItem = parent->removeItem();
                        Node* rightParent = new Node();
                        rightParent->insertItem(tempRightItem);
                        rightParent->connectChild(0, parent->disconnectChild(1));
                        rightParent->connectChild(1, parent->disconnectChild(2));

                        middleNode->connectChild(0, leftNode);
                        middleNode->connectChild(1, rightNode);

                        parent->connectChild(0, middleNode);
                        parent->connectChild(1, rightParent);
                    }
                } else if (childPos == 1) {
                    if (!parent->isFull()) {
                        parent->insertItem(leftItem);
                        thisNode->insertItem(middleItem);
                        thisNode->insertItem(rightItem);

                        Node* newNode = new Node();
                        parent->connectChild(2, parent->disconnectChild(1));
                        parent->connectChild(1, newNode);
                    } else {
                        // Работает идеально. Никаких исправлений!

                        Node* grandParent = parent->getParent();

                        DataItem* tempRightItem = parent->removeItem();
                        Node* rightParent = new Node();
                        rightParent->insertItem(tempRightItem);
                        rightParent->connectChild(0, rightNode);
                        rightParent->connectChild(1, parent->disconnectChild(2));

                        parent->connectChild(1, leftNode);

                        middleNode->connectChild(0, parent);
                        middleNode->connectChild(1, rightParent);

                        if (grandParent == nullptr)
                            root = middleNode;
                        else {
                            int parentPos = grandParent->findChildPos(parent);
                            grandParent->connectChild(parentPos, middleNode);
                            middleNode->connectChild(0, parent);
                            middleNode->connectChild(1, rightParent);
                        }
                    }
                } else if (childPos == 2) {
                    // Работает идеально. Никаких исправлений!
                
                    Node* grandParent = parent->getParent();

                    Node* rightParent = new Node();
                    rightParent->insertItem(middleItem);
                    rightParent->connectChild(0, leftNode);
                    rightParent->connectChild(1, rightNode);

                    DataItem* tempRightItem = parent->removeItem();
                    Node* newNode = new Node();
                    newNode->insertItem(tempRightItem);
                    newNode->connectChild(0, parent);
                    newNode->connectChild(1, rightParent);

                    if (grandParent == nullptr)
                        root = newNode;
                    else {
                        int parentPos = grandParent->findChildPos(parent);
                        grandParent->connectChild(parentPos, newNode);
                    }
                } else
                    return;
            }
        }
        void privateDisplay(Node* localRoot) {
            if (localRoot != nullptr) {
                int numCount = localRoot->getNumItems();
                int i;
                for (i = 0; i < numCount; i++) {
                    privateDisplay(localRoot->getChild(i));
                    cout << localRoot->getItem(i)->dData << " ";
                }
                privateDisplay(localRoot->getChild(i));
            }
        }
    public:
        Tree234() {
            root = new Node();
        }
        ~Tree234() {
            delete root;
        }
        int find(long key) {
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
            Node* curNode = root;
            DataItem* tempItem = new DataItem(dValue);
            while (!curNode->isLeaf())
                curNode = getNextChild(curNode, dValue);

            if (curNode->isFull())
                split(curNode, tempItem);
            else
                curNode->insertItem(tempItem);
        }
        Node* getNextChild(Node* theNode, long theValue) {
            int j;
            int numItems = theNode->getNumItems();
            for (j = 0; j < numItems; j++)
                if (theValue < theNode->getItem(j)->dData)
                    return theNode->getChild(j);
            return theNode->getChild(j);
        }
        void displayTree() {
            recDisplayTree(root, 0, 0);
        }
        void displayElems() {
            privateDisplay(root);
        }
};

class Tree234App {
    public:
        static void main() {
            // long value;
            int count = 1000;
            for (int i = 0; i < count; i++) {
                Tree234* theTree = new Tree234();
                srand(unsigned(time(0)));
                int j = (rand() % 1000) + 1;
                cout << j << " elements" << endl;
                for (int k = 0; k < j; k++) {
                    int num = (rand() % 1000) + 1;
                    cout << num << " ";
                    theTree->insert(num);
                }
                cout << endl << endl;
                theTree->displayElems();
                cout << endl << endl;
                theTree->displayTree();
                delete theTree;
            }
            cout << endl;
            // theTree->displayTree();
            
            // while (true) {
            //     cout << "Enter first letter of ";
            //     cout << "show, insert of find: ";

            //     char choice;
            //     cin >> choice;

            //     switch(choice) {
            //         case 's':
            //             theTree->displayTree();
            //             break;
            //         case 'i':
            //             cout << "Enter value to insert: ";
            //             cin >> value;
            //             theTree->insert(value);
            //             break;
            //         case 'f': {
            //             cout << "Enter value to find: ";
            //             cin >> value;
            //             int found = theTree->find(value);
            //             if (found != -1)
            //                 cout << "Found " << value << endl;
            //             else {
            //                 cout << "Could not find " << value << endl;
            //                 break;
            //             }
            //             break;
            //         }
            //         default:
            //             cout << "Ivalid entry\n";
            //     }
            // }
        }
};

int main() {
    Tree234App::main();
    return 0;
}
