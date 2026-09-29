// stack.cpp

#include <iostream>
using namespace std;

class StackX {
    private:
        int maxSize;
        long* stackArray;
        int top;
    public:
        StackX(int s) {
            maxSize = s;
            stackArray = new long[maxSize];
            top = -1;
        }
        void push(long j) {
            stackArray[++top] = j;
        }
        long pop() {
            return stackArray[top--];
        }
        long peek() {
            return stackArray[top];
        }
        bool isEmpty() {
            return top == -1;
        }
        bool isFull() {
            return top == maxSize - 1;
        }
};

int main() {
    StackX* theStack = new StackX(10);

    theStack->push(20);
    theStack->push(40);
    theStack->push(60);
    theStack->push(80);

    while (!theStack->isEmpty()) {
        long value = theStack->pop();
        cout << value << " ";
    }
    cout << endl;

    delete theStack;

    return 0;
}