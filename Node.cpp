#ifndef NODE_CPP_
#define NODE_CPP_

#include "Node.h"
#include <math.h>
using namespace std;


Node::Node() {
    accuracy = 0;
    greedyBest = nullptr;
};

Node::Node(vector<int> data) {
    characteristics = data;
    greedyBest = nullptr;
};

Node::Node(Node* curr) {
    accuracy = curr->accuracy;
    characteristics = curr->characteristics;
    results = curr->results;
    greedyBest = curr->greedyBest;
};

void Node::printChar() {
    if(characteristics.size() >= 1) {
    cout << "{";
    for(int i = 0; i < characteristics.size(); i++) {
        cout << characteristics.at(i);
        if(i < characteristics.size()-1) { cout << ",";}
    }
    cout << "}";
    }
    else {
        cout << "no features";
    }
};

void Node::printResult() {
    if(results.size() >= 1) {
    cout << "{";
    for(int i = 0; i < results.size(); i++) {
        cout << results.at(i);
        if(i < results.size()-1) { cout << ",";}
    }
    cout << "}";
    }
    else {
        cout << "no features";
    }
};

double Node::getAcc() {
    return accuracy;
}

#endif
