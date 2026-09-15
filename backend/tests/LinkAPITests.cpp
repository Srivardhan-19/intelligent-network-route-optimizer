#include <iostream>
#include <cassert>

#include "NetworkAPI.h"

using namespace std;

int main() {

    NetworkAPI api;

    // --------------------------------
    // Create routers
    // --------------------------------

    api.addRouter("R1");
    api.addRouter("R2");
    api.addRouter("R3");

    // --------------------------------
    // Test 1: Add link
    // --------------------------------

    api.addLink(
        "R1",
        "R2",
        5,
        10,
        100
    );

    assert(
        api.getGraph().hasLink("R1", "R2")
    );

    assert(
        api.getGraph().hasLink("R2", "R1")
    );

    cout << "Test 1 passed: link added in both directions\n";


    // --------------------------------
    // Test 2: Check initial metrics
    // --------------------------------

    vector<LinkInfo> neighbors =
        api.getGraph().getNeighbors("R1");

    assert(neighbors.size() == 1);

    assert(neighbors[0].router == "R2");
    assert(neighbors[0].cost == 5);
    assert(neighbors[0].latency == 10);
    assert(neighbors[0].bandwidth == 100);

    cout << "Test 2 passed: initial link metrics stored correctly\n";


    // --------------------------------
    // Test 3: Update link
    // --------------------------------

    api.updateLink(
        "R1",
        "R2",
        8,
        20,
        200
    );

    neighbors =
        api.getGraph().getNeighbors("R1");

    assert(neighbors.size() == 1);

    assert(neighbors[0].cost == 8);
    assert(neighbors[0].latency == 20);
    assert(neighbors[0].bandwidth == 200);

    cout << "Test 3 passed: link metrics updated correctly\n";


    // --------------------------------
    // Test 4: Reverse link updated
    // --------------------------------

    neighbors =
        api.getGraph().getNeighbors("R2");

    assert(neighbors.size() == 1);

    assert(neighbors[0].router == "R1");
    assert(neighbors[0].cost == 8);
    assert(neighbors[0].latency == 20);
    assert(neighbors[0].bandwidth == 200);

    cout << "Test 4 passed: reverse link metrics updated correctly\n";


    // --------------------------------
    // Test 5: Add another link
    // --------------------------------

    api.addLink(
        "R2",
        "R3",
        3,
        15,
        150
    );

    assert(
        api.getGraph().hasLink("R2", "R3")
    );

    assert(
        api.getGraph().hasLink("R3", "R2")
    );

    cout << "Test 5 passed: second link added correctly\n";


    // --------------------------------
    // Test 6: Delete link
    // --------------------------------

    api.removeLink(
        "R1",
        "R2"
    );

    assert(
        !api.getGraph().hasLink("R1", "R2")
    );

    assert(
        !api.getGraph().hasLink("R2", "R1")
    );

    cout << "Test 6 passed: link deleted in both directions\n";


    // --------------------------------
    // Test 7: Remaining link preserved
    // --------------------------------

    assert(
        api.getGraph().hasLink("R2", "R3")
    );

    assert(
        api.getGraph().hasLink("R3", "R2")
    );

    cout << "Test 7 passed: remaining link preserved\n";


    // --------------------------------
    // Test 8: Delete nonexistent link
    // --------------------------------

    api.removeLink(
        "R1",
        "R3"
    );

    assert(
        api.getGraph().hasLink("R2", "R3")
    );

    cout << "Test 8 passed: nonexistent link handled\n";


    cout << "\nAll Link API tests passed!\n";

    return 0;
}