// 8Given sequence k = k1 <k2 < … <kn of n sorted keys, with a search probability pi for each
// key ki . Build the Binary search tree that has the least search cost given the access
// probability for each key?


#include <iostream>
#include <vector>
using namespace std;

class OBST {
    int n;
    vector<int> keys;
    vector<float> p, q;
    vector<vector<float>> cost;
    vector<vector<int>> root;

public:
    void input() {
        cout << "Enter number of keys: ";
        cin >> n;
        keys.resize(n + 1);
        p.resize(n + 1);
        q.resize(n + 1);
        cost.assign(n + 2, vector<float>(n + 2, 0));
        root.assign(n + 2, vector<int>(n + 2, 0));

        cout << "Enter keys (sorted):\n";
        for (int i = 1; i <= n; ++i) {
            cout << "Key " << i << ": ";
            cin >> keys[i];
        }

        cout << "Enter success probabilities (p[i]):\n";
        for (int i = 1; i <= n; ++i) {
            cout << "p[" << i << "]: ";
            cin >> p[i];
        }

        cout << "Enter failure probabilities (q[i]):\n";
        for (int i = 0; i <= n; ++i) {
            cout << "q[" << i << "]: ";
            cin >> q[i];
        }
    }

    void build() {
        for (int i = 0; i <= n; ++i) {
            cost[i][i] = q[i]; // empty tree
        }

        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len;
                cost[i][j] = 1e9;

                float weight = 0;
                for (int m = i + 1; m <= j; ++m)
                    weight += p[m];
                for (int m = i; m <= j; ++m)
                    weight += q[m];

                for (int r = i + 1; r <= j; ++r) {
                    float c = cost[i][r - 1] + cost[r][j] + weight;
                    if (c < cost[i][j]) {
                        cost[i][j] = c;
                        root[i][j] = r;
                    }
                }
            }
        }

        cout << "\nMinimum cost of OBST: " << cost[0][n] << "\n";
        cout << "Root key: " << keys[root[0][n]] << "\n";
    }
};

int main() {
    OBST t;
    t.input();
    t.build();
    return 0;
}
