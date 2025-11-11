#include <iostream>
#include <string>

using namespace std;

struct Student {
    int rollNumber;
    string name;
    float marks;
    Student* next;
};

class StudentList {
private:
    Student* head;

public:
    StudentList() : head(nullptr) {}

    void addStudent(int roll, const string& name, float marks) {
        Student* newStudent = new Student{roll, name, marks, nullptr};
        if (!head) {
            head = newStudent;
        } else {
            Student* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newStudent;
        }
        cout << "Student added successfully.\n";
    }

    void deleteStudent(int roll) {
        if (!head) {
            cout << "No records to delete.\n";
            return;
        }
        if (head->rollNumber == roll) {
            Student* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Student with Roll Number " << roll << " deleted.\n";
            return;
        }
        Student* current = head;
        Student* prev = nullptr;
        while (current && current->rollNumber != roll) {
            prev = current;
            current = current->next;
        }
        if (!current) {
            cout << "Student with Roll Number " << roll << " not found.\n";
            return;
        }
        prev->next = current->next;
        delete current;
        cout << "Student with Roll Number " << roll << " deleted.\n";
    }

    void searchStudent(int roll) {
        Student* temp = head;
        while (temp) {
            if (temp->rollNumber == roll) {
                cout << "Student Found:\n";
                cout << "Roll Number: " << temp->rollNumber << "\n";
                cout << "Name: " << temp->name << "\n";
                cout << "Marks: " << temp->marks << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Student with Roll Number " << roll << " not found.\n";
    }

    void displayAll() {
        if (!head) {
            cout << "No student records available.\n";
            return;
        }
        Student* temp = head;
        cout << "\nAll Student Records:\n";
        cout << "-------------------------\n";
        while (temp) {
            cout << "Roll Number: " << temp->rollNumber << "\n";
            cout << "Name: " << temp->name << "\n";
            cout << "Marks: " << temp->marks << "\n";
            cout << "-------------------------\n";
            temp = temp->next;
        }
    }

    ~StudentList() {
        Student* current = head;
        while (current) {
            Student* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    StudentList list;
    int choice;

    do {
        cout << "\n--- Student Records Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student by Roll Number\n";
        cout << "3. Search Student by Roll Number\n";
        cout << "4. Display All Students\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                int roll;
                string name;
                float marks;
                cout << "Enter Roll Number: ";
                cin >> roll;
                cin.ignore(); // clear newline from buffer
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Marks: ";
                cin >> marks;
                list.addStudent(roll, name, marks);
                break;
            }
            case 2: {
                int roll;
                cout << "Enter Roll Number to delete: ";
                cin >> roll;
                list.deleteStudent(roll);
                break;
            }
            case 3: {
                int roll;
                cout << "Enter Roll Number to search: ";
                cin >> roll;
                list.searchStudent(roll);
                break;
            }
            case 4:
                list.displayAll();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

