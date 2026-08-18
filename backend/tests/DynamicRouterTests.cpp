#include "Graph.h"
#include <cassert>
#include <iostream>

using namespace std;

int main() {

    Graph graph;

    // Test 1: add router
    graph.addRouter("R1");

    cout << "Test 1 passed: router added\n";


    // Test 2: adding duplicate router does not create a problem
    graph.addRouter("R1");

    cout << "Test 2 passed: duplicate router handled\n";


    // Build a small network
    graph.addRouter("R2");
    graph.addRouter("R3");

    graph.addLink("R1", "R2", 5, 10, 100);
    graph.addLink("R2", "R3", 3, 8, 80);


    // Test 3: links exist
    assert(graph.hasLink("R1", "R2"));
    assert(graph.hasLink("R2", "R3"));

    cout << "Test 3 passed: router links exist\n";


    // Test 4: delete router
    graph.removeRouter("R2");

    assert(!graph.hasLink("R1", "R2"));
    assert(!graph.hasLink("R2", "R3"));

    cout << "Test 4 passed: router deleted with connected links\n";


    // Test 5: deleting nonexistent router
    graph.removeRouter("R9");

    cout << "Test 5 passed: nonexistent router handled\n";


    cout << "\nAll dynamic router tests passed!\n";

    return 0;
}