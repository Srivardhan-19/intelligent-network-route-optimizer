#include <iostream>
#include "Graph.h"

using namespace std;

int main() {

    Graph network;

    network.addRouter("R1");
    network.addRouter("R2");
    network.addRouter("R3");
    network.addRouter("R4");

    network.addLink("R1", "R2");
    network.addLink("R1", "R3");
    network.addLink("R2", "R4");
    network.addLink("R3", "R4");

    cout << "Network topology:\n";

    network.displayGraph();

    return 0;
}