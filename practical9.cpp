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

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int getBalance(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, string key, string meaning) {
        if (!node) return new Node(key, meaning);
        if (key < node->key)
            node->left = insert(node->left, key, meaning);
        else if (key > node->key)
            node->right = insert(node->right, key, meaning);
        else {
            cout << "Duplicate key.\n";
            return node;
        }
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
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
        while (current->left)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, string key) {
        if (!root) return root;
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = NULL;
                } else
                    *root = *temp;
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
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    Node* search(Node* root, string key) {
        int comparisons = 0;
        while (root) {
            comparisons++;
            if (key == root->key) {
                cout << "Found. Meaning: " << root->meaning << ", Comparisons: " << comparisons << "\n";
                return root;
            } else if (key < root->key) {
                root = root->left;
            } else {
                root = root->right;
            }
        }
        cout << "Not found. Comparisons: " << comparisons << "\n";
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

    void update(Node* root, string key, string newMeaning) {
        Node* found = search(root, key);
        if (found) {
            found->meaning = newMeaning;
            cout << "Updated successfully.\n";
        } else {
            cout << "Key not found.\n";
        }
    }

public:
    AVLTree() : root(NULL) {}

    void insert(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    void deleteKey(string key) {
        root = deleteNode(root, key);
    }

    void updateMeaning(string key, string newMeaning) {
        update(root, key, newMeaning);
    }

    void displayAscending() {
        cout << "Dictionary (Ascending):\n";
        inOrder(root);
    }

    void displayDescending() {
        cout << "Dictionary (Descending):\n";
        reverseInOrder(root);
    }

    void searchKey(string key) {
        search(root, key);
    }
};

int main() {
    AVLTree dict;
    int choice;
    string key, meaning;

    do {
        cout << "\n1. Insert\n2. Delete\n3. Update\n4. Search\n5. Display Ascending\n6. Display Descending\n7. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter key: "; cin >> key;
                cout << "Enter meaning: "; cin >> meaning;
                dict.insert(key, meaning);
                break;
            case 2:
                cout << "Enter key to delete: "; cin >> key;
                dict.deleteKey(key);
                break;
            case 3:
                cout << "Enter key to update: "; cin >> key;
                cout << "Enter new meaning: "; cin >> meaning;
                dict.updateMeaning(key, meaning);
                break;
            case 4:
                cout << "Enter key to search: "; cin >> key;
                dict.searchKey(key);
                break;
            case 5:
                dict.displayAscending();
                break;
            case 6:
                dict.displayDescending();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}