#ifndef ROUTER_H
#define ROUTER_H

#include <string>

using namespace std;

class Router {
private:
    string id;

public:
    Router(const string& id);

    string getId() const;
};

#endif