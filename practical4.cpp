// 4 Construct an expression tree from the given prefix expression eg. +--a*bc/def and traverse it using postordertraversal(non recursive) 
// and then delete the entire tree.

#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    char data;
    Node *left, *right;
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

class Stack {
    Node* arr[30];
    int top = -1;
public:
    void push(Node* n) { arr[++top] = n; }
    Node* pop() { return arr[top--]; }
    bool empty() { return top == -1; }
};

class ExprTree {
public:
    Node* root = nullptr;

    void build(const char* pre) {
        Stack s;
        for (int i = strlen(pre) - 1; i >= 0; i--) {
            Node* node = new Node(pre[i]);
            if (isalpha(pre[i])) s.push(node);
            else {
                node->left = s.pop();
                node->right = s.pop();
                s.push(node);
            }
        }
        root = s.pop();
    }

    void postorderNonRec(Node* node) {
        Stack s1, s2;
        s1.push(node);
        while (!s1.empty()) {
            Node* temp = s1.pop();
            s2.push(temp);
            if (temp->left) s1.push(temp->left);
            if (temp->right) s1.push(temp->right);
        }
        while (!s2.empty()) cout << s2.pop()->data;
    }

    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        cout << "Deleting: " << node->data << endl;
        delete node;
    }
};

int main() {
    char expr[20];
    cout << "Enter Prefix: ";
    cin >> expr;

    ExprTree t;
    t.build(expr);
    cout << "Postorder: ";
    t.postorderNonRec(t.root);

    cout << "\nDelete tree? (1/0): ";
    int op; cin >> op;
    if (op) t.deleteTree(t.root);
    return 0;
}
