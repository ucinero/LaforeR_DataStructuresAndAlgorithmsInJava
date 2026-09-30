// project_4_1.cpp

#include <iostream>
using namespace std;

class Queue {
    private:
        int maxSize;
        long* queArray;
        int front;
        int rear;
        int nItems;
    public:
        Queue(int s) {
            maxSize = s;
            queArray = new long[maxSize];
            front = 0;
            rear = -1;
            nItems = 0;
        }
        void insert(long j) {
            if (rear == maxSize - 1)
                rear = -1;
            queArray[++rear] = j;
            nItems++;
        }
        long remove() {
            if (isEmpty())
                return 0;
            long temp = queArray[front++];
            if (front == maxSize)
                front = 0;
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
        void display() {
            if (isEmpty())
                cout << "the Queue is empty";
            else {
                if (front > rear) {
                    for (int i = front; i < nItems; i++)
                        cout << queArray[i] << " ";
                    for (int i = 0; i <= rear; i++)
                        cout << queArray[i] << " ";
                }
                else {
                    for (int i = front; i <= rear; i++)
                        cout << queArray[i] << " ";
                }
            }
            cout << endl;
        }
};

int main() {
    Queue theQueue(5);

    theQueue.insert(10);
    theQueue.insert(20);
    theQueue.insert(30);
    theQueue.insert(40);

    theQueue.display();

    theQueue.remove();
    theQueue.remove();
    theQueue.remove();

    theQueue.insert(50);
    theQueue.insert(60);
    theQueue.insert(70);
    theQueue.insert(80);

    theQueue.display();

    while (!theQueue.isEmpty()) {
        long n = theQueue.remove();
        cout << n << " ";
    }
    cout << endl;
    
    return 0;
}