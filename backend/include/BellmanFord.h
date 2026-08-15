#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "Graph.h"
#include "RoutingResult.h"

using namespace std;

class BellmanFord {
public:
    static RoutingResult findShortestPath(
        const Graph& graph,
        const string& source,
        const string& destination
    );
};

#endif