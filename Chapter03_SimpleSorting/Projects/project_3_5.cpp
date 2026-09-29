// project_3_5.cpp

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
            int copy_count = 0;
            int compare_count = 0;
            for (out = 1; out < nElems; out++) {
                long temp = a[out];
                in = out;
                while (true) {
                    if (in > 0) {
                        compare_count++;
                        if (a[in - 1] > temp) {
                            a[in] = a[in - 1];
                            in--;
                            copy_count++;
                        }
                        else
                            break;
                    }
                    else
                        break;
                }
                a[in] = temp;
                copy_count++;
            }
            cout << "copy_count = " << copy_count << endl;
            cout << "compare_count = " << compare_count << endl;
        }
};

int main() {
    int maxSize = 100;
    ArrayIns arr(maxSize);
    
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

    arr.insertionSort();

    arr.display();

    return 0;
}