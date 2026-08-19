#include "Graph.h"

#include <cassert>
#include <iostream>

using namespace std;

int main() {

    Graph graph;

    // Create routers
    graph.addRouter("R1");
    graph.addRouter("R2");
    graph.addRouter("R3");
    graph.addRouter("R4");

    cout << "Test 1 passed: routers created\n";


    // Create network topology
    graph.addLink("R1", "R2", 5, 10, 100);
    graph.addLink("R2", "R3", 3, 8, 80);
    graph.addLink("R3", "R4", 4, 12, 90);
    graph.addLink("R1", "R4", 10, 20, 60);

    assert(graph.hasLink("R1", "R2"));
    assert(graph.hasLink("R2", "R3"));
    assert(graph.hasLink("R3", "R4"));
    assert(graph.hasLink("R1", "R4"));

    cout << "Test 2 passed: network topology created\n";


    // Edit an existing link
    graph.updateLink(
        "R1",
        "R4",
        2,
        5,
        150
    );

    vector<LinkInfo> neighbors =
        graph.getNeighbors("R1");

    bool updated = false;

    for (const auto& edge : neighbors) {
        if (edge.router == "R4") {
            assert(edge.cost == 2);
            assert(edge.latency == 5);
            assert(edge.bandwidth == 150);

            updated = true;
        }
    }

    assert(updated);

    cout << "Test 3 passed: link metrics updated\n";


    // Delete one link
    graph.removeLink("R1", "R2");

    assert(!graph.hasLink("R1", "R2"));
    assert(!graph.hasLink("R2", "R1"));

    // Other links must remain
    assert(graph.hasLink("R2", "R3"));
    assert(graph.hasLink("R3", "R4"));
    assert(graph.hasLink("R1", "R4"));

    cout << "Test 4 passed: link deleted without affecting other links\n";


    // Delete a router
    graph.removeRouter("R3");

    // Links connected to R3 must disappear
    assert(!graph.hasLink("R2", "R3"));
    assert(!graph.hasLink("R3", "R4"));

    // Unrelated link must remain
    assert(graph.hasLink("R1", "R4"));

    cout << "Test 5 passed: router deletion removed connected links\n";


    // Verify remaining topology
    assert(graph.hasLink("R1", "R4"));
    assert(!graph.hasLink("R1", "R2"));
    assert(!graph.hasLink("R2", "R3"));

    cout << "Test 6 passed: remaining graph is consistent\n";


    cout << "\nAll dynamic graph tests passed!\n";

    return 0;
}
