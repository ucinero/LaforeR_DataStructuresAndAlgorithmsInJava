// mergeSort.cpp

#include <iostream>
using namespace std;

class DArray {
    private:
        long* theArray;
        int nElems;
    private:
        void recMergeSort(long* workSpace, int lowerBound, int upperBound) {
            if (lowerBound == upperBound)
                return;
            else {
                int mid = (lowerBound + upperBound) / 2;
                recMergeSort(workSpace, lowerBound, mid);
                recMergeSort(workSpace, mid + 1, upperBound);
                merge(workSpace, lowerBound, mid + 1, upperBound);
            }
        }
        void merge(long* workSpace, int lowPtr, int highPtr, int upperBound) {
            int j = 0;
            int lowerBound = lowPtr;
            int mid = highPtr - 1;
            int n = upperBound - lowerBound + 1;

            while (lowPtr <= mid && highPtr <= upperBound) {
                if (theArray[lowPtr] < theArray[highPtr])
                    workSpace[j++] = theArray[lowPtr++];
                else
                    workSpace[j++] = theArray[highPtr++];
            }
            while (lowPtr <= mid)
                workSpace[j++] = theArray[lowPtr++];
            while (highPtr <= upperBound)
                workSpace[j++] = theArray[highPtr++];

            for (j = 0; j < n; j++)
                theArray[lowerBound + j] = workSpace[j];
        }
    public:
        DArray(int max) {
            theArray = new long[max];
            nElems = 0;
        }
        ~DArray() {
            delete[] theArray;
        }
        void insert(long value) {
            theArray[nElems] = value;
            nElems++;
        }
        void display() {
            for (int j = 0; j < nElems; j++)
                cout << theArray[j] << " ";
            cout << endl;
        }
        void mergeSort() {
            long* workSpace = new long[nElems];
            recMergeSort(workSpace, 0, nElems - 1);
        }
};

int main() {
    const int maxSize = 100;
    DArray arr(maxSize);

    arr.insert(64);
    arr.insert(21);
    arr.insert(33);
    arr.insert(70);

    arr.insert(12);
    arr.insert(85);
    arr.insert(44);
    arr.insert(3);

    arr.insert(99);
    arr.insert(0);
    arr.insert(108);
    arr.insert(36);

    arr.display();

    arr.mergeSort();

    arr.display();
}