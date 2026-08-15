#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include "RoutingResult.h"

using namespace std;

class Dijkstra {
public:
    static RoutingResult findShortestPath(
        const Graph& graph,
        const string& source,
        const string& destination
    );
};

#endif