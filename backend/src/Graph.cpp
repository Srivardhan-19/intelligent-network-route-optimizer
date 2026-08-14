#include "Graph.h"
#include <iostream>
#include <algorithm>

using namespace std;

void Graph::addRouter(const string& routerId) {
    if (adjacencyList.find(routerId) == adjacencyList.end()) {
        adjacencyList[routerId] = {};
    }
}

void Graph::addLink(
    const string& routerA,
    const string& routerB,
    int weight
) {
    addRouter(routerA);
    addRouter(routerB);

    adjacencyList[routerA].push_back(
        {routerB, weight}
    );

    adjacencyList[routerB].push_back(
        {routerA, weight}
    );
}

void Graph::removeLink(
    const string& routerA,
    const string& routerB
) {
    auto& neighborsA = adjacencyList[routerA];
    auto& neighborsB = adjacencyList[routerB];

    neighborsA.erase(
        remove_if(
            neighborsA.begin(),
            neighborsA.end(),
            [&](const pair<string, int>& edge) {
                return edge.first == routerB;
            }
        ),
        neighborsA.end()
    );

    neighborsB.erase(
        remove_if(
            neighborsB.begin(),
            neighborsB.end(),
            [&](const pair<string, int>& edge) {
                return edge.first == routerA;
            }
        ),
        neighborsB.end()
    );
}

bool Graph::hasLink(
    const string& routerA,
    const string& routerB
) const {
    auto it = adjacencyList.find(routerA);

    if (it == adjacencyList.end()) {
        return false;
    }

    for (const auto& edge : it->second) {
        if (edge.first == routerB) {
            return true;
        }
    }

    return false;
}

vector<pair<string, int>> Graph::getNeighbors(
    const string& routerId
) const {

    auto it = adjacencyList.find(routerId);

    if (it == adjacencyList.end()) {
        return {};
    }

    return it->second;
}

void Graph::displayGraph() const {
    for (const auto& entry : adjacencyList) {
        cout << entry.first << " -> ";

        for (const auto& neighbor : entry.second) {
            cout << neighbor.first << "("<<neighbor.second<<")";
        }

        cout << "\n";
    }
}