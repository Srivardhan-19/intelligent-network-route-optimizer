#ifndef LINK_H
#define LINK_H

#include <string>

using namespace std;

class Link {
private:
    string routerA;
    string routerB;

public:
    Link(const string& routerA, const string& routerB);

    string getRouterA() const;
    string getRouterB() const;
};

#endif