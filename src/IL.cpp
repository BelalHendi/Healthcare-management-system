#include "../include/IL.h"

#include <fstream>
#include <algorithm>

void IL::push_to_avail_list (int RRN) {
    int ptr_to_secondNode = avail_list_header;
    avail_list_header = RRN;

    recs[RRN].pointer = ptr_to_secondNode;
    recs[RRN].is_deleted = true;
}

int IL::pop_from_avail_list () {
    if (avail_list_header == -1)
    {
        return -1;
    }

    int ptr_to_firstNode = recs[avail_list_header].pointer;
    int removedNode_RRN = avail_list_header;
    avail_list_header = ptr_to_firstNode;

    recs[removedNode_RRN].pointer = -1;
    recs[removedNode_RRN].is_deleted = false;
    return removedNode_RRN;
}

//first -> RRN of the record previous to the record containing the pk (-1 if the record containing the pk is the first binding or doesn't exist)
//second -> RRN of the record containing the pk  (-1 if no record with such PK)
pair<int, int> IL::search_in_IL (int RRN, string pk) {
    pair<int, int> prevRRN_targetRRN;
    prevRRN_targetRRN.first = -1;
    prevRRN_targetRRN.second = -1;

    while (RRN != -1)
    {
        if (recs[RRN].PK == pk)
        {
            prevRRN_targetRRN.second = RRN;
            break;
        }
        else
        {
            prevRRN_targetRRN.first = RRN;
            RRN = recs[RRN].pointer;
        }
    }

    return prevRRN_targetRRN;
}





IL::IL (DataFile type_value) {
    type = type_value;
    fileName = type == DOCTOR? "doctor_IL.txt" : "appointment_IL.txt";
    PK_SIZE = 15;
    avail_list_header = -1;

    //If the list file doesn't exist, create it
    fstream listFile(fileName, ios::in | ios::out | ios::binary);
    bool file_has_no_recs = false;
    if (!listFile) {
        cerr << "Index file not found. Creating a new file: " << fileName << endl;
        fstream createFile(fileName, ios::out | ios::binary);
        file_has_no_recs = true;
    }

    if (file_has_no_recs)
    {
        listFile.write((char *) &avail_list_header, sizeof(int));
        listFile.close();
        return;
    }

    //read the content of the inverted list file

    //read the avail_list_header
    listFile.read((char *) &avail_list_header, sizeof(int));

    //read the recs of the inverted list file
    int RRN = 0;
    vector<char> pk_buffer(PK_SIZE + 1, '\0');
    int pointer = 0;
    bool is_deleted = false;
    
    // While the file is in a good state
    //read each atribute of IL_rec
    //and break whenever reading the data fails
    while (listFile) {  
        //RRN
        if (!listFile.read(reinterpret_cast<char*>(&RRN), sizeof(RRN)))
            break;

        //PK
        if (!listFile.read(pk_buffer.data(), PK_SIZE))
            break;

        // Convert to string and remove null characters
        string pk(pk_buffer.data());
        pk.erase(remove(pk.begin(), pk.end(), '\0'), pk.end());

        //pointer
        if (!listFile.read(reinterpret_cast<char*>(&pointer), sizeof(pointer)))
            break;

        //is_deleted
        if (!listFile.read((char *) (&is_deleted), sizeof(is_deleted)))
            break;

        //add the read record to the memory
        IL_rec rec (RRN, pk, pointer, is_deleted);
        recs.push_back(rec);

        // Reset buffer
        fill(pk_buffer.begin(), pk_buffer.end(), '\0');
    }
    listFile.close();
}

IL::~IL () {
    ofstream listFile (fileName, ios::binary);
    listFile.seekp(0, ios::beg);

    //write the avail_list_header
    listFile.write((char *) &avail_list_header, sizeof(avail_list_header));

    //write the recs
    for (int i = 0; i < recs.size(); i++)
    {
        listFile.write((char *) &recs[i].RRN, sizeof(recs[i].RRN));
        listFile.write((char *) recs[i].PK.c_str(), PK_SIZE);
        listFile.write((char *) &recs[i].pointer, sizeof(recs[i].pointer));
        listFile.write((char *) &recs[i].is_deleted, sizeof(recs[i].is_deleted));
    }
    listFile.close();
}

int IL::reflectOnAdd (int RRN, string pk) {
    int RRN_of_obtained_rec_from_availList = pop_from_avail_list ();
    int RRN_of_added_rec;

    //if no record obtained from avail list, then append at the end of the il
    if (RRN_of_obtained_rec_from_availList == -1)
    {
        IL_rec rec (recs.size(), pk, -1, false);
        recs.push_back(rec);
        RRN_of_added_rec = recs.size() - 1;
    }
    //else, write to this obtained record
    else
    {
        recs[RRN_of_obtained_rec_from_availList].PK = pk;
        RRN_of_added_rec = RRN_of_obtained_rec_from_availList;
    }

    //The added binding is now the last binding
    //If there is a previous binding to the added binding, set its pointer to the RRN of the newly added binding
    
    //search for the RRN of the rec of the previous binding to the added binding
    int prev_to_beforeLastBinding_RRN = -1;
    int beforeLastBinding_RRN = RRN;
    while (beforeLastBinding_RRN != -1)
    {
        prev_to_beforeLastBinding_RRN = beforeLastBinding_RRN;
        beforeLastBinding_RRN = recs[beforeLastBinding_RRN].pointer;
    }
    beforeLastBinding_RRN = prev_to_beforeLastBinding_RRN;
    //if the binding exists, ..
    if (beforeLastBinding_RRN != -1)
    {
        recs[beforeLastBinding_RRN].pointer = RRN_of_added_rec;
    }

    //if the added binding is the first binding, update the sk's pointer
    if (beforeLastBinding_RRN == -1)
    {
        return RRN_of_added_rec;
    }
    //else, keep it as it is
    else
    {
        return RRN;
    }
}

//returns pointer to the new first binding: if -> the deleted record was the first binding
//returns RRN: if -> the deleted record is after the first binding
//returns -1: if -> the there is no record with this pk (this should never happen)
int IL::reflectOnDelete (int RRN, string pk) {
    // starting from RRN, search for the rec with PK == pk
    // if not found, out error message and -1
    // if found
    //1. link its previous binding to its following binding
    //2. add to the avail list
    //3.1 If it was the first binding -> return the RRN of the current first binding 
    //3.2 else -> keep the sk's pointer as it is

    //this shouldn't happen
    if (RRN == -1)
    {
        return -1;
    }

    pair<int, int> prevRRN_PKRRN = search_in_IL (RRN, pk);
    if (prevRRN_PKRRN.second == -1)
    {
        cout << "no record with this primary key exists already\n";
        return -1;
    }
    else
    {
        if (prevRRN_PKRRN.first != -1)
        {
            recs[prevRRN_PKRRN.first].pointer = recs[prevRRN_PKRRN.second].pointer;
        }
        int afterDeleted_RRN = recs[prevRRN_PKRRN.second].pointer;
        push_to_avail_list(prevRRN_PKRRN.second);
        if (prevRRN_PKRRN.first == -1)
        {
            return afterDeleted_RRN;
        }
        else
        {
            return RRN;
        }
    }
}

vector <string> IL::search (int RRN) {
    vector <string> associated_PKs;
    while (RRN != -1)
    {
        associated_PKs.push_back(recs[RRN].PK);
        RRN = recs[RRN].pointer;
    }
    return associated_PKs;
}