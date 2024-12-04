#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Instance.cpp"
#include "search.cpp"
using namespace std;

vector<Instance> parse(string);
void normalize(vector<Instance>&);

main() {
    string filename;
    cout << "Please enter the data file you want to use." << endl;
    cin >> filename;

    vector<Instance> dataset = parse("small-test-dataset.txt"); //fix this to filename after
    /* cout << "Now printing dataset..." << endl << endl << endl;
    for(int i = 0; i < dataset.size(); i++) {
        dataset.at(i).print();
        cout << endl;
    } */

    normalize(dataset);
    /* cout << "Now printing normalized dataset..." << endl << endl << endl;
    for(int i = 0; i < dataset.size(); i++) {
        dataset.at(i).print();
        cout << endl;
    } */

   //can comment out below for now

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

vector<Instance> parse(string filename) {
    vector<Instance> dataset;
    //open the file
    ifstream f;
    f.open(filename.c_str());

    if(!f.is_open()) {
        cerr<<"Error opening the file[" << filename << "]\n Please enter valid file.";
        exit(1);
    }

    string s;
    while(getline(f,s)) {
        if (s.empty()) continue;
        Instance n;
        double classtype = INT_MAX;
        vector<double> features;
        double temp;
        istringstream row(s); //now parse string of row
        row >> classtype; //get first double in string == class
        //cout << "Class: " << classtype << endl;  // Debug output for class
        n.classtype = classtype;
        n.id = dataset.size(); //add id
        while(row >> temp) { //get rest of doubles == features
            features.push_back(temp);
        }
        /* cout << endl;
        cout << "Saved As:" << endl;
        for(int i = 0; i < features.size(); ++i) { //Debug features vector
            cout << features.at(i) << " ";
        }
        cout << endl;
        cout << "ID: " << n.id << endl; */
        n.features = features; //add features
       /*  for(int i = 0; i < n.features.size(); ++i) { //Debug features vector
            cout << n.features.at(i) << " ";
        }
        cout << endl << endl; */
        dataset.push_back(n); //add to dataset
    }
    return dataset;
}


void normalize(vector<Instance>& dataset) { //method people mentioned in discord (ie x_n = x-min/max-min)
    int instance_sz = dataset.size(); //number of instances
    int feature_sz = dataset.at(0).features.size(); // number of features
    double min =  dataset.at(0).features.front(); //use to find min of each feature
    double max =   dataset.at(0).features.front(); //use to find max of each feature
    //for DEBUGGING
    int min_index = 0;
    int max_index = 0;
    double sum = 0;

    for(int i = 0; i < feature_sz; ++i) {
        min = max = dataset.front().features.at(i);
        min_index = max_index = 0;
        for(int j = 0; j < instance_sz; ++j) {
            if(dataset.at(j).features.at(i) < min) {
                min = dataset.at(j).features.at(i);
                min_index = j;
            }
            if(dataset.at(j).features.at(i) > max) {
                max = dataset.at(j).features.at(i);
                max_index = j;
            }
            //sum += dataset.at(j).features.at(i);
        } //done checking column of features

        for(int j = 0; j < instance_sz; ++j) {
            dataset.at(j).features.at(i) = (dataset.at(j).features.at(i)-min)/(max-min);
        }//loop through again and normalize data;
        //cout << "INDEX:" << i << "\t MIN[" << min_index << "]:" << min << "\t MAX[" << max_index << "]:" <<  max << endl << endl; //Debug min/max values
        //sum = 0;
    } //done checking min/max of all features
}

