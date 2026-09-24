// project_2_5.cpp

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
        void merge(OrdArray* first, OrdArray* second) {
            int first_size = first->size();
            int second_size = second->size();
            int third_size = first_size + second_size;

            OrdArray* third = new OrdArray(third_size);
            int i = 0;
            int j = 0;
            while (i < first_size && j < second_size) {
                if (first->a[i] < second->a[j]) {
                    this->insert(first->a[i]);
                    i++;
                }
                else {
                    this->insert(second->a[j]);
                    j++;
                }
            }
            while (i < first_size) {
                this->insert(first->a[i]);
                i++;
            }
            while (j < second_size) {
                this->insert(second->a[j]);
                j++;
            }
        }
};

int main() {
    int maxSize = 100;
    OrdArray arr1(maxSize);
    OrdArray arr2(maxSize);

    arr1.insert(77);
    arr1.insert(99);
    arr1.insert(44);
    arr2.insert(55);
    arr2.insert(22);
    arr2.insert(88);
    arr2.insert(11);
    arr2.insert(00);
    arr2.insert(66);
    arr2.insert(33);

    arr1.display();
    arr2.display();

    OrdArray arr(maxSize);
    arr.merge(&arr1, &arr2);
    arr.display();

    return 0;
}