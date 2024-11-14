#ifndef NODE_CPP_
#define NODE_CPP_

#include "Node.h"
#include <math.h>
using namespace std;


Node::Node() {
    accuracy = 0;
};

Node::Node(vector<int> data) {
    accuracy = rand() % 100 + 1;
    characteristics = data;
};

#endif
