// project_5_3.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
        Link* previous;
    public:
        Link(long dd) : dData(dd), next(nullptr), previous(nullptr) {}
        void displayLink() {
            cout << dData << " ";
        }
};

class CircularList {
    private:
        Link* current;
    public:
        CircularList() : current(nullptr) {}
        ~CircularList() {
            if (current == nullptr)
                return;
            Link* start = current;
            Link* temp = current;
            do {
                Link* next = temp->next;
                delete temp;
                temp = next;
            } while (temp != start);
            current = nullptr;
        }
        bool isEmpty() {
            return current == nullptr;
        }
        void step() {
            if (isEmpty())
                return;
            current = current->next;
        }
        bool find(long key) {
            if (isEmpty())
                return false;
            Link* start = current;
            Link* temp = current;
            do {
                if (temp->dData == key) {
                    current = temp;
                    return true;
                }
                temp = temp->next;
            } while (temp != start);
            return false;
        }
        void insert(long key) {
            Link* newLink = new Link(key);
            if (isEmpty()) {
                current = newLink;
                newLink->next = newLink;
                newLink->previous = newLink;
                return;
            }
            newLink->next = current->next;
            newLink->next->previous = newLink;--
            newLink->previous = current;
            current->next = newLink;
            current = newLink;
        }
        long remove() {
            if (isEmpty())
                return 0;
            if (current->next == current) {
                long dData = current->dData;
                delete current;
                current = nullptr;
                return dData;
            }
            Link* temp = current;
            long dData = current->dData;
            current = temp->previous;
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            delete temp;
            return dData;
        }
        void display() {
            if (isEmpty())
                return;
            if (current->next == current) {
                current->displayLink();
                return;
            }
            Link* start = current;
            Link* temp = current;
            do {
                temp->displayLink();
                temp = temp->next;
            } while (temp != start);
        }
};

int main() {
    // =========================================================
    // ТЕСТ 1: Пустой список
    // =========================================================
    cout << "=== ТЕСТ 1: Пустой список ===" << endl;
    {
        CircularList list;
        cout << "isEmpty (ожидаем 1): " << list.isEmpty() << endl;
        cout << "find(10) (ожидаем 0): " << list.find(10) << endl;
        cout << "remove из пустого (ожидаем 0): " << list.remove() << endl;
        cout << "display: ";
        list.display();
        cout << endl;
    }

    // =========================================================
    // ТЕСТ 2: Первый элемент
    // =========================================================
    cout << "=== ТЕСТ 2: Первый элемент ===" << endl;
    {
        CircularList list;
        list.insert(10);
        cout << "isEmpty (ожидаем 0): " << list.isEmpty() << endl;
        cout << "display (ожидаем 10): ";
        list.display();
        cout << endl;
    }

    // =========================================================
    // ТЕСТ 3: Вставка 10, 20, 30 (current смещается)
    // =========================================================
    cout << "=== ТЕСТ 3: Вставка 10, 20, 30 ===" << endl;
    {
        CircularList list;
        list.insert(10);   // [10],         current=10
        list.insert(20);   // [10,20],      current=20
        list.insert(30);   // [10,20,30],   current=30

        // обход от current=30: 30, 10, 20
        cout << "display (ожидаем 30 10 20): ";
        list.display();
        cout << endl;

        list.insert(40);   // [10,20,30,40], current=40
        // обход от current=40: 40, 10, 20, 30
        cout << "display (ожидаем 40 10 20 30): ";
        list.display();
        cout << endl;
    }

    // =========================================================
    // ТЕСТ 4: step() — перемещение по кругу
    // =========================================================
    cout << "=== ТЕСТ 4: step() ===" << endl;
    {
        CircularList list;
        list.insert(10);   // [10],           current=10
        list.insert(20);   // [10,20],        current=20
        list.insert(30);   // [10,20,30],     current=30

        // список в памяти: 10 -> 20 -> 30 -> (10)
        // current = 30
        cout << "старт, display (ожидаем 30 10 20): ";
        list.display();
        cout << endl;

        list.step();       // current = 10
        cout << "step 1, display (ожидаем 10 20 30): ";
        list.display();
        cout << endl;

        list.step();       // current = 20
        cout << "step 2, display (ожидаем 20 30 10): ";
        list.display();
        cout << endl;

        list.step();       // current = 30 — вернулись
        cout << "step 3, display (ожидаем 30 10 20): ";
        list.display();
        cout << endl;
    }

    // =========================================================
    // ТЕСТ 5: find() — поиск элемента
    // =========================================================
    cout << "=== ТЕСТ 5: find() ===" << endl;
    {
        CircularList list;
        list.insert(10);   // [10],           current=10
        list.insert(20);   // [10,20],        current=20
        list.insert(30);   // [10,20,30],     current=30

        cout << "find(10) (ожидаем 1): " << list.find(10) << endl;
        // current переместился на 10
        cout << "display после find(10) (ожидаем 10 20 30): ";
        list.display();
        cout << endl;

        cout << "find(30) (ожидаем 1): " << list.find(30) << endl;
        // current = 30
        cout << "display после find(30) (ожидаем 30 10 20): ";
        list.display();
        cout << endl;

        cout << "find(99) (ожидаем 0): " << list.find(99) << endl;
        cout << "display (ожидаем без изменений 30 10 20): ";
        list.display();
        cout << endl;
    }

    // =========================================================
    // ТЕСТ 6: remove() — удаление текущего элемента (current)
    // =========================================================
    cout << "=== ТЕСТ 6: remove() ===" << endl;
    {
        CircularList list;
        list.insert(10);   // [10],           current=10
        list.insert(20);   // [10,20],        current=20
        list.insert(30);   // [10,20,30],     current=30

        // список: 10 -> 20 -> 30 -> (10), current=30

        // удаляется сам current=30, current сдвигается на 10
        cout << "remove (ожидаем 30): " << list.remove() << endl;
        // список: 10 -> 20 -> (10), current=10
        cout << "display (ожидаем 20 10): ";
        list.display();
        cout << endl;

        // удаляется current=10, current сдвигается на 20
        cout << "remove (ожидаем 20): " << list.remove() << endl;
        // список: 20 -> (20), current=20
        cout << "display (ожидаем 10): ";
        list.display();
        cout << endl;

        // удаляется current=20 — список пуст
        cout << "remove (ожидаем 10): " << list.remove() << endl;
        cout << "isEmpty (ожидаем 1): " << list.isEmpty() << endl;
    }

    // =========================================================
    // ТЕСТ 7: Полный круг через step()
    // =========================================================
    cout << "=== ТЕСТ 7: Полный круг ===" << endl;
    {
        CircularList list;
        list.insert(1);   // [1],             current=1
        list.insert(2);   // [1,2],           current=2
        list.insert(3);   // [1,2,3],         current=3
        list.insert(4);   // [1,2,3,4],       current=4

        // список: 1 -> 2 -> 3 -> 4 -> (1), current=4
        cout << "Идём по кругу 8 шагов:" << endl;
        for (int i = 0; i < 8; i++) {
            cout << "шаг " << i << ": ";
            list.display();
            cout << endl;
            list.step();
        }
    }

    // =========================================================
    // ТЕСТ 8: Смешанные операции
    // =========================================================
    cout << "=== ТЕСТ 8: Смешанные операции ===" << endl;
    {
        CircularList list;
        list.insert(100);       // [100],               current=100
        list.insert(200);       // [100,200],           current=200
        list.step();            // current=100 (следующий после 200)
        list.insert(300);       // [100,300,200],       current=300
        list.step();            // current=200
        list.insert(400);       // [100,300,200,400],   current=400

        // список: 100 -> 300 -> 200 -> 400 -> (100), current=400
        cout << "display (ожидаем 400 100 300 200): ";
        list.display();
        cout << endl;

        cout << "find(300) (ожидаем 1): " << list.find(300) << endl;
        cout << "display (ожидаем 300 200 400 100): ";
        list.display();
        cout << endl;

        // следующий за current=300: 200
        cout << "remove (ожидаем 200): " << list.remove() << endl;
        // список: 100 -> 300 -> 400 -> (100), current=300
        cout << "display (ожидаем 300 400 100): ";
        list.display();
        cout << endl;

        list.step();            // current=400
        // следующий за current=400: 100
        cout << "remove (ожидаем 100): " << list.remove() << endl;
        // список: 300 -> 400 -> (300), current=400
        cout << "display (ожидаем 400 300): ";
        list.display();
        cout << endl;
    }

    // =========================================================
    // ТЕСТ 9: Опустошение через remove()
    // =========================================================
    cout << "=== ТЕСТ 9: Опустошение ===" << endl;
    {
        CircularList list;
        list.insert(5);    // [5],             current=5
        list.insert(6);    // [5,6],           current=6
        list.insert(7);    // [5,6,7],         current=7

        // список: 5 -> 6 -> 7 -> (5), current=7
        cout << "Удаляем все элементы:" << endl;
        while (!list.isEmpty()) {
            cout << "remove = " << list.remove()
                 << ", isEmpty = " << list.isEmpty() << endl;
        }
        cout << "Финальный isEmpty (ожидаем 1): " << list.isEmpty() << endl;
    }

    return 0;
}