#include <iostream>
#include <cassert>

#include "NetworkAPI.h"

using namespace std;

int main() {

    NetworkAPI api;

    // --------------------------------
    // Test 1: Add routers
    // --------------------------------

    api.addRouter("R1");
    api.addRouter("R2");
    api.addRouter("R3");

    vector<string> routers =
        api.getGraph().getRouters();

    assert(routers.size() == 3);

    cout << "Test 1 passed: routers added through API\n";


    // --------------------------------
    // Test 2: Duplicate router
    // --------------------------------

    api.addRouter("R1");

    routers =
        api.getGraph().getRouters();

    assert(routers.size() == 3);

    cout << "Test 2 passed: duplicate router handled\n";


    // --------------------------------
    // Test 3: Create connected topology
    // --------------------------------

    api.addLink(
        "R1",
        "R2",
        5,
        10,
        100
    );

    api.addLink(
        "R2",
        "R3",
        3,
        20,
        200
    );

    assert(
        api.getGraph().hasLink("R1", "R2")
    );

    assert(
        api.getGraph().hasLink("R2", "R3")
    );

    cout << "Test 3 passed: router connections created\n";


    // --------------------------------
    // Test 4: Delete router
    // --------------------------------

    api.removeRouter("R2");

    routers =
        api.getGraph().getRouters();

    assert(routers.size() == 2);

    assert(
        !api.getGraph().hasLink("R1", "R2")
    );

    assert(
        !api.getGraph().hasLink("R2", "R3")
    );

    cout << "Test 4 passed: router deleted with connected links\n";


    // --------------------------------
    // Test 5: Remaining routers preserved
    // --------------------------------

    assert(
        api.getGraph().getNeighbors("R1").empty()
    );

    assert(
        api.getGraph().getNeighbors("R3").empty()
    );

    cout << "Test 5 passed: remaining topology is consistent\n";


    // --------------------------------
    // Test 6: Delete nonexistent router
    // --------------------------------

    api.removeRouter("R99");

    routers =
        api.getGraph().getRouters();

    assert(routers.size() == 2);

    cout << "Test 6 passed: nonexistent router handled\n";


    cout << "\nAll Router API tests passed!\n";

    return 0;
}