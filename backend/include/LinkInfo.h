#ifndef LINK_INFO_H
#define LINK_INFO_H

#include <string>

using namespace std;

struct LinkInfo {
    string router;
    int cost;
    int latency;
    int bandwidth;
};

#endif