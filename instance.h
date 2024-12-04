#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <math.h>
#include <vector>
using namespace std;


class Instance {
    public:
    Instance();
    Instance(int); //Instance with class known
    Instance(int, vector<double>); // Instance with class and features known
    int id, classtype;
    vector<double> features;
    vector<double> getVector();
    void print();

};


#endif
