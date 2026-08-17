#include <cassert>
#include <iostream>

#include "Graph.h"

using namespace std;

int main() {

    Graph graph;

    graph.addLink(
        "R1",
        "R2",
        10,   // cost
        20,   // latency
        100   // bandwidth
    );

    auto neighbors = graph.getNeighbors("R1");

    assert(neighbors.size() == 1);

    const auto& link = neighbors[0];

    assert(link.router == "R2");
    cout << "Test 1 passed: neighbor stored correctly\n";

    assert(link.cost == 10);
    cout << "Test 2 passed: cost stored correctly\n";

    assert(link.latency == 20);
    cout << "Test 3 passed: latency stored correctly\n";

    assert(link.bandwidth == 100);
    cout << "Test 4 passed: bandwidth stored correctly\n";

    auto reverseNeighbors = graph.getNeighbors("R2");

    assert(reverseNeighbors.size() == 1);

    const auto& reverseLink = reverseNeighbors[0];

    assert(reverseLink.router == "R1");
    assert(reverseLink.cost == 10);
    assert(reverseLink.latency == 20);
    assert(reverseLink.bandwidth == 100);

    cout << "Test 5 passed: reverse link preserves all metrics\n";

    cout << "\nAll link metric tests passed!\n";

    return 0;
}