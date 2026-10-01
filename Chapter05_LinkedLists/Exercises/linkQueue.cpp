// linkQueue.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
    public:
        Link(long d) : dData(d) {}
        void displayLink() {
            cout << dData << " ";
        }
};

class FirstLastList {
    private:
        Link* first;
        Link* last;
    public:
        FirstLastList() : first(nullptr), last(nullptr) {}
        bool isEmpty() {
            return first == nullptr;
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
            Link* tempLink = first;
            if (first->next == nullptr)
                last = nullptr;
            first = first->next;
            delete tempLink;
            return temp;
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

class LinkQueue {
    private:
        FirstLastList* theList;
    public:
        LinkQueue() {
            theList = new FirstLastList();
        }
        bool isEmpty() {
            return theList->isEmpty();
        }
        void insert(long j) {
            theList->insertLast(j);
        }
        long remove() {
            return theList->deleteFirst();
        }
        void displayQueue() {
            cout << "Queue (front-->rear): ";
            theList->displayList();
        }
};

int main() {
    LinkQueue* theQueue = new LinkQueue();

    theQueue->insert(20);
    theQueue->insert(40);

    theQueue->displayQueue();

    theQueue->insert(60);
    theQueue->insert(80);

    theQueue->remove();
    theQueue->remove();

    theQueue->displayQueue();

    return 0;
}