#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// ---------------- NODE STRUCTURE ----------------
struct Node {
    int data;
    vector<Node*> neighbors;
};

// ---------------- PARALLEL DFS ----------------
void parallelDFS(Node* node, vector<bool>& visited) {

    // check + mark visited safely
    bool isSafe = false;

    #pragma omp critical
    {
        if (!visited[node->data]) {
            visited[node->data] = true;
            cout << node->data << " ";
            isSafe = true;
        }
    }

    // if already visited, return
    if (!isSafe)
        return;

    // explore neighbors in parallel
    #pragma omp parallel for
    for (int i = 0; i < node->neighbors.size(); i++) {

        Node* neigh = node->neighbors[i];

        if (!visited[neigh->data]) {
            parallelDFS(neigh, visited);
        }
    }
}

// ---------------- MAIN FUNCTION ----------------
int main() {

    // Create graph (example)
    vector<Node> graph(5);

    for (int i = 0; i < 5; i++)
        graph[i].data = i;

    // Undirected graph
    graph[0].neighbors = {&graph[1], &graph[2]};
    graph[1].neighbors = {&graph[0], &graph[3]};
    graph[2].neighbors = {&graph[0], &graph[4]};
    graph[3].neighbors = {&graph[1]};
    graph[4].neighbors = {&graph[2]};

    vector<bool> visited(5, false);

    cout << "Parallel DFS Traversal: ";

    #pragma omp parallel
    {
        #pragma omp single
        parallelDFS(&graph[0], visited);
    }

    cout << endl;

    return 0;
}