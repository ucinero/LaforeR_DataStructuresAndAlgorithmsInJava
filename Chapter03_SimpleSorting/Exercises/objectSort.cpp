// objectSort.cpp

#include <iostream>
#include <string>
using namespace std;

class Person {
    private:
        string lastName;
        string firstName;
        int age;
    public:
        Person(string last, string first, int a) {
            lastName = last;
            firstName = first;
            age = a;
        }
        void displayPerson() {
            cout << "Last name: " << lastName
                 << ", First name: " << firstName
                 << ", Age: " << age << endl;
        }
        string getLast() {
            return lastName;
        }
};

class ArrayInOb {
    private:
        Person** a;
        int nElems;
    public:
        ArrayInOb(int max) {
            a = new Person*[max];
            nElems = 0;
        }
        void insert(string last, string first, int age) {
            a[nElems] = new Person(last, first, age);
            nElems++;
        }
        void display() {
            for (int j = 0; j < nElems; j++)
                a[j]->displayPerson();
            cout << endl;
        }
        void insertionSort() {
            int in, out;
            for (out = 1; out < nElems; out++) {
                Person* temp = a[out];
                in = out;
                while (in > 0 && a[in - 1]->getLast() > temp->getLast()) {
                    a[in] = a[in - 1];
                    in--;
                }
                a[in] = temp;
            }
        }
};

int main() {
    int maxSize = 100;
    ArrayInOb arr(maxSize);

    arr.insert("Evans",     "Patty",    24);
    arr.insert("Smith",     "Lorraine", 37);
    arr.insert("Yee",       "Tom",      43);
    arr.insert("Adams",     "Henry",    63);
    arr.insert("Hashimoto", "Sato",     21);
    arr.insert("Stimson",   "Henry",    29);
    arr.insert("Velasquez", "Jose",     72);
    arr.insert("Lamarque",  "Henry",    54);
    arr.insert("Vang",      "Minh",     22);
    arr.insert("Creswell",  "Lucinda",  18);

    cout << "Before sorting: ";
    arr.display();

    arr.insertionSort();

    cout << "After sorting: ";
    arr.display();

    return 0;
}