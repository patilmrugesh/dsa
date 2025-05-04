// 3Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given.
//  After constructing a binary tree - i. Insert new node ii. Find number of nodes in longest path from root 
//  iii. Minimum data value found in the tree iv. Change a tree so that the roles of the left and right pointers are swapped at every
//   node v. Search a value

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        val < node->data ? node->left = insert(node->left, val)
                         : node->right = insert(node->right, val);
        return node;
    }

    bool search(Node* node, int key) {
        if (!node) return false;
        if (node->data == key) return true;
        return key < node->data ? search(node->left, key) : search(node->right, key);
    }

    int height(Node* node) {
        if (!node) return 0;
        return max(height(node->left), height(node->right)) + 1;
    }

    int minValue(Node* node) {
        while (node && node->left) node = node->left;
        return node->data;
    }

    Node* mirror(Node* node) {
        if (!node) return nullptr;
        Node* l = mirror(node->left), *r = mirror(node->right);
        node->left = r; node->right = l;
        return node;
    }

    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(int val) { root = insert(root, val); }
    void search(int val) { cout << (search(root, val) ? "Found\n" : "Not Found\n"); }
    void printHeight() { cout << "Height: " << height(root) << endl; }
    void printMin() { if (root) cout << "Min: " << minValue(root) << endl; }
    void mirrorTree() { root = mirror(root); cout << "Tree mirrored.\n"; }
    void showInorder() { cout << "Inorder: "; inorder(root); cout << endl; }
};

int main() {
    BST tree;
    int init[] = {50, 30, 70, 20, 40, 60, 80};
    for (int val : init) tree.insert(val);

    int ch, val;
    do {
        cout << "\n1.Insert 2.Search 3.Height 4.Min 5.Mirror 6.Inorder 7.Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: cout << "Enter value: "; cin >> val; tree.insert(val); break;
            case 2: cout << "Enter value: "; cin >> val; tree.search(val); break;
            case 3: tree.printHeight(); break;
            case 4: tree.printMin(); break;
            case 5: tree.mirrorTree(); break;
            case 6: tree.showInorder(); break;
        }
    } while (ch != 7);
    return 0;
}
