#include <iostream>
#include <cassert>

#include "Graph.h"
#include "BFS.h"

using namespace std;

int main() {

    Graph graph;

    // Create routers
    graph.addRouter("R1");
    graph.addRouter("R2");
    graph.addRouter("R3");
    graph.addRouter("R4");

    // Create topology
    //
    // R1 --- R2 --- R4
    //  \             /
    //   ---- R3 ----
    //
    graph.addLink("R1", "R2", 10, 20, 100);
    graph.addLink("R2", "R4", 10, 20, 100);

    graph.addLink("R1", "R3", 10, 20, 100);
    graph.addLink("R3", "R4", 10, 20, 100);

    // Test 1:
    // Both routes have 2 hops.
    // BFS should find one of the shortest-hop routes.
    RoutingResult result1 =
        BFS::findShortestPath(
            graph,
            "R1",
            "R4"
        );

    assert(result1.path.size() == 3);
    assert(result1.path.front() == "R1");
    assert(result1.path.back() == "R4");

    cout << "Test 1 passed: BFS found a shortest-hop route\n";


    // Add a direct link.
    //
    // R1 -------- R4
    //
    graph.addLink("R1", "R4", 50, 50, 50);

    RoutingResult result2 =
        BFS::findShortestPath(
            graph,
            "R1",
            "R4"
        );

    // Direct route has only 1 hop.
    assert(result2.path.size() == 2);
    assert(result2.path[0] == "R1");
    assert(result2.path[1] == "R4");

    cout << "Test 2 passed: BFS selected new direct route\n";


    // Remove the direct link.
    graph.removeLink("R1", "R4");

    RoutingResult result3 =
        BFS::findShortestPath(
            graph,
            "R1",
            "R4"
        );

    // BFS should return to a 2-hop route.
    assert(result3.path.size() == 3);
    assert(result3.path.front() == "R1");
    assert(result3.path.back() == "R4");

    cout << "Test 3 passed: BFS recalculated route after link deletion\n";


    // Delete R3.
    graph.removeRouter("R3");

    RoutingResult result4 =
        BFS::findShortestPath(
            graph,
            "R1",
            "R4"
        );

    // R1 -> R2 -> R4 should still exist.
    assert(result4.path.size() == 3);
    assert(result4.path[0] == "R1");
    assert(result4.path[1] == "R2");
    assert(result4.path[2] == "R4");

    cout << "Test 4 passed: BFS found remaining route after router deletion\n";


    // Delete R2.
    graph.removeRouter("R2");

    RoutingResult result5 =
        BFS::findShortestPath(
            graph,
            "R1",
            "R4"
        );

    // No route should remain.
    assert(result5.path.empty());

    cout << "Test 5 passed: BFS correctly detected unreachable destination\n";


    cout << "\nAll BFS topology change tests passed!\n";

    return 0;
}