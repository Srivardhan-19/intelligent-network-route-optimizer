#ifndef BALANCED_ROUTING_H
#define BALANCED_ROUTING_H

#include "Graph.h"
#include "RoutingResult.h"
#include "RoutingWeights.h"

using namespace std;

class BalancedRouting {
public:
    static RoutingResult findBestRoute(
        const Graph& graph,
        const string& source,
        const string& destination,
        const RoutingWeights& weights
    );
};

#endif