#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>


#ifndef _Primary_index_Service_h_
#define _Primary_index_Service_h_
#include <iostream>
#include <vector>

#include "secondaryIndex.h"
#include "invertdList.cpp"


using namespace std;
class SecondaryIndexService {
    private:
        vector<SecondaryIndex> secondaryIndexs;
        string fileName;

        unsigned int indexFile_no_recs;
        unsigned int indexFile_no_real_recs;
        //the # of records that are not deleted
        dataFile type;
        unsigned short SK_size;
        SI_IL invertedList;

        int search_in_SI (string target, int beg, int end);

    public:
        SecondaryIndexService(string fileName, dataFile type_value);
        void reflectOnAdd (string sk, string pk)
        void addIndex(string id, int offset);
        int getById(string id);
        int removeById(string id);
        void printIndexs();
};

#endif