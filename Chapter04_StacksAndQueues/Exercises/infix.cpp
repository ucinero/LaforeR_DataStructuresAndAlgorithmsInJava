// infix.cpp

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
        int size() {
            return top + 1;
        }
        char peekN(int n) {
            return stackArray[n];
        }
        void displayStack(string s) {
            cout << s;
            cout << "Stack (bottom-->top): ";
            for (int j = 0; j < size(); j++) {
                cout << peekN(j);
                cout << " ";
            }
            cout << endl;
        }
};

class InToPost {
    private:
        StackX* theStack;
        string input;
        string output = "";
    public:
        InToPost(string in) {
            input = in;
            int stackSize = input.size();
            theStack = new StackX(stackSize);
        }
        string doTrans() {
            for (int j = 0; j < input.size(); j++) {
                char ch = input[j];
                string answer = "For " + ch;
                answer += " ";
                theStack->displayStack(answer);
                switch(ch) {
                    case '+':
                    case '-':
                        gotOper(ch, 1);
                        break;
                    case '*':
                    case '/':
                        gotOper(ch, 2);
                        break;
                    case '(':
                        theStack->push(ch);
                        break;
                    case ')':
                        gotParen(ch);
                        break;
                    default:
                        output += ch;
                        break;
                }
            }
            while (!theStack->isEmpty()) {
                theStack->displayStack("While ");
                output += theStack->pop();
            }
            theStack->displayStack("End ");
            return output;
        }
        void gotOper(char opThis, int prec1) {
            while (!theStack->isEmpty()) {
                char opTop = theStack->pop();
                if (opTop == '(') {
                    theStack->push(opTop);
                    break;
                }
                else {
                    int prec2;
                    if (opTop == '+' || opTop == '-')
                        prec2 = 1;
                    else
                        prec2 = 2;
                    if (prec2 < prec1) {
                        theStack->push(opTop);
                        break;
                    }
                    else
                        output += opTop;
                }
            }
            theStack->push(opThis);
        }
        void gotParen(char ch) {
            while (!theStack->isEmpty()) {
                char chx = theStack->pop();
                if (chx == '(')
                    break;
                else
                    output += chx;
            }
        }
};

int main() {
    string input, output;
    while (true) {
        cout << "Enter infix: ";
        cout.flush();
        cin >> input;
        if (input == "")
            break;
        
        InToPost* theTrans = new InToPost(input);
        output = theTrans->doTrans();
        cout << "Postfix is " << output << endl;
    }

    return 0;
}