#include <iostream>
#include <cassert>

#include "Graph.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "BalancedRouting.h"
#include "RoutingWeights.h"
#include "RoutingMetric.h"

using namespace std;

int main() {

    Graph graph;

    // --------------------------------------------------
    // Create routers
    // --------------------------------------------------

    graph.addRouter("R1");
    graph.addRouter("R2");
    graph.addRouter("R3");
    graph.addRouter("R4");
    graph.addRouter("R5");

    // --------------------------------------------------
    // Initial topology
    //
    // R1 -- R2 -- R4
    //  \           /
    //   R3 -------/
    //
    // R4 -- R5
    // --------------------------------------------------

    graph.addLink("R1", "R2", 2, 10, 100);
    graph.addLink("R2", "R4", 2, 10, 100);

    graph.addLink("R1", "R3", 5, 5, 100);
    graph.addLink("R3", "R4", 5, 5, 100);

    graph.addLink("R4", "R5", 1, 5, 100);


    // --------------------------------------------------
    // Test 1: BFS
    // --------------------------------------------------

    RoutingResult bfsResult =
        BFS::findShortestPath(
            graph,
            "R1",
            "R5"
        );

    assert(bfsResult.found);
    assert(!bfsResult.path.empty());
    assert(bfsResult.path.front() == "R1");
    assert(bfsResult.path.back() == "R5");

    cout << "Test 1 passed: BFS finds route in initial topology\n";


    // --------------------------------------------------
    // Test 2: Dijkstra
    // --------------------------------------------------

    RoutingResult dijkstraResult =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R5",
            RoutingMetric::COST
        );

    assert(dijkstraResult.found);
    assert(!dijkstraResult.path.empty());
    assert(dijkstraResult.path.front() == "R1");
    assert(dijkstraResult.path.back() == "R5");

    cout << "Test 2 passed: Dijkstra finds cost-optimized route\n";


    // --------------------------------------------------
    // Test 3: Bellman-Ford
    // --------------------------------------------------

    RoutingResult bellmanResult =
        BellmanFord::findShortestPath(
            graph,
            "R1",
            "R5"
        );

    assert(bellmanResult.found);
    assert(!bellmanResult.path.empty());
    assert(bellmanResult.path.front() == "R1");
    assert(bellmanResult.path.back() == "R5");

    cout << "Test 3 passed: Bellman-Ford finds route\n";


    // --------------------------------------------------
    // Test 4: Multi-metric routing
    // --------------------------------------------------

    RoutingResult latencyResult =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R5",
            RoutingMetric::LATENCY
        );

    assert(latencyResult.found);
    assert(!latencyResult.path.empty());
    assert(latencyResult.path.front() == "R1");
    assert(latencyResult.path.back() == "R5");

    cout << "Test 4 passed: multi-metric routing finds latency route\n";


    // --------------------------------------------------
    // Test 5: Weighted routing
    // --------------------------------------------------

    RoutingWeights weights;

    weights.costWeight = 0.7;
    weights.latencyWeight = 0.3;
    weights.bandwidthWeight = 0.0;

    RoutingResult weightedResult =
        BalancedRouting::findBestRoute(
            graph,
            "R1",
            "R5",
            weights
        );

    assert(weightedResult.found);
    assert(!weightedResult.path.empty());
    assert(weightedResult.path.front() == "R1");
    assert(weightedResult.path.back() == "R5");

    cout << "Test 5 passed: weighted routing finds route\n";


    // --------------------------------------------------
    // Test 6: Modify topology
    // --------------------------------------------------

    graph.updateLink(
        "R1",
        "R2",
        20,
        50,
        100
    );

    graph.removeLink(
        "R2",
        "R4"
    );


    // --------------------------------------------------
    // Test 7: Dijkstra adapts
    // --------------------------------------------------

    RoutingResult updatedDijkstra =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R5",
            RoutingMetric::COST
        );

    assert(updatedDijkstra.found);
    assert(!updatedDijkstra.path.empty());
    assert(updatedDijkstra.path.front() == "R1");
    assert(updatedDijkstra.path.back() == "R5");

    cout << "Test 7 passed: Dijkstra adapts to updated topology\n";


    // --------------------------------------------------
    // Test 8: Bellman-Ford adapts
    // --------------------------------------------------

    RoutingResult updatedBellman =
        BellmanFord::findShortestPath(
            graph,
            "R1",
            "R5"
        );

    assert(updatedBellman.found);
    assert(!updatedBellman.path.empty());
    assert(updatedBellman.path.front() == "R1");
    assert(updatedBellman.path.back() == "R5");

    cout << "Test 8 passed: Bellman-Ford adapts to updated topology\n";


    // --------------------------------------------------
    // Test 9: Delete remaining connection
    // --------------------------------------------------

    graph.removeLink(
        "R1",
        "R3"
    );

    RoutingResult unreachableResult =
        Dijkstra::findShortestPath(
            graph,
            "R1",
            "R5",
            RoutingMetric::COST
        );

    assert(!unreachableResult.found);
    assert(unreachableResult.path.empty());

    cout << "Test 9 passed: routing detects unreachable destination\n";


    // --------------------------------------------------
    // Final
    // --------------------------------------------------

    cout << "\nAll routing integration tests passed!\n";

    return 0;
}