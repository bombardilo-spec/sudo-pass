#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// ---------------- NODE STRUCTURE ----------------
struct Node {
    int data;
    vector<Node*> neighbors;
};

// ---------------- PARALLEL BFS ----------------
void parallelBFS(Node* start, vector<bool>& visited) {

    queue<Node*> q;

    q.push(start);
    visited[start->data] = true;

    while (!q.empty()) {

        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {

            Node* node = nullptr;

            // safely pop from queue
            #pragma omp critical
            {
                node = q.front();
                q.pop();
            }

            cout << node->data << " ";

            // explore neighbors
            for (Node* neigh : node->neighbors) {

                #pragma omp critical
                {
                    if (!visited[neigh->data]) {
                        visited[neigh->data] = true;
                        q.push(neigh);
                    }
                }
            }
        }
    }
}

// ---------------- MAIN FUNCTION ----------------
int main() {

    // Create graph (example)
    vector<Node> graph(5);

    graph[0].data = 0;
    graph[1].data = 1;
    graph[2].data = 2;
    graph[3].data = 3;
    graph[4].data = 4;

    // Undirected graph
    graph[0].neighbors = {&graph[1], &graph[2]};
    graph[1].neighbors = {&graph[0], &graph[3]};
    graph[2].neighbors = {&graph[0], &graph[4]};
    graph[3].neighbors = {&graph[1]};
    graph[4].neighbors = {&graph[2]};

    vector<bool> visited(5, false);

    cout << "Parallel BFS Traversal: ";
    parallelBFS(&graph[0], visited);

    cout << endl;

    return 0;
}