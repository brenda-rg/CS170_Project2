#ifndef INSTANCE_CPP_
#define INSTANCE_CPP_

#include "Instance.h"
#include <iostream>
using namespace std;

Instance::Instance() {
   // features = {1,2,3};
};
Instance::Instance(int n) {
    classtype = n;
};

vector<double> Instance::getVector() {
    return features;
}

void Instance::print() {
    cout << "ID:" << id << "\tclass:" << classtype << endl << "\t\tfeatures:\t";
    for (int i=0; i < features.size(); ++i) {
        cout << features.at(i) << "  ";
    }
}


#endif