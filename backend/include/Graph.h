#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
private:
    unordered_map<string, vector<string>> adjacencyList;

public:
    void addRouter(const string& routerId);

    void addLink(
        const string& routerA,
        const string& routerB
    );

    void removeLink(
        const string& routerA,
        const string& routerB
    );

    void displayGraph() const;
};

#endif