#include <iostream>
#include <cassert>

#include "Graph.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

using namespace std;

int main() {

    Graph network;

    /*
              10
        R1 -------- R2
         |           |
        2|           |3
         |           |
        R3 -------- R4
              2
    */

    network.addLink("R1", "R2", 10);
    network.addLink("R1", "R3", 2);
    network.addLink("R3", "R4", 2);
    network.addLink("R2", "R4", 3);


    // ------------------------------------------------
    // BFS
    // ------------------------------------------------

    RoutingResult bfsResult =
        BFS::findShortestPath(
            network,
            "R1",
            "R4"
        );

    assert(bfsResult.found);

    // BFS should find a 2-hop route.
    assert(bfsResult.path.size() == 3);

    cout << "BFS route: ";

    for (const string& router : bfsResult.path) {
        cout << router << " ";
    }

    cout << "\n";
    cout << "BFS hops: "
         << bfsResult.path.size() - 1
         << "\n\n";


    // ------------------------------------------------
    // Dijkstra
    // ------------------------------------------------

    RoutingResult dijkstraResult =
        Dijkstra::findShortestPath(
            network,
            "R1",
            "R4"
        );

    assert(dijkstraResult.found);
    assert(dijkstraResult.cost == 4);

    assert(dijkstraResult.path.size() == 3);
    assert(dijkstraResult.path[0] == "R1");
    assert(dijkstraResult.path[1] == "R3");
    assert(dijkstraResult.path[2] == "R4");

    cout << "Dijkstra route: ";

    for (const string& router : dijkstraResult.path) {
        cout << router << " ";
    }

    cout << "\n";
    cout << "Dijkstra cost: "
         << dijkstraResult.cost
         << "\n\n";


    // ------------------------------------------------
    // Bellman-Ford
    // ------------------------------------------------

    RoutingResult bellmanResult =
        BellmanFord::findShortestPath(
            network,
            "R1",
            "R4"
        );

    assert(bellmanResult.found);
    assert(bellmanResult.cost == 4);

    assert(bellmanResult.path.size() == 3);
    assert(bellmanResult.path[0] == "R1");
    assert(bellmanResult.path[1] == "R3");
    assert(bellmanResult.path[2] == "R4");

    cout << "Bellman-Ford route: ";

    for (const string& router : bellmanResult.path) {
        cout << router << " ";
    }

    cout << "\n";
    cout << "Bellman-Ford cost: "
         << bellmanResult.cost
         << "\n\n";



    cout << "========== ROUTING COMPARISON ==========\n";

    cout << "BFS:\n";
    cout << "  Objective: minimum hops\n";
    cout << "  Hops: "
        << bfsResult.path.size() - 1
        << "\n";

    cout << "\nDijkstra:\n";
    cout << "  Objective: minimum cost\n";
    cout << "  Cost: "
        << dijkstraResult.cost
        << "\n";

    cout << "\nBellman-Ford:\n";
    cout << "  Objective: minimum cost\n";
    cout << "  Cost: "
        << bellmanResult.cost
        << "\n";

    cout << "\nConclusion:\n";
    cout << "  BFS optimizes hop count.\n";
    cout << "  Dijkstra optimizes network cost.\n";
    cout << "  Bellman-Ford verifies the minimum-cost route.\n";

    cout << "=========================================\n\n";

    // ------------------------------------------------
    // Final comparison
    // ------------------------------------------------

    assert(dijkstraResult.cost ==
           bellmanResult.cost);

    cout << "Dijkstra and Bellman-Ford agree on "
         << "the lowest-cost route.\n";

    cout << "Algorithm comparison passed!\n";

    return 0;
}