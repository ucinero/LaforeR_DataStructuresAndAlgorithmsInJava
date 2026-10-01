// linkStack.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
    public:
        Link(long dd) : dData(dd) {}
        void displayLink() {
            cout << dData << " ";
        }
};

class LinkList {
    private:
        Link* first;
    public:
        LinkList() : first(nullptr) {}
        bool isEmpty() {
            return first == nullptr;
        }
        void insertFirst(long dd) {
            Link* newLink = new Link(dd);
            newLink->next = first;
            first = newLink;
        }
        long deleteFirst() {
            long data = first->dData;
            Link* temp = first;
            first = first->next;
            delete temp;
            return data;
        }
        void displayList() {
            Link* current = first;
            while (current != nullptr) {
                current->displayLink();
                current = current->next;
            }
            cout << endl;
        }
};

class LinkStack {
    private:
        LinkList* theList;
    public:
        LinkStack() {
            theList = new LinkList();
        }
        void push(long j) {
            theList->insertFirst(j);
        }
        long pop() {
            return theList->deleteFirst();
        }
        bool isEmpty() {
            return theList->isEmpty();
        }
        void displayStack() {
            cout << "Stack (top-->bottom): ";
            theList->displayList();
        }
};

int main() {
    LinkStack* theStack = new LinkStack();

    theStack->push(20);
    theStack->push(40);

    theStack->displayStack();

    theStack->push(60);
    theStack->push(80);

    theStack->displayStack();

    theStack->pop();
    theStack->pop();

    theStack->displayStack();

    delete theStack;

    return 0;
}