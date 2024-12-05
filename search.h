#ifndef SEARCH_H_
#define SEARCH_H_

#include "Node.cpp"
using namespace std;

class searchTree {
    public:
    Node* ForwardSelect(Node*);
    Node* BackwardElim(Node*);
    Node* Traverse(Node*);

    void NN(vector<Instance>, vector<int>);
    double Euclidean(vector<int> featSub, Instance train, Instance test);
    double normalize(vector<double>);
    double accuracy = 0;
};

#endif