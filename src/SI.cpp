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

int SI::search_in_SI (const string& sk, int beg, int end) {
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





SI::SI(DataFile type_value) : il(type_value) {
    type = type_value;
    SK_SIZE = (type == DOCTOR) ? 30 : 15;
    fileName = (type == DOCTOR) ? "doctor_SI.txt" : "appointment_SI.txt";

    ifstream indexFile(fileName, ios::binary);
    if (!indexFile) {
        cerr << "Index file not found. Creating a new file: " << fileName << endl;
        ofstream createFile(fileName, ios::binary);
        createFile.close();
        return;
    }

    vector<char> sk_buffer(SK_SIZE + 1, '\0');
    int pointer = 0;
    while (indexFile) {  // While the file is in a good state
        // Read search key
        if (!indexFile.read(sk_buffer.data(), SK_SIZE))
            break; // Exit the loop if reading failed or reached EOF

        // Convert to string and remove null characters
        string searchKey(sk_buffer.data());
        searchKey.erase(remove(searchKey.begin(), searchKey.end(), '\0'), searchKey.end());

        // Read pointer
        if (!indexFile.read(reinterpret_cast<char*>(&pointer), sizeof(pointer)))
            break; // Exit the loop if reading failed

        SI_rec rec;
        rec.SK = searchKey;
        rec.pointer = pointer;
        recs.push_back(rec);

        // Reset buffer
        fill(sk_buffer.begin(), sk_buffer.end(), '\0');
    }
    indexFile.close();
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

void SI::reflectOnAdd (const string& sk, const string& pk) {
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