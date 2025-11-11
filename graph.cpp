



#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

class Graph {
    int V; // number of vertices
    vector<list<int>> adjList;
    vector<vector<int>> adjMatrix;
    vector<string> vertexNames;

public:
    Graph(int V) {
        this->V = V; //The parameter V (from function input) is assigned to the class variable V
        adjList.resize(V); //Creates space
        adjMatrix.resize(V, vector<int>(V, 0)); //Creates a V × V matrix (2D vector)
        vertexNames.resize(V);
    }

    void setVertexName(int index, string name) {
        if (index >= 0 && index < V) {
            vertexNames[index] = name;
        }
    }

    void addEdge(int u, int v) {
        // For adjacency list (undirected graph)
        adjList[u].push_back(v);
        adjList[v].push_back(u);

        // For adjacency matrix
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    void displayAdjList() {
        cout << "\nAdjacency List Representation:\n";
        for (int i = 0; i < V; i++) {
            cout << vertexNames[i] << " -> ";
            for (auto v : adjList[i]) {
                cout << vertexNames[v] << " ";
            }
            cout << endl;
        }
    }

    void displayAdjMatrix() {
        cout << "\nAdjacency Matrix Representation:\n    ";
        for (int i = 0; i < V; i++)
            cout << vertexNames[i] << " ";
        cout << endl;

        for (int i = 0; i < V; i++) {
            cout << vertexNames[i] << " ";
            // Format for alignment
            if (vertexNames[i].length() == 1) cout << "  ";
            else if (vertexNames[i].length() == 2) cout << " ";
            for (int j = 0; j < V; j++) {
                cout << " " << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int V = 6;

    Graph campusGraph(V);

    // Naming the vertices
    campusGraph.setVertexName(0, "Library");
    campusGraph.setVertexName(1, "Cafeteria");
    campusGraph.setVertexName(2, "Class1");
    campusGraph.setVertexName(3, "Class2");
    campusGraph.setVertexName(4, "Admin");
    campusGraph.setVertexName(5, "Gym");

    // Adding edges (paths between locations)
    campusGraph.addEdge(0, 1); // Library - Cafeteria
    campusGraph.addEdge(0, 2); // Library - Class1
    campusGraph.addEdge(1, 2); // Cafeteria - Class1
    campusGraph.addEdge(1, 3); // Cafeteria - Class2
    campusGraph.addEdge(2, 4); // Class1 - Admin
    campusGraph.addEdge(3, 4); // Class2 - Admin
    campusGraph.addEdge(4, 5); // Admin - Gym

    // Display both representations
    campusGraph.displayAdjList();
    campusGraph.displayAdjMatrix();

    return 0;
}
