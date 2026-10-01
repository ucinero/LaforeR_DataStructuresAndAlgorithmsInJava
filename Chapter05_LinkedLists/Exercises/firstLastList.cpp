// firstLastList.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
    public:
        Link(long d) : dData(d), next(nullptr) {}
        void displayLink() {
            cout << dData << " ";
        }
};

class FirstLastList {
    private:
        Link* first;
        Link* last;
    public:
        FirstLastList() {
            first = nullptr;
            last = nullptr;
        }
        bool isEmpty() {
            return first == nullptr;
        }
        void insertFirst(long dd) {
            Link* newLink = new Link(dd);
            if (isEmpty())
                last = newLink;
            newLink->next = first;
            first = newLink;
        }
        void insertLast(long dd) {
            Link* newLink = new Link(dd);
            if (isEmpty())
                first = newLink;
            else
                last->next = newLink;
            last = newLink;
        } 
        long deleteFirst() {
            long temp = first->dData;
            if (first->next == nullptr)
                last = nullptr;
            Link* delFirst = first;
            first = first->next;
            delete delFirst;
            return temp;
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
    FirstLastList* theList = new FirstLastList();
    
    theList->insertFirst(22);
    theList->insertFirst(44);
    theList->insertFirst(66);

    theList->insertLast(11);
    theList->insertLast(33);
    theList->insertLast(55);

    theList->displayList();

    theList->deleteFirst();
    theList->deleteFirst();

    theList->displayList();

    delete theList;
    return 0;

}