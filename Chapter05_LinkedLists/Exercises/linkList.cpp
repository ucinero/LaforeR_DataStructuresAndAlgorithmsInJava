// linkList.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        int iData;
        double dData;
        Link* next;
    public:
        Link(int id, double dd) : iData(id), dData(dd) {}
        void displayLink() {
            cout << "{" << iData << ", " << dData << "} ";
        }
};

class LinkList {
    private:
        Link* first;
    public:
        LinkList() : first(nullptr) {}
        ~LinkList() {
            while (first != nullptr) {
                Link* temp = first;
                first = first->next;
                cout << "deleted: ";
                temp->displayLink();
                cout << endl;
                delete temp;
            }
        }
        bool isEmpty() {
            return first == nullptr;
        }
        void insertFirst(int id, double dd) {
            Link* newLink = new Link(id, dd);
            newLink->next = first;
            first = newLink;
        }
        void deleteFirst() {
            if (first == nullptr)
                return;
            Link* temp = first;
            first = first->next;
            delete temp;
        }
        void displayList() {
            cout << "List (first-->last): ";
            Link* current = first;
            while (current != nullptr) {
                current->displayLink();
                current = current->next;
            }
            cout << endl;
        }
};

int main() {
    LinkList* theList = new LinkList();

    theList->insertFirst(22, 2.99);
    theList->insertFirst(44, 4.99);
    theList->insertFirst(66, 6.99);
    theList->insertFirst(88, 8.99);

    theList->displayList();

    delete theList;
    
    return 0;
}