#ifndef SEARCH_CPP_
#define SEARCH_CPP_

#include "search.h"
#include <math.h>
#include <vector>
using namespace std;

Node* searchTree::ForwardSelect(Node* bestNode) {

}

Node* searchTree::Traverse(vector<int> travHold) {
    Node* newNode = nullptr;
    vector<Node*> children;
    
    for (int i = 0; i < travHold.size(); i++) {
        vector<int> copyTrav = travHold;
        copyTrav.erase(copyTrav.begin() + i);
        newNode = new Node(copyTrav);
        children.push_back(newNode);
    }

    Node* best = children.front();

    for (int k = 0; k < children.size(); k++) {
        if (best->accuracy < children.at(k)->accuracy) {
            best = children.at(k);
        }
    }

    return best;
}

#endif