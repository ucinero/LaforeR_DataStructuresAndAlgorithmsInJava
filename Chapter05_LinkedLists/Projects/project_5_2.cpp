// project_5_2.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
        Link* previous;
    public:
        Link(long d) : dData(d), next(nullptr), previous(nullptr) {}
        void displayLink() {
            cout << dData << " ";
        }
};

class DoublyLinkedList {
    private:
        Link* first;
        Link* last;
    public:
        DoublyLinkedList() : first(nullptr), last(nullptr) {}
        ~DoublyLinkedList() {
            Link* current = first;
            while (current != nullptr) {
                Link* next = current->next;
                delete current;
                current = next;
            }
        }
        bool isEmpty() {
            return first == nullptr;
        }
        void insertFirst(long dd) {
            Link* newLink = new Link(dd);
            if (isEmpty())
                last = newLink;
            else {
                first->previous = newLink;
                newLink->next = first;
            }
            first = newLink;
        }
        void insertLast(long dd) {
            Link* newLink = new Link(dd);
            if (isEmpty())
                first = newLink;
            else {
                last->next = newLink;
                newLink->previous = last;
            }
            last = newLink;
        }
        long deleteFirst() {
            if (isEmpty())
                return 0;
            Link* temp = first;
            long data = temp->dData;
            if (first->next == nullptr)
                last = nullptr;
            else
                first->next->previous = nullptr;
            first = first->next;
            delete temp;
            return data;
        }
        long deleteLast() {
            if (isEmpty())
                return 0;
            if (first->next == nullptr)
                first = nullptr;
            else
                last->previous->next = nullptr;
            long data = last->dData;
            Link* temp = last;
            last = last->previous;
            delete temp;
            return data;
        }
        bool insertAfter(long key, long dd) {
            if (isEmpty())
                return false;
            Link* current = first;
            while (current->dData != key) {
                current = current->next;
                if (current == nullptr)
                    return false;
            }
            Link* newLink = new Link(dd);
            if (current == last) {
                newLink->next = nullptr;
                last = newLink;
            }
            else {
                newLink->next = current->next;
                current->next->previous = newLink;
            }
            newLink->previous = current;
            current->next = newLink;
            return true;
        }
        long deleteKey(long key) {
            if (isEmpty())
                return 0;
            Link* current = first;
            while (current->dData != key) {
                current = current->next;
                if (current == nullptr)
                    return 0;
            }
            if (current == first)
                first = current->next;
            else
                current->previous->next = current->next;

            if (current == last)
                last = current->previous;
            else
                current->next->previous = current->previous;
            
            long data = current->dData;
            delete current;
            return data;
        }
        void displayForward() {
            cout << "List (first-->last): ";
            Link* current = first;
            while (current != nullptr) {
                current->displayLink();
                current = current->next;
            }
            cout << endl;
        }
        void displayBackward() {
            cout << "List (last-->first): ";
            Link* current = last;
            while (current != nullptr) {
                current->displayLink();
                current = current->previous;
            }
            cout << endl;
        }
        long getFirst() {
            if (isEmpty())
                return 0;
            return first->dData;
        }
        long getLast() {
            if (isEmpty())
                return 0;
            return last->dData;
        }
};

class Deque {
    private:
        int maxSize;
        DoublyLinkedList* queArray;
        int nItems;
    public:
        Deque(int s) {
            maxSize = s;
            queArray = new DoublyLinkedList();
            nItems = 0;
        }
        ~Deque() {
            delete queArray;
        }
        void insertLeft(long j) {
            if (isFull())
                return;
            queArray->insertFirst(j);
            nItems++;
        }
        void insertRight(long j) {
            if (isFull())
                return;
            queArray->insertLast(j);
            nItems++;
        }
        long removeLeft() {
            if (isEmpty())
                return 0;
            nItems--;
            return queArray->deleteFirst();
        }
        long removeRight() {
            if (isEmpty())
                return 0;
            nItems--;
            return queArray->deleteLast();
        }
        long peekFront() {
            if (isEmpty())
                return 0;
            return queArray->getFirst();
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