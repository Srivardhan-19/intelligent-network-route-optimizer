#include "Link.h"

using namespace std;

Link::Link(
    const string& routerA,
    const string& routerB,
    int cost,
    int latency,
    int bandwidth
) {
    this->routerA = routerA;
    this->routerB = routerB;

    this->cost = cost;
    this->latency = latency;
    this->bandwidth = bandwidth;
}

string Link::getRouterA() const {
    return routerA;
}

string Link::getRouterB() const {
    return routerB;
}

int Link::getCost() const {
    return cost;
}

int Link::getLatency() const {
    return latency;
}

int Link::getBandwidth() const {
    return bandwidth;
}