#ifndef ROUTE_SCORE_H
#define ROUTE_SCORE_H

#include "LinkInfo.h"
#include "RoutingWeights.h"

class RouteScore {
public:
    static double calculate(
        const LinkInfo& link,
        const RoutingWeights& weights,
        int maxCost,
        int maxLatency,
        int minBandwidth
    );
};

#endif