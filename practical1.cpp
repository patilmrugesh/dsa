#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

struct ClientNode {
    string name;
    long long phone;
    ClientNode* next;
    ClientNode(string n, long long p) : name(n), phone(p), next(nullptr) {}
};

// Hash Table with Chaining
class HashTableChaining {
    ClientNode* table[TABLE_SIZE];

public:
    HashTableChaining() {
        for (int i = 0; i < TABLE_SIZE; ++i) table[i] = nullptr;
    }

    int hashFunc(string key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % TABLE_SIZE;
    }

    void insert(string name, long long phone) {
        int index = hashFunc(name);
        ClientNode* newNode = new ClientNode(name, phone);
        newNode->next = table[index];
        table[index] = newNode;
    }

    bool search(string name, int &comparisons) {
        int index = hashFunc(name);
        ClientNode* curr = table[index];
        while (curr) {
            comparisons++;
            if (curr->name == name) {
                cout << "Found: " << curr->phone << endl;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << i << ": ";
            ClientNode* curr = table[i];
            while (curr) {
                cout << "(" << curr->name << ", " << curr->phone << ") -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
        }
    }
};

// Hash Table with Linear Probing
class HashTableLinearProbing {
    string names[TABLE_SIZE];
    long long phones[TABLE_SIZE];

public:
    HashTableLinearProbing() {
        for (int i = 0; i < TABLE_SIZE; ++i) names[i] = "";
    }

    int hashFunc(string key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % TABLE_SIZE;
    }

    void insert(string name, long long phone) {
        int index = hashFunc(name);
        int startIndex = index;
        while (names[index] != "") {
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                cout << "Hash table is full!\n";
                return;
            }
        }
        names[index] = name;
        phones[index] = phone;
    }

    bool search(string name, int &comparisons) {
        int index = hashFunc(name);
        int startIndex = index;
        while (names[index] != "") {
            comparisons++;
            if (names[index] == name) {
                cout << "Found: " << phones[index] << endl;
                return true;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) break;
        }
        return false;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (names[i] != "")
                cout << i << ": (" << names[i] << ", " << phones[i] << ")\n";
            else
                cout << i << ": NULL\n";
        }
    }
};

int main() {
    HashTableChaining chainingTable;
    HashTableLinearProbing probingTable;

    int choice;
    string name;
    long long phone;

    do {
        cout << "\n1. Insert\n2. Search\n3. Display\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter name and phone: ";
                cin >> name >> phone;
                chainingTable.insert(name, phone);
                probingTable.insert(name, phone);
                break;
            case 2: {
                cout << "Enter name to search: ";
                cin >> name;
                int c1 = 0, c2 = 0;
                cout << "\n-- Chaining --\n";
                chainingTable.search(name, c1);
                cout << "Comparisons: " << c1 << endl;
                cout << "\n-- Linear Probing --\n";
                probingTable.search(name, c2);
                cout << "Comparisons: " << c2 << endl;
                break;
            }
            case 3:
                cout << "\nChaining Table:\n";
                chainingTable.display();
                cout << "\nLinear Probing Table:\n";
                probingTable.display();
                break;
        }
    } while (choice != 4);

    return 0;
}
