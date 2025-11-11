
#include <iostream>
#include <string>

using namespace std;

// Node for linked list queue
struct Node {
    string customerName;
    Node* next;
    Node(const string& name) : customerName(name), next(nullptr) {}
};

// Queue class using linked list
class Queue {
    Node* frontNode;
    Node* rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    ~Queue() {
        while (!isEmpty()) dequeue();
    }

    bool isEmpty() {
        return frontNode == nullptr;
    }

    // Enqueue: Add customer at rear
    void enqueue(const string& name) {
        Node* newNode = new Node(name);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        cout << "Customer \"" << name << "\" booked a ticket and joined the queue.\n";
    }

    // Dequeue: Serve customer from front
    void dequeue() {
        if (isEmpty()) {
            cout << "No customers to serve, queue is empty.\n";
            return;
        }
        Node* temp = frontNode;
        cout << "Serving customer: " << temp->customerName << endl;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
    }

    // Display queue
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Customers waiting in queue: ";
        Node* temp = frontNode;
        while (temp) {
            cout << temp->customerName;
            if (temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    Queue q;
    int choice;
    string name;

    while (true) {
        cout << "\nTicket Booking System Menu:\n";
        cout << "1. Book Ticket (Enqueue)\n";
        cout << "2. Serve Customer (Dequeue)\n";
        cout << "3. Display Waiting Queue\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter customer name: ";
                cin.ignore(); // To ignore leftover newline from previous input
                getline(cin, name);
                q.enqueue(name);
                break;

            case 2:
                q.dequeue();
                break;

            case 3:
                q.display();
                break;

            case 4:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice, try again.\n";
        }
    }
}
