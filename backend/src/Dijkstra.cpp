#include "Dijkstra.h"

#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

static int getRoutingWeight(
    const LinkInfo& edge,
    RoutingMetric metric
) {
    switch (metric) {

        case RoutingMetric::COST:
            return edge.cost;

        case RoutingMetric::LATENCY:
            return edge.latency;

        case RoutingMetric::BANDWIDTH:
            // Higher bandwidth is better,
            // so convert it into a value that Dijkstra minimizes.
            if (edge.bandwidth <= 0) {
                return numeric_limits<int>::max();
            }

            return 1000000 / edge.bandwidth;
    }

    return edge.cost;
}

RoutingResult Dijkstra::findShortestPath(
    const Graph& graph,
    const string& source,
    const string& destination,
    RoutingMetric metric
) {
    RoutingResult result;

    result.found = false;
    result.cost = -1;

    if (source == destination) {
        result.found = true;
        result.path.push_back(source);
        result.cost = 0;

        return result;
    }

    // Distance from source to each router
    unordered_map<string, int> distance;

    // Previous router used to reach each router
    unordered_map<string, string> parent;

    // Min-priority queue:
    // {distance, router}
    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;

    // Start from source
    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {

        int currentDistance = pq.top().first;
        string current = pq.top().second;

        pq.pop();

        // Ignore an outdated queue entry
        if (distance[current] != currentDistance) {
            continue;
        }

        // We reached the destination
        if (current == destination) {
            break;
        }

        // Examine all connected routers
        vector<LinkInfo> neighbors =
            graph.getNeighbors(current);

        for (const auto& edge : neighbors) {

            string neighbor = edge.router;
            int weight = getRoutingWeight(edge,metric);

            int newDistance =
                currentDistance + weight;

            // First time visiting OR found a cheaper route
            if (
                distance.find(neighbor) == distance.end() ||
                newDistance < distance[neighbor]
            ) {
                distance[neighbor] = newDistance;
                parent[neighbor] = current;

                pq.push({
                    newDistance,
                    neighbor
                });
            }
        }
    }

    // Destination was never reached
    if (distance.find(destination) == distance.end()) {
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