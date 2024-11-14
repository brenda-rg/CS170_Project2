#ifndef SEARCH_H_
#define SEARCH_H_

#include "Node.cpp"
using namespace std;

class searchTree {
    public:
    Node* ForwardSelect(Node* bestNode);
    Node* BackwardElim();
    Node* Traverse(vector<int>);
};

#endif