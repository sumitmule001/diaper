#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
using namespace std;

#define MAX 100

// Stack implementation using array
class Stack {
    int top;
    char arr[MAX];

public:
    Stack() { top = -1; }

    bool isEmpty() { return top == -1; }

    bool isFull() { return top == MAX - 1; }

    void push(char val) {
        if (isFull())
            cout << "Stack Overflow\n";
        else
            arr[++top] = val;
    }

    char pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        } else
            return arr[top--];
    }

    char peek() {
        if (isEmpty())
            return -1;
        return arr[top];
    }
};

// Function to define precedence of operators
int precedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}

// Convert infix expression to postfix
string infixToPostfix(string infix) {
    Stack s;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (isalnum(ch))  // operand
            postfix += ch;
        else if (ch == '(')
            s.push(ch);
        else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(')
                postfix += s.pop();
            s.pop(); // remove '('
        } else { // operator
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch))
                postfix += s.pop();
            s.push(ch);
        }
    }

    while (!s.isEmpty())
        postfix += s.pop();

    return postfix;
}

// Evaluate postfix expression
int evaluatePostfix(string postfix) {
    int stack[MAX];
    int top = -1;

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        if (isdigit(ch))
            stack[++top] = ch - '0';
        else {
            int val2 = stack[top--];
            int val1 = stack[top--];
            switch (ch) {
                case '+': stack[++top] = val1 + val2; break;
                case '-': stack[++top] = val1 - val2; break;
                case '*': stack[++top] = val1 * val2; break;
                case '/': stack[++top] = val1 / val2; break;
                case '^': stack[++top] = pow(val1, val2); break;
            }
        }
    }
    return stack[top];
}

// Main function
int main() {
    string infix;
    cout << "Enter Infix Expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Evaluated Result: " << result << endl;

    return 0;
}
