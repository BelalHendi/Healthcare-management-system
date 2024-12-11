#include "../include/SI.h"

#include <fstream>

void SI::reclaim () {
    for (int i = 0; i < no_recs; i++)
    {
        if (recs[i].pointer == -1)
        {
            recs.erase(recs.begin() + i);
            i--;
            no_recs--;
        }
    }
}

int SI::search_in_SI (string sk, int beg, int end) {
    if (beg > end)
    {
        return -1;
    }
    int mid = beg + (end - beg) / 2;
    if (recs[mid].SK < sk)
    {
        return search_in_SI (sk, mid+1, end);
    }
    else if (recs[mid].SK > sk)
    {
        return search_in_SI (sk, beg, mid-1);
    }
    else
    {
        return mid;
    }
}





SI::SI (DataFile type_value) : il (type_value) {
    type = type_value;
    SK_SIZE = type == DOCTOR? 30 : 15;
    string prepend_to_fileName = type == DOCTOR? "doctor" : "appointment";
    fileName = prepend_to_fileName + "_SI.txt";
    no_recs = 0;
    no_realRecs = 0;

    fstream indexFile (fileName, ios::in | ios::binary);
    //if the file doesn't exist, create it and close it
    if (!indexFile.is_open()) {
        indexFile.open(fileName, ios::out | ios::binary);
        indexFile.close();
    }
    //If exists, read its content into memory
    else
    {
        SI_rec rec = SI_rec ();
        while (
        indexFile.read((char *) rec.SK.c_str(), SK_SIZE) &&
        indexFile.read((char *) &rec.pointer, sizeof(rec.pointer))
        )
        {
            recs.push_back(rec);
        }
        indexFile.close();
    }
}

SI::~SI () {
    fstream indexFile (fileName, ios::out | ios::binary);
    indexFile.seekp(0, ios::beg);
    for (int i = 0; i < recs.size(); i++)
    {
        indexFile.write((char *) recs[i].SK.c_str(), SK_SIZE);
        indexFile.write((char *) &recs[i].pointer, sizeof(recs[i].pointer));
    }
    indexFile.close();
}

void SI::reflectOnAdd (string sk, string pk) {
    int RRN_of_rec_containing_SK = search_in_SI(sk, 0, no_recs - 1);
    //no real rec with such sk
    if (RRN_of_rec_containing_SK == -1 || recs[RRN_of_rec_containing_SK].pointer == -1)
    {
        int newPtr = il.reflectOnAdd(-1, pk);
        no_realRecs++;
        //no rec with such sk
        if (RRN_of_rec_containing_SK == -1)
        {
            SI_rec rec (sk, newPtr);
            recs.push_back(rec);
            sort (recs.begin(), recs.end());
            no_recs++;
        }
        //there exists a rec with such sk but not real
        else
        {
            recs[RRN_of_rec_containing_SK].pointer = newPtr;
        }
    }
    //there exists a real rec with such sk
    else
    {
        recs[RRN_of_rec_containing_SK].pointer = il.reflectOnAdd(recs[RRN_of_rec_containing_SK].pointer, pk);
    }
}

void SI::reflectOnUpdate (string old_sk, string new_sk) {
    if (type == APPOINTMENT)
    {
        return;
    }
    int RRN_of_rec_containing_SK = search_in_SI(old_sk, 0, recs.size() - 1);
    if (RRN_of_rec_containing_SK == -1)
    {
        cout << "the old secondary key doesn't exist already to update it\nYou can insert the new secondary key directly";
    }
    else
    {
        recs[RRN_of_rec_containing_SK].SK = new_sk;
        sort(recs.begin(), recs.end());
    }
}

void SI::reflectOnDelete (string sk, string pk) {
    int RRN_of_rec_containing_SK = search_in_SI(sk, 0, no_recs - 1);
    //no real rec with such sk
    if (RRN_of_rec_containing_SK == -1 || recs[RRN_of_rec_containing_SK].pointer == -1)
    {
        cout << "no record with this secondary key exists already\n";
    }
    //there exists a real rec with such sk
    else
    {
        //search in il
        //update the pointer of the SK according to the result of deletion from the il
        //If there are no more bindings in the il associated with this sk
        //then reduce the # of real recs and check if the SI requires reclamation of space
        int newPointer = il.reflectOnDelete(recs[RRN_of_rec_containing_SK].pointer, pk);
        recs[RRN_of_rec_containing_SK].pointer = newPointer;
        if (newPointer == -1)
        {
            no_realRecs--;
            if (no_realRecs < (int) floor(0.75 * no_recs))
            {
                reclaim ();
            }
        }
    }
}

vector <string> SI::search (string sk) {
    int RRN_of_SK = search_in_SI(sk, 0, no_recs - 1);
    return il.search(recs[RRN_of_SK].pointer);
}