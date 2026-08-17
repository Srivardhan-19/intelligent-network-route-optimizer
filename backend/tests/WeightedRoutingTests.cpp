#include <cassert>
#include <cmath>
#include <iostream>

#include "RouteScore.h"
#include "RoutingWeights.h"
#include "LinkInfo.h"

using namespace std;

bool approximatelyEqual(double a, double b) {
    return fabs(a - b) < 0.000001;
}

int main() {

    /*
        Route A:
        Low cost
        High latency
        Low bandwidth

        Route B:
        High cost
        Low latency
        High bandwidth
    */

    LinkInfo routeA{
        "RouteA",
        10,     // cost
        100,    // latency
        100     // bandwidth
    };

    LinkInfo routeB{
        "RouteB",
        100,    // cost
        10,     // latency
        1000    // bandwidth
    };


    /*
        Normalization bounds:

        Maximum cost     = 100
        Maximum latency  = 100
        Minimum bandwidth = 100
    */


    // --------------------------------------------------
    // Test 1: Cost-focused preference
    // --------------------------------------------------

    RoutingWeights costFocused{
        0.8,    // cost
        0.1,    // latency
        0.1     // bandwidth
    };

    double scoreA =
        RouteScore::calculate(
            routeA,
            costFocused,
            100,
            100,
            100
        );

    double scoreB =
        RouteScore::calculate(
            routeB,
            costFocused,
            100,
            100,
            100
        );

    assert(scoreA < scoreB);

    cout << "Test 1 passed: cost-focused weights prefer low-cost route\n";


    // --------------------------------------------------
    // Test 2: Latency/bandwidth-focused preference
    // --------------------------------------------------

    RoutingWeights performanceFocused{
        0.1,    // cost
        0.5,    // latency
        0.4     // bandwidth
    };

    scoreA =
        RouteScore::calculate(
            routeA,
            performanceFocused,
            100,
            100,
            100
        );

    scoreB =
        RouteScore::calculate(
            routeB,
            performanceFocused,
            100,
            100,
            100
        );

    assert(scoreB < scoreA);

    cout << "Test 2 passed: performance-focused weights prefer high-performance route\n";


    // --------------------------------------------------
    // Test 3: Changing weights changes preference
    // --------------------------------------------------

    assert(
        RouteScore::calculate(
            routeA,
            costFocused,
            100,
            100,
            100
        )
        <
        RouteScore::calculate(
            routeB,
            costFocused,
            100,
            100,
            100
        )
    );

    assert(
        RouteScore::calculate(
            routeB,
            performanceFocused,
            100,
            100,
            100
        )
        <
        RouteScore::calculate(
            routeA,
            performanceFocused,
            100,
            100,
            100
        )
    );

    cout << "Test 3 passed: changing weights changes route preference\n";


    cout << "\nAll weighted routing tests passed!\n";

    return 0;
}