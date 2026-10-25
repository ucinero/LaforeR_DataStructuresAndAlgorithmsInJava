// binarySearch.cpp

#include <iostream>
using namespace std;

class ordArray {
    private:
        long* a;
        int nElems;
    private:
        int recFind(long searchKey, int lowerBound, int upperBound) {
            int curIn;
            curIn = (lowerBound + upperBound) / 2;
            if (a[curIn] == searchKey)
                return curIn;
            else if (lowerBound > upperBound)
                return nElems;
            else {
                if (a[curIn] < searchKey)
                    return recFind(searchKey, curIn + 1, upperBound);
                else
                    return recFind(searchKey, lowerBound, curIn - 1);
            }
        }
    public:
        ordArray(int max) {
            a = new long[max];
            nElems = 0;
        }
        ~ordArray() {
            delete a;
        }
        int size() const {
            return nElems;
        }
        int find(long searchKey) {
            return recFind(searchKey, 0, nElems - 1);
        }
        void insert(long value) {
            int j;
            for (j = 0; j < nElems; j++)
                if (a[j] > value)
                    break;
            for (int k = nElems; k > j; k--)
                a[k] = a[k - 1];
            a[j] = value;
            nElems++;
        }
        void display() const {
            for (int j = 0; j < nElems; j++)
                cout << a[j] << " ";
            cout << endl;
        }
};

int main() {
    const int maxSize = 100;
    ordArray* arr = new ordArray(maxSize);

    arr->insert(72);
    arr->insert(90);
    arr->insert(45);
    arr->insert(126);

    arr->insert(54);
    arr->insert(99);
    arr->insert(144);
    arr->insert(27);

    arr->insert(135);
    arr->insert(81);
    arr->insert(18);
    arr->insert(108);
    
    arr->insert(9);
    arr->insert(117);
    arr->insert(63);
    arr->insert(36);

    arr->display();

    int searchKey = 27;
    if (arr->find(searchKey) != arr->size())
        cout << "Found " << searchKey << endl;
    else
        cout << "Can't find " << searchKey << endl;

    delete arr;
    return 0;
}