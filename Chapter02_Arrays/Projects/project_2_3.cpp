// project_2_3.cpp

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

    const int size = 5;
    HighArray arr2(size);
    arr2.insert(5);
    arr2.insert(1);
    arr2.insert(6);
    arr2.insert(9);
    arr2.insert(2);

    HighArray arr_sort(size);
    for (int i = 0; i < size; i++)
        arr_sort.insert(arr2.removeMax());

    cout << "arr_sort = "; arr_sort.display();

    return 0;
}