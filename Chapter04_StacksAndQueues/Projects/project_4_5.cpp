// project_4_5.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

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
        
        ~Queue() {
            delete[] queArray;
        }

        void insert(long j) {
            if (rear == maxSize - 1)
                rear = -1;
            queArray[++rear] = j;
            nItems++;
        }

        long remove() {
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
            if (isEmpty()) {
                cout << "[пусто]";
                return;
            }
            for (int i = 0; i < nItems; i++) {
                int index = (front + i) % maxSize;
                cout << "[" << queArray[index] << "] ";
            }
        }
};

class Customer {
public:
    int id;
    int itemsCount;

    Customer() : id(0), itemsCount(0) {}
    Customer(int i, int items) : id(i), itemsCount(items) {}
};

const int NUM_QUEUES = 3;
const int MAX_QUEUE_SIZE = 20;

int main() {
    srand(time(0));

    Queue* queues[NUM_QUEUES];
    for (int i = 0; i < NUM_QUEUES; i++) {
        queues[i] = new Queue(MAX_QUEUE_SIZE);
    }

    int customerTimes[1000]; 
    int nextCustomerId = 1;

    cout << "--- СИМУЛЯЦИЯ МАГАЗИНА ---" << endl;
    cout << "Нажмите Enter, чтобы добавить покупателя (или 'q' для выхода)." << endl;
    cout << "Каждое нажатие Enter также моделирует 1 минуту времени." << endl;

    while (true) {
        cout << "\n--- Состояние очередей (Минута) ---" << endl;
        for (int i = 0; i < NUM_QUEUES; i++) {
            cout << "Касса " << (i + 1) << " (размер " << queues[i]->size() << "): ";
            queues[i]->display();
            cout << endl;
        }
        cout << "-----------------------------------" << endl;
        cout << "Нажмите Enter (добавить покупателя и пропустить минуту) или 'q' (выход): ";
        
        string input;
        getline(cin, input);
        if (input == "q" || input == "Q") break;

        int shortestQueueIndex = 0;
        int minSize = queues[0]->size();

        for (int i = 1; i < NUM_QUEUES; i++) {
            if (queues[i]->size() < minSize) {
                minSize = queues[i]->size();
                shortestQueueIndex = i;
            }
        }

        int items = rand() % 5 + 1; 
        Customer newCust(nextCustomerId, items);
        
        customerTimes[newCust.id] = newCust.itemsCount;

        if (!queues[shortestQueueIndex]->isFull()) {
            queues[shortestQueueIndex]->insert(newCust.id);
            cout << ">> Новый покупатель #" << newCust.id 
                 << " (товаров: " << newCust.itemsCount << ") встал в очередь на Кассу " 
                 << (shortestQueueIndex + 1) << endl;
            nextCustomerId++;
        } else {
            cout << ">> Все кассы переполнены! Покупатель ушел." << endl;
        }

        for (int i = 0; i < NUM_QUEUES; i++) {
            if (!queues[i]->isEmpty()) {
                long currentCustId = queues[i]->peekFront();
                
                customerTimes[currentCustId]--;

                if (customerTimes[currentCustId] <= 0) {
                    queues[i]->remove();
                    cout << "   [Касса " << (i + 1) << "] Покупатель #" << currentCustId << " обслужен и ушел." << endl;
                }
            }
        }
    }

    for (int i = 0; i < NUM_QUEUES; i++) {
        delete queues[i];
    }

    return 0;
}