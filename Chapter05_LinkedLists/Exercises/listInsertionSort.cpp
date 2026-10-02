// listInsertionSort.cpp

#include <iostream>
#include <random>
using namespace std;

std::mt19937_64 gen(std::random_device{}());

// randint: inclusive [lo, hi], any integer type
template <typename T = int>
T randint(T lo, T hi) {
    return std::uniform_int_distribution<T>(lo, hi)(gen);
}

class Link {
    public:
        long dData;
        Link* next;
    public:
        Link(long dd) : dData(dd), next(nullptr) {}
};

class SortedList {
    private:
        Link* first;
    public:
        SortedList() : first(nullptr) {}
        SortedList(Link** linkArr, int size) {
            first = nullptr;
            for (int j = 0; j < size; j++)
                insert(linkArr[j]);
        }
        void insert(Link* k) {
            Link* previous = nullptr;
            Link* current = first;

            while (current != nullptr && k->dData > current->dData) {
                previous = current;
                current = current->next;
            }
            if (previous == nullptr)
                first = k;
            else
                previous->next = k;
            k->next = current;
        }
        Link* remove() {
            if (first == nullptr)
                return nullptr;
            Link* temp = first;
            first = first->next;
            return temp;
        }
};

int main() {
    const int size = 10;

    Link** linkArray = new Link*[size];

    for (int j = 0; j < size; j++) {
        long n = randint(0, 100);
        Link* newLink = new Link(n);
        linkArray[j] = newLink;
    }

    cout << "Unsorted Array: ";
    for (int j = 0; j < size; j++)
        cout << linkArray[j]->dData << " ";
    cout << endl;

    SortedList* theSortedList = new SortedList(linkArray, size);

    for (int j = 0; j < size; j++)
        linkArray[j] = theSortedList->remove();

    cout << "Sorted Array: ";
    for (int j = 0; j < size; j++)
        cout << linkArray[j]->dData << " ";

    cout << endl;

    for (int j = 0; j < size; j++) 
        delete linkArray[j];
    delete[] linkArray;

    delete theSortedList;

    return 0;
}