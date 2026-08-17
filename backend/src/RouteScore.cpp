#include "RouteScore.h"
#include "MetricNormalizer.h"

double RouteScore::calculate(
    const LinkInfo& link,
    const RoutingWeights& weights,
    int maxCost,
    int maxLatency,
    int minBandwidth
) {
    double normalizedCost =
        MetricNormalizer::normalizeCost(
            link.cost,
            maxCost
        );

    double normalizedLatency =
        MetricNormalizer::normalizeLatency(
            link.latency,
            maxLatency
        );

    double normalizedBandwidth =
        MetricNormalizer::normalizeBandwidth(
            link.bandwidth,
            minBandwidth
        );

    return
        (weights.costWeight * normalizedCost) +
        (weights.latencyWeight * normalizedLatency) +
        (weights.bandwidthWeight * normalizedBandwidth);
}