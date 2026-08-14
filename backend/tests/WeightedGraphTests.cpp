#include <iostream>
#include <cassert>

#include "Graph.h"

using namespace std;

int main() {

    Graph network;

    network.addLink("R1", "R2", 10);
    network.addLink("R1", "R3", 5);

    // Test 1: R1 has two weighted neighbors
    vector<pair<string, int>> neighbors =
        network.getNeighbors("R1");

    assert(neighbors.size() == 2);

    cout << "Test 1 passed: weighted neighbors stored\n";


    // Test 2: Check weights
    bool foundR2 = false;
    bool foundR3 = false;

    for (const auto& edge : neighbors) {

        if (edge.first == "R2") {
            assert(edge.second == 10);
            foundR2 = true;
        }

        if (edge.first == "R3") {
            assert(edge.second == 5);
            foundR3 = true;
        }
    }

    assert(foundR2);
    assert(foundR3);

    cout << "Test 2 passed: link weights are correct\n";


    // Test 3: Graph is undirected
    vector<pair<string, int>> r2Neighbors =
        network.getNeighbors("R2");

    assert(r2Neighbors.size() == 1);
    assert(r2Neighbors[0].first == "R1");
    assert(r2Neighbors[0].second == 10);

    cout << "Test 3 passed: reverse link preserves weight\n";


    cout << "\nAll weighted graph tests passed!\n";

    return 0;
}