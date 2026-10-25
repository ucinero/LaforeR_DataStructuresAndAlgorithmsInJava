// towers.cpp

#include <iostream>
using namespace std;

void doTowers(int topN, char from, char inter, char to) {
    if (topN == 1)
        cout << "Disk 1 from " << from << " to " << to << endl;
    else {
        doTowers(topN - 1, from, to, inter);
        cout << "Disk " << topN << " from " << from << " to " << to << endl;
        doTowers(topN - 1, inter, from, to);
    }
}

int main() {
    int nDisks = 4;
    doTowers(nDisks, 'A', 'B', 'C');
}