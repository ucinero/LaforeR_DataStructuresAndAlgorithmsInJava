// project_6_1.cpp

#include <iostream>
using namespace std;

int mult(int x, int y) {
    if (y == 0)
        return 1;
    return x * mult(x, y - 1);
}

int main() {
    int x, y;

    cout << "x = "; cin >> x;
    cout << "y = "; cin >> y;
    cout << "x ^ y = " << mult(x, y) << endl;

    return 0;
}