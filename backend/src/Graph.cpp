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
    const string& routerB
) {
    addRouter(routerA);
    addRouter(routerB);

    adjacencyList[routerA].push_back(routerB);
    adjacencyList[routerB].push_back(routerA);
}

void Graph::removeLink(
    const string& routerA,
    const string& routerB
) {
    auto& neighborsA = adjacencyList[routerA];
    auto& neighborsB = adjacencyList[routerB];

    neighborsA.erase(
        remove(neighborsA.begin(), neighborsA.end(), routerB),
        neighborsA.end()
    );

    neighborsB.erase(
        remove(neighborsB.begin(), neighborsB.end(), routerA),
        neighborsB.end()
    );
}

void Graph::displayGraph() const {
    for (const auto& entry : adjacencyList) {
        cout << entry.first << " -> ";

        for (const auto& neighbor : entry.second) {
            cout << neighbor << " ";
        }

        cout << "\n";
    }
}