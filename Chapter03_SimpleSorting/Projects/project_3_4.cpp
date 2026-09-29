// project_3_4.cpp

#include <iostream>
using namespace std;

class ArrayBub {
    private:
        long* a;
        int nElems;
    private:
        void swap(int one, int two) {
            long temp = a[one];
            a[one] = a[two];
            a[two] = temp;
        }
    public:
        ArrayBub(int max) {
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
        void oddEvenSort() {
            int out, even, odd;
            for (out = 0; out < nElems; out += 2) {
                for (even = 0; even < nElems - 1; even += 2)
                    if (a[even] > a[even + 1])
                        swap(even, even + 1);
                for (odd = 1; odd < nElems - 1; odd += 2)
                    if (a[odd] > a[odd + 1])
                        swap(odd, odd + 1);
            }
        }
};

int main() {
    int maxSize = 100;
    ArrayBub* arr = new ArrayBub(maxSize);

    arr->insert(77);
    arr->insert(99);
    arr->insert(44);
    arr->insert(55);
    arr->insert(22);

    arr->insert(88);
    arr->insert(11);
    arr->insert(00);
    arr->insert(66);
    arr->insert(33);

    arr->display();

    arr->oddEvenSort();

    arr->display();

    return 0;
}