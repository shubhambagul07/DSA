#include <iostream>
#include <climits>  // For INT_MAX
using namespace std;

#define MAX 10  // Maximum number of departments/nodes

int parent[MAX];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSets(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

// Kruskal's Algorithm
void kruskalMST(int adj[MAX][MAX], int V) {
    int mincost = 0;
    int edge_count = 0;

    for (int i = 0; i < V; i++)
        parent[i] = i;

    cout << "\nEdges in MST using Kruskal's Algorithm:\n";
    while (edge_count < V - 1) {
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (find(i) != find(j) && adj[i][j] < min && adj[i][j] != 0) {
                    min = adj[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        if (a != -1 && b != -1) {
            unionSets(a, b);
            cout << "Edge (" << a << ", " << b << ") - Weight: " << min << "\n";
            mincost += min;
            edge_count++;
        }
    }

    cout << "Total cost of MST: " << mincost << "\n";
}

// Prim's Algorithm
void primMST(int adj[MAX][MAX], int V) {
    int selected[MAX];
    for (int i = 0; i < V; i++)
        selected[i] = 0;

    selected[0] = 1;
    int edge_count = 0;
    int mincost = 0;

    cout << "\nEdges in MST using Prim's Algorithm:\n";
    while (edge_count < V - 1) {
        int min = INT_MAX, x = -1, y = -1;

        for (int i = 0; i < V; i++) {
            if (selected[i]) {
                for (int j = 0; j < V; j++) {
                    if (!selected[j] && adj[i][j]) {
                        if (adj[i][j] < min) {
                            min = adj[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        if (x != -1 && y != -1) {
            cout << "Edge (" << x << ", " << y << ") - Weight: " << adj[x][y] << "\n";
            selected[y] = 1;
            mincost += adj[x][y];
            edge_count++;
        }
    }

    cout << "Total cost of MST: " << mincost << "\n";
}

int main() {
    int V;
    int adj[MAX][MAX];

    cout << "Enter number of departments/nodes (max 10): ";
    cin >> V;

    cout << "Enter adjacency matrix (0 if no direct path):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> adj[i][j];
        }
    }

    kruskalMST(adj, V);
    primMST(adj, V);

    return 0;
}

