#ifndef INSTANCE_CPP_
#define INSTANCE_CPP_

#include "instance.h"
using namespace std;

instance::instance() {
    currInstance = {1,2,3};
};

vector<float> instance::getVector() {
    return currInstance;
}


#endif