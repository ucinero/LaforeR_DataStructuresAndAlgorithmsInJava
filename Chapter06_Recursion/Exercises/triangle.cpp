// triangle.cpp

#include <iostream>
using namespace std;

int triangle(int n) {
    cout << "Entering: n = " << n << endl;
    if (n == 1) {
        cout << "Returning 1" << endl;
        return 1;
    }
    int temp = n + triangle(n - 1);
    cout << "Returning " << temp << endl;
    return temp;
}

int main() {
    int theNumber;
    cout << "Enter a number: ";
    cin >> theNumber;
    int theAnswer = triangle(theNumber);
    cout << "Triangle = " << theAnswer << endl;

    return 0;
}