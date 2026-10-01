// project_4_3.cpp

#include <iostream>
using namespace std;

class Deque {
    private:
        int maxSize;
        long* queArray;
        int front;
        int rear;
        int nItems;
    public:
        Deque(int s) {
            maxSize = s;
            queArray = new long[maxSize];
            front = 0;
            rear = -1;
            nItems = 0;
        }
        void insertLeft(long j) {
            if (front == 0)
                front = maxSize - 1;
            else
                front--;
            queArray[front] = j;
            nItems++;
        }
        void insertRight(long j) {
            if (rear == maxSize - 1)
                rear = -1;
            else
                rear++;
            queArray[rear] = j;
            nItems++;
        }
        long removeLeft() {
            long temp = queArray[front];
            if (front == maxSize - 1)
                front = 0;
            else
                front++;
            nItems--;
            return temp;
        }
        long removeRight() {
            long temp = queArray[rear];
            if (rear == 0)
                rear = maxSize - 1;
            else
                rear--;
            nItems--;
            return temp;
        }
        long peekFront() {
            return queArray[front];
        }
        bool isEmpty() {
            return nItems == 0;
        }
        bool isFull() {
            return nItems == maxSize;
        }
        int size() {
            return nItems;
        }
};

class StackX : private Deque {
    private:
        int maxSize;
        long* stackArray;
        int top;
    public:
        StackX(int s) : Deque(s) {
            maxSize = s;
            stackArray = new long[maxSize];
            top = -1;
        }
        void push(long j) {
            Deque::insertRight(j);
        }
        long pop() {
            return Deque::removeRight();
        }
        long peek() {
            return Deque::peekFront();
        }
        bool isEmpty() {
            return Deque::isEmpty();
        }
        bool isFull() {
            return Deque::isFull();
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

    return 0;
}