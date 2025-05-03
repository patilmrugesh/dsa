#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
using namespace std;

// Graph to represent cities (nodes) and flights (edges)
class Graph {
    unordered_map<string, list<pair<string, int>>> adjList; // key: city, value: list of pairs (destination city, flight cost)

public:
    // Function to add a city (vertex)
    void addCity(string city) {
        adjList[city] = list<pair<string, int>>(); // Add city as key with empty edge list
    }

    // Function to add a flight (edge)
    void addFlight(string city1, string city2, int cost) {
        adjList[city1].push_back(make_pair(city2, cost)); // Add flight from city1 to city2 with cost
        adjList[city2].push_back(make_pair(city1, cost)); // Assuming bidirectional flights
    }

    // Function to display all cities and their flight paths
    void displayFlights() {
        for (auto& city : adjList) {
            cout << city.first << " -> ";
            for (auto& flight : city.second) {
                cout << flight.first << "(" << flight.second << " mins) ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    int numCities, numFlights;
    string city1, city2;
    int cost;

    // Get number of cities and flights from user
    cout << "Enter number of cities: ";
    cin >> numCities;

    // Take input for cities
    for (int i = 0; i < numCities; i++) {
        cout << "Enter city name: ";
        cin >> city1;
        g.addCity(city1);
    }

    // Get number of flights
    cout << "Enter number of flights: ";
    cin >> numFlights;

    // Take input for each flight
    for (int i = 0; i < numFlights; i++) {
        cout << "Enter source city, destination city, and flight time (in minutes): ";
        cin >> city1 >> city2 >> cost;
        g.addFlight(city1, city2, cost);
    }

    // Display all flight paths
    cout << "\nFlight paths between cities:\n";
    g.displayFlights();

    return 0;
}
