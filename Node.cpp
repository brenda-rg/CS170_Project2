#ifndef NODE_CPP_
#define NODE_CPP_

#include "Node.h"
#include <math.h>
using namespace std;


Node::Node() {
    accuracy = 0;
};

Node::Node(vector<int> data) {
    accuracy = (rand() % 1000 + 1)/10.0;
    characteristics = data;
    greedyBest = nullptr;
    printChar();
    cout << endl << "accuracy: " << accuracy << endl;
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
};

double Node::getAcc() {
    return accuracy;
}
#endif
