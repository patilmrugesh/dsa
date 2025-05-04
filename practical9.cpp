// 9 A Dictionary stores keywords & its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry.
//  Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may require
//   for finding any keyword. Use Height balance tree and find the complexity for finding a keyword

#include <iostream>
#include <string>
using namespace std;

struct Node {
    string key, meaning;
    Node *left, *right;
    int height;
    Node(string k, string m) : key(k), meaning(m), left(NULL), right(NULL), height(1) {}
};

class AVLTree {
    Node* root;

    int height(Node* n) { return n ? n->height : 0; }
    int getBalance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }
    
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }
    
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, string key, string meaning) {
        if (!node) return new Node(key, meaning);
        if (key < node->key) node->left = insert(node->left, key, meaning);
        else if (key > node->key) node->right = insert(node->right, key, meaning);
        else return node;
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key) return rightRotate(node);
        if (balance < -1 && key > node->right->key) return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, string key) {
        if (!root) return root;
        if (key < root->key) root->left = deleteNode(root->left, key);
        else if (key > root->key) root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) { temp = root; root = NULL; }
                else *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        if (!root) return root;
        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) { root->left = leftRotate(root->left); return rightRotate(root); }
        if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) { root->right = rightRotate(root->right); return leftRotate(root); }
        return root;
    }

    Node* search(Node* root, string key, int &comparisons) {
        while (root) {
            comparisons++;
            if (key == root->key) return root;
            root = (key < root->key) ? root->left : root->right;
        }
        return NULL;
    }

    void inOrder(Node* root) {
        if (root) {
            inOrder(root->left);
            cout << root->key << ": " << root->meaning << endl;
            inOrder(root->right);
        }
    }

    void reverseInOrder(Node* root) {
        if (root) {
            reverseInOrder(root->right);
            cout << root->key << ": " << root->meaning << endl;
            reverseInOrder(root->left);
        }
    }

public:
    AVLTree() : root(NULL) {}

    void insert(string key, string meaning) { root = insert(root, key, meaning); }
    void deleteKey(string key) { root = deleteNode(root, key); }
    void updateMeaning(string key, string newMeaning) { Node* found = search(root, key, *new int(0)); if (found) found->meaning = newMeaning; }

    void displayAscending() { inOrder(root); }
    void displayDescending() { reverseInOrder(root); }

    void searchKey(string key) {
        int comparisons = 0;
        Node* found = search(root, key, comparisons);
        if (found) cout << "Found. Meaning: " << found->meaning << ", Comparisons: " << comparisons << "\n";
        else cout << "Not found. Comparisons: " << comparisons << "\n";
    }

    int maxComparisons() { return height(root); }
};

int main() {
    AVLTree dict;
    int choice;
    string key, meaning;

    do {
        cout << "\n1. Insert\n2. Delete\n3. Update\n4. Search\n5. Display Ascending\n6. Display Descending\n7. Max Comparisons\n8. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: cout << "Enter key: "; cin >> key; cout << "Enter meaning: "; cin >> meaning; dict.insert(key, meaning); break;
            case 2: cout << "Enter key to delete: "; cin >> key; dict.deleteKey(key); break;
            case 3: cout << "Enter key to update: "; cin >> key; cout << "Enter new meaning: "; cin >> meaning; dict.updateMeaning(key, meaning); break;
            case 4: cout << "Enter key to search: "; cin >> key; dict.searchKey(key); break;
            case 5: dict.displayAscending(); break;
            case 6: dict.displayDescending(); break;
            case 7: cout << "Max comparisons: " << dict.maxComparisons() << endl; break;
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 8);

    return 0;
}
