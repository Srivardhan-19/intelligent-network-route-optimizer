#include <iostream>
#include <cassert>

#include "NetworkAPI.h"

using namespace std;

int main() {

    NetworkAPI api;

    // --------------------------------
    // Create routers
    // --------------------------------

    api.addRouter("R1");
    api.addRouter("R2");
    api.addRouter("R3");
    api.addRouter("R4");

    // --------------------------------
    // Create topology
    // --------------------------------

    api.addLink(
        "R1",
        "R2",
        2,
        20,
        100
    );

    api.addLink(
        "R2",
        "R4",
        2,
        20,
        100
    );

    api.addLink(
        "R1",
        "R3",
        5,
        10,
        200
    );

    api.addLink(
        "R3",
        "R4",
        5,
        10,
        200
    );


    // --------------------------------
    // Test 1: BFS
    // --------------------------------

    RoutingResult bfsResult =
        api.findRoute(
            "R1",
            "R4",
            "BFS"
        );

    assert(bfsResult.found);
    assert(bfsResult.path.size() == 3);

    cout << "Test 1 passed: API finds route using BFS\n";


    // --------------------------------
    // Test 2: Dijkstra - cost
    // --------------------------------

    RoutingResult dijkstraResult =
        api.findRoute(
            "R1",
            "R4",
            "Dijkstra",
            RoutingMetric::COST
        );

    assert(dijkstraResult.found);
    assert(dijkstraResult.path.size() == 3);

    assert(dijkstraResult.path[0] == "R1");
    assert(dijkstraResult.path[1] == "R2");
    assert(dijkstraResult.path[2] == "R4");

    cout << "Test 2 passed: API finds cost route using Dijkstra\n";


    // --------------------------------
    // Test 3: Dijkstra - latency
    // --------------------------------

    RoutingResult latencyResult =
        api.findRoute(
            "R1",
            "R4",
            "Dijkstra",
            RoutingMetric::LATENCY
        );

    assert(latencyResult.found);
    assert(latencyResult.path.size() == 3);

    assert(latencyResult.path[0] == "R1");
    assert(latencyResult.path[1] == "R3");
    assert(latencyResult.path[2] == "R4");

    cout << "Test 3 passed: API finds latency route using Dijkstra\n";


    // --------------------------------
    // Test 4: Bellman-Ford
    // --------------------------------

    RoutingResult bellmanResult =
        api.findRoute(
            "R1",
            "R4",
            "Bellman-Ford"
        );

    assert(bellmanResult.found);
    assert(bellmanResult.path.size() == 3);

    cout << "Test 4 passed: API finds route using Bellman-Ford\n";


    // --------------------------------
    // Test 5: Invalid algorithm
    // --------------------------------

    RoutingResult invalidResult =
        api.findRoute(
            "R1",
            "R4",
            "Invalid"
        );

    assert(!invalidResult.found);
    assert(invalidResult.path.empty());

    cout << "Test 5 passed: invalid algorithm handled\n";


    // --------------------------------
    // Test 6: Unreachable destination
    // --------------------------------

    api.removeLink("R1", "R2");
    api.removeLink("R1", "R3");

    RoutingResult unreachableResult =
        api.findRoute(
            "R1",
            "R4",
            "Dijkstra",
            RoutingMetric::COST
        );

    assert(!unreachableResult.found);
    assert(unreachableResult.path.empty());

    cout << "Test 6 passed: API detects unreachable destination\n";


    cout << "\nAll Routing API tests passed!\n";

    return 0;
}