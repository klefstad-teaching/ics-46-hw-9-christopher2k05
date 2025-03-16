#include "dijkstras.h"
#include <functional>
#include <queue>
#include <utility>
#include <vector>

constexpr int UNDEFINED = -1;

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous) {
    int num_vertices = G.size();
    vector <int> distances(num_vertices, INF);
    vector<bool> visited(num_vertices, false);
    distances[source] = 0;
    previous[source] = UNDEFINED;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});
    while (!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (Edge edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> shortest_path;
    for (int current = destination; current != UNDEFINED; current = previous[current]) {
        shortest_path.insert(shortest_path.begin(), current);
    }
    return shortest_path;
}

void print_path(const vector<int> &v, int total) {
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl << "Total cost is " << total << endl;
}