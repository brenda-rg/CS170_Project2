#ifndef SEARCH_CPP_
#define SEARCH_CPP_

#include "search.h"
#include <math.h>
#include <vector>
using namespace std;

Node* searchTree::ForwardSelect(Node* bestNode) {
    Node* best = bestNode;
    best->greedyBest = bestNode;
    Node* childBest = Traverse(bestNode->characteristics);
    //check if we have the best node so far
    if(bestNode->accuracy < childBest->accuracy) {
       best = childBest;
       bestNode->greedyBest = childBest;
    }
    //expand best until no more in vector but keep the best in mind
    return ForwardSelect(childBest);
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