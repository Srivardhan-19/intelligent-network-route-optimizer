#include <iostream>
#include <cassert>
#include <string>

#include "NetworkAPI.h"

using namespace std;

int main() {

    NetworkAPI api;

    // Create routers
    api.addRouter("R1");
    api.addRouter("R2");
    api.addRouter("R3");

    // Create links
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

    string json =
        api.getNetworkJSON();

    cout << "Generated JSON:\n";
    cout << json << "\n\n";

    // Check routers
    assert(
        json.find("\"R1\"") != string::npos
    );

    assert(
        json.find("\"R2\"") != string::npos
    );

    assert(
        json.find("\"R3\"") != string::npos
    );

    cout << "Test 1 passed: routers included in JSON\n";

    // Check link metrics
    assert(
        json.find("\"cost\":5") != string::npos
    );

    assert(
        json.find("\"latency\":10") != string::npos
    );

    assert(
        json.find("\"bandwidth\":100") != string::npos
    );

    assert(
        json.find("\"cost\":3") != string::npos
    );

    assert(
        json.find("\"latency\":20") != string::npos
    );

    assert(
        json.find("\"bandwidth\":200") != string::npos
    );

    cout << "Test 2 passed: link metrics included in JSON\n";

    // Check JSON structure
    assert(
        json.find("\"routers\"") != string::npos
    );

    assert(
        json.find("\"links\"") != string::npos
    );

    cout << "Test 3 passed: JSON contains routers and links\n";

    // Update link
    api.updateLink(
        "R1",
        "R2",
        8,
        15,
        150
    );

    string updatedJSON =
        api.getNetworkJSON();

    assert(
        updatedJSON.find("\"cost\":8") != string::npos
    );

    assert(
        updatedJSON.find("\"latency\":15") != string::npos
    );

    assert(
        updatedJSON.find("\"bandwidth\":150") != string::npos
    );

    cout << "Test 4 passed: JSON reflects updated link metrics\n";

    // Remove link
    api.removeLink(
        "R1",
        "R2"
    );

    string afterDelete =
        api.getNetworkJSON();

    assert(
        afterDelete.find("\"R1\",\"routerB\":\"R2\"")
        == string::npos
    );

    cout << "Test 5 passed: JSON reflects link deletion\n";

    cout << "\nAll Network JSON tests passed!\n";

    return 0;
}