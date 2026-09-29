// reverse.cpp

#include <iostream>
using namespace std;

class StackX {
    private:
        int maxSize;
        char* stackArray;
        int top;
    public:
        StackX(int max) {
            maxSize = max;
            stackArray = new char[maxSize];
            top = -1;
        }
        void push(char j) {
            stackArray[++top] = j;
        }
        char pop() {
            return stackArray[top--];
        }
        char peek() {
            return stackArray[top];
        }
        bool isEmpty() {
            return top == -1;
        }
};

class Reverser {
    private:
        string input;
        string output;
    public:
        Reverser(string in) {
            input = in;
        }
        string doRev() {
            int stackSize = input.size();
            StackX* theStack = new StackX(stackSize);

            for (int j = 0; j < stackSize; j++) {
                char ch = input[j];
                theStack->push(ch);
            }

            output = "";
            
            while (!theStack->isEmpty()) {
                char ch = theStack->pop();
                output += ch;
            }

            delete theStack;
            return output;
        }
};

int main() {
    string input, output;
    while (true) {
        cout << "Enter a string: ";
        cout.flush();
        cin >> input;
        if (input == "")
            break;
        
        Reverser* theReverser = new Reverser(input);

        output = theReverser->doRev();
        cout << "Reversed: " << output << endl;
        
        delete theReverser;
    }
}