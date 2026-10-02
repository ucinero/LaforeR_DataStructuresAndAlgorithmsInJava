// doubleLinked.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
        Link* previous;
    public:
        Link(long d) : dData(d), next(nullptr), previous(nullptr) {}
        void displayLink() {
            cout << dData << " ";
        }
};

class DoublyLinkedList {
    private:
        Link* first;
        Link* last;
    public:
        DoublyLinkedList() : first(nullptr), last(nullptr) {}
        bool isEmpty() {
            return first == nullptr;
        }
        void insertFirst(long dd) {
            Link* newLink = new Link(dd);
            if (isEmpty())
                last = newLink;
            else {
                first->previous = newLink;
                newLink->next = first;
            }
            first = newLink;
        }
        void insertLast(long dd) {
            Link* newLink = new Link(dd);
            if (isEmpty())
                first = newLink;
            else {
                last->next = newLink;
                newLink->previous = last;
            }
            last = newLink;
        }
        Link* deleteFirst() {
            Link* temp = first;
            if (first->next == nullptr)
                last = nullptr;
            else
                first->next->previous = nullptr;
            first = first->next;
            return temp;
        }
        Link* deleteLast() {
            if (isEmpty())
                return nullptr;
            Link* temp = first;
            if (first->next == nullptr)
                first = nullptr;
            else
                last->previous->next = nullptr;
            last = last->previous;
            return temp;
        }
        bool insertAfter(long key, long dd) {
            if (isEmpty())
                return false;
            Link* current = first;
            while (current->dData != key) {
                current = current->next;
                if (current == nullptr)
                    return false;
            }
            Link* newLink = new Link(dd);
            if (current == last) {
                newLink->next = nullptr;
                last = newLink;
            }
            else {
                newLink->next = current->next;
                current->next->previous = newLink;
            }
            newLink->previous = current;
            current->next = newLink;
            return true;
        }
        Link* deleteKey(long key) {
            Link* current = first;
            while (current->dData != key) {
                current = current->next;
                if (current == nullptr)
                    return nullptr;
            }
            if (current == first)
                first = current->next;
            else
                current->previous->next = current->next;

            if (current == last)
                last = current->previous;
            else
                current->next->previous = current->previous;
            return current;
        }
        void displayForward() {
            cout << "List (first-->last): ";
            Link* current = first;
            while (current != nullptr) {
                current->displayLink();
                current = current->next;
            }
            cout << endl;
        }
        void displayBackward() {
            cout << "Lsit (last-->first): ";
            Link* current = last;
            while (current != nullptr) {
                current->displayLink();
                current = current->previous;
            }
            cout << endl;
        }
};

int main() {
    DoublyLinkedList* theList = new DoublyLinkedList();

    theList->insertFirst(22);
    theList->insertFirst(44);
    theList->insertFirst(66);

    theList->insertLast(11);
    theList->insertLast(33);
    theList->insertLast(55);

    theList->displayForward();
    theList->displayBackward();

    theList->deleteFirst();
    theList->deleteLast();
    theList->deleteKey(11);

    theList->displayForward();

    theList->insertAfter(22, 77);
    theList->insertAfter(33, 88);

    theList->displayForward();

    return 0;
}