#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class SmartCampus {
    int V;
    vector<vector<int>> adjMatrix;
    vector<string> locations;

public:
    SmartCampus(int vertices) {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, 0));
        locations.resize(V);
    }

    void setLocationName(int index, string name) {
        if (index >= 0 && index < V)
            locations[index] = name;
    }

    void addEdge(int u, int v) {
        if (u >= 0 && v >= 0 && u < V && v < V) {
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1; // undirected graph
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        stack<int> s;

        cout << "DFS traversal starting from " << locations[start] << ":\n";

        s.push(start);

        while (!s.empty()) {
            int curr = s.top();
            s.pop();

            if (!visited[curr]) {
                cout << locations[curr] << " ";
                visited[curr] = true;
            }

            // Push adjacent unvisited vertices in reverse order to visit in correct order
            for (int i = V - 1; i >= 0; i--) {
                if (adjMatrix[curr][i] == 1 && !visited[i]) {
                    s.push(i);
                }
            }
        }
        cout << endl;
    }

    void displayAdjMatrix() {
        cout << "\nAdjacency Matrix:\n    ";
        for (int i = 0; i < V; i++)
            cout << locations[i] << " ";
        cout << endl;

        for (int i = 0; i < V; i++) {
            cout << locations[i] << " ";
            if (locations[i].length() == 1) cout << "  ";
            else if (locations[i].length() == 2) cout << " ";
            for (int j = 0; j < V; j++)
                cout << " " << adjMatrix[i][j] << " ";
            cout << endl;
        }
    }
};

int main() {
    int V = 6;
    SmartCampus campus(V);

    // Set location names
    campus.setLocationName(0, "Library");
    campus.setLocationName(1, "Cafeteria");
    campus.setLocationName(2, "Class1");
    campus.setLocationName(3, "Class2");
    campus.setLocationName(4, "Admin");
    campus.setLocationName(5, "Gym");

    // Add edges (paths)
    campus.addEdge(0, 1); // Library - Cafeteria
    campus.addEdge(0, 2); // Library - Class1
    campus.addEdge(1, 2); // Cafeteria - Class1
    campus.addEdge(1, 3); // Cafeteria - Class2
    campus.addEdge(2, 4); // Class1 - Admin
    campus.addEdge(3, 4); // Class2 - Admin
    campus.addEdge(4, 5); // Admin - Gym

    campus.displayAdjMatrix();

    int startIndex;
    cout << "\nEnter starting location index (0-Library, 1-Cafeteria, 2-Class1, 3-Class2, 4-Admin, 5-Gym): ";
    cin >> startIndex;

    if (startIndex >= 0 && startIndex < V) {
        campus.DFS(startIndex);
    } else {
        cout << "Invalid starting index!\n";
    }

    return 0;
}

