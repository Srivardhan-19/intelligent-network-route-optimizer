#include "MetricNormalizer.h"

double MetricNormalizer::normalizeCost(
    int cost,
    int maxCost
) {
    if (maxCost <= 0) {
        return 0.0;
    }

    return static_cast<double>(cost) / maxCost;
}

double MetricNormalizer::normalizeLatency(
    int latency,
    int maxLatency
) {
    if (maxLatency <= 0) {
        return 0.0;
    }

    return static_cast<double>(latency) / maxLatency;
}

double MetricNormalizer::normalizeBandwidth(
    int bandwidth,
    int minBandwidth
) {
    if (bandwidth <= 0) {
        return 1.0;
    }

    return static_cast<double>(minBandwidth) / bandwidth;
}