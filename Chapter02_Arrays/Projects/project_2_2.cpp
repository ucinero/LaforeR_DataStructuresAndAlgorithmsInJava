// project_2_2.cpp

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
        long removeMax() {
            if (nElems == 0)
                return -1;
            int max_ind = 0;
            long max_elem = a[max_ind];
            for (int i = 1; i < nElems; i++)
                if (a[i] > a[max_ind]) {
                    max_ind = i;
                    max_elem = a[max_ind];
                }
            for (int k = max_ind; k < nElems - 1; k++)
                a[k] = a[k + 1];
            nElems--;
            return max_elem;
        }
};

int main() {
    HighArray arr1(0);

    HighArray arr2(5);
    arr2.insert(5);
    arr2.insert(1);
    arr2.insert(6);
    arr2.insert(9);
    arr2.insert(2);

    cout << "max of arr1 = " << arr1.removeMax() << endl;
    cout << "arr2 = "; arr2.display();
    cout << "max of arr2 = " << arr2.removeMax() << endl;
    cout << "arr2 = "; arr2.display();

    return 0;
}