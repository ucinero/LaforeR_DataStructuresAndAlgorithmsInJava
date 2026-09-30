// project_4_2.cpp

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

int main() {
    cout << "=== ТЕСТ 1: Базовая вставка и удаление ===" << endl;
    Deque d1(5);
    d1.insertRight(10);
    d1.insertRight(20);
    d1.insertLeft(5);
    d1.insertLeft(1);
    cout << "Текущий размер: " << d1.size() << endl;
    cout << "Удаляем слева (ожидаем 1): " << d1.removeLeft() << endl;
    cout << "Удаляем справа (ожидаем 20): " << d1.removeRight() << endl;
    cout << "Текущий размер: " << d1.size() << endl;
    cout << endl;

    cout << "=== ТЕСТ 2: Проверка закольцовывания (Circular) ===" << endl;
    Deque d2(4);
    d2.insertRight(1);
    d2.insertRight(2);
    d2.insertRight(3);
    // Массив: [1, 2, 3, _], front=0, rear=2
    cout << "Удаляем слева (ожидаем 1): " << d2.removeLeft() << endl; 
    cout << "Удаляем слева (ожидаем 2): " << d2.removeLeft() << endl; 
    // Массив: [_, _, 3, _], front=2, rear=2
    d2.insertRight(4); 
    d2.insertRight(5); 
    // Если закольцовывание работает, 5 должно встать в начало массива
    cout << "Размер после закольцовывания (ожидаем 3): " << d2.size() << endl;
    cout << "Удаляем слева (ожидаем 3): " << d2.removeLeft() << endl; 
    cout << "Удаляем справа (ожидаем 5): " << d2.removeRight() << endl; 
    cout << "Удаляем слева (ожидаем 4): " << d2.removeLeft() << endl; 
    cout << endl;

    cout << "=== ТЕСТ 3: Проверка переполнения (isFull) ===" << endl;
    Deque d3(3);
    d3.insertRight(100);
    d3.insertRight(200);
    d3.insertLeft(50);
    cout << "Размер (ожидаем 3): " << d3.size() << endl;
    cout << "Очередь полна? (ожидаем 1): " << d3.isFull() << endl;
    // Попытка вставить 4-й элемент (должна быть обработана корректно)
    d3.insertRight(300); 
    cout << "Размер после попытки вставки (ожидаем 3): " << d3.size() << endl;
    cout << endl;

    cout << "=== ТЕСТ 4: Проверка опустошения (isEmpty) ===" << endl;
    Deque d4(2);
    d4.insertRight(7);
    cout << "Удаляем единственный элемент (ожидаем 7): " << d4.removeLeft() << endl;
    cout << "Очередь пуста? (ожидаем 1): " << d4.isEmpty() << endl;
    // Попытка удалить из пустой очереди (должна быть обработана корректно)
    cout << "Попытка удалить слева: " << d4.removeLeft() << endl; 
    cout << "Попытка удалить справа: " << d4.removeRight() << endl; 
    cout << endl;

    cout << "=== ТЕСТ 5: Смешанные операции ===" << endl;
    Deque d5(5);
    d5.insertLeft(10);
    d5.insertRight(20);
    d5.insertLeft(5);
    d5.insertRight(30);
    cout << "Размер (ожидаем 4): " << d5.size() << endl;
    cout << "Удаляем слева (ожидаем 5): " << d5.removeLeft() << endl; 
    cout << "Удаляем справа (ожидаем 30): " << d5.removeRight() << endl; 
    d5.insertLeft(1);
    d5.insertRight(40);
    cout << "Размер (ожидаем 4): " << d5.size() << endl;
    cout << "Удаляем слева (ожидаем 1): " << d5.removeLeft() << endl; 
    cout << "Удаляем слева (ожидаем 10): " << d5.removeLeft() << endl; 
    cout << "Удаляем справа (ожидаем 40): " << d5.removeRight() << endl; 
    cout << "Удаляем слева (ожидаем 20): " << d5.removeLeft() << endl; 
    cout << "Очередь пуста? (ожидаем 1): " << d5.isEmpty() << endl;

    return 0;
}