#include "Router.h"

using namespace std;

Router::Router(const string& id) {
    this->id = id;
}

string Router::getId() const {
    return id;
}