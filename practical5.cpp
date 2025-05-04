// 5Convert given binary tree into threaded binary tree. Analyze time and space complexity of the algorithm.

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

    Node* insert(Node* root, int data) {
        if (root == nullptr) {
            Node* newNode = new Node{data, nullptr, nullptr, false};
            return newNode;
        }
        if (data < root->data) root->left = insert(root->left, data);
        else root->right = insert(root->right, data);
        return root;
    }

    void inorderTraversal(Node* root) {
        Node* current = root;
        while (current != nullptr) {
            while (current->left != nullptr)
                current = current->left;

            cout << current->data << " ";

            while (current->isThreaded) {
                current = current->right;
                if (current) cout << current->data << " ";
            }

            current = current->right;
        }
        cout << endl;
    }

    void convertToThreaded(Node* root) {
        Node* prev = nullptr;
        while (root != nullptr) {
            if (root->left == nullptr) {
                if (prev) {
                    prev->right = root;
                    prev->isThreaded = true;
                }
                prev = root;
                root = root->right;
            } else {
                Node* temp = root->left;
                while (temp->right && temp->right != root)
                    temp = temp->right;

                if (!temp->right) {
                    temp->right = root;
                    root = root->left;
                } else {
                    temp->right = nullptr;
                    if (prev) {
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
    ThreadedBinaryTree() { root = nullptr; }

    void insert(int data) { root = insert(root, data); }

    void convertToThreadedTree() { convertToThreaded(root); }

    void inorderTraversal() { inorderTraversal(root); }
};

int main() {
    ThreadedBinaryTree tbt;
    int choice, value;
    do {
        cout << "\n1. Insert\n2. Convert to Threaded Tree\n3. In-order Traversal\n4. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                tbt.insert(value);
                break;
            case 2:
                tbt.convertToThreadedTree();
                cout << "Converted to threaded binary tree.\n";
                break;
            case 3:
                cout << "In-order traversal: ";
                tbt.inorderTraversal();
                break;
            case 4:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
