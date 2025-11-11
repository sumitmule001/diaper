#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
using namespace std;
#define MAX 100
//=================== STACK IMPLEMENTATION USING ARRAY ===================
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
}
return arr[top--];
}
char peek() {
if (isEmpty())
return -1;
return arr[top];
}
};
//=================== FUNCTION TO DEFINE OPERATOR PRECEDENCE ===================
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
//=================== INFIX TO POSTFIX CONVERSION ===================
string infixToPoshix(string infix) {
Stack s;
string poshix = "";
for (int i = 0; i < infix.length(); i++) {
char ch = infix[i];
if (isalnum(ch)) // If operand (number/variable)
poshix += ch;
else if (ch == '(')
s.push(ch);
else if (ch == ')') {
while (!s.isEmpty() && s.peek() != '(')
poshix += s.pop();
s.pop(); // remove '('
} else { // Operator
while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch))
poshix += s.pop();
s.push(ch);
}
}
// Pop remaining operators
while (!s.isEmpty())
poshix += s.pop();
return poshix;
}
//=================== POSTFIX EXPRESSION EVALUATION ===================
int evaluatePoshix(string poshix) {
int stack[MAX];
int top = -1;
for (int i = 0; i < poshix.length(); i++) {
char ch = poshix[i];
if (isdigit(ch))
stack[++top] = ch - '0'; // Convert char to int
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
//=================== MAIN FUNCTION ===================
int main() {
string infix;
cout << "Enter an infix expression (use single-digit numbers): ";
cin >> infix;
string poshix = infixToPoshix(infix);
cout << "\nPoshix Expression: " << poshix << endl;
int result = evaluatePoshix(poshix);
cout << "Evaluated Result: " << result << endl;
return 0;
}
