#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Insert node at the end
    void insert(int value) {
        Node* newNode = new Node{value, nullptr, nullptr};
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Inserted " << value << " into the list.\n";
    }

    // Delete node by value
    void deleteNode(int value) {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        Node* current = head;

        while (current && current->data != value) {
            current = current->next;
        }

        if (!current) {
            cout << "Value " << value << " not found in the list.\n";
            return;
        }

        if (current == head) {
            head = head->next;
            if (head)
                head->prev = nullptr;
            else
                tail = nullptr;
        } else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
        cout << "Deleted " << value << " from the list.\n";
    }

    // Search for a node by value
    void search(int value) {
        Node* current = head;
        int position = 1;
        while (current) {
            if (current->data == value) {
                cout << "Value " << value << " found at position " << position << ".\n";
                return;
            }
            current = current->next;
            position++;
        }
        cout << "Value " << value << " not found in the list.\n";
    }

    // Display list forward
    void displayForward() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        cout << "List (forward): ";
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n";
    }

    // Display list backward
    void displayBackward() {
        if (!tail) {
            cout << "List is empty.\n";
            return;
        }
        cout << "List (backward): ";
        Node* current = tail;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << "\n";
    }

    // Destructor to free nodes
    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    DoublyLinkedList dll;
    int choice, value;

    do {
        cout << "\n--- Doubly Linked List Menu ---\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display Forward\n";
        cout << "5. Display Backward\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                dll.insert(value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                dll.deleteNode(value);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                dll.search(value);
                break;
            case 4:
                dll.displayForward();
                break;
            case 5:
                dll.displayBackward();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
