#include <iostream>
#include <cassert>

#include "NetworkAPI.h"

using namespace std;

int main() {

    NetworkAPI api;

    // Add routers
    api.addRouter("R1");
    api.addRouter("R2");
    api.addRouter("R3");

    // Add links
    api.addLink(
        "R1",
        "R2",
        2,
        10,
        100
    );

    api.addLink(
        "R2",
        "R3",
        2,
        10,
        100
    );

    // Find route
    RoutingResult result =
        api.findRoute(
            "R1",
            "R3",
            RoutingMetric::COST
        );

    assert(result.found);

    assert(result.path.size() == 3);

    assert(result.path[0] == "R1");
    assert(result.path[1] == "R2");
    assert(result.path[2] == "R3");

    cout << "Test 1 passed: API finds route\n";

    // Update link
    api.updateLink(
        "R1",
        "R2",
        20,
        10,
        100
    );

    cout << "Test 2 passed: API updates link\n";

    // Remove link
    api.removeLink(
        "R1",
        "R2"
    );

    cout << "Test 3 passed: API removes link\n";

    // Remove router
    api.removeRouter("R2");

    cout << "Test 4 passed: API removes router\n";

    cout << "\nAll Network API tests passed!\n";

    return 0;
}