// 1 Consider telephone book database of N clients. Make use of a hash table 
// implementation to quickly look up client‘s telephone number. Make use of two
// collision handling techniques and compare them using number of comparisons 
// required to find a set of telephone numbers

#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Node {
    string name;
    long long phone;
    Node* next;
    Node(string n, long long p) : name(n), phone(p), next(nullptr) {}
};

class HashChaining {
    Node* table[SIZE]{};

public:
    int hashFunc(string key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % SIZE;
    }

    void insert(string name, long long phone) {
        int idx = hashFunc(name);
        Node* newNode = new Node(name, phone);
        newNode->next = table[idx];
        table[idx] = newNode;
    }

    bool search(string name, int &comp) {
        Node* curr = table[hashFunc(name)];
        while (curr) {
            comp++;
            if (curr->name == name) {
                cout << "Found: " << curr->phone << endl;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    void display() {
        for (int i = 0; i < SIZE; ++i) {
            cout << i << ": ";
            for (Node* curr = table[i]; curr; curr = curr->next)
                cout << "(" << curr->name << ", " << curr->phone << ") -> ";
            cout << "NULL\n";
        }
    }
};

class HashLinear {
    string names[SIZE];
    long long phones[SIZE];

public:
    HashLinear() { for (int i = 0; i < SIZE; ++i) names[i] = ""; }

    int hashFunc(string key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % SIZE;
    }

    void insert(string name, long long phone) {
        int idx = hashFunc(name), start = idx;
        while (!names[idx].empty()) {
            idx = (idx + 1) % SIZE;
            if (idx == start) return;
        }
        names[idx] = name;
        phones[idx] = phone;
    }

    bool search(string name, int &comp) {
        int idx = hashFunc(name), start = idx;
        while (!names[idx].empty()) {
            comp++;
            if (names[idx] == name) {
                cout << "Found: " << phones[idx] << endl;
                return true;
            }
            idx = (idx + 1) % SIZE;
            if (idx == start) break;
        }
        return false;
    }

    void display() {
        for (int i = 0; i < SIZE; ++i)
            cout << i << ": " << (names[i].empty() ? "NULL" : "(" + names[i] + ", " + to_string(phones[i]) + ")") << endl;
    }
};

int main() {
    HashChaining chain;
    HashLinear probe;
    int ch;
    string name;
    long long phone;

    do {
        cout << "\n1.Insert 2.Search 3.Display 4.Exit\nChoice: ";
        cin >> ch;
        if (ch == 1) {
            cout << "Name Phone: ";
            cin >> name >> phone;
            chain.insert(name, phone);
            probe.insert(name, phone);
        } else if (ch == 2) {
            cout << "Name to search: ";
            cin >> name;
            int c1 = 0, c2 = 0;
            cout << "-- Chaining --\n";
            chain.search(name, c1);
            cout << "Comparisons: " << c1 << endl;
            cout << "-- Linear Probing --\n";
            probe.search(name, c2);
            cout << "Comparisons: " << c2 << endl;
        } else if (ch == 3) {
            cout << "Chaining Table:\n"; chain.display();
            cout << "Linear Probing Table:\n"; probe.display();
        }
    } while (ch != 4);
    return 0;
}
