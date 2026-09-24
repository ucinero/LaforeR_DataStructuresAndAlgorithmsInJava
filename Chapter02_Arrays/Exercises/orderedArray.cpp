// orderedArray.cpp

#include <iostream>
using namespace std;

class OrdArray {
    private:
        long* a;
        int nElems;
    public:
        OrdArray(int max) {
            a = new long[max];
            nElems = 0;
        }
        int size() {
            return nElems;
        }
        int find(long searchKey) {
            int lowerBound = 0;
            int upperBound = nElems - 1;
            int curIn;
            while (true) {
                curIn = (lowerBound + upperBound) / 2;
                if (a[curIn] == searchKey)
                    return curIn;
                else if (lowerBound > upperBound)
                    return nElems;
                else {
                    if (a[curIn] < searchKey)
                        lowerBound = curIn + 1;
                    else
                        upperBound = curIn - 1;
                }
            }
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
        bool Delete(long value) {
            int j = find(value);
            if (j == nElems)
                return false;
            else {
                for (int k = j; k < nElems - 1; k++)
                    a[k] = a[k + 1];
                nElems--;
                return true;
            }
        }
        void display() {
            for (int j = 0; j < nElems; j++)
                cout << a[j] << " ";
            cout << endl;
        }
};

int main() {
    int maxSize = 100;
    OrdArray arr(maxSize);

    arr.insert(77);
    arr.insert(99);
    arr.insert(44);
    arr.insert(55);
    arr.insert(22);
    arr.insert(88);
    arr.insert(11);
    arr.insert(00);
    arr.insert(66);
    arr.insert(33);

    int searchKey = 55;
    if (arr.find(searchKey) != arr.size())
        cout << "Found " << searchKey << endl;
    else
        cout << "Can't find " << searchKey << endl;

    arr.display();

    arr.Delete(00);
    arr.Delete(55);
    arr.Delete(99);

    arr.display();

    return 0;
}