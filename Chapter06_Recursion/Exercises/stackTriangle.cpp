// stackTriangle.cpp

#include <iostream>
using namespace std;

class Params {
    public:
        int n;
        int returnAddress;
    public:
        Params(int nn, int ra) : n(nn), returnAddress(ra) {}
};

class StackX {
    private:
        int maxSize;
        Params** stackArray;
        int top;
    public:
        StackX(int s) {
            maxSize = s;
            stackArray = new Params*[maxSize];
            top = -1;
        }
        ~StackX() {
            for (int i = 0; i < maxSize; i++)
                delete stackArray[i];
            delete[] stackArray;
        }
        void push(Params* p) {
            stackArray[++top] = p;
        }
        Params* pop() {
            return stackArray[top--];
        }
        Params* peek() {
            return stackArray[top];
        }
};

int theNumber;
int theAnswer;
StackX* theStack;
int codePart;
Params* theseParams;

bool step() {
    switch(codePart) {
        case 1: {
            theseParams = new Params(theNumber, 6);
            theStack->push(theseParams);
            codePart = 2;
            break; }
        case 2: {
            theseParams = theStack->peek();
            if (theseParams->n == 1) {
                theAnswer = 1;
                codePart = 5;
            }
            else
                codePart = 3;
            break; }
        case 3: {
            Params* newParams = new Params(theseParams->n - 1, 4);
            theStack->push(newParams);
            codePart = 2;
            break; }
        case 4: {
            theseParams = theStack->peek();
            theAnswer += theseParams->n;
            codePart = 5;
            break; }
        case 5: {
            theseParams = theStack->peek();
            codePart = theseParams->returnAddress;
            theStack->pop();
            break; }
        case 6:
            return true;
    }
    return false;
}

void recTriangle() {
    theStack = new StackX(10'000);
    codePart = 1;
    while (step() == false) {}
    delete theStack;
}

int main() {
    cout << "Enter a number: ";
    cin >> theNumber;
    recTriangle();
    cout << "Triangle = " << theAnswer << endl;
}