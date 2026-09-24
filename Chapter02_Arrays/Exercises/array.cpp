// array.cpp

#include <iostream>
using namespace std;

int main() {
    long arr[100];
    int nElems = 0;
    int j;
    long searchKey;

    arr[0] = 77;
    arr[1] = 99;
    arr[2] = 44;
    arr[3] = 55;
    arr[4] = 22;
    arr[5] = 88;
    arr[6] = 11;
    arr[7] = 00;
    arr[8] = 66;
    arr[9] = 33;
    nElems = 10;

    for (j = 0; j < nElems; j++)
        cout << arr[j] << " ";
    cout << endl;

    searchKey = 66;
    for (j = 0; j < nElems; j++)
        if (arr[j] == searchKey)
            break;

    if (j == nElems)
        cout << "Can't find " << searchKey << endl;
    else
        cout << "Found " << searchKey << endl;

    searchKey = 55;
    for (j = 0; j < nElems; j++)
        if (arr[j] == searchKey)
            break;

    for (int k = j; k < nElems - 1; k++)
        arr[k] = arr[k + 1];

    nElems--;

    for (j = 0; j < nElems; j++)
        cout << arr[j] << " ";
    cout << endl;

    return 0;
}