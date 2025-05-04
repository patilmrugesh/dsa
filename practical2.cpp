// 2 Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with / without replacement.
//  Data: Set of (key, value) pairs, Keys are mapped to values,
//  Keys must be comparable, Keys must be unique Standard Operations: Insert(key, value), Find(key), Delete(key)

#include <iostream>
using namespace std;

const int SIZE = 10;

struct Node {
    string key, value;
    Node* next;
};
class HashTable {
    Node* table[SIZE];

    int hashFunc(string key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % SIZE;
    }
public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) table[i] = nullptr;
    }
    void insert(string key, string value) {
        int idx = hashFunc(key);
        Node* curr = table[idx];
        while (curr) {
            if (curr->key == key) {
                cout << "Key already exists.\n";
                return;
            }
            curr = curr->next;
        }
        Node* newNode = new Node{key, value, table[idx]};
        table[idx] = newNode;
        cout << "Inserted (" << key << ", " << value << ")\n";
    }
    void search(string key) {
        int idx = hashFunc(key);
        Node* curr = table[idx];
        while (curr) {
            if (curr->key == key) {
                cout << "Found: " << curr->value << "\n";
                return;
            }
            curr = curr->next;
        }
        cout << "Not found.\n";
    }
    void del(string key) {
        int idx = hashFunc(key);
        Node *curr = table[idx], *prev = nullptr;
        while (curr) {
            if (curr->key == key) {
                if (prev) prev->next = curr->next;
                else table[idx] = curr->next;
                delete curr;
                cout << "Deleted.\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Key not found.\n";
    }
    void display() {
        for (int i = 0; i < SIZE; i++) {
            cout << "[" << i << "] -> ";
            Node* curr = table[i];
            while (curr) {
                cout << "(" << curr->key << ", " << curr->value << ") -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
        }
    }
};
int main() {
    HashTable dict;
    int ch;
    string key, value;
    do {
        cout << "\n1.Insert 2.Search 3.Delete 4.Display 5.Exit\nEnter choice: ";
        cin >> ch;
        switch (ch) {
            case 1: cout << "Key: "; cin >> key; cout << "Value: "; cin >> value; dict.insert(key, value); break;
            case 2: cout << "Search key: "; cin >> key; dict.search(key); break;
            case 3: cout << "Delete key: "; cin >> key; dict.del(key); break;
            case 4: dict.display(); break;
        }
    } while (ch != 5);
    return 0;
}
