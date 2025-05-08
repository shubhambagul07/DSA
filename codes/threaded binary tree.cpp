#include <iostream>
using namespace std;

// Structure of a node in the threaded binary tree
struct ThreadedNode {
    int data;
    ThreadedNode* left;
    ThreadedNode* right;
    bool leftThread;  // True if left pointer is a thread
    bool rightThread; // True if right pointer is a thread
    
    // Constructor to initialize a new node without initialization list
    ThreadedNode(int val) {
        data = val;
        left = NULL;   // Use NULL instead of nullptr
        right = NULL;  // Use NULL instead of nullptr
        leftThread = false;
        rightThread = false;
    }
};

// In-order traversal of Threaded Binary Tree
void inorder(ThreadedNode* root) {
    if (root == NULL) return;
    
    // Find the leftmost node
    ThreadedNode* current = root;
    while (current != NULL) {
        // Go to the leftmost node
        while (!current->leftThread && current->left != NULL) {
            current = current->left;
        }
        cout << current->data << " ";
        
        // If there's a right thread, move to the in-order successor
        while (current->rightThread) {
            current = current->right;
            cout << current->data << " ";
        }
        
        // Move to the right child if it exists
        current = current->right;
    }
}

// Pre-order traversal of Threaded Binary Tree
void preorder(ThreadedNode* root) {
    if (root == NULL) return;
    
    // Pre-order traversal (visit node, left, right)
    ThreadedNode* current = root;
    cout << current->data << " ";
    
    while (current != NULL) {
        if (!current->leftThread) {
            current = current->left;
            cout << current->data << " ";
        } else {
            // If no left child, go to the right thread
            while (current->rightThread && current->right != NULL) {
                current = current->right;
                cout << current->data << " ";
            }
            current = current->right;
        }
    }
}

// Threading the binary tree to create In-order threads
void inorderThreading(ThreadedNode* root) {
    if (root == NULL) return;
    ThreadedNode* prev = NULL;
    
    // Start from the root and perform In-order threading
    ThreadedNode* current = root;
    while (current != NULL) {
        // Reach the leftmost node
        while (current->left != NULL && !current->leftThread) {
            current = current->left;
        }
        
        // If left pointer is null, set leftThread to true and link it to the previous node
        if (current->left == NULL) {
            current->leftThread = true;
            current->left = prev;
        }
        
        // Set the right thread if the right child is null
        if (prev != NULL && prev->right == NULL) {
            prev->rightThread = true;
            prev->right = current;
        }
        
        // Mark the current node as previous for the next iteration
        prev = current;
        
        // Move to the right child
        if (!current->rightThread) {
            current = current->right;
        } else {
            break;
        }
    }
}

int main() {
    // Creating a simple threaded binary tree
    ThreadedNode* root = new ThreadedNode(1);
    root->left = new ThreadedNode(2);
    root->right = new ThreadedNode(3);
    root->left->left = new ThreadedNode(4);
    root->left->right = new ThreadedNode(5);
    
    // Thread the binary tree
    inorderThreading(root);
    
    // Perform In-order traversal
    cout << "In-order traversal: ";
    inorder(root);
    cout << endl;
    
    // Perform Pre-order traversal
    cout << "Pre-order traversal: ";
    preorder(root);
    cout << endl;
    
    return 0;
}

