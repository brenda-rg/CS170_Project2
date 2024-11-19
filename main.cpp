#include <iostream>
#include <vector>
#include "search.cpp"
using namespace std;

main() {
    int opt;
    vector<int> init;
    cout << "Please enter total number of features: \t";
    cin >> opt;

    for(int i = 0; i < opt; i++) {
        init.push_back(i+1);
    }

    cout << "{" ;

    for(int i = 0; i < init.size(); i++) {
        cout << init.at(i) << "," ;
    }

    cout << "}" << endl;;

  /*   cout << "Type the number of the algorithm you want to run." << endl
        << "1. Forward Selection" << endl
        << "2. Backward Elimination" << endl
        << "3. Bertie’s Special Algorithm.\t" << endl;
    cin >> opt; */
    Node* start = new Node(init);
    start->greedyBest = start;
    searchTree* search;
    cout << "Using no features and \"random\" evaluation, I get an accuracy of " << start->accuracy << "%" << endl;
    cout << "Beginning search" << endl << endl;
    Node* best = search->ForwardSelect(start);
    cout << "The best feature subset is ";
    best->greedyBest->printResult();
    cout << ", which has an accuracy of " <<  best->greedyBest->accuracy << endl;
    cout << "Finished Search!" << endl;

    //cout <<  best->accuracy;

    return 0;
}