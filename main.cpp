// 4 Libraries being used in this program
#include <iostream>      // For cout
#include <unordered_map> // For DFS type traversals
#include <list>          // For adjList
#include <vector>        // For output formatting

using namespace std; // Using namespace standard

/*  struct vertexType
    - Stores the destination node (string to)
    - Stores the length of the neighbors edge (int edge) 
*/
struct vertexType {
    string to = "";
    int edge = 0;
};

/*
    dfs function: 
    - Returns a bool
    - Contains 6 parameters for:
        - current: Building we're at currently
        - end: The SU Building
        - stamina: The amount of stamina given
        - adjList: A adjacency list that maps a building to a LL of all its neighbors and edges
        - predecessor: Map that constructs paths
        - visited: Map that determines if you visited a node or not
    - Recursive function
    - Traverses the graph in a DFS-like traversal
*/
bool dfs(string current, string end, int stamina, unordered_map<string, list<vertexType>>& adjList,
         unordered_map<string, bool>& visited, unordered_map<string, string>& predecessor) {
    // Base case: check if we reached the end node with enough stamina
    if (current == end && stamina >= 1) {
        return true; // Return true
    }

    visited[current] = true; // Set the current building we visited to true

    // STL for loop that picks a neighbor to go to
    for (const vertexType& neighbor : adjList[current]) {
        int newStamina = stamina - neighbor.edge; // Set the new stamina of the current stamina - edge
        // If we didn't visit that neighbor and our new stamina is greater than 0
        if (!visited[neighbor.to] && newStamina >= 0) {
            predecessor[neighbor.to] = current; // Set the predecessor to the current node we were at
            
            // If path is valid keep trying to find the best path
            if (dfs(neighbor.to, end, newStamina, adjList, visited, predecessor)) {
                return true; // Return true if a possible path was found
            }
        }
    }

    visited[current] = false; // Sets the current building we visited to false

    return false; // Return false if no possible paths found
}

/*  Main function:
    - Reads in the start and end of the path and the stamina.
    - Reads in the "from" and "to" buildings and edge and stores to adjList
    - Creates a bool variable called foundPath and sets it to dfs recursive function
    - If path was found, you output the paths
    - If path was not found, you output "This is going to be a long summer..."
*/
int main() {
    // Declaring start and end to strings; Used to store the start of the path and the end of the path
    string start = "", end = "";
    int stamina = 0; // Create stamina

    // Reads in the first line of TBE, SU, and stamina and then the inner while loop takes over
    while (cin >> start >> end >> stamina) {
        string from = "", to = ""; // "from" and "to" used to store the buildings
        int edge = 0; // "edge" used to store the edges/weights
        /* 3 unordered_maps
        - adjList: A adjacency list that maps a building to a LL of all its neighbors and edges
        - predecessor: Map that constructs paths
        - visited: Map that determines if you visited a node or not
        */
        unordered_map<string, list<vertexType>> adjList;
        unordered_map<string, string> predecessor;
        unordered_map<string, bool> visited;

        // While loop that reads in the from, to vertices and distance of the edge
        // and then inserts each edge into the adjacency list
        while (cin >> from >> to >> edge) {
            adjList[from].push_back({to, edge});
        }

        // Create a bool variable called foundPath and set it to the dfs function
        bool foundPath = dfs(start, end, stamina, adjList, visited, predecessor);

        if (foundPath) { // If path is found
            // Output "Time to cool off!" and the paths that led from TBE to SU
            cout << "Time to cool off!" << endl;
            cout << "Path: ";

            // Reconstruct and print the path in reverse order
            vector <string> path; // Declared a vector string called path
            string node = end; // Creating a string called node and setting it to the end

            // While loop runs until the building names match
            while (node != start) {
                path.push_back(node); // Insert the name of the building into the vector
                node = predecessor[node]; // Setting the next 
            }
            path.push_back(start); // Insert TBE into the vector

            // Print the path in reverse order
            for (int i = path.size() - 1; i >= 0; i--) {
                cout << path[i] << " "; // Output the paths
            }
            cout << endl;
        } else { // If path wasn't found
            cout << "This is going to be a long summer..." << endl;
        }
    }

    return 0; // End of program
}
