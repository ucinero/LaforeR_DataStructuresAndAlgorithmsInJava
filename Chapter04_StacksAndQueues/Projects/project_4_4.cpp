// project_4_4.cpp

// priorityQ.cpp

#include <iostream>
using namespace std;

class PriorityQ {
    private:
        int maxSize;
        long* queArray;
        int nItems;
    public:
        PriorityQ(int s) {
            maxSize = s;
            queArray = new long[maxSize];
            nItems = 0;
        }
        void insert(long item) {
            queArray[nItems++] = item;
        }
        long remove() {
            if (nItems == 0) {
                cout << "the priority queue is empty!" << endl;
                return 0;
            }
            int j;
            long min_elem = queArray[0];
            int min_index = 0;
            for (j = 0; j < nItems; j++) {
                if (min_elem > queArray[j]) {
                    min_elem  = queArray[j];
                    min_index = j;
                }
            }
            for (j = min_index; j < nItems - 1; j++)
                queArray[j] = queArray[j + 1];

            nItems--;
            return min_elem;
        }
        long peekMin() {
            return queArray[nItems - 1];
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