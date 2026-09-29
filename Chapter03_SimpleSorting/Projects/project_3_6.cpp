// project_3_6.cpp

#include <iostream>
using namespace std;

class ArrayIns {
    private:
        long* a;
        int nElems;
    public:
        ArrayIns(int max) {
            a = new long[max];
            nElems = 0;
        }
        void insert(long value) {
            a[nElems] = value;
            nElems++;
        }
        void display() {
            for (int j = 0; j < nElems; j++)
                cout << a[j] << " ";
            cout << endl;
        }
        void insertionSort() {
            int in, out;
            int k = 0;
            for (out = 1; out < nElems; out++) {
                long temp = a[out];
                in = out;
                while (in > 0 && a[in - 1] >= temp) {
                    if (a[in - 1] == temp)
                        temp = -1;
                    a[in] = a[in - 1];
                    in--;
                }
                a[in] = temp;
                if (a[in] == -1)
                    k++;
            }
            int i = 0;
            while (i + k < nElems) {
                a[i] = a[i + k];
                i++;
            }
            nElems -= k;
        }
};

int main() {
    int maxSize = 100;
    ArrayIns arr(maxSize);
    
    arr.insert(22);
    arr.insert(44);
    arr.insert(55);
    arr.insert(22);
    arr.insert(55);
    arr.insert(11);
    arr.insert(00);
    arr.insert(66);
    arr.insert(00);
    
    arr.display();

    arr.insertionSort();

    arr.display();

    return 0;
}