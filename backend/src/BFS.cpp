#include "BFS.h"

#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

RoutingResult BFS::findShortestPath(
    const Graph& graph,
    const string& source,
    const string& destination
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

    queue<string> q;

    unordered_set<string> visited;

    unordered_map<string, string> parent;

    q.push(source);
    visited.insert(source);

    while (!q.empty()) {

        string current = q.front();
        q.pop();
        
        vector<string> neighbors =
            graph.getNeighbors(current);

        for (const string& neighbor : neighbors) {

            if (visited.find(neighbor) != visited.end()) {
                continue;
            }

            visited.insert(neighbor);
            parent[neighbor] = current;

            if (neighbor == destination) {

                vector<string> path;

                string currentNode = destination;

                while (currentNode != source) {
                    path.push_back(currentNode);
                    currentNode = parent[currentNode];
                }

                path.push_back(source);

                reverse(path.begin(), path.end());

                result.found = true;
                result.path = path;
                result.cost = path.size() - 1;

                return result;
            }

            q.push(neighbor);
        }
    }

    return result;
}