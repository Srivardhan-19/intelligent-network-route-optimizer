#include <iostream>
#include <cassert>

#include "Graph.h"
#include "Dijkstra.h"
#include "RoutingMetric.h"

using namespace std;

int main() {

    Graph graph;

    // --------------------------------------------------
    // Test 1: Create routers
    // --------------------------------------------------

    graph.addRouter("R1");
    graph.addRouter("R2");
    graph.addRouter("R3");
    graph.addRouter("R4");

    assert(!graph.getNeighbors("R1").empty() ||
           graph.getNeighbors("R1").empty());

    cout << "Test 1 passed: routers created\n";


    // --------------------------------------------------
    // Test 2: Create links with metrics
    // --------------------------------------------------

    graph.addLink("R1", "R2", 2, 10, 100);
    graph.addLink("R2", "R4", 2, 10, 100);

    graph.addLink("R1", "R3", 5, 5, 100);
    graph.addLink("R3", "R4", 5, 5, 100);

    assert(graph.hasLink("R1", "R2"));
    assert(graph.hasLink("R2", "R4"));
    assert(graph.hasLink("R1", "R3"));
    assert(graph.hasLink("R3", "R4"));

    cout << "Test 2 passed: links created with network metrics\n";


    // --------------------------------------------------
    // Test 3: Initial cost routing
    // --------------------------------------------------

    RoutingResult result1 =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::COST
        );

    assert(result1.found);
    assert(result1.path.size() == 3);
    assert(result1.path[0] == "R1");
    assert(result1.path[1] == "R2");
    assert(result1.path[2] == "R4");

    cout << "Test 3 passed: initial cost route is R1 -> R2 -> R4\n";


    // --------------------------------------------------
    // Test 4: Update link metrics
    // --------------------------------------------------

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
            "R4",
            RoutingMetric::COST
        );

    assert(result2.found);
    assert(result2.path.size() == 3);
    assert(result2.path[0] == "R1");
    assert(result2.path[1] == "R3");
    assert(result2.path[2] == "R4");

    cout << "Test 4 passed: route changed after metric update\n";


    // --------------------------------------------------
    // Test 5: Verify reverse link update
    // --------------------------------------------------

    vector<LinkInfo> r2Neighbors =
        graph.getNeighbors("R2");

    bool reverseUpdated = false;

    for (const auto& edge : r2Neighbors) {
        if (edge.router == "R1") {
            assert(edge.cost == 20);
            assert(edge.latency == 10);
            assert(edge.bandwidth == 100);

            reverseUpdated = true;
        }
    }

    assert(reverseUpdated);

    cout << "Test 5 passed: reverse link metrics updated correctly\n";


    // --------------------------------------------------
    // Test 6: Delete preferred link
    // --------------------------------------------------

    graph.removeLink(
        "R1",
        "R3"
    );

    assert(!graph.hasLink("R1", "R3"));
    assert(!graph.hasLink("R3", "R1"));

    RoutingResult result3 =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::COST
        );

    assert(result3.found);
    assert(result3.path.size() == 3);
    assert(result3.path[0] == "R1");
    assert(result3.path[1] == "R2");
    assert(result3.path[2] == "R4");

    cout << "Test 6 passed: routing uses remaining route after link deletion\n";


    // --------------------------------------------------
    // Test 7: Delete another link
    // --------------------------------------------------

    graph.removeLink(
        "R1",
        "R2"
    );

    RoutingResult result4 =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R4",
            RoutingMetric::COST
        );

    assert(!result4.found);
    assert(result4.path.empty());

    cout << "Test 7 passed: routing detects unreachable destination\n";


    // --------------------------------------------------
    // Test 8: Delete router
    // --------------------------------------------------

    graph.removeRouter("R3");

    assert(graph.getNeighbors("R3").empty());
    assert(!graph.hasLink("R3", "R4"));

    cout << "Test 8 passed: router deletion removes connected topology\n";


    // --------------------------------------------------
    // Test 9: Final topology consistency
    // --------------------------------------------------

    assert(graph.getNeighbors("R1").empty());

vector<LinkInfo> r4Neighbors =
    graph.getNeighbors("R4");

assert(r4Neighbors.size() == 1);
assert(r4Neighbors[0].router == "R2");

cout << "Test 9 passed: final graph topology is consistent\n";


    // --------------------------------------------------
    // Final result
    // --------------------------------------------------

    cout << "\nAll Phase 4 integration tests passed!\n";

    return 0;
}
