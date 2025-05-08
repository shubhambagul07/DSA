#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    int rollNo;
    char name[50];
    char division;
    char address[100];
};

// Function to add a student record
void addStudent() {
    ofstream outFile("students.dat", ios::binary | ios::app);
    Student s;

    cout << "Enter Roll Number: ";
    cin >> s.rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(s.name, 50);
    cout << "Enter Division: ";
    cin >> s.division;
    cin.ignore();
    cout << "Enter Address: ";
    cin.getline(s.address, 100);

    outFile.write((char*)&s, sizeof(s));
    outFile.close();
    cout << "Student record added successfully.\n";
}

// Function to display a student by roll number
void displayStudent() {
    ifstream inFile("students.dat", ios::binary);
    Student s;
    int roll;
    bool found = false;

    cout << "Enter Roll Number to search: ";
    cin >> roll;

    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "\nStudent Found:\n";
            cout << "Roll No: " << s.rollNo << "\n";
            cout << "Name: " << s.name << "\n";
            cout << "Division: " << s.division << "\n";
            cout << "Address: " << s.address << "\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student record not found.\n";

    inFile.close();
}

// Function to delete a student record by roll number
void deleteStudent() {
    ifstream inFile("students.dat", ios::binary);
    ofstream tempFile("temp.dat", ios::binary);
    Student s;
    int roll;
    bool found = false;

    cout << "Enter Roll Number to delete: ";
    cin >> roll;

    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.rollNo != roll) {
            tempFile.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student record deleted successfully.\n";
    else
        cout << "Student record not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\n--- Student Database Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student by Roll Number\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudent(); break;
            case 3: deleteStudent(); break;
            case 4: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

