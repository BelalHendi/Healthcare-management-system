#ifndef SECONDARY_INDEX_H
#define SECONDARY_INDEX_H

#include "SI_rec.h"
#include "IL.h"

#include <algorithm>
#include <cmath>

class SI {
    private:
        DataFile type;
        string fileName;
        unsigned short SK_SIZE;
        vector <SI_rec> recs;
        unsigned int no_recs;
        //the # of records that are not deleted
        unsigned int no_realRecs;
        IL il;

        void reclaim ();
        int search_in_SI (string sk, int beg, int end);

    public:
        SI (DataFile type_value);
        ~SI ();
        void reflectOnAdd (string sk, string pk);
        void reflectOnUpdate(string old_sk, string new_sk);
        void reflectOnDelete (string sk, string pk);
        vector <string> search (string sk);
};

#endif