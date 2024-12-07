#include "secondaryIndexService.h"
#include "secondaryIndex.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

SecondaryIndexService::SecondaryIndexService(string fileName, dataFile type_value) {
    this->fileName = fileName;
    fstream fin(fileName, ios::in);
    if (!fin.is_open()) {
        fin.open(fileName, ios::out | ios::binary);
        fin.close();
        return;
    }
    SecondaryIndex index;
    index.type = type_value;
    index.SK_size = index.type == DOCTOR? 30 : 15;
    while (!fin.eof()) {
        fin.read((char *) &index.SK, index.SK_size);
        fin.read((char*) &index.pointer, sizeof(index.pointer));
        secondaryIndexs.push_back(index);
    }

    fin.close();
}

int SecondaryIndexService::search_in_SI (string target, int beg, int end) {
    if (beg > end)
    {
        return -1;
    }
    int mid = beg + (end - beg) / 2;
    if (secondaryIndexs[mid].SK < target)
    {
        return search_in_SI (target, mid+1, end);
    }
    else if (secondaryIndexs[mid].SK > target)
    {
        return search_in_SI (target, beg, mid-1);
    }
    else
    {
        return mid;
    }
}

int PrimaryIndexService::getById(string id) {
    char charId[15];
    memset(charId, '\0', 15);
    strcpy(charId, id.c_str());
    int l = 0;
    int r = 0;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int cmp = strcmp(primaryIndexs[mid].Id, charId);

        if (cmp == 0) {
        return primaryIndexs[mid].offset;
        } else if (cmp < 0) {
        l = mid + 1;
        } else {
        r = mid - 1;
        }
    }

    return -1;
}

void PrimaryIndexService::printIndexs() {
    for ( primaryIndex index : primaryIndexs ) {
        cout << index.Id << " " << index.offset << endl;
    }
}

int PrimaryIndexService::removeById(string id) {
    char charId[15];
    memset(charId, '\0', 15);
    strcpy(charId, id.c_str());
    int l = 0;
    int r = primaryIndexs.size() - 1;

    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        int cmp = strcmp(primaryIndexs[mid].Id, charId);

        if (cmp == 0) {
        int offset = primaryIndexs[mid].offset;
        primaryIndexs.erase(primaryIndexs.begin() + mid);
        return offset;
        } else if (cmp < 0) {
        l = mid + 1;
        } else {
        r = mid - 1;
        }
    }

    fstream fin(fileName, ios::out);
    for (int i = 0; i < primaryIndexs.size(); i++) {
        fin.write(primaryIndexs[i].Id, 15);
        fin.write((char*)&primaryIndexs[i].offset, sizeof(int));
    }

    return -1;
}

void SecondaryIndexService::reflectOnAdd (string sk, string pk) {
    int RRN_of_record_containing_SK_of_addedRecord = search_in_SI(sk, 0, indexFile_no_recs - 1);
    if (RRN_of_record_containing_SK_of_addedRecord == -1 || si[RRN_of_record_containing_SK_of_addedRecord].pointer == -1)
    {
        int newPtr = invertedList.reflectOnAdd(-1, pk);
        indexFile_no_real_recs++;
        if (RRN_of_record_containing_SK_of_addedRecord == -1)
        {
            SI_Rec rec (type, (char *) &(sk), newPtr);
            si.push_back(rec);
            sort (si.begin(), si.end());
            indexFile_no_recs++;
        }
        else
        {
            si[RRN_of_record_containing_SK_of_addedRecord].pointer = newPtr;
        }
    }
    else
    {
        invertedList.reflectOnAdd(si[RRN_of_record_containing_SK_of_addedRecord].pointer, pk);
    }
}

void PrimaryIndexService::addIndex(string id, int offset) {
    primaryIndex index;
    strcpy(index.Id, id.c_str());
    index.offset = offset;
    primaryIndexs.push_back(index);
    sort(primaryIndexs.begin(), primaryIndexs.end());
    fstream fin(fileName, ios::out);
    for (int i = 0; i < primaryIndexs.size(); i++) {
        fin.write(primaryIndexs[i].Id, 15);
        fin.write((char*)&primaryIndexs[i].offset, sizeof(int));
    }
}