// project_5_4.cpp

// project_5_3.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
    public:
        Link(long dd) : dData(dd), next(nullptr) {}
        void displayLink() {
            cout << dData << " ";
        }
};

class CircularList {
    private:
        Link* current;
    public:
        CircularList() : current(nullptr) {}
        ~CircularList() {
            if (current == nullptr)
                return;
            Link* start = current;
            Link* temp = current;
            do {
                Link* next = temp->next;
                delete temp;
                temp = next;
            } while (temp != start);
            current = nullptr;
        }
        bool isEmpty() {
            return current == nullptr;
        }
        void step() {
            if (isEmpty())
                return;
            current = current->next;
        }
        bool find(long key) {
            if (isEmpty())
                return false;
            Link* start = current;
            Link* temp = current;
            do {
                if (temp->dData == key) {
                    current = temp;
                    return true;
                }
                temp = temp->next;
            } while (temp != start);
            return false;
        }
        void insert(long key) {
            Link* newLink = new Link(key);
            if (isEmpty()) {
                current = newLink;
                newLink->next = current;
                return;
            }
            newLink->next = current->next;
            current->next = newLink;
            current = newLink;
        }
        long remove() {
            if (isEmpty())
                return 0;
            if (current->next == current) {
                long dData = current->dData;
                delete current;
                current = nullptr;
                return dData;
            }
            Link* temp = current->next;
            long dData = temp->dData;
            current->next = temp->next;
            delete temp;
            return dData;
        }
        long removeCurrent() {
            if (isEmpty())
                return 0;
            if (current->next == current) {
                long d = current->dData;
                delete current;
                current = nullptr;
                return d;
            }
            Link* prev = current;
            while (prev->next != current)
                prev = prev->next;
            long d = current->dData;
            Link* toDelete = current;
            prev->next = current->next;
            current = prev;
            delete toDelete;
            return d;
        }
        void display() {
            if (isEmpty())
                return;
            if (current->next == current) {
                current->displayLink();
                return;
            }
            Link* start = current;
            Link* temp = current;
            do {
                temp->displayLink();
                temp = temp->next;
            } while (temp != start);
        }
        long getCurrent() {
            return current->dData;
        }
        
};

class StackX {
    private:
        int maxSize;
        CircularList* stackArray;
        int nItems = 0;
    public:
        StackX(int s) {
            maxSize = s;
            stackArray = new CircularList();
        }
        ~StackX() {
            delete stackArray;
        }
        void push(long j) {
            if (isFull())
                return;
            stackArray->insert(j);
            nItems++;
        }
        long pop() {
            if (nItems == 0)
                return 0;
            nItems--;
            return stackArray->removeCurrent();
        }
        long peek() {
            return stackArray->getCurrent();
        }
        bool isEmpty() {
            return stackArray->isEmpty();
        }
        bool isFull() {
            return nItems == maxSize;
        }
};

int main() {
    StackX* theStack = new StackX(10);

    theStack->push(20);
    theStack->push(40);
    theStack->push(60);
    theStack->push(80);

    while (!theStack->isEmpty()) {
        long value = theStack->pop();
        cout << value << " ";
    }
    cout << endl;

    delete theStack;

    return 0;
}