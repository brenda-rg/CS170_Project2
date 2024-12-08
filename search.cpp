#ifndef SEARCH_CPP_
#define SEARCH_CPP_

#include "Instance.h"
#include "search.h"
#include <math.h>
#include <vector>
#include <chrono>
using namespace std;

Node* searchTree::ForwardSelect(Node* curr, vector<Instance> dataset) {
    static bool First = true;
    static auto Time_begin = chrono::high_resolution_clock::now();
    
    if (First) {
        Time_begin = chrono::high_resolution_clock::now();
        First = false;
    }

     Node* best = new Node(curr);
    Node* childBest = Traverse(curr, dataset); //get best child of current node
    if(childBest == nullptr) return curr; //if no children then return overall best
    cout << "Feature set ";
    childBest->printResult();
    cout << " was best, accuracy is " << childBest->getAcc() << "%" << endl << endl;
    if(best->greedyBest->accuracy < childBest->accuracy) {
       best->greedyBest = childBest;
    }
    curr->greedyBest = best->greedyBest;
    childBest->greedyBest = best->greedyBest;
    auto Time_ends = chrono::high_resolution_clock::now();
    search_time = chrono::duration_cast<chrono::milliseconds>(Time_ends - Time_begin);
    return ForwardSelect(childBest, dataset); 
    
    // Node* childBest = Traverse(curr, dataset); //get best child of current node
    // if(childBest == nullptr || childBest->accuracy < curr->accuracy) {
    //     if(childBest->accuracy < curr->accuracy) cout <<  "(Warning, Accuracy has decreased!)" << endl;
    //     return curr; //if no children then return overall best
    // }
    // cout << "Feature set ";
    // childBest->printResult();
    // cout << " was best, accuracy is " << childBest->getAcc() << "%" << endl << endl;
    // childBest->greedyBest = childBest;
    // auto Time_ends = chrono::high_resolution_clock::now();
    // search_time = chrono::duration_cast<chrono::milliseconds>(Time_ends - Time_begin);
    // //cout << "Total search time: " << search_time.count() << " milliseconds" << endl;
    // return ForwardSelect(childBest, dataset);
}

Node* searchTree::BackwardElim(Node* curr, vector<Instance> dataset) {
    static bool First = true;
    static auto Time_begins = chrono::high_resolution_clock::now();
    
    if (First) {
        Time_begins = chrono::high_resolution_clock::now();
        First = false;
    }
    
    vector<Node*> children;
    if(curr->results.size() == 0) {
        return curr;
    }
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
    if(children.size() == 0) bestChild = nullptr;
    for (Node* child : children) {
        NN(dataset, child->results);
        child->accuracy = accuracy;
        cout << "\tUsing Features";
        child->printResult();
        cout << " accuracy is " << child->accuracy << "%" << endl;

        if (bestChild->accuracy < child->accuracy) {
            bestChild = child;
        }
    }

    
    Node* best = new Node(curr);
    if(bestChild == nullptr) return curr; //if no children then return overall best

  
    cout << "\n\nFeature set ";
    bestChild->printResult();
    cout << " was best, accuracy is " << bestChild->getAcc() << "%" << endl << endl;
    if(best->greedyBest->accuracy < bestChild->accuracy) {
       best->greedyBest = bestChild;
    }
    curr->greedyBest = best->greedyBest;
    bestChild->greedyBest = best->greedyBest;
    auto Time_ends = chrono::high_resolution_clock::now();
    search_time = chrono::duration_cast<chrono::milliseconds>(Time_ends - Time_begins);
    return BackwardElim(bestChild, dataset); 

    //  if(bestChild == nullptr || bestChild->accuracy < curr->accuracy) {
    //     cout << endl << "(Warning, Accuracy has decreased!)" << endl;
    //     return curr; //if no children then return overall best
    //  }

    // cout << "Feature set ";
    // bestChild -> printResult();
    // cout << " was the best accuracy is " << bestChild->getAcc() << "%" << endl;
    // bestChild-> greedyBest = bestChild;

    /* auto Time_ends = chrono::high_resolution_clock::now();
    search_time = chrono::duration_cast<chrono::milliseconds>(Time_ends - Time_begins); */
    // //cout << "Total search time: " << search_time.count() << " milliseconds" << endl;
    // return BackwardElim(bestChild, dataset); 
    }

Node* searchTree::Traverse(Node* curr, vector<Instance> dataset) {
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
        NN(dataset, children.at(k)->results);
        children.at(k)->accuracy = accuracy;
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

void searchTree::NN(vector<Instance> dataset, vector<int> featSub) { //featSub is the features we are currently using; can be v= {1,3,4} for example
    auto start_time = chrono::high_resolution_clock::now(); 
    
    int sz = dataset.size(); //number of total instances
    int nn = 0; //used to keep track of the nearest neighbor
    double dist;
    double newDist;
    int correct =0;

    for(int i = 0; i < sz; ++i) { //test instance
    auto time_starts = chrono::high_resolution_clock::now(); 
        dist = INT_MAX;
        for(int j = 0; j < sz; ++j) { //train instance
            if(i == j) continue; //if test and train the same do nothing
            newDist = Euclidean(featSub, dataset.at(j), dataset.at(i)); //get the distance between train and test
            if(newDist < dist) { //check if the instance is closer to 
                nn = j; //change nn
                dist = newDist; //change closest dist value
                
            }

        }
        if(dataset.at(nn).classtype == dataset.at(i).classtype) {
            correct +=1;
            
        } 
    } 
    accuracy = (correct/(sz*1.0))*100;    
     auto time_stops1 = chrono::high_resolution_clock::now(); // Stop timer
     classifier_time = chrono::duration_cast<chrono::milliseconds>(time_stops1 - start_time);
}


double searchTree::Euclidean(vector<int> featSub, Instance train, Instance test) { 
    // 2 instances train and test 
    //vector of indexes for feature we want to use 
    vector<double> train_vec = train.getVector();
    vector<double> test_vec = test.getVector();
    double result = 0;
    for (int i = 0; i < featSub.size(); i++) {
        int featureIn = featSub[i] - 1;  // index 0 of feature we want to use 
        double diff = train_vec[featureIn] - test_vec[featureIn];
        result += pow(diff,2);   
    }
    return sqrt(result);
}
#endif