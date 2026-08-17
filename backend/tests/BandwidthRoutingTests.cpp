#include <cassert>
#include <iostream>

#include "Graph.h"
#include "Dijkstra.h"
#include "RoutingMetric.h"

using namespace std;

int main() {

    Graph graph;

    /*
        Network:

              R2
             /  \
           /      \
         R1        R4
           \      /
            \    /
              R3

        Route through R2:
        R1 → R2 → R4
        bandwidth = 100 Mbps on each link

        Route through R3:
        R1 → R3 → R4
        bandwidth = 1000 Mbps on each link
    */

    graph.addLink("R1", "R2", 5, 20, 100);
    graph.addLink("R2", "R4", 5, 20, 100);

    graph.addLink("R1", "R3", 10, 30, 1000);
    graph.addLink("R3", "R4", 10, 30, 1000);


    // --------------------------------------------------
    // Test 1: Bandwidth optimization
    // --------------------------------------------------

    RoutingResult result =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::BANDWIDTH
        );

    assert(result.found);

    assert(
        result.path.size() == 3 &&
        result.path[0] == "R1" &&
        result.path[1] == "R3" &&
        result.path[2] == "R4"
    );

    cout << "Test 1 passed: bandwidth optimization selects highest-bandwidth route\n";


    // --------------------------------------------------
    // Test 2: Cost still selects the cheaper route
    // --------------------------------------------------

    RoutingResult costResult =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::COST
        );

    assert(costResult.found);

    assert(
        costResult.path.size() == 3 &&
        costResult.path[0] == "R1" &&
        costResult.path[1] == "R2" &&
        costResult.path[2] == "R4"
    );

    cout << "Test 2 passed: cost optimization still selects cheaper route\n";


    // --------------------------------------------------
    // Test 3: Different objectives select different routes
    // --------------------------------------------------

    assert(result.path != costResult.path);

    cout << "Test 3 passed: bandwidth and cost select different routes\n";


    cout << "\nAll bandwidth routing tests passed!\n";

    return 0;
}