#include "Link.h"

using namespace std;

Link::Link(const string& routerA, const string& routerB) {
    this->routerA = routerA;
    this->routerB = routerB;
}

string Link::getRouterA() const {
    return routerA;
}

string Link::getRouterB() const {
    return routerB;
}