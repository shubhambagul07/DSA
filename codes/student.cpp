#include <iostream>
#include <cstring>
using namespace std;

struct Student {
    int rollNo;
    char name[50];
    float sgpa;
};

void inputData(Student s[], int n) {
    cout << "\nEnter student details:\n";
    for (int i = 0; i < n; i++) {
        cout << "Student " << i + 1 << ":\n";
        cout << "Roll No: ";
        cin >> s[i].rollNo;
        cout << "Name: ";
        cin.ignore();
        cin.getline(s[i].name, 50);
        cout << "SGPA: ";
        cin >> s[i].sgpa;
    }
}

// (a) Bubble Sort by Roll No
void bubbleSortByRoll(Student s[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (s[j].rollNo > s[j + 1].rollNo)
                swap(s[j], s[j + 1]);
}

// (b) Insertion Sort by Name
void insertionSortByName(Student s[], int n) {
    for (int i = 1; i < n; i++) {
        Student key = s[i];
        int j = i - 1;
        while (j >= 0 && strcmp(s[j].name, key.name) > 0) {
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = key;
    }
}

// (c) Quick Sort by SGPA
int partition(Student s[], int low, int high) {
    float pivot = s[high].sgpa;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (s[j].sgpa > pivot) { // descending order
            i++;
            swap(s[i], s[j]);
        }
    }
    swap(s[i + 1], s[high]);
    return i + 1;
}

void quickSortBySGPA(Student s[], int low, int high) {
    if (low < high) {
        int pi = partition(s, low, high);
        quickSortBySGPA(s, low, pi - 1);
        quickSortBySGPA(s, pi + 1, high);
    }
}

// (d) Search students with specific SGPA
void searchBySGPA(Student s[], int n, float keySGPA) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (s[i].sgpa == keySGPA) {
            cout << s[i].rollNo << " " << s[i].name << " " << s[i].sgpa << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No student found with SGPA " << keySGPA << endl;
}

// (e) Binary Search by Name (without recursion)
void binarySearchByName(Student s[], int n, const char key[]) {
    insertionSortByName(s, n); // binary search needs sorted data
    int low = 0, high = n - 1;
    bool found = false;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(s[mid].name, key);
        if (cmp == 0) {
            cout << "Student found:\n";
            cout << s[mid].rollNo << " " << s[mid].name << " " << s[mid].sgpa << endl;
            found = true;
            break;
        } else if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (!found)
        cout << "Student with name \"" << key << "\" not found.\n";
}

// Display students
void display(Student s[], int n) {
    cout << "\nRoll No\tName\t\tSGPA\n";
    for (int i = 0; i < n; i++) {
        cout << s[i].rollNo << "\t" << s[i].name << "\t\t" << s[i].sgpa << endl;
    }
}

int main() {
    int n = 15;
    Student s[50];

    inputData(s, n);

    cout << "\n(a) Sorted by Roll No:\n";
    bubbleSortByRoll(s, n);
    display(s, n);

    cout << "\n(b) Sorted Alphabetically:\n";
    insertionSortByName(s, n);
    display(s, n);

    cout << "\n(c) Top 10 Toppers:\n";
    quickSortBySGPA(s, 0, n - 1);
    display(s, 10);

    float keySGPA;
    cout << "\n(d) Enter SGPA to search: ";
    cin >> keySGPA;
    searchBySGPA(s, n, keySGPA);

    char keyName[50];
    cout << "\n(e) Enter Name to search: ";
    cin.ignore();
    cin.getline(keyName, 50);
    binarySearchByName(s, n, keyName);

    return 0;
}

