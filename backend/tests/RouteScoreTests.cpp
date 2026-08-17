#include <cassert>
#include <cmath>
#include <iostream>

#include "RouteScore.h"

using namespace std;

bool approximatelyEqual(double a, double b) {
    return fabs(a - b) < 0.000001;
}

int main() {

    LinkInfo link{
        "R2",
        10,
        20,
        1000
    };

    RoutingWeights weights{
        0.5,
        0.3,
        0.2
    };

    double score =
        RouteScore::calculate(
            link,
            weights,
            20,    // maximum cost
            40,    // maximum latency
            500    // minimum bandwidth
        );

    /*
        Normalized cost:
        10 / 20 = 0.5

        Normalized latency:
        20 / 40 = 0.5

        Normalized bandwidth:
        500 / 1000 = 0.5

        Final:
        (0.5 × 0.5)
        + (0.3 × 0.5)
        + (0.2 × 0.5)
        = 0.5
    */

    assert(approximatelyEqual(score, 0.5));

    cout << "Test 1 passed: normalized weighted score calculated\n";

    cout << "\nAll normalized route score tests passed!\n";

    return 0;
}