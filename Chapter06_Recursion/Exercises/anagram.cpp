// anagram.cpp

#include <iostream>
#include <iomanip>
using namespace std;

int size;
int wordCount = 0;
char* arrChar = new char[100];

void rotate(int newSize) {
    int j;
    int position = size - newSize;
    char temp = arrChar[position];
    for (j = position + 1; j < size; j++)
        arrChar[j - 1] = arrChar[j];
    arrChar[j - 1] = temp;
}

void displayWord() {
    cout << setw(3) << ++wordCount << " ";
    for (int j = 0; j < size; j++)
        cout << arrChar[j];
    cout << "   ";
    cout.flush();
    if (wordCount % 6 == 0)
        cout << endl;
}

void doAnagram(int newSize) {
    if (newSize == 1)
        return;
    for (int j = 0; j < newSize; j++) {
        doAnagram(newSize - 1);
        if (newSize == 2)
            displayWord();
        rotate(newSize);
    }
}

int main() {
    cout << "Enter a word: ";
    string input;
    cin >> input;
    size = input.size();
    for (int j = 0; j < size; j++)
        arrChar[j] = input[j];
    doAnagram(size);
}