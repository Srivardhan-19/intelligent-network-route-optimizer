#ifndef METRIC_NORMALIZER_H
#define METRIC_NORMALIZER_H

#include "LinkInfo.h"

class MetricNormalizer {
public:
    static double normalizeCost(
        int cost,
        int maxCost
    );

    static double normalizeLatency(
        int latency,
        int maxLatency
    );

    static double normalizeBandwidth(
        int bandwidth,
        int minBandwidth
    );
};

#endif