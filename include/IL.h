#ifndef INVERTED_LIST_H
#define INVERTED_LIST_H

#include "dataFileType.h"
#include "IL_rec.h"

#include <vector>

class IL {
    private:
        DataFile type;
        string fileName;
        unsigned int PK_SIZE;
        vector <IL_rec> recs;
        int avail_list_header;

        void push_to_avail_list (int RRN);
        int pop_from_avail_list ();
        pair<int, int> search_in_IL (int RRN, string target);

    public:
    IL (DataFile type_value);
    int reflectOnAdd (int RRN, string pk);
    int reflectOnDelete (int RRN, string pk);
    vector <string> search (int RRN);

};

#endif