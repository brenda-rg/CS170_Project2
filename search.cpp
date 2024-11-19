#ifndef SEARCH_CPP_
#define SEARCH_CPP_

#include "search.h"
#include <math.h>
#include <vector>
using namespace std;

Node* searchTree::ForwardSelect(Node* curr) {
    Node* best = new Node(curr);
    Node* childBest = Traverse(curr); //get best child of current node
    if(childBest == nullptr) return best->greedyBest; //if no children then return overall best
    if(best->greedyBest->accuracy < childBest->accuracy) {
       best->greedyBest = childBest;
    }
    curr->greedyBest = best->greedyBest;
    childBest->greedyBest = best->greedyBest;
    return ForwardSelect(childBest);
}

Node* searchTree::Traverse(Node* curr) {
    Node* newNode = nullptr;
    vector<Node*> children;
    if(curr->characteristics.size() == 0) return nullptr;

    //push to reseults and 
    for (int i = 0; i < curr->characteristics.size(); i++) {
        vector<int> copyTrav = curr->characteristics;
        copyTrav.erase(copyTrav.begin() + i);
        newNode = new Node(copyTrav);
        newNode->results = curr->results;
        newNode->results.push_back(curr->characteristics.at(i));
        newNode->greedyBest = curr->greedyBest; //haven't expanded so the new children have greedyBest of the parent
        children.push_back(newNode);
    }

    Node* best = children.front();

    //compare all of the children until the best accuracy is found
    for (int k = 0; k < children.size(); k++) {
        cout << "Using feature(s) ";
        children.at(k)->printResult();
        cout << " accuracy is " << children.at(k)->getAcc() << "%" << endl;

        if (best->accuracy < children.at(k)->accuracy) {
            best = children.at(k);
        }
    }
    if(best->accuracy >= best->greedyBest->accuracy) {
        cout << "feature set ";
        best->printResult();
        cout << " was best, accuracy is " << best->getAcc() << "%" << endl;
    }
    else {
        cout << endl << endl << "(Warning, Accuracy has decreased!)" << endl;
    }
    //return the best child
    return best;
}

#endif