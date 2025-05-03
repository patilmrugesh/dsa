#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class OBST {
    int n;
    vector<int> keys;
    vector<float> p, q;
    vector<vector<float>> w, c;
    vector<vector<int>> r;

    int findMin(int i, int j) {
        float minCost = 1e9;
        int minK = -1;
        for (int k = r[i][j - 1]; k <= r[i + 1][j]; ++k) {
            float cost = c[i][k - 1] + c[k][j];
            if (cost < minCost) {
                minCost = cost;
                minK = k;
            }
        }
        return minK;
    }

public:
    void input() {
        cout << "Enter number of keys: ";
        cin >> n;
        keys.resize(n + 1);
        p.resize(n + 1);
        q.resize(n + 1);
        w.assign(n + 2, vector<float>(n + 2, 0));
        c.assign(n + 2, vector<float>(n + 2, 0));
        r.assign(n + 2, vector<int>(n + 2, 0));

        cout << "Enter keys in sorted order:\n";
        for (int i = 1; i <= n; ++i) {
            cout << "Key " << i << ": ";
            cin >> keys[i];
        }

        cout << "Enter success probabilities (p[i]) for each key:\n";
        for (int i = 1; i <= n; ++i) {
            cout << "p[" << i << "]: ";
            cin >> p[i];
        }

        cout << "Enter failure probabilities (q[i]) for each gap:\n";
        for (int i = 0; i <= n; ++i) {
            cout << "q[" << i << "]: ";
            cin >> q[i];
        }
    }

    void buildOBST() {
        for (int i = 0; i <= n; ++i) {
            w[i][i] = q[i];
            c[i][i] = 0;
            r[i][i] = 0;

            w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
            c[i][i + 1] = w[i][i + 1];
            r[i][i + 1] = i + 1;
        }

        for (int m = 2; m <= n; ++m) {
            for (int i = 0; i <= n - m; ++i) {
                int j = i + m;
                w[i][j] = w[i][j - 1] + p[j] + q[j];
                int k = findMin(i, j);
                c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
                r[i][j] = k;
            }
        }

        cout << "\nOptimal cost: " << c[0][n];
        cout << "\nRoot of OBST: Key[" << r[0][n] << "] = " << keys[r[0][n]] << "\n";
    }

    void displayTree() {
        cout << "\nNode\tLeft\tRight";
        printSubtree(0, n);
    }

    void printSubtree(int i, int j) {
        int root = r[i][j];
        if (root == 0) return;

        int left = r[i][root - 1];
        int right = r[root][j];

        cout << "\n" << keys[root] << "\t"
             << (left ? to_string(keys[left]) : "NULL") << "\t"
             << (right ? to_string(keys[right]) : "NULL");

        printSubtree(i, root - 1);
        printSubtree(root, j);
    }
};

int main() {
    OBST tree;
    tree.input();
    tree.buildOBST();
    tree.displayTree();
    return 0;
}
