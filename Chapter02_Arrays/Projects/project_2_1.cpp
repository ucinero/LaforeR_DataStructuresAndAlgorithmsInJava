// project_2_1.cpp

#include <iostream>
using namespace std;

class HighArray {
    private:
        long* a;
        int nElems;
    public:
        HighArray(int max) {
            a = new long[max];
            nElems = 0;
        }
        bool find(long searchKey) {
            int j;
            for (j = 0; j < nElems; j++)
                if (a[j] == searchKey)
                    break;
            if (j == nElems)
                return false;
            else
                return true;
        }
        void insert(long value) {
            a[nElems] = value;
            nElems++;
        }
        bool Delete(long value) {
            int j;
            for (j = 0; j < nElems; j++)
                if (value == a[j])
                    break;
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
        long getMax() {
            if (nElems == 0)
                return -1;
            long max = a[0];
            for (int i = 1; i < nElems; i++)
                if (a[i] > max)
                    max = a[i];
            return max;
        }
};

int main() {
    HighArray arr1(0);

    HighArray arr2(5);
    arr2.insert(5);
    arr2.insert(1);
    arr2.insert(7);
    arr2.insert(4);
    arr2.insert(9);

    cout << "max of arr1 = " << arr1.getMax() << endl;
    cout << "max of arr2 = " << arr2.getMax() << endl;

    return 0;
}