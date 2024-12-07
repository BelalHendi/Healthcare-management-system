#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

enum dataFile {
    DOCTOR,
    APPOINTMENT
};

class SecondaryIndex {
    public:
        string SK;
        int pointer;
        short SK_size;
        dataFile type;

        SecondaryIndex() {}
        
        bool operator<(const SecondaryIndex& index) const {
            return strcmp(this->SK.c_str(), index.SK.c_str()) < 0;
        }
};