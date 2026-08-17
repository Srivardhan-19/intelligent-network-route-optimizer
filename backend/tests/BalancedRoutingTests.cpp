#include <cassert>
#include <iostream>

#include "Graph.h"
#include "BalancedRouting.h"
#include "RoutingWeights.h"

using namespace std;

int main() {

    Graph graph;

    /*
        Route A:
        R1 → R2 → R4

        Low cost
        High latency
        Low bandwidth
    */

    graph.addLink(
        "R1",
        "R2",
        10,
        100,
        100
    );

    graph.addLink(
        "R2",
        "R4",
        10,
        100,
        100
    );


    /*
        Route B:
        R1 → R3 → R4

        High cost
        Low latency
        High bandwidth
    */

    graph.addLink(
        "R1",
        "R3",
        100,
        10,
        1000
    );

    graph.addLink(
        "R3",
        "R4",
        100,
        10,
        1000
    );


    // ---------------------------------------------
    // Test 1: Cost-focused balanced routing
    // ---------------------------------------------

    RoutingWeights costFocused{
        0.8,
        0.1,
        0.1
    };

    RoutingResult costResult =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            costFocused
        );

    assert(costResult.found);

    assert(
        costResult.path.size() == 3 &&
        costResult.path[0] == "R1" &&
        costResult.path[1] == "R2" &&
        costResult.path[2] == "R4"
    );

    cout << "Test 1 passed: balanced routing favors cost\n";


    // ---------------------------------------------
    // Test 2: Performance-focused routing
    // ---------------------------------------------

    RoutingWeights performanceFocused{
        0.1,
        0.5,
        0.4
    };

    RoutingResult performanceResult =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            performanceFocused
        );

    assert(performanceResult.found);

    assert(
        performanceResult.path.size() == 3 &&
        performanceResult.path[0] == "R1" &&
        performanceResult.path[1] == "R3" &&
        performanceResult.path[2] == "R4"
    );

    cout << "Test 2 passed: balanced routing favors performance\n";


    // ---------------------------------------------
    // Test 3: Weight changes change the route
    // ---------------------------------------------

    assert(
        costResult.path !=
        performanceResult.path
    );

    cout << "Test 3 passed: changing weights changes balanced route\n";


    // ---------------------------------------------
    // Test 4: Same source and destination
    // ---------------------------------------------

    RoutingResult sameResult =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R1",
            costFocused
        );

    assert(sameResult.found);
    assert(sameResult.path.size() == 1);
    assert(sameResult.path[0] == "R1");

    cout << "Test 4 passed: same source and destination\n";


    // ---------------------------------------------
    // Test 5: Unreachable destination
    // ---------------------------------------------

    RoutingResult unreachableResult =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R9",
            costFocused
        );

    assert(!unreachableResult.found);

    cout << "Test 5 passed: unreachable destination\n";


    cout << "\nAll balanced routing tests passed!\n";

    return 0;
}