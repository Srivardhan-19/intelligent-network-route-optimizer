#ifndef NETWORK_API_H
#define NETWORK_API_H

#include "Graph.h"
#include "RoutingResult.h"
#include "RoutingMetric.h"
#include "RoutingWeights.h"

using namespace std;

class NetworkAPI {
private:
    Graph graph;

public:
    NetworkAPI();

    void addRouter(const string& routerId);

    void removeRouter(const string& routerId);

    void addLink(
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

    void updateLink(
        const string& routerA,
        const string& routerB,
        int cost,
        int latency,
        int bandwidth
    );

    RoutingResult findRoute(
    const string& source,
    const string& destination,
    const string& algorithm,
    RoutingMetric metric = RoutingMetric::COST
    );
    string getNetworkJSON() const;

    Graph& getGraph();
};

#endif