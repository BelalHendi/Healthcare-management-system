#include "IL.h"

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
    string prepend_to_fileName = type == DOCTOR? "doctor" : "appointment";
    fileName = prepend_to_fileName + "_IL.txt";
    PK_SIZE = 15;
    avail_list_header = -1;
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