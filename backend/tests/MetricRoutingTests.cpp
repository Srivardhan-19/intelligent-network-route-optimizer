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
           5/    \5
           /      \
         R1        R4
           \      /
          10\    /10
             \  /
              R3

        Cost:
        R1-R2 = 5
        R2-R4 = 5
        R1-R3 = 10
        R3-R4 = 10

        Latency:
        R1-R2 = 50
        R2-R4 = 50
        R1-R3 = 10
        R3-R4 = 10
    */

    graph.addLink("R1", "R2", 5, 50, 100);
    graph.addLink("R2", "R4", 5, 50, 100);

    graph.addLink("R1", "R3", 10, 10, 100);
    graph.addLink("R3", "R4", 10, 10, 100);


    // --------------------------------------------------
    // Test 1: Cost optimization
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

    assert(costResult.cost == 10);

    cout << "Test 1 passed: cost optimization selects lowest-cost route\n";


    // --------------------------------------------------
    // Test 2: Latency optimization
    // --------------------------------------------------

    RoutingResult latencyResult =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::LATENCY
        );

    assert(latencyResult.found);

    assert(
        latencyResult.path.size() == 3 &&
        latencyResult.path[0] == "R1" &&
        latencyResult.path[1] == "R3" &&
        latencyResult.path[2] == "R4"
    );

    assert(latencyResult.cost == 20);

    cout << "Test 2 passed: latency optimization selects lowest-latency route\n";


    // --------------------------------------------------
    // Test 3: Objectives produce different routes
    // --------------------------------------------------

    assert(costResult.path != latencyResult.path);

    cout << "Test 3 passed: different metrics can select different routes\n";


    cout << "\nAll metric routing tests passed!\n";

    return 0;
}