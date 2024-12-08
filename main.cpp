#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include "Instance.cpp"
#include "search.cpp"
using namespace std;

vector<Instance> parse(string);
void normalize(vector<Instance>&);
chrono::milliseconds parse_time;
chrono::milliseconds norm_time;

main() {
    int opt;
    string filename;
    vector<Instance> dataset;
    cout << "Please enter the data file you want to use:" << endl;
    cin >> filename;
   dataset = parse(filename);
    

    normalize(dataset);

    int featsz = dataset.front().features.size();

    searchTree search;
    vector<int> featIndex;

    for(int i = 0; i < featsz; ++i) {
        featIndex.push_back(i+1);
    }


    search.NN(dataset,featIndex);
    
    vector<int> init;

    cout << "Type the number of the algorithm you want to run." << endl << endl
        << "\t1. Forward Selection" << endl
        << "\t2. Backward Elimination" << endl << endl << "\t\t\t\t\t";
    cin >> opt;
    cout << endl;
    Node* start = new Node();
    start->greedyBest = start;

    //searchTree* search;
    cout << "Using ";
   if(opt != 1) {
        cout << "features ";
        start->results = featIndex;
        start->accuracy = search.accuracy;
    }
    else start->characteristics = featIndex;
    start->printResult();
    cout << ": " << endl;
    cout << " and leave one out evaluation, I get an accuracy of " << start->accuracy << "%" << endl << endl;
    cout << "Beginning search" << endl << endl;
    Node* best = nullptr;
    if(opt == 1) {
        best = search.ForwardSelect(start,dataset);
    }
    else {
        best = search.BackwardElim(start,dataset);
    }

    cout << "Finished Search!! "
    << "The best feature subset is ";
    best->greedyBest->printResult();
    cout << ", which has an accuracy of " <<  best->greedyBest->accuracy << "%" << endl;
    cout << "Parsing runtime: " << parse_time.count() << " millisec" << endl;
    cout << "Normalizing runtime: " << norm_time.count() << " millisec" << endl;
    cout << "Classifier runtime: " << search.classifier_time.count() << " millisec" << endl;
    cout << "Search runtime: " << search.search_time.count() << " millisec" << endl;
    return 0;
}

vector<Instance> parse(string filename) {
    auto start_time = chrono::high_resolution_clock::now(); 
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
        n.id = dataset.size() + 1; //add id
        while(row >> temp) { //get rest of doubles == features
            features.push_back(temp);
        }
        n.features = features; //add features
        dataset.push_back(n); //add to dataset
    }
    auto time_stops1 = chrono::high_resolution_clock::now(); // Stop timer
    parse_time = chrono::duration_cast<chrono::milliseconds>(time_stops1 - start_time);
    return dataset;
}


void normalize(vector<Instance>& dataset) { //method people mentioned in discord (ie x_n = x-min/max-min)
    auto start_time = chrono::high_resolution_clock::now(); 

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
            
        } //done checking column of features

        for(int j = 0; j < instance_sz; ++j) {
            dataset.at(j).features.at(i) = (dataset.at(j).features.at(i)-min)/(max-min);
        }//loop through again and normalize data;
       
    } //done checking min/max of all features
    auto time_stops1 = chrono::high_resolution_clock::now(); // Stop timer
    norm_time = chrono::duration_cast<chrono::milliseconds>(time_stops1 - start_time);
}

