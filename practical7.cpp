// 7There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. 
// The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey. 
// Represent this as a graph. The node can be represented by airport name or name of the city. 
// Use adjacency list representation of the graph or use adjacency matrix representation of the graph. 
// Check whether the graph is connected or not. Justify the storage representation used.

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <set>
using namespace std;

// Graph to represent cities (nodes) and flights (edges)
class Graph {
    unordered_map<string, list<pair<string, int>>> adjList;

public:
    // Add a city (vertex)
    void addCity(string city) {
        adjList[city] = list<pair<string, int>>();
    }

    // Add a flight (edge) with cost (e.g., time in minutes)
    void addFlight(string city1, string city2, int cost) {
        adjList[city1].push_back({city2, cost});
        adjList[city2].push_back({city1, cost}); // Assuming bidirectional flight
    }

    // Display all cities and their flight paths
    void displayFlights() {
        for (auto& city : adjList) {
            cout << city.first << " -> ";
            for (auto& flight : city.second) {
                cout << flight.first << "(" << flight.second << " mins) ";
            }
            cout << endl;
        }
    }

    // DFS utility to visit all reachable cities
    void dfs(string city, set<string>& visited) {
        visited.insert(city);
        for (auto& neighbor : adjList[city]) {
            if (visited.find(neighbor.first) == visited.end()) {
                dfs(neighbor.first, visited);
            }
        }
    }

    // Check if the graph is connected
    bool isConnected() {
        if (adjList.empty()) return true;

        set<string> visited;
        string start = adjList.begin()->first;
        dfs(start, visited);
        return visited.size() == adjList.size();
    }
};

int main() {
    Graph g;
    int numCities, numFlights, cost;
    string city1, city2;

    cout << "Enter number of cities: ";
    cin >> numCities;

    // Input cities
    for (int i = 0; i < numCities; i++) {
        cout << "Enter city name: ";
        cin >> city1;
        g.addCity(city1);
    }

    cout << "Enter number of flights: ";
    cin >> numFlights;

    // Input flights between cities
    for (int i = 0; i < numFlights; i++) {
        cout << "Enter source city, destination city, and flight time (in minutes): ";
        cin >> city1 >> city2 >> cost;
        g.addFlight(city1, city2, cost);
    }

    // Display all flight paths
    cout << "\nFlight paths between cities:\n";
    g.displayFlights();

    // Check connectivity of the graph
    if (g.isConnected()) {
        cout << "\nThe graph is connected. All cities are reachable from one another.\n";
    } else {
        cout << "\nThe graph is NOT connected. Some cities are unreachable from others.\n";
    }

    cout << "\nNote: Adjacency List is used for graph representation as it is more space-efficient for sparse graphs like flight networks,\n"
         << "where most cities are not directly connected to every other city.\n";

    return 0;
}
