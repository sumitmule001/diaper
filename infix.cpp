#include <iostream>
#include <string>
#include <cctype>  // isdigit
#include <cmath>   // pow

using namespace std;

// Node for linked list stack
template<typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

// Stack class using linked list
template<typename T>
class Stack {
    Node<T>* topNode;
public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!isEmpty()) pop();
    }

    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    T pop() {
        if (isEmpty()) throw runtime_error("Stack underflow");
        Node<T>* temp = topNode;
        T val = topNode->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    T top() {
        if (isEmpty()) throw runtime_error("Stack empty");
        return topNode->data;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }
};

// Function to get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Check if operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Infix to Postfix conversion
string infixToPostfix(const string& infix) {
    Stack<char> s;
    string postfix;

    for (size_t i = 0; i < infix.length(); ++i) {
        char ch = infix[i];

        if (isspace(ch)) continue;

        if (isdigit(ch)) {
            // Append full number (support multi-digit)
            while (i < infix.length() && isdigit(infix[i])) {
                postfix += infix[i++];
            }
            postfix += ' ';  // delimiter for number
            --i;
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.isEmpty() && s.top() != '(') {
                postfix += s.pop();
                postfix += ' ';
            }
            if (!s.isEmpty()) s.pop();  // pop '('
            else throw runtime_error("Mismatched parentheses");
        }
        else if (isOperator(ch)) {
            while (!s.isEmpty() && precedence(s.top()) >= precedence(ch)) {
                // For right-associative '^', break if same precedence
                if (ch == '^' && s.top() == '^') break;
                postfix += s.pop();
                postfix += ' ';
            }
            s.push(ch);
        }
        else {
            throw runtime_error(string("Invalid character: ") + ch);
        }
    }

    while (!s.isEmpty()) {
        if (s.top() == '(') throw runtime_error("Mismatched parentheses");
        postfix += s.pop();
        postfix += ' ';
    }

    return postfix;
}

// Apply operator for evaluation
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        case '^': return (int)pow(a, b);
    }
    throw runtime_error("Invalid operator");
}

// Evaluate postfix expression
int evaluatePostfix(const string& postfix) {
    Stack<int> s;
    size_t i = 0;

    while (i < postfix.length()) {
        if (isspace(postfix[i])) {
            i++;
            continue;
        }

        if (isdigit(postfix[i])) {
            int num = 0;
            while (i < postfix.length() && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            s.push(num);
        }
        else if (isOperator(postfix[i])) {
            int b = s.pop();
            int a = s.pop();
            int res = applyOp(a, b, postfix[i]);
            s.push(res);
            i++;
        }
        else {
            throw runtime_error(string("Invalid postfix char: ") + postfix[i]);
        }
    }

    int result = s.pop();
    if (!s.isEmpty()) throw runtime_error("Invalid postfix expression");
    return result;
}

int main() {
    cout << "Enter infix expression (e.g. 3+(2*4)-5^2): ";
    string infix;
    getline(cin, infix);

    try {
        string postfix = infixToPostfix(infix);
        cout << "Postfix expression: " << postfix << endl;

        int result = evaluatePostfix(postfix);
        cout << "Evaluated result: " << result << endl;
    }
    catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}




