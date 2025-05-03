#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool isThreaded;
};

class ThreadedBinaryTree {
private:
    Node *root;

    // Helper function to insert a node in BST
    Node* insert(Node* root, int data) {
        if (root == nullptr) {
            Node* newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->isThreaded = false;
            return newNode;
        }
        if (data < root->data) {
            root->left = insert(root->left, data);
        } else {
            root->right = insert(root->right, data);
        }
        return root;
    }

    // Helper function for in-order traversal of a threaded binary tree
    void inorderTraversal(Node* root) {
        Node* current = root;
        while (current != nullptr) {
            // Traverse leftmost node
            while (current->left != nullptr) {
                current = current->left;
            }

            // Print current node data
            cout << current->data << " ";

            // If there is a thread, follow it
            if (current->isThreaded) {
                current = current->right;
            } else {
                current = current->right;
            }
        }
        cout << endl;
    }

    // Function to convert BST to threaded binary tree
    void convertToThreaded(Node* root) {
        Node* prev = nullptr;
        while (root != nullptr) {
            if (root->left == nullptr) {
                if (prev != nullptr) {
                    prev->right = root;
                    prev->isThreaded = true;
                }
                prev = root;
                root = root->right;
            } else {
                Node* temp = root->left;
                while (temp->right != nullptr && temp->right != root) {
                    temp = temp->right;
                }

                if (temp->right == nullptr) {
                    temp->right = root;
                    root = root->left;
                } else {
                    temp->right = nullptr;
                    if (prev != nullptr) {
                        prev->right = root;
                        prev->isThreaded = true;
                    }
                    prev = root;
                    root = root->right;
                }
            }
        }
    }

public:
    ThreadedBinaryTree() {
        root = nullptr;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void convertToThreadedTree() {
        convertToThreaded(root);
    }

    void inorderTraversal() {
        inorderTraversal(root);
    }
};

int main() {
    ThreadedBinaryTree tbt;
    int choice, value;
    do {
        cout << "\n--- Threaded Binary Tree Operations ---\n";
        cout << "1. Insert Node\n";
        cout << "2. Convert to Threaded Binary Tree\n";
        cout << "3. In-order Traversal\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> value;
                tbt.insert(value);
                cout << "Node inserted successfully.\n";
                break;
            case 2:
                tbt.convertToThreadedTree();
                cout << "BST converted to Threaded Binary Tree.\n";
                break;
            case 3:
                cout << "In-order Traversal of Threaded Binary Tree: ";
                tbt.inorderTraversal();
                break;
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter again.\n";
        }
    } while (choice != 4);

    return 0;
}
