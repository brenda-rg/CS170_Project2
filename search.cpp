#ifndef SEARCH_CPP_
#define SEARCH_CPP_

#include "search.h"
#include <math.h>
#include <vector>
using namespace std;

//fix so that it returns right away instead of keep on searching;
Node* searchTree::ForwardSelect(Node* curr) {
    Node* best = new Node(curr);
    Node* childBest = Traverse(curr); //get best child of current node
    cout << "Feature set ";
    childBest->printResult();
    cout << " was best, accuracy is " << best->getAcc() << "%" << endl << endl;
    if(childBest == nullptr || childBest->accuracy < curr->accuracy) {
        if(childBest->accuracy < curr->accuracy) cout <<  "(Warning, Accuracy has decreased!)" << endl;
        return best->greedyBest; //if no children then return overall best
    }
    childBest->greedyBest = childBest;
    return ForwardSelect(childBest);
}

Node* searchTree::BackwardElim(Node* curr) {
    //write function
    cout << "---------------STUB---------------\n\n";
    return curr;
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
        cout << "\tUsing feature(s) ";
        children.at(k)->printResult();
        cout << " accuracy is " << children.at(k)->getAcc() << "%" << endl;

        if (best->accuracy < children.at(k)->accuracy) {
            best = children.at(k);
        }
    }
    cout << endl;
    //return the best child
    return best;
}

#endif