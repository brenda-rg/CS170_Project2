#ifndef SEARCH_CPP_
#define SEARCH_CPP_

#include "Instance.h"
#include "search.h"
#include <math.h>
#include <vector>
#include <chrono>
using namespace std;

Node* searchTree::ForwardSelect(Node* curr) {
    static bool First = true;
    static auto Time_begin = chrono::high_resolution_clock::now();
    
    if (First) {
        Time_begin = chrono::high_resolution_clock::now();
        First = false;
    }
    
    Node* childBest = Traverse(curr); //get best child of current node
    if(childBest == nullptr || childBest->accuracy < curr->accuracy) {
        if(childBest->accuracy < curr->accuracy) cout <<  "(Warning, Accuracy has decreased!)" << endl;
        return curr; //if no children then return overall best
    }
    cout << "Feature set ";
    childBest->printResult();
    cout << " was best, accuracy is " << childBest->getAcc() << "%" << endl << endl;
    childBest->greedyBest = childBest;
    auto Time_ends = chrono::high_resolution_clock::now();
    auto Period = chrono::duration_cast<chrono::milliseconds>(Time_ends - Time_begin);
    cout << "Total search time: " << Period.count() << " milliseconds" << endl;
    return ForwardSelect(childBest);
}

Node* searchTree::BackwardElim(Node* curr) {
    static bool First = true;
    static auto Time_begins = chrono::high_resolution_clock::now();
    
    if (First) {
        Time_begins = chrono::high_resolution_clock::now();
        First = false;
    }
    
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

    auto Time_ends = chrono::high_resolution_clock::now();
    auto Period = chrono::duration_cast<chrono::milliseconds>(Time_ends - Time_begins);
    cout << "Total search time: " << Period.count() << " milliseconds" << endl;
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

void searchTree::NN(vector<Instance> dataset, vector<int> featSub) { //featSub is the features we are currently using; can be v= {1,3,4} for example
    auto time_starts = chrono::high_resolution_clock::now(); 
    
    int sz = dataset.size(); //number of total instances
    int nn = 0; //used to keep track of the nearest neighbor
    double dist;
    double newDist;
    int correct =0;

    for(int i = 0; i < sz; ++i) { //test instance
        dist = INT_MAX;
        for(int j = 0; j < sz; ++j) { //train instance
            if(i == j) continue; //if test and train the same do nothing
            newDist = Euclidean(featSub, dataset.at(j), dataset.at(i)); //get the distance between train and test
            if(newDist < dist) { //check if the instance is closer to 
                nn = j; //change nn
                dist = newDist; //change closest dist value
                //cout << "changed NN" << endl;
            }

        }//done going through instance -> found nn -->now classify
        //test = i;
        cout << "Test ID[" << dataset.at(i).id << "]" 
        << "  ||  Nearest Neighbot ID[" << dataset.at(nn).id << "]" 
        << "  ||  Predicted Class[" << dataset.at(nn).classtype << "]" 
        << "  ||  Actual Class[" << dataset.at(i).classtype << "]";
        //test.classtype = nn.classtype; //set class to the class of the nearest neighbor (prediction)
        if(dataset.at(nn).classtype == dataset.at(i).classtype) {
            correct +=1;
            cout << "  ||  Correct";
        } //add to correct counter if prediciton == actual
        else cout << "  ||  Incorrect";
        cout << endl;
    } //loop until done going through all instances
    //calculate accuracy
    cout << "Total Correct[" << correct << "]" << "out of [" << sz << "] Total Instances" << endl;
    accuracy = (correct/(sz*1.0))*100; //accuracy = #instances predicted correct/#total instances
    cout << "The NN classifier using all [" << featSub.size() << "] features has a " << accuracy << "%" << " accuracy" << endl;
    
    auto time_stops = chrono::high_resolution_clock::now(); // Stop timer
    auto Period = chrono::duration_cast<chrono::milliseconds>(time_stops - time_starts);
    
    cout << "Time for code to run: " << Period.count() << " millisec" << endl;
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