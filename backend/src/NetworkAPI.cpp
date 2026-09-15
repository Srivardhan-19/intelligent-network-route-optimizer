#include "NetworkAPI.h"

#include "BFS.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

#include <sstream>
#include <unordered_set>

using namespace std;

NetworkAPI::NetworkAPI() {
}

void NetworkAPI::addRouter(
    const string& routerId
) {
    graph.addRouter(routerId);
}

void NetworkAPI::removeRouter(
    const string& routerId
) {
    graph.removeRouter(routerId);
}

void NetworkAPI::addLink(
    const string& routerA,
    const string& routerB,
    int cost,
    int latency,
    int bandwidth
) {
    graph.addLink(
        routerA,
        routerB,
        cost,
        latency,
        bandwidth
    );
}

void NetworkAPI::removeLink(
    const string& routerA,
    const string& routerB
) {
    graph.removeLink(
        routerA,
        routerB
    );
}

void NetworkAPI::updateLink(
    const string& routerA,
    const string& routerB,
    int cost,
    int latency,
    int bandwidth
) {
    graph.updateLink(
        routerA,
        routerB,
        cost,
        latency,
        bandwidth
    );
}

RoutingResult NetworkAPI::findRoute(
    const string& source,
    const string& destination,
    const string& algorithm,
    RoutingMetric metric
) {

    if (algorithm == "BFS") {

        return BFS::findShortestPath(
            graph,
            source,
            destination
        );
    }

    if (algorithm == "Dijkstra") {

        return Dijkstra::findShortestPath(
            graph,
            source,
            destination,
            metric
        );
    }

    if (algorithm == "Bellman-Ford") {

        return BellmanFord::findShortestPath(
            graph,
            source,
            destination
        );
    }

    // Invalid algorithm
    RoutingResult result;

    result.found = false;
    result.cost = -1;

    return result;
}
string NetworkAPI::getNetworkJSON() const {

    ostringstream json;

    json << "{";

    // Routers
    json << "\"routers\":[";

    vector<string> routers =
        graph.getRouters();

    for (size_t i = 0; i < routers.size(); i++) {

        if (i > 0) {
            json << ",";
        }

        json << "\""
             << routers[i]
             << "\"";
    }

    json << "],";

    // Links
    json << "\"links\":[";

    unordered_set<string> processedLinks;

    bool firstLink = true;

    for (const auto& router : routers) {

        vector<LinkInfo> neighbors =
            graph.getNeighbors(router);

        for (const auto& edge : neighbors) {

            string linkKey;

            if (router < edge.router) {
                linkKey =
                    router + "|" + edge.router;
            }
            else {
                linkKey =
                    edge.router + "|" + router;
            }

            // Graph is undirected, so avoid
            // outputting R1-R2 and R2-R1.
            if (processedLinks.find(linkKey) !=
                processedLinks.end()) {
                continue;
            }

            processedLinks.insert(linkKey);

            if (!firstLink) {
                json << ",";
            }

            firstLink = false;

            json << "{";

            json << "\"routerA\":\""
                 << router
                 << "\",";

            json << "\"routerB\":\""
                 << edge.router
                 << "\",";

            json << "\"cost\":"
                 << edge.cost
                 << ",";

            json << "\"latency\":"
                 << edge.latency
                 << ",";

            json << "\"bandwidth\":"
                 << edge.bandwidth;

            json << "}";
        }
    }

    json << "]";

    json << "}";

    return json.str();
}

Graph& NetworkAPI::getGraph() {
    return graph;
}