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
        Initial topology:

        R1 -> R2 -> R4
        R1 -> R3 -> R4

        Route A: lower cost
        Route B: lower latency
    */

    graph.addLink("R1", "R2", 2, 20, 100);
    graph.addLink("R2", "R4", 2, 20, 100);

    graph.addLink("R1", "R3", 8, 5, 100);
    graph.addLink("R3", "R4", 8, 5, 100);


    // --------------------------------------------------
    // Test 1: Balanced weights initially favor cost
    // --------------------------------------------------

    RoutingWeights weights;

    weights.costWeight = 0.7;
    weights.latencyWeight = 0.3;
    weights.bandwidthWeight = 0.0;

    RoutingResult result1 =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            weights
        );

    assert(result1.found);
    assert(result1.path.size() == 3);
    assert(result1.path[0] == "R1");
    assert(result1.path[1] == "R2");
    assert(result1.path[2] == "R4");

    cout << "Test 1 passed: balanced routing initially favors cost\n";


    // --------------------------------------------------
    // Test 2: Change weights to favor latency
    // --------------------------------------------------

    weights.costWeight = 0.2;
    weights.latencyWeight = 0.8;
    weights.bandwidthWeight = 0.0;

    RoutingResult result2 =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            weights
        );

    assert(result2.found);
    assert(result2.path.size() == 3);
    assert(result2.path[0] == "R1");
    assert(result2.path[1] == "R3");
    assert(result2.path[2] == "R4");

    cout << "Test 2 passed: balanced routing changes preference with weights\n";


    // --------------------------------------------------
    // Test 3: Change link metrics
    // --------------------------------------------------

    graph.updateLink(
        "R1",
        "R2",
        20,
        2,
        100
    );

    graph.updateLink(
        "R2",
        "R4",
        20,
        2,
        100
    );

    // Cost-focused weights should now prefer R3
    weights.costWeight = 0.7;
    weights.latencyWeight = 0.3;
    weights.bandwidthWeight = 0.0;

    RoutingResult result3 =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            weights
        );

    assert(result3.found);
    assert(result3.path.size() == 3);
    assert(result3.path[0] == "R1");
    assert(result3.path[1] == "R3");
    assert(result3.path[2] == "R4");

    cout << "Test 3 passed: balanced routing adapts after metric update\n";


    // --------------------------------------------------
    // Test 4: Delete preferred route
    // --------------------------------------------------

    graph.removeLink("R1", "R3");
    graph.removeLink("R3", "R4");

    RoutingResult result4 =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            weights
        );

    assert(result4.found);
    assert(result4.path.size() == 3);
    assert(result4.path[0] == "R1");
    assert(result4.path[1] == "R2");
    assert(result4.path[2] == "R4");

    cout << "Test 4 passed: balanced routing uses remaining route after deletion\n";


    // --------------------------------------------------
    // Test 5: Delete remaining route
    // --------------------------------------------------

    graph.removeLink("R1", "R2");
    graph.removeLink("R2", "R4");

    RoutingResult result5 =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R4",
            weights
        );

    assert(!result5.found);
    assert(result5.path.empty());

    cout << "Test 5 passed: balanced routing detects unreachable destination\n";


    cout << "\nAll balanced routing topology change tests passed!\n";

    return 0;
}