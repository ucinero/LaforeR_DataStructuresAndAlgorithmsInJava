// selectSort.cpp

#include <iostream>
using namespace std;

class ArraySel {
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
        ArraySel(int max) {
            a = new long[max];
            nElems = 0;
        }
        void insert(long value) {
            a[nElems] = value;
            nElems++;
        }
        void display() {
            for (int i = 0; i < nElems; i++)
                cout << a[i] << " ";
            cout << endl;
        }
        void selectionSort() {
            int out, in, min;
            for (out = 0; out < nElems - 1; out++) {
                min = out;
                for (in = out + 1; in < nElems; in++)
                    if (a[in] < a[min])
                        min = in;
                swap(out, min);
            }
        }
};

int main() {
   int maxSize = 100;
   ArraySel arr(maxSize);
   
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

   arr.display();

   arr.selectionSort();

   arr.display();

   return 0;
}