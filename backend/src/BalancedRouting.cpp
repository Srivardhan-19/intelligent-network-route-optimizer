#include "BalancedRouting.h"
#include "RouteScore.h"

#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

RoutingResult BalancedRouting::findBestRoute(
    const Graph& graph,
    const string& source,
    const string& destination,
    const RoutingWeights& weights
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

    /*
        Determine normalization bounds from the graph.

        These bounds are calculated from all links reachable
        through the graph's stored adjacency lists.
    */

    int maxCost = 0;
    int maxLatency = 0;
    int minBandwidth = numeric_limits<int>::max();

    unordered_map<string, bool> visitedRouters;

    queue<string> routerQueue;

    routerQueue.push(source);
    visitedRouters[source] = true;

    while (!routerQueue.empty()) {

        string current = routerQueue.front();
        routerQueue.pop();

        vector<LinkInfo> neighbors =
            graph.getNeighbors(current);

        for (const auto& edge : neighbors) {

            maxCost = max(maxCost, edge.cost);
            maxLatency = max(maxLatency, edge.latency);

            if (edge.bandwidth > 0) {
                minBandwidth =
                    min(minBandwidth, edge.bandwidth);
            }

            if (!visitedRouters[edge.router]) {
                visitedRouters[edge.router] = true;
                routerQueue.push(edge.router);
            }
        }
    }

    if (minBandwidth == numeric_limits<int>::max()) {
        minBandwidth = 1;
    }

    if (maxCost <= 0) {
        maxCost = 1;
    }

    if (maxLatency <= 0) {
        maxLatency = 1;
    }

    /*
        Distance from source to each router.
        This distance represents the combined score.
    */

    unordered_map<string, double> distance;

    unordered_map<string, string> parent;

    priority_queue<
        pair<double, string>,
        vector<pair<double, string>>,
        greater<pair<double, string>>
    > pq;

    distance[source] = 0.0;

    pq.push({
        0.0,
        source
    });

    while (!pq.empty()) {

        double currentDistance =
            pq.top().first;

        string current =
            pq.top().second;

        pq.pop();

        if (
            distance.find(current) == distance.end() ||
            currentDistance != distance[current]
        ) {
            continue;
        }

        if (current == destination) {
            break;
        }

        vector<LinkInfo> neighbors =
            graph.getNeighbors(current);

        for (const auto& edge : neighbors) {

            double weight =
                RouteScore::calculate(
                    edge,
                    weights,
                    maxCost,
                    maxLatency,
                    minBandwidth
                );

            double newDistance =
                currentDistance + weight;

            if (
                distance.find(edge.router) ==
                    distance.end() ||
                newDistance < distance[edge.router]
            ) {
                distance[edge.router] = newDistance;

                parent[edge.router] = current;

                pq.push({
                    newDistance,
                    edge.router
                });
            }
        }
    }

    if (
        distance.find(destination) ==
        distance.end()
    ) {
        return result;
    }

    vector<string> path;

    string current = destination;

    while (current != source) {

        path.push_back(current);

        current = parent[current];
    }

    path.push_back(source);

    reverse(
        path.begin(),
        path.end()
    );

    result.found = true;
    result.path = path;

    /*
        RoutingResult currently stores the result
        in an integer cost field.

        The balanced route uses a double score,
        so for now we store the rounded score.
    */

    result.cost =
        static_cast<int>(
            distance[destination] + 0.5
        );

    return result;
}