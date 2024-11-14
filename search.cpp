#ifndef SEARCH_CPP_
#define SEARCH_CPP_

#include "search.h"
#include <math.h>
#include <vector>
using namespace std;

Node* searchTree::ForwardSelect(Node* bestNode) {
    Node* best = bestNode;
    best->greedyBest = bestNode;
    Node* childBest = Traverse(bestNode);
    if(childBest == nullptr) return best->greedyBest;
    //check if we have the best node so far
    if(bestNode->accuracy < childBest->accuracy) {
       best = childBest;
       bestNode->greedyBest = childBest;
    }
    //expand best until no more in vector but keep the best in mind
    return ForwardSelect(childBest);
}

Node* searchTree::Traverse(Node* curr) {
    Node* newNode = nullptr;
    vector<Node*> children;
    if(curr->characteristics.size() == 0) return nullptr;

    for (int i = 0; i < curr->characteristics.size(); i++) {
        vector<int> copyTrav = curr->characteristics;
        copyTrav.erase(copyTrav.begin() + i);
        newNode = new Node(copyTrav);
        newNode->results.push_back(i);
        newNode->greedyBest = curr->greedyBest;
        newNode->results = curr->results;
        children.push_back(newNode);
    }

    Node* best = children.front();

    for (int k = 0; k < children.size(); k++) {
        cout << "Using feature(s) {" << children.at(k)->print() << 
        if (best->accuracy < children.at(k)->accuracy) {
            best = children.at(k);
        }
    }

    return best;
}

#endif