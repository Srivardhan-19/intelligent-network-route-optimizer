#include <iostream>
#include <cassert>

#include "Graph.h"
#include "BFS.h"

using namespace std;

int main() {

    // Create network
    Graph network;

    network.addLink("R1", "R2");
    network.addLink("R2", "R3");
    network.addLink("R1", "R4");
    network.addLink("R4", "R3");


    // Test 1: Shortest-hop route
    RoutingResult result =
        BFS::findShortestPath(
            network,
            "R1",
            "R3"
        );

    assert(result.found);
    assert(result.cost == 2);

    assert(result.path.size() == 3);
    assert(result.path.front() == "R1");
    assert(result.path.back() == "R3");

    cout << "Test 1 passed: shortest-hop route\n";


    // Test 2: Source and destination are same
    result =
        BFS::findShortestPath(
            network,
            "R1",
            "R1"
        );

    assert(result.found);
    assert(result.cost == 0);
    assert(result.path.size() == 1);
    assert(result.path[0] == "R1");

    cout << "Test 2 passed: same source and destination\n";


    // Test 3: Destination does not exist
    result =
        BFS::findShortestPath(
            network,
            "R1",
            "R99"
        );

    assert(!result.found);
    assert(result.cost == -1);
    assert(result.path.empty());

    cout << "Test 3 passed: unreachable destination\n";


    // Test 4: Completely disconnected routers
    network.addRouter("R10");

    result =
        BFS::findShortestPath(
            network,
            "R1",
            "R10"
        );

    assert(!result.found);
    assert(result.cost == -1);
    assert(result.path.empty());

    cout << "Test 4 passed: disconnected routers\n";


    cout << "\nAll BFS tests passed!\n";

    return 0;
}