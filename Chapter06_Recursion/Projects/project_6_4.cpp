// project_6_4.cpp

#include <iostream>
using namespace std;

const int size = 5;
int a[size] = { 11, 8, 7, 6, 5 };

bool knapsack(int weight, int indx) {
    if (weight == 0) {
        return true;
    }
    for (int i = indx; i < size; i++) {
        if (knapsack(weight - a[i], i + 1)) {
            cout << a[i] << " ";
            return true;
        }
    }
}

int main() {
    knapsack(20, 0);
    cout << endl;
    return 0;
}