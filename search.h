#ifndef SEARCH_H_
#define SEARCH_H_

#include "Node.cpp"
using namespace std;

class searchTree {
    public:
    Node* ForwardSelect(Node*);
    Node* BackwardElim(Node*);
    Node* Traverse(Node*);

    double NN(vector<Instance>, vector<int>);
    double Euclidean(vector<int>, Instance, Instance);
    double normalize(vector<double>);
    int accuracy = 0;
};

#endif