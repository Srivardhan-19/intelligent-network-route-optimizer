#ifndef BFS_H
#define BFS_H

#include "Graph.h"
#include "RoutingResult.h"

using namespace std;

class BFS {
public:
    static RoutingResult findShortestPath(
        const Graph& graph,
        const string& source,
        const string& destination
    );
};

#endif