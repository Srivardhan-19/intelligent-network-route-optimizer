#include <iostream>
#include <cassert>

#include "Graph.h"
#include "BalancedRouting.h"
#include "RoutingWeights.h"

using namespace std;

int main() {

    Graph graph;

    // Create routers
    graph.addRouter("R1");
    graph.addRouter("R2");
    graph.addRouter("R3");
    graph.addRouter("R4");

    /*
        Two possible routes:

        Route A:
        R1 -> R2 -> R4

        Route B:
        R1 -> R3 -> R4
    */

    graph.addLink("R1", "R2", 2, 20, 100);
    graph.addLink("R2", "R4", 2, 20, 100);

    graph.addLink("R1", "R3", 8, 5, 100);
    graph.addLink("R3", "R4", 8, 5, 100);

    // --------------------------------------------------
    // Test 1: Cost-focused routing
    // --------------------------------------------------

    RoutingWeights costFocused;

    costFocused.costWeight = 1.0;
    costFocused.latencyWeight = 0.0;
    costFocused.bandwidthWeight = 0.0;

    RoutingResult result1 =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            costFocused
        );

    assert(result1.found);
    assert(result1.path.size() == 3);
    assert(result1.path[0] == "R1");
    assert(result1.path[1] == "R2");
    assert(result1.path[2] == "R4");

    cout << "Test 1 passed: cost-focused routing selects lowest-cost route\n";


    // --------------------------------------------------
    // Test 2: Performance-focused routing
    // --------------------------------------------------

    RoutingWeights latencyFocused;

    latencyFocused.costWeight = 0.0;
    latencyFocused.latencyWeight = 1.0;
    latencyFocused.bandwidthWeight = 0.0;

    RoutingResult result2 =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            latencyFocused
        );

    assert(result2.found);
    assert(result2.path.size() == 3);
    assert(result2.path[0] == "R1");
    assert(result2.path[1] == "R3");
    assert(result2.path[2] == "R4");

    cout << "Test 2 passed: latency-focused routing selects lowest-latency route\n";


    // --------------------------------------------------
    // Test 3: Change link metric
    // --------------------------------------------------

    graph.updateLink(
        "R1",
        "R2",
        20,
        20,
        100
    );

    graph.updateLink(
        "R2",
        "R4",
        20,
        20,
        100
    );

    RoutingResult result3 =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            costFocused
        );

    assert(result3.found);
    assert(result3.path.size() == 3);
    assert(result3.path[0] == "R1");
    assert(result3.path[1] == "R3");
    assert(result3.path[2] == "R4");

    cout << "Test 3 passed: weighted routing changes after link metric update\n";


    // --------------------------------------------------
    // Test 4: Remove preferred route
    // --------------------------------------------------

    graph.removeLink("R1", "R3");
    graph.removeLink("R3", "R4");

    RoutingResult result4 =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            latencyFocused
        );

    assert(result4.found);
    assert(result4.path.size() == 3);
    assert(result4.path[0] == "R1");
    assert(result4.path[1] == "R2");
    assert(result4.path[2] == "R4");

    cout << "Test 4 passed: routing uses remaining route after preferred route deletion\n";


    // --------------------------------------------------
    // Test 5: Remove all routes
    // --------------------------------------------------

    graph.removeLink("R1", "R2");
    graph.removeLink("R2", "R4");

    RoutingResult result5 =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            costFocused
        );

    assert(!result5.found);
    assert(result5.path.empty());

    cout << "Test 5 passed: weighted routing detects unreachable destination\n";


    cout << "\nAll weighted routing topology change tests passed!\n";

    return 0;
}