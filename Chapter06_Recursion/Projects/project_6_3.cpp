// project_6_3.cpp

#include <iostream>
using namespace std;

int power(int n, int m) {
    if (m == 0)
        return 1;
    else {
        if (m % 2 == 0)
            return power(n * n, m / 2);
        else
            return n * power(n * n, m / 2);
    }
}

int main() {
    int n = 3;
    int m = 9;
    cout << power(n, m) << endl;
    return 0;
}