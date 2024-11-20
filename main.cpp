#include <iostream>
#include <vector>
#include "search.cpp"
using namespace std;

main() {
    srand(time(0));
    int opt;
    vector<int> init;
    cout << "Please enter total number of features: \t";
    cin >> opt;

    for(int i = 0; i < opt; i++) {
        init.push_back(i+1);
    }
    cout << endl << endl;

    cout << "Type the number of the algorithm you want to run." << endl << endl
        << "\t1. Forward Selection" << endl
        << "\t2. Backward Elimination" << endl << endl << "\t\t\t\t\t";
    cin >> opt;
    cout << endl;
    Node* start = new Node(init);
    start->greedyBest = start;
    searchTree* search;
    cout << "Using ";
    if(opt != 1) {
        cout << "features ";
        start->results = init;
    }
    start->printResult();
    cout << " and \"random\" evaluation, I get an accuracy of " << start->accuracy << "%" << endl << endl;
    cout << "Beginning search" << endl << endl;
    Node* best = nullptr;
    if(opt == 1) {
        best = search->ForwardSelect(start);
    }
    else {
        best = search->BackwardElim(start);
    }
    
    cout << "Finished Search!! "
    << "The best feature subset is ";
    best->greedyBest->printResult();
    cout << ", which has an accuracy of " <<  best->greedyBest->accuracy << "%" << endl;

    return 0;
}