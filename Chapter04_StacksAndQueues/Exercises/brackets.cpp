// brackets.cpp

#include <iostream>
using namespace std;

class StackX {
    private:
        int maxSize;
        char* stackArray;
        int top;
    public:
        StackX(int s) {
            maxSize = s;
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
        bool isFull() {
            return top == maxSize - 1;
        }
};

class BracketChecker {
    private:
        string input;
    public:
        BracketChecker(string in) {
            input = in;
        }
        void check() {
            int stackSize = input.size();
            StackX* theStack = new StackX(stackSize);

            for (int j = 0; j < input.size(); j++) {
                char ch = input[j];
                switch (ch) {
                    case '{':
                    case '[':
                    case '(':
                        theStack->push(ch);
                        break;
                    case '}':
                    case ']':
                    case ')':
                        if (!theStack->isEmpty()) {
                            char chx = theStack->pop();
                            if ((ch == '}' && chx != '{') ||
                                (ch == ']' && chx != '[') ||
                                (ch == ')' && chx != '(')) 
                                cout << "Error: " << ch << " at " << j;
                        }
                        else
                            cout << "Error: " << ch << " at " << j;
                        break;
                    default:
                        break;
                }
            }
            if (!theStack->isEmpty())
            cout << "Error: missing right delimiter";
        }
};

int main() {
    string input;
    while (true) {
        cout << "Enter string containing delimiters: ";
        cout.flush();
        cin >> input;
        if (input == "")
            break;
        
        BracketChecker* theChecker = new BracketChecker(input);
        theChecker->check();
        delete theChecker;
        cout << endl;
    }
    return 0;
}