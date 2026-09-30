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
            int j;
            if (nItems == 0)
                queArray[nItems++] = item;
            else {
                for (j = nItems - 1; j >= 0; j--) {
                    if (item > queArray[j])
                        queArray[j + 1] = queArray[j];
                    else
                        break;
                }
                queArray[j + 1] = item;
                nItems++;
            }
        }
        long remove() {
            return queArray[--nItems];
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