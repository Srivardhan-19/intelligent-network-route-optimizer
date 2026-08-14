#ifndef ROUTING_RESULT_H
#define ROUTING_RESULT_H

#include <string>
#include <vector>

using namespace std;

struct RoutingResult {
    bool found;
    vector<string> path;
    int cost;
};

#endif