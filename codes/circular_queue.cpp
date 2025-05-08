#include <iostream>
using namespace std;

#define SIZE 5  // Fixed size of the circular queue

class CircularQueue {
private:
    int queue[SIZE];
    int front, rear;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
    }

    // Enqueue operation
    void enqueue(int value) {
        if ((front == 0 && rear == SIZE - 1) || (rear + 1) % SIZE == front) {
            cout << "Queue is FULL!" << endl;
            return;
        }

        if (front == -1) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }

        queue[rear] = value;
        cout << "Inserted: " << value << endl;
    }

    // Dequeue operation
    void dequeue() {
        if (front == -1) {
            cout << "Queue is EMPTY!" << endl;
            return;
        }

        cout << "Deleted: " << queue[front] << endl;

        if (front == rear) {
            // Only one element was present
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }

    // Display operation
    void display() {
        if (front == -1) {
            cout << "Queue is EMPTY!" << endl;
            return;
        }

        cout << "Queue: ";
        int i = front;
        while (true) {
            cout << queue[i] << " ";
            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
        cout << endl;
    }
};

// Main function
int main() {
    CircularQueue cq;
    int choice, value;

    do {
        cout << "\n--- Circular Queue Menu ---\n";
        cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            cq.enqueue(value);
            break;
        case 2:
            cq.dequeue();
            break;
        case 3:
            cq.display();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}

