// 6Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to perform BFS.
// Use the map of the area around the college as the graph. Identify the prominent land marks as nodes and perform DFS and BFS on that.

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <set>
using namespace std;

class Graph {
    map<string, vector<string>> adjList;

public:
    // Add an edge between landmarks
    void addEdge(string u, string v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Undirected
    }

    // Display the adjacency list
    void displayGraph() {
        cout << "\nGraph (Adjacency List):\n";
        for (auto &pair : adjList) {
            cout << pair.first << " -> ";
            for (auto &neighbor : pair.second) {
                cout << neighbor << ", ";
            }
            cout << "\n";
        }
    }

    // BFS Traversal
    void bfs(string start) {
        set<string> visited;
        queue<string> q;
        q.push(start);
        visited.insert(start);

        cout << "\nBFS Traversal starting from " << start << ":\n";
        while (!q.empty()) {
            string current = q.front();
            q.pop();
            cout << current << " ";

            for (auto &neighbor : adjList[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
    }

    // DFS Traversal
    void dfs(string start) {
        set<string> visited;
        stack<string> s;
        s.push(start);

        cout << "\nDFS Traversal starting from " << start << ":\n";
        while (!s.empty()) {
            string current = s.top();
            s.pop();

            if (visited.find(current) == visited.end()) {
                visited.insert(current);
                cout << current << " ";

                for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
                    if (visited.find(*it) == visited.end()) {
                        s.push(*it);
                    }
                }
            }
        }
        cout << "\n";
    }
};

int main() {
    Graph g;

    // Sample College Map Landmarks (customize as needed)
    g.addEdge("Library", "Canteen");
    g.addEdge("Library", "Admin Block");
    g.addEdge("Canteen", "Auditorium");
    g.addEdge("Admin Block", "Main Gate");
    g.addEdge("Auditorium", "Playground");
    g.addEdge("Main Gate", "Playground");

    g.displayGraph();

    string startNode;
    cout << "\nEnter starting landmark for traversal (e.g., Library): ";
    cin >> ws; // to consume any trailing newline
    getline(cin, startNode);

    g.bfs(startNode);
    g.dfs(startNode);

    cout << "\nNote: Adjacency List is used as the graph is sparse and it saves memory.\n";

    return 0;
}
