#include <iostream>
#include <cassert>
#include "Graph.h"

using namespace std;

int main() {

    Graph network;

    // Test 1: Add routers and link
    network.addRouter("R1");
    network.addRouter("R2");

    network.addLink("R1", "R2");

    assert(network.hasLink("R1", "R2"));
    assert(network.hasLink("R2", "R1"));

    cout << "Test 1 passed: Add link\n";


    // Test 2: Add another link
    network.addRouter("R3");

    network.addLink("R2", "R3");

    assert(network.hasLink("R2", "R3"));
    assert(network.hasLink("R3", "R2"));

    cout << "Test 2 passed: Multiple links\n";


    // Test 3: Link that doesn't exist
    assert(!network.hasLink("R1", "R3"));

    cout << "Test 3 passed: Non-existing link\n";


    // Test 4: Remove link
    network.removeLink("R1", "R2");

    assert(!network.hasLink("R1", "R2"));
    assert(!network.hasLink("R2", "R1"));

    cout << "Test 4 passed: Remove link\n";


    cout << "\nAll graph tests passed!\n";

    return 0;
}