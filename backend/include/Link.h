#ifndef LINK_H
#define LINK_H

#include <string>

using namespace std;

class Link {
private:
    string routerA;
    string routerB;

    int cost;
    int latency;
    int bandwidth;

public:
    Link(
        const string& routerA,
        const string& routerB,
        int cost,
        int latency,
        int bandwidth
    );

    string getRouterA() const;
    string getRouterB() const;

    int getCost() const;
    int getLatency() const;
    int getBandwidth() const;
};

#endif