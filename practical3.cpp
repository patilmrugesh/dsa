#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BST {
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else
            node->right = insert(node->right, val);
        return node;
    }

    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    int height(Node* node) {
        if (!node) return 0;
        int l = height(node->left);
        int r = height(node->right);
        return max(l, r) + 1;
    }

    int minValue(Node* node) {
        Node* current = node;
        while (current && current->left)
            current = current->left;
        return current->data;
    }

    Node* mirror(Node* node) {
        if (!node) return nullptr;
        Node* left = mirror(node->left);
        Node* right = mirror(node->right);
        node->left = right;
        node->right = left;
        return node;
    }

    bool search(Node* node, int key) {
        if (!node) return false;
        if (node->data == key) return true;
        if (key < node->data)
            return search(node->left, key);
        return search(node->right, key);
    }

    Node* deleteNode(Node* node, int key) {
        if (!node) return nullptr;
        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            // Node with one child or no child
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Node with two children
            node->data = minValue(node->right);
            node->right = deleteNode(node->right, node->data);
        }
        return node;
    }

    void BFS(Node* root) {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr = q.front(); q.pop();
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

public:
    BST() { root = nullptr; }

    void insert(int val) {
        root = insert(root, val);
    }

    void displayTraversals() {
        cout << "Inorder: "; inorder(root); cout << endl;
        cout << "Preorder: "; preorder(root); cout << endl;
        cout << "Postorder: "; postorder(root); cout << endl;
    }

    void displayBFS() {
        cout << "BFS: ";
        BFS(root);
        cout << endl;
    }

    void mirrorTree() {
        root = mirror(root);
        cout << "Tree mirrored.\n";
    }

    void deleteValue(int val) {
        root = deleteNode(root, val);
        cout << "Value deleted (if existed).\n";
    }

    void searchValue(int val) {
        cout << (search(root, val) ? "Found\n" : "Not Found\n");
    }

    void printHeight() {
        cout << "Longest Path (Height): " << height(root) << endl;
    }

    void printMin() {
        if (root)
            cout << "Minimum Value: " << minValue(root) << endl;
        else
            cout << "Tree is empty.\n";
    }
};

int main() {
    BST tree;
    int initial[] = {50, 30, 70, 20, 40, 60, 80};
    for (int val : initial)
        tree.insert(val);

    int choice, value;
    do {
        cout << "\n1.Insert \n2.Delete \n3.Search \n4.Mirror \n5.Height \n6.Minimum \n7.Traversals \n8.BFS \n9.Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> value;
            tree.deleteValue(value);
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> value;
            tree.searchValue(value);
            break;
        case 4:
            tree.mirrorTree();
            break;
        case 5:
            tree.printHeight();
            break;
        case 6:
            tree.printMin();
            break;
        case 7:
            tree.displayTraversals();
            break;
        case 8:
            tree.displayBFS();
            break;
        case 9:
            cout << "Exiting.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 9);

    return 0;
}
