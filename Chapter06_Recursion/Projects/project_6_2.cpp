// project_6_2.cpp

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int size = 64;
const int rows = static_cast<int>(log2(size)) + 1;
char** tree = new char*[rows];

void makeBranches(int left, int right, int number) {
    if (left > right)
        return;
    else {
        int mid = left + (right - left) / 2;
        tree[number][mid] = 'X';
        makeBranches(left, mid - 1, number + 1);
        makeBranches(mid + 1, right, number + 1);
    }
}

void display() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < size; j++)
            cout << tree[i][j];
        cout << endl;
    }
}

int main() {
    for (int i = 0; i < rows; i++)
        tree[i] = new char[size];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < size; j++)
            tree[i][j] = '-';

    makeBranches(0, size - 1, 0);
    display();

    for (int i = 0; i < rows; i++)
        delete tree[i];
    delete[] tree;

    return 0;
}