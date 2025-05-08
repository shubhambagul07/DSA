#include <iostream>
#include <stack>
#include <cctype>
#include <string>
using namespace std;

// Tree Node
struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

// Check if character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Build Expression Tree from Postfix
Node* buildFromPostfix(string postfix) {
    stack<Node*> s;
    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];
        if (isspace(ch)) continue;
        if (isOperator(ch)) {
            Node* right = s.top(); s.pop();
            Node* left = s.top(); s.pop();
            Node* node = new Node(ch);
            node->left = left;
            node->right = right;
            s.push(node);
        } else {
            s.push(new Node(ch));
        }
    }
    return s.top();
}

// Build Expression Tree from Prefix
Node* buildFromPrefix(string prefix) {
    stack<Node*> s;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];
        if (isspace(ch)) continue;
        if (isOperator(ch)) {
            Node* left = s.top(); s.pop();
            Node* right = s.top(); s.pop();
            Node* node = new Node(ch);
            node->left = left;
            node->right = right;
            s.push(node);
        } else {
            s.push(new Node(ch));
        }
    }
    return s.top();
}

// Recursive Traversals
void recursiveInorder(Node* root) {
    if (root != NULL) {
        recursiveInorder(root->left);
        cout << root->data << " ";
        recursiveInorder(root->right);
    }
}

void recursivePreorder(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        recursivePreorder(root->left);
        recursivePreorder(root->right);
    }
}

void recursivePostorder(Node* root) {
    if (root != NULL) {
        recursivePostorder(root->left);
        recursivePostorder(root->right);
        cout << root->data << " ";
    }
}

// Non-Recursive Inorder
void nonRecursiveInorder(Node* root) {
    stack<Node*> s;
    Node* current = root;

    while (current != NULL || !s.empty()) {
        while (current != NULL) {
            s.push(current);
            current = current->left;
        }

        current = s.top(); s.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

// Non-Recursive Preorder
void nonRecursivePreorder(Node* root) {
    if (root == NULL) return;
    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* current = s.top(); s.pop();
        cout << current->data << " ";

        if (current->right != NULL) s.push(current->right);
        if (current->left != NULL) s.push(current->left);
    }
}

// Non-Recursive Postorder
void nonRecursivePostorder(Node* root) {
    if (root == NULL) return;
    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);

        if (curr->left != NULL) s1.push(curr->left);
        if (curr->right != NULL) s1.push(curr->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// Main function
int main() {
    string expression;
    int choice;
    Node* root = NULL;

    do {
        cout << "\n--- Expression Tree Menu ---\n";
        cout << "1. Build from Postfix\n";
        cout << "2. Build from Prefix\n";
        cout << "3. Recursive Inorder\n";
        cout << "4. Recursive Preorder\n";
        cout << "5. Recursive Postorder\n";
        cout << "6. Non-Recursive Inorder\n";
        cout << "7. Non-Recursive Preorder\n";
        cout << "8. Non-Recursive Postorder\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter postfix expression (e.g., ab+cd-*): ";
            getline(cin, expression);
            root = buildFromPostfix(expression);
            break;
        case 2:
            cout << "Enter prefix expression (e.g., *+ab-cd): ";
            getline(cin, expression);
            root = buildFromPrefix(expression);
            break;
        case 3:
            cout << "Recursive Inorder: ";
            recursiveInorder(root); cout << endl;
            break;
        case 4:
            cout << "Recursive Preorder: ";
            recursivePreorder(root); cout << endl;
            break;
        case 5:
            cout << "Recursive Postorder: ";
            recursivePostorder(root); cout << endl;
            break;
        case 6:
            cout << "Non-Recursive Inorder: ";
            nonRecursiveInorder(root); cout << endl;
            break;
        case 7:
            cout << "Non-Recursive Preorder: ";
            nonRecursivePreorder(root); cout << endl;
            break;
        case 8:
            cout << "Non-Recursive Postorder: ";
            nonRecursivePostorder(root); cout << endl;
            break;
        case 9:
            cout << "Exiting...\n"; break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 9);

    return 0;
}

