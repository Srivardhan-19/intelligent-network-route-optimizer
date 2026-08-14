#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include<utility>

using namespace std;

class Graph {
private:
    unordered_map<string, vector<pair<string,int>>> adjacencyList;

public:
    void addRouter(const string& routerId);

    void addLink(
        const string& routerA,
        const string& routerB,
        int weight=1
        );

    void removeLink(
        const string& routerA,
        const string& routerB
    );

    bool hasLink(
    const string& routerA,
    const string& routerB
    ) const;

    vector<pair<string,int>> getNeighbors(
        const string& routerId
    ) const;

    void displayGraph() const;
};

#endif