#ifndef SEARCH_CPP_
#define SEARCH_CPP_

#include "Instance.h"
#include "search.h"
#include <math.h>
#include <vector>
using namespace std;

Node* searchTree::ForwardSelect(Node* curr) {
    Node* childBest = Traverse(curr); //get best child of current node
    if(childBest == nullptr || childBest->accuracy < curr->accuracy) {
        if(childBest->accuracy < curr->accuracy) cout <<  "(Warning, Accuracy has decreased!)" << endl;
        return curr; //if no children then return overall best
    }
    cout << "Feature set ";
    childBest->printResult();
    cout << " was best, accuracy is " << childBest->getAcc() << "%" << endl << endl;
    childBest->greedyBest = childBest;
    return ForwardSelect(childBest);
}

Node* searchTree::BackwardElim(Node* curr) {
    vector<Node*> children;

    // Generate all children by removing one feature at a time
    for (int i = 0; i < curr->results.size(); i++) {
        vector<int> copyTrav = curr->results;
        copyTrav.erase(copyTrav.begin() + i);
        Node* newNode = new Node(copyTrav);
        newNode->results = copyTrav;
        newNode->greedyBest = curr->greedyBest;
        children.push_back(newNode);
    }
    Node* bestChild = children.front();
    for (Node* child : children) {
        cout << "\tUsing Features";
        child->printResult();
        cout << " accuracy is " << child->accuracy << "%" << endl;

        if (bestChild->accuracy < child->accuracy) {
            bestChild = child;
        }
    }
     if(bestChild == nullptr || curr->accuracy > bestChild->accuracy) {
        cout << endl << "(Warning, Accuracy has decreased!)" << endl;
        return curr; //if no children then return overall best
     }

    cout << "Feature set ";
    bestChild -> printResult();
    cout << " was the best accuracy is " << bestChild->getAcc() << "%" << endl;
    bestChild-> greedyBest = bestChild;

    return BackwardElim(bestChild); 
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

double searchTree::NN(vector<Instance> dataset, vector<int> featSub) { //featSub is the features we are currently using; can be v= {1,3,4} for example
    int sz = dataset.size(); //number of total instances
    Instance nn; //used to keep track of the nearest neighbor
    Instance test;
    double dist = INT_MAX;
    double newDist;
    double acc = 0;
    int correct =0;

    for(int i = 0; i < sz; ++i) { //test instance
        for(int j = 0; j < sz; ++i) { //train instance
            if(i == j) continue; //if test and train the same do nothing
            newDist = Euclidean(featSub, dataset.at(j), dataset.at(i)); //get the distance between train and test
            if(dist < newDist) { //check if the instance is closer to 
                nn = dataset.at(j); //change nn
                dist = newDist; //change closest dist value
            }
        }//done going through instance -> found nn -->now classify
        test = i;
        test.classtype = nn.classtype; //set class to the class of the nearest neighbor (prediction)
        if(test.classtype == dataset.at(i).classtype) {
            correct +=1;
        } //add to correct counter if prediciton == actual
    } //loop until done going through all instances
    //calculate accuracy
    acc = correct/sz; //accuracy = #instances predicted correct/#total instances
    return acc;
}


double searchTree::Euclidean(Instance test, Instance train, vector<int> features) { 
    double dist = 0;
    /* for (int i =0; i < features.size(); i++) {
        int index = features.at(i);

    }

    double dist = pow(x,2);
    dist = sqrt(dist); */
    return dist;
}

#endif