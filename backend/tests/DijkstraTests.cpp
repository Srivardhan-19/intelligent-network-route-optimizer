#include <iostream>
#include <cassert>

#include "Graph.h"
#include "Dijkstra.h"

using namespace std;

int main() {

    Graph network;

    /*
             10
        R1 ------- R2
         |         |
        5|         |3
         |         |
        R3 ------- R4
              2
    */

    network.addLink("R1", "R2", 10);
    network.addLink("R1", "R3", 5);
    network.addLink("R2", "R4", 3);
    network.addLink("R3", "R4", 2);

    // Test 1: lowest-cost route
    RoutingResult result =
        Dijkstra::findShortestPath(
            network,
            "R1",
            "R4"
        );

    assert(result.found);
    assert(result.cost == 7);

    assert(result.path.size() == 3);
    assert(result.path[0] == "R1");
    assert(result.path[1] == "R3");
    assert(result.path[2] == "R4");

    cout << "Test 1 passed: lowest-cost route found\n";


    // Test 2: source == destination
    result =
        Dijkstra::findShortestPath(
            network,
            "R1",
            "R1"
        );

    assert(result.found);
    assert(result.cost == 0);
    assert(result.path.size() == 1);
    assert(result.path[0] == "R1");

    cout << "Test 2 passed: same source and destination\n";


    // Test 3: unreachable destination
    network.addRouter("R5");

    result =
        Dijkstra::findShortestPath(
            network,
            "R1",
            "R5"
        );

    assert(!result.found);

    cout << "Test 3 passed: unreachable destination\n";


    // Test 4: cheapest route can have more hops
    Graph network2;

    network2.addLink("A", "B", 100);
    network2.addLink("A", "C", 5);
    network2.addLink("C", "D", 5);
    network2.addLink("D", "B", 5);

    result =
        Dijkstra::findShortestPath(
            network2,
            "A",
            "B"
        );

    assert(result.found);
    assert(result.cost == 15);

    assert(result.path.size() == 4);
    assert(result.path[0] == "A");
    assert(result.path[1] == "C");
    assert(result.path[2] == "D");
    assert(result.path[3] == "B");

    cout << "Test 4 passed: cheapest route can have more hops\n";


    cout << "\nAll Dijkstra tests passed!\n";

    return 0;
}