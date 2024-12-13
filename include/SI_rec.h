#ifndef SECONDARY_INDEX_RECORD_H
#define SECONDARY_INDEX_RECORD_H

#include <iostream>

using namespace std;

class SI_rec {
    public:
        string SK;
        int pointer;
   
        SI_rec ();
        SI_rec (string SK_value, int pointer_value);
        bool operator< (const SI_rec& index) const;
};

#endif