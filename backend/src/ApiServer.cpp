#include "NetworkAPI.h"

#include <iostream>
#include <string>

using namespace std;

/*
 * Phase 6 C++ API bridge.
 *
 * Communication format:
 *
 * Request:
 * {"action":"getNetwork"}
 *
 * Response:
 * {"routers":[],"links":[]}
 *
 * One JSON request is processed per input line.
 *
 * This bridge keeps NetworkAPI unchanged.
 */

string getValue(
    const string& json,
    const string& key
) {
    string searchKey = "\"" + key + "\":\"";

    size_t start = json.find(searchKey);

    if (start == string::npos) {
        return "";
    }

    start += searchKey.length();

    size_t end = json.find("\"", start);

    if (end == string::npos) {
        return "";
    }

    return json.substr(start, end - start);
}

int getIntValue(
    const string& json,
    const string& key
) {
    string searchKey = "\"" + key + "\":";

    size_t start = json.find(searchKey);

    if (start == string::npos) {
        return 0;
    }

    start += searchKey.length();

    size_t end = json.find_first_of(",}", start);

    if (end == string::npos) {
        return 0;
    }

    return stoi(
        json.substr(start, end - start)
    );
}

string escapeJson(const string& value) {

    string result;

    for (char c : value) {

        if (c == '"') {
            result += "\\\"";
        }
        else if (c == '\\') {
            result += "\\\\";
        }
        else {
            result += c;
        }
    }

    return result;
}

int main() {

    NetworkAPI api;

    string request;

    while (getline(cin, request)) {

        string action =
            getValue(request, "action");

        if (action == "addRouter") {

            string routerId =
                getValue(request, "routerId");

            api.addRouter(routerId);

            cout
                << "{\"status\":\"success\"}"
                << endl;
        }

        else if (action == "removeRouter") {

            string routerId =
                getValue(request, "routerId");

            api.removeRouter(routerId);

            cout
                << "{\"status\":\"success\"}"
                << endl;
        }

        else if (action == "addLink") {

            string routerA =
                getValue(request, "routerA");

            string routerB =
                getValue(request, "routerB");

            int cost =
                getIntValue(request, "cost");

            int latency =
                getIntValue(request, "latency");

            int bandwidth =
                getIntValue(request, "bandwidth");

            api.addLink(
                routerA,
                routerB,
                cost,
                latency,
                bandwidth
            );

            cout
                << "{\"status\":\"success\"}"
                << endl;
        }

        else if (action == "updateLink") {

            string routerA =
                getValue(request, "routerA");

            string routerB =
                getValue(request, "routerB");

            int cost =
                getIntValue(request, "cost");

            int latency =
                getIntValue(request, "latency");

            int bandwidth =
                getIntValue(request, "bandwidth");

            api.updateLink(
                routerA,
                routerB,
                cost,
                latency,
                bandwidth
            );

            cout
                << "{\"status\":\"success\"}"
                << endl;
        }

        else if (action == "removeLink") {

            string routerA =
                getValue(request, "routerA");

            string routerB =
                getValue(request, "routerB");

            api.removeLink(
                routerA,
                routerB
            );

            cout
                << "{\"status\":\"success\"}"
                << endl;
        }

        else if (action == "getNetwork") {

            cout
                << api.getNetworkJSON()
                << endl;
        }

        else if (action == "findRoute") {

            string source =
                getValue(request, "source");

            string destination =
                getValue(request, "destination");

            string algorithm =
                getValue(request, "algorithm");

            string metricString =
                getValue(request, "metric");

            RoutingMetric metric =
                RoutingMetric::COST;

            if (metricString == "LATENCY") {

                metric =
                    RoutingMetric::LATENCY;
            }
            else if (metricString == "BANDWIDTH") {

                metric =
                    RoutingMetric::BANDWIDTH;
            }

            RoutingResult result =
                api.findRoute(
                    source,
                    destination,
                    algorithm,
                    metric
                );

            cout << "{";

            cout
                << "\"found\":"
                << (result.found ? "true" : "false")
                << ",";

            cout
                << "\"cost\":"
                << result.cost
                << ",";

            cout << "\"path\":[";

            for (size_t i = 0;
                 i < result.path.size();
                 i++) {

                if (i > 0) {
                    cout << ",";
                }

                cout
                    << "\""
                    << escapeJson(result.path[i])
                    << "\"";
            }

            cout << "]}";
            cout << endl;
        }

        else {

            cout
                << "{\"error\":\"Unknown action\"}"
                << endl;
        }
    }

    return 0;
}