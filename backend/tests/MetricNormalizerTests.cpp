#include <cassert>
#include <cmath>
#include <iostream>

#include "MetricNormalizer.h"

using namespace std;

bool approximatelyEqual(double a, double b) {
    return fabs(a - b) < 0.000001;
}

int main() {

    double cost =
        MetricNormalizer::normalizeCost(10, 20);

    assert(approximatelyEqual(cost, 0.5));

    cout << "Test 1 passed: cost normalization\n";


    double latency =
        MetricNormalizer::normalizeLatency(20, 40);

    assert(approximatelyEqual(latency, 0.5));

    cout << "Test 2 passed: latency normalization\n";


    double bandwidth =
        MetricNormalizer::normalizeBandwidth(1000, 500);

    assert(approximatelyEqual(bandwidth, 0.5));

    cout << "Test 3 passed: bandwidth normalization\n";


    cout << "\nAll metric normalization tests passed!\n";

    return 0;
}