#ifndef INVERTED_LIST_RECORD_H
#define INVERTED_LIST_RECORD_H

#include <iostream>
#include <string.h>

using namespace std;

class IL_rec {
    public:
        int RRN;
        string PK;
        int pointer;
        bool is_deleted;

        IL_rec (int RRN_value, string PK_value, int ptr_value, bool is_deleted_value = false);
        IL_rec& operator= (const IL_rec &other);
};

#endif