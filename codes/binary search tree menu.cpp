#include <iostream>
#include <queue>
using namespace std;

// BST Node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Insertion (ignores duplicate values)
Node* insert(Node* root, int val) {
    if (root == NULL) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    else cout << "Duplicate value " << val << " not inserted.\n";
    return root;
}

// Minimum value node (used in deletion)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Deletion
Node* deleteNode(Node* root, int val) {
    if (root == NULL) return root;
    if (val < root->data) root->left = deleteNode(root->left, val);
    else if (val > root->data) root->right = deleteNode(root->right, val);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Search
bool search(Node* root, int val) {
    if (root == NULL) return false;
    if (root->data == val) return true;
    if (val < root->data) return search(root->left, val);
    return search(root->right, val);
}

// Inorder Traversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Preorder Traversal
void preorder(Node* root) {
    if (root) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal
void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

// Depth of tree
int depth(Node* root) {
    if (root == NULL) return 0;
    return 1 + max(depth(root->left), depth(root->right));
}

// Mirror Image
Node* mirror(Node* root) {
    if (root == NULL) return NULL;
    Node* temp = new Node(root->data);
    temp->left = mirror(root->right);
    temp->right = mirror(root->left);
    return temp;
}

// Copy Tree
Node* copyTree(Node* root) {
    if (root == NULL) return NULL;
    Node* newNode = new Node(root->data);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

// Display parent and children
void displayParentChild(Node* root) {
    if (root == NULL) return;
    if (root->left || root->right) {
        cout << "Parent: " << root->data << " -> ";
        if (root->left) cout << "Left Child: " << root->left->data << " ";
        if (root->right) cout << "Right Child: " << root->right->data;
        cout << endl;
    }
    displayParentChild(root->left);
    displayParentChild(root->right);
}

// Display leaf nodes
void displayLeaves(Node* root) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL)
        cout << root->data << " ";
    displayLeaves(root->left);
    displayLeaves(root->right);
}

// Level-wise display
void levelOrder(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front(); q.pop();
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// Menu
int main() {
    Node* root = NULL;
    int choice, val;

    do {
        cout << "\n--- Binary Search Tree Menu ---\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Inorder\n5. Preorder\n6. Postorder\n";
        cout << "7. Depth of Tree\n8. Mirror Image\n9. Copy Tree\n10. Parent-Child Display\n";
        cout << "11. Display Leaf Nodes\n12. Level-wise Display\n13. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: "; cin >> val;
            root = insert(root, val);
            break;
        case 2:
            cout << "Enter value to delete: "; cin >> val;
            root = deleteNode(root, val);
            break;
        case 3:
            cout << "Enter value to search: "; cin >> val;
            cout << (search(root, val) ? "Found\n" : "Not Found\n");
            break;
        case 4:
            cout << "Inorder Traversal: "; inorder(root); cout << endl;
            break;
        case 5:
            cout << "Preorder Traversal: "; preorder(root); cout << endl;
            break;
        case 6:
            cout << "Postorder Traversal: "; postorder(root); cout << endl;
            break;
        case 7:
            cout << "Depth of tree: " << depth(root) << endl;
            break;
        case 8:
            cout << "Mirror Image (Inorder): ";
            inorder(mirror(root)); cout << endl;
            break;
        case 9:
            cout << "Copied Tree (Inorder): ";
            inorder(copyTree(root)); cout << endl;
            break;
        case 10:
            cout << "Parent and Child Nodes:\n";
            displayParentChild(root);
            break;
        case 11:
            cout << "Leaf Nodes: "; displayLeaves(root); cout << endl;
            break;
        case 12:
            cout << "Level-wise Display: "; levelOrder(root); cout << endl;
            break;
        case 13:
            cout << "Exiting...\n"; break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 13);

    return 0;
}

