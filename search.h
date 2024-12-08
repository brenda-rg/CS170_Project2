#ifndef SEARCH_H_
#define SEARCH_H_

#include "Node.cpp"
using namespace std;

class searchTree {
    public:
    Node* ForwardSelect(Node*, vector<Instance>);
    Node* BackwardElim(Node*, vector<Instance>);
    Node* Traverse(Node*, vector<Instance>);
    chrono::milliseconds classifier_time;
    chrono::milliseconds search_time;

    void NN(vector<Instance>, vector<int>);
    double Euclidean(vector<int> featSub, Instance train, Instance test);
    double normalize(vector<double>);
    double accuracy = 0;
};

#endif