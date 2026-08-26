#include <iostream>
#include <cassert>

#include "Graph.h"
#include "Dijkstra.h"

using namespace std;

int main() {

    Graph graph;

    // Create routers
    graph.addRouter("R1");
    graph.addRouter("R2");
    graph.addRouter("R3");
    graph.addRouter("R4");

    // Initial topology
    graph.addLink("R1", "R2", 2, 10, 100);
    graph.addLink("R2", "R4", 2, 10, 100);

    graph.addLink("R1", "R3", 5, 10, 100);
    graph.addLink("R3", "R4", 5, 10, 100);

    // Test 1: Initial route
    RoutingResult result1 =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4"
        );

    assert(result1.found);
    assert(result1.path.size() == 3);
    assert(result1.path[0] == "R1");
    assert(result1.path[1] == "R2");
    assert(result1.path[2] == "R4");

    cout << "Test 1 passed: Dijkstra finds initial lowest-cost route\n";

    // Test 2: Update link cost
    graph.updateLink(
        "R1",
        "R2",
        20,
        10,
        100
    );

    RoutingResult result2 =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4"
        );

    assert(result2.found);
    assert(result2.path.size() == 3);
    assert(result2.path[0] == "R1");
    assert(result2.path[1] == "R3");
    assert(result2.path[2] == "R4");

    cout << "Test 2 passed: Dijkstra changes route after link metric update\n";

    // Test 3: Delete link
    graph.removeLink("R1", "R2");

    RoutingResult result3 =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4"
        );

    assert(result3.found);
    assert(result3.path.size() == 3);
    assert(result3.path[0] == "R1");
    assert(result3.path[1] == "R3");
    assert(result3.path[2] == "R4");

    cout << "Test 3 passed: Dijkstra adapts after link deletion\n";

    // Test 4: Delete router
    graph.removeRouter("R3");

    RoutingResult result4 =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4"
        );

    assert(!result4.found);
    assert(result4.path.empty());

    cout << "Test 4 passed: Dijkstra detects unreachable destination after router deletion\n";

    cout << "\nAll Dijkstra topology change tests passed!\n";

    return 0;
}