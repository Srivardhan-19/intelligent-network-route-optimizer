#include <iostream>
#include <cassert>

#include "Graph.h"
#include "Dijkstra.h"
#include "RoutingMetric.h"

using namespace std;

int main() {

    Graph graph;

    // Create routers
    graph.addRouter("R1");
    graph.addRouter("R2");
    graph.addRouter("R3");
    graph.addRouter("R4");

    // Route A:
    // R1 -> R2 -> R4
    graph.addLink("R1", "R2", 2, 20, 50);
    graph.addLink("R2", "R4", 2, 20, 50);

    // Route B:
    // R1 -> R3 -> R4
    graph.addLink("R1", "R3", 5, 10, 100);
    graph.addLink("R3", "R4", 5, 10, 100);

    // --------------------------------------------------
    // Test 1: Cost routing
    // Route A should be cheaper
    // --------------------------------------------------

    RoutingResult costResult =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::COST
        );

    assert(costResult.found);
    assert(costResult.path.size() == 3);
    assert(costResult.path[0] == "R1");
    assert(costResult.path[1] == "R2");
    assert(costResult.path[2] == "R4");

    cout << "Test 1 passed: cost routing selects lowest-cost route\n";


    // --------------------------------------------------
    // Test 2: Latency routing
    // Route B should have lower latency
    // --------------------------------------------------

    RoutingResult latencyResult =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::LATENCY
        );

    assert(latencyResult.found);
    assert(latencyResult.path.size() == 3);
    assert(latencyResult.path[0] == "R1");
    assert(latencyResult.path[1] == "R3");
    assert(latencyResult.path[2] == "R4");

    cout << "Test 2 passed: latency routing selects lowest-latency route\n";


    // --------------------------------------------------
    // Test 3: Bandwidth routing
    // Route B should have higher bandwidth
    // --------------------------------------------------

    RoutingResult bandwidthResult =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::BANDWIDTH
        );

    assert(bandwidthResult.found);
    assert(bandwidthResult.path.size() == 3);
    assert(bandwidthResult.path[0] == "R1");
    assert(bandwidthResult.path[1] == "R3");
    assert(bandwidthResult.path[2] == "R4");

    cout << "Test 3 passed: bandwidth routing selects highest-bandwidth route\n";


    // --------------------------------------------------
    // Test 4: Change latency of Route B
    // Route A should now become the lower-latency route
    // --------------------------------------------------

    graph.updateLink(
        "R1",
        "R3",
        5,
        30,
        100
    );

    graph.updateLink(
        "R3",
        "R4",
        5,
        30,
        100
    );

    RoutingResult latencyResult2 =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::LATENCY
        );

    assert(latencyResult2.found);
    assert(latencyResult2.path.size() == 3);
    assert(latencyResult2.path[0] == "R1");
    assert(latencyResult2.path[1] == "R2");
    assert(latencyResult2.path[2] == "R4");

    cout << "Test 4 passed: latency route changes after metric update\n";


    // --------------------------------------------------
    // Test 5: Change cost of Route A
    // Route B should now become the cheaper route
    // --------------------------------------------------

    graph.updateLink(
        "R1",
        "R2",
        20,
        20,
        50
    );

    graph.updateLink(
        "R2",
        "R4",
        20,
        20,
        50
    );

    RoutingResult costResult2 =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::COST
        );

    assert(costResult2.found);
    assert(costResult2.path.size() == 3);
    assert(costResult2.path[0] == "R1");
    assert(costResult2.path[1] == "R3");
    assert(costResult2.path[2] == "R4");

    cout << "Test 5 passed: cost route changes after metric update\n";


    // --------------------------------------------------
    // Test 6: Delete the remaining Route B
    // Destination should become unreachable
    // --------------------------------------------------

    // Test 6: Delete the remaining route
graph.removeLink("R1", "R2");
graph.removeLink("R2", "R4");
graph.removeLink("R1", "R3");
graph.removeLink("R3", "R4");

RoutingResult result6 =
    Dijkstra::findShortestPath(
        graph,
        "R1",
        "R4",
        RoutingMetric::COST
    );

assert(!result6.found);
assert(result6.path.empty());

cout << "Test 6 passed: routing detects unreachable destination after topology change\n";

cout << "\nAll metric routing topology change tests passed!\n";

return 0;
}
 
