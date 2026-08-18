#include "Graph.h"

#include <cassert>
#include <iostream>

using namespace std;

int main() {

    Graph graph;

    // Test 1: Add link
    graph.addLink("R1", "R2", 5, 10, 100);

    assert(graph.hasLink("R1", "R2"));
    assert(graph.hasLink("R2", "R1"));

    cout << "Test 1 passed: link added in both directions\n";


    // Test 2: Initial metrics stored correctly
    vector<LinkInfo> neighbors =
        graph.getNeighbors("R1");

    assert(neighbors.size() == 1);
    assert(neighbors[0].router == "R2");
    assert(neighbors[0].cost == 5);
    assert(neighbors[0].latency == 10);
    assert(neighbors[0].bandwidth == 100);

    cout << "Test 2 passed: initial link metrics stored correctly\n";


    // Test 3: Update link metrics
    graph.updateLink(
        "R1",
        "R2",
        3,
        8,
        120
    );

    neighbors = graph.getNeighbors("R1");

    assert(neighbors[0].cost == 3);
    assert(neighbors[0].latency == 8);
    assert(neighbors[0].bandwidth == 120);

    cout << "Test 3 passed: link metrics updated correctly\n";


    // Test 4: Reverse direction also updated
    neighbors = graph.getNeighbors("R2");

    assert(neighbors.size() == 1);
    assert(neighbors[0].router == "R1");
    assert(neighbors[0].cost == 3);
    assert(neighbors[0].latency == 8);
    assert(neighbors[0].bandwidth == 120);

    cout << "Test 4 passed: reverse link preserves updated metrics\n";


    // Test 5: Delete link
    graph.removeLink("R1", "R2");

    assert(!graph.hasLink("R1", "R2"));
    assert(!graph.hasLink("R2", "R1"));

    cout << "Test 5 passed: link deleted in both directions\n";


    // Test 6: Update nonexistent link
    graph.updateLink(
        "R1",
        "R3",
        10,
        20,
        50
    );

    cout << "Test 6 passed: nonexistent link handled\n";


    cout << "\nAll dynamic link tests passed!\n";

    return 0;
}