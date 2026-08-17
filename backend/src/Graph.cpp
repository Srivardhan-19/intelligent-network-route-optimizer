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
    int cost,
    int latency,
    int bandwidth
) {
    addRouter(routerA);
    addRouter(routerB);

    adjacencyList[routerA].push_back(
        {routerB, cost, latency, bandwidth}
    );

    adjacencyList[routerB].push_back(
        {routerA, cost, latency, bandwidth}
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
            [&](const LinkInfo& edge) {
                return edge.router == routerB;
            }
        ),
        neighborsA.end()
    );

    neighborsB.erase(
        remove_if(
            neighborsB.begin(),
            neighborsB.end(),
            [&](const LinkInfo& edge) {
                return edge.router == routerA;
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
        if (edge.router == routerB) {
            return true;
        }
    }

    return false;
}

vector<LinkInfo> Graph::getNeighbors(
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

            cout << neighbor.router
                 << "(cost=" << neighbor.cost
                 << ", latency=" << neighbor.latency
                 << ", bandwidth=" << neighbor.bandwidth
                 << ") ";
        }

        cout << "\n";
    }
}