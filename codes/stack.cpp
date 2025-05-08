#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <algorithm> 


using namespace std;

// Node for Linked List Stack
template <typename T>
class StackNode {
public:
    T data;
    StackNode* next;
    StackNode(T val) : data(val), next(NULL) {}
};

// Stack ADT using Linked List
template <typename T>
class Stack {
private:
    StackNode<T>* top;

public:
    Stack() : top(NULL) {}

    void push(T val) {
        StackNode<T>* newNode = new StackNode<T>(val);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) return;
        StackNode<T>* temp = top;
        top = top->next;
        delete temp;
    }

    T peek() {
        if (!isEmpty()) return top->data;
        throw runtime_error("Stack is empty");
    }

    bool isEmpty() {
        return top == NULL;
    }
};

// Function to check precedence of operators
int precedence(char op) {
    if (op == '^') return 3;
    else if (op == '*' || op == '/') return 2;
    else if (op == '+' || op == '-') return 1;
    else return -1;
}

// Function to check if character is operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Convert infix to postfix
string infixToPostfix(string infix) {
    Stack<char> st;
    string postfix;

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (c == ' ') continue;

        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                postfix += st.peek();
                st.pop();
            }
            st.pop(); // pop '('
        } else if (isOperator(c)) {
            while (!st.isEmpty() && precedence(c) <= precedence(st.peek())) {
                postfix += st.peek();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.isEmpty()) {
        postfix += st.peek();
        st.pop();
    }

    return postfix;
}

// Reverse and swap brackets for infix to prefix
string reverseAndSwap(string exp) {
    reverse(exp.begin(), exp.end());
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(')
            exp[i] = ')';
        else if (exp[i] == ')')
            exp[i] = '(';
    }
    return exp;
}

// Convert infix to prefix
string infixToPrefix(string infix) {
    string rev = reverseAndSwap(infix);
    string postfix = infixToPostfix(rev);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

// Evaluate postfix expression
int evaluatePostfix(string postfix) {
    Stack<int> st;
    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (isdigit(c)) {
            st.push(c - '0');
        } else if (isOperator(c)) {
            int b = st.peek(); st.pop();
            int a = st.peek(); st.pop();
            switch (c) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
                case '^': st.push(pow(a, b)); break;
            }
        }
    }
    return st.peek();
}

// Evaluate prefix expression
int evaluatePrefix(string prefix) {
    Stack<int> st;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isdigit(c)) {
            st.push(c - '0');
        } else if (isOperator(c)) {
            int a = st.peek(); st.pop();
            int b = st.peek(); st.pop();
            switch (c) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
                case '^': st.push(pow(a, b)); break;
            }
        }
    }
    return st.peek();
}

int main() {
    string infix;
    cout << "Enter infix expression (single-digit operands, no spaces): ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;

    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << endl;
    cout << "Prefix Evaluation: " << evaluatePrefix(prefix) << endl;

    return 0;
}

