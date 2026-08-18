#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

#include "LinkInfo.h"

using namespace std;

class Graph {
private:
    unordered_map<string, vector<LinkInfo>> adjacencyList;

public:
    void addRouter(const string& routerId);
    void removeRouter(const string& routerId);

    void addLink(
        const string& routerA,
        const string& routerB,
        int cost = 1,
        int latency = 0,
        int bandwidth = 0
    );

    void updateLink(
    const string& routerA,
    const string& routerB,
    int cost,
    int latency,
    int bandwidth
);

    void removeLink(
        const string& routerA,
        const string& routerB
    );

    bool hasLink(
        const string& routerA,
        const string& routerB
    ) const;

    vector<LinkInfo> getNeighbors(
        const string& routerId
    ) const;

    void displayGraph() const;
};

#endif