#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

struct Node {
    Node();
    Node(vector<int>);
    double accuracy;
    Node* head = nullptr;

    vector<int> characteristics;
    vector<int> results;
    Node* greedyBest = nullptr;

};

#endif 