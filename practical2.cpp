#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

struct Node {
    string key;
    string value;
    Node* next;
};

class HashTable {
private:
    Node* table[TABLE_SIZE];

    int hashFunction(string key) {
        int sum = 0;
        for (char c : key)
            sum += c;
        return sum % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = nullptr;
    }

    void insert(string key, string value) {
        int index = hashFunction(key);
        Node* newNode = new Node{key, value, nullptr};

        if (!table[index]) {
            table[index] = newNode;
        } else {
            // Chain at the end
            Node* current = table[index];
            while (current->next)
                current = current->next;
            current->next = newNode;
        }
        cout << "Inserted (" << key << ", " << value << ")\n";
    }

    void search(string key) {
        int index = hashFunction(key);
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                cout << "Found: " << current->value << "\n";
                return;
            }
            current = current->next;
        }
        cout << "Key not found.\n";
    }

    void deleteKey(string key) {
        int index = hashFunction(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev)
                    prev->next = current->next;
                else
                    table[index] = current->next;
                delete current;
                cout << "Deleted key: " << key << "\n";
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Key not found.\n";
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "] -> ";
            Node* current = table[i];
            while (current) {
                cout << "(" << current->key << ", " << current->value << ") -> ";
                current = current->next;
            }
            cout << "NULL\n";
        }
    }
};
int main() {
    HashTable dict;
    int choice;
    string key, value;

    do {
        cout << "\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                dict.insert(key, value);
                break;
            case 2:
                cout << "Enter key to search: ";
                cin >> key;
                dict.search(key);
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                dict.deleteKey(key);
                break;
            case 4:
                dict.display();
                break;
        }
    } while (choice != 5);

    return 0;
}
