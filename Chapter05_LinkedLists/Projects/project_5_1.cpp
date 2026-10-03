// project_5_1.cpp

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

class SortedList {
    private:
        Link* first;
    public:
        SortedList() : first(nullptr) {}
        bool isEmpty() {
            return first == nullptr;
        }
        void insert(long key) {
            Link* newLink = new Link(key);
            Link* previous = nullptr;
            Link* current = first;
            
            while (current != nullptr && key > current->dData) {
                previous = current;
                current = current->next;
            }

            if (previous == nullptr)
                first = newLink;
            else
                previous->next = newLink;
            newLink->next = current;
        }
        long remove() {
            if (isEmpty())
                return 0;
            Link* temp = first;
            long data = temp->dData;
            first = first->next;
            delete temp;
            return data;
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
        long operator[](int index) {
            if (index < 0)
                return 0;
            Link* current = first;
            int temp_index = 0;
            while (current != nullptr && temp_index != index) {
                current = current->next;
                temp_index++;
            }
            if (current == nullptr)
                return 0;
            return current->dData;
        }
};

class PriorityQ {
    private:
        int maxSize;
        SortedList* queArray;
        int nItems;
    public:
        PriorityQ(int s) {
            maxSize = s;
            queArray = new SortedList();
            nItems = 0;
        }
        void insert(long item) {
            queArray->insert(item);
            nItems++;
        }
        long remove() {
            if (isEmpty())
                return 0;
            nItems--;
            return queArray->remove();
        }
        long peekMin() {
            return (*queArray)[0];
        }
        bool isEmpty() {
            return nItems == 0;
        }
        bool isFull() {
            return nItems == maxSize;
        }
};

int main() {
    PriorityQ thePQ(5);
    
    thePQ.insert(30);
    thePQ.insert(50);
    thePQ.insert(10);
    thePQ.insert(40);
    thePQ.insert(20);

    while (!thePQ.isEmpty()) {
        long item = thePQ.remove();
        cout << item << " ";
    }
    cout << endl;

    return 0;
}