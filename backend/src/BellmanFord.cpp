#include "BellmanFord.h"

#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

RoutingResult BellmanFord::findShortestPath(
    const Graph& graph,
    const string& source,
    const string& destination
) {
    RoutingResult result;

    result.found = false;
    result.cost = -1;

    // Source and destination are the same
    if (source == destination) {
        result.found = true;
        result.path.push_back(source);
        result.cost = 0;

        return result;
    }

    unordered_map<string, int> distance;
    unordered_map<string, string> parent;

    // Get all routers from the graph.
    // We will discover routers by traversing from the source.
    vector<string> routers;
    unordered_map<string, bool> visited;

    vector<string> stack;
    stack.push_back(source);

    while (!stack.empty()) {

        string current = stack.back();
        stack.pop_back();

        if (visited[current]) {
            continue;
        }

        visited[current] = true;
        routers.push_back(current);

        for (const auto& edge : graph.getNeighbors(current)) {

            string neighbor = edge.first;

            if (!visited[neighbor]) {
                stack.push_back(neighbor);
            }
        }
    }

    // Destination is not in the source's connected component
    if (!visited[destination]) {
        return result;
    }

    const int INF = numeric_limits<int>::max();

    // Initialize distances
    for (const string& router : routers) {
        distance[router] = INF;
    }

    distance[source] = 0;

    /*
        Relax all edges repeatedly.

        If there are V routers, we need at most
        V - 1 rounds.
    */
    for (size_t i = 1; i < routers.size(); ++i) {

        bool changed = false;

        for (const string& router : routers) {

            if (distance[router] == INF) {
                continue;
            }

            for (const auto& edge :
                 graph.getNeighbors(router)) {

                string neighbor = edge.first;
                int weight = edge.second;

                int newDistance =
                    distance[router] + weight;

                if (newDistance < distance[neighbor]) {

                    distance[neighbor] = newDistance;
                    parent[neighbor] = router;

                    changed = true;
                }
            }
        }

        // No changes means the distances are already optimal
        if (!changed) {
            break;
        }
    }

    // Check for a reachable negative-weight cycle
    for (const string& router : routers) {

        if (distance[router] == INF) {
            continue;
        }

        for (const auto& edge :
             graph.getNeighbors(router)) {

            string neighbor = edge.first;
            int weight = edge.second;

            if (distance[router] + weight <
                distance[neighbor]) {

                // Negative cycle detected.
                return result;
            }
        }
    }

    // Destination was not reached
    if (distance[destination] == INF) {
        return result;
    }

    // Reconstruct path
    vector<string> path;

    string current = destination;

    while (current != source) {

        path.push_back(current);
        current = parent[current];
    }

    path.push_back(source);

    reverse(path.begin(), path.end());

    result.found = true;
    result.path = path;
    result.cost = distance[destination];

    return result;
}