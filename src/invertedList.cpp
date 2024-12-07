#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

class SI_IL_Rec {
    public:
        int RRN;
        string PK;
        int pointer;
        //-2 -> deleted (belongs to the avail list) + availList_ptr is meaningful
        //-1 -> last binding
        //>= 0 -> still more bindings
        int availList_ptr;
        //-1 -> last node
        //>= 0 -> there exist a next node

        SI_IL_Rec () {}

        SI_IL_Rec (string PK_value, int RRN_value = 0, int ptr_value = -1) {
            RRN = RRN_value;
            PK = PK_value;
            pointer = ptr_value;
            availList_ptr = -1;
        }

        SI_IL_Rec& operator= (const SI_IL_Rec &other) {
            this->RRN = other.RRN;
            strcpy((char *) &this->PK, other.PK.c_str());
            this->pointer = other.pointer;
            this->availList_ptr = other.availList_ptr;
            return *this;
        }
};

class SI_IL {
    private:
        vector <SI_IL_Rec> il;
        string invertedListFileName;
        int avail_list_header;
        unsigned int PK_SIZE;

        void add_to_avail_list (int RRN) {
            int second_node_ptr = avail_list_header;
            avail_list_header = RRN;
            il[RRN].availList_ptr = second_node_ptr;
            il[RRN].pointer = -2;
        }

        int remove_from_avail_list () {
            if (avail_list_header == -1)
            {
                return -1;
            }
            int first_node_refPtr = il[avail_list_header].availList_ptr;
            il[avail_list_header].pointer = -1;
            il[avail_list_header].availList_ptr = -1;
            avail_list_header = first_node_refPtr;
            return avail_list_header;
        }

        //first -> RRN of the record previous to the record containing the target PK (-1 if the record containing the target PK is the first binding)
        //second -> RRN of the record containing the target PK  (-1 if no record with such PK)
        pair<int, int> search_in_SI_IL (int RRN, string target) {
            pair<int, int> prevRRN_targetRRN;
            prevRRN_targetRRN.first = -1;
            prevRRN_targetRRN.second = -1;
            while (RRN != -1)
            {
                if (il[RRN].PK == target)
                {
                    prevRRN_targetRRN.second = RRN;
                    break;
                }
                else
                {
                    prevRRN_targetRRN.first = RRN;
                    RRN = il[RRN].pointer;
                }
            }
            return prevRRN_targetRRN;
        }

    public:

        SI_IL (string invertedListFileName_value, unsigned int PK_SIZE_value = 15) {
            invertedListFileName = invertedListFileName_value;
            PK_SIZE = PK_SIZE_value;
            fstream invertedListFile (invertedListFileName, ios::in);
            if (!invertedListFile.is_open()) {
                invertedListFile.open(invertedListFileName, ios::out | ios::binary);
                invertedListFile.close();
                return;
            }
            SI_IL_Rec rec;
            while (!invertedListFile.eof()) {
                invertedListFile.read((char *) &rec.RRN, sizeof(rec.RRN));
                invertedListFile.read((char *) &rec.PK, sizeof(rec.PK));
                invertedListFile.read((char*) &rec.pointer, sizeof(rec.pointer));
                il.push_back(rec);
            }
            invertedListFile.close();
        }

        int reflectOnAdd (int RRN, string pk) {
            int RRN_of_obtained_rec_from_availList = remove_from_avail_list ();
            int RRN_of_added_rec;
            //if no record obtained from avail list, then append at the end of the il
            if (RRN_of_obtained_rec_from_availList == -1)
            {
                SI_IL_Rec rec (pk, (int) il.size());
                il.push_back(rec);
                RRN_of_added_rec = il.size() - 1;
            }
            //else, write to this obtained record
            else
            {
                //SI_IL_Rec rec (RRN_of_obtained_rec_from_availList, (char *) &pk);
                //il[RRN_of_obtained_rec_from_availList] = rec;
                il[RRN_of_obtained_rec_from_availList].PK = (char *) &pk;
                RRN_of_added_rec = RRN_of_obtained_rec_from_availList;
            }
            if (RRN != -1)
            {
                int prev;
                while (RRN != -1)
                {
                    prev = RRN;
                    RRN = il[RRN].pointer;
                }
                RRN = prev;
                il[RRN].pointer = RRN_of_added_rec;
            }

            fstream invertedListFile(invertedListFileName, ios::out);
            for (int i = 0; i < il.size(); i++) {
                invertedListFile.write((char*)&il[i].RRN, sizeof(il[i].RRN));
                invertedListFile.write((char*)&il[i].PK, PK_SIZE);
                invertedListFile.write((char*)&il[i].pointer, sizeof(il[i].pointer));
            }

            return RRN_of_added_rec;
        }

        //returns pointer to the second binding: if -> the deleted record is the first binding
        //returns RRN: if -> the deleted record is after the first binding
        //returns -1: if -> the there is no record with this pk (this should never happen)
        int reflectOnDelete (int RRN, string pk) {
            // starting from RRN, search for the rec with pk
            // if not found, out error message and -1
            // if found
            // is it the record with rrn == the input RRN (is it the first binding)? 
            // yes: return il[RRN].pointer (RRN of the second bondong) to update the pointer of the secondary key
            // no: no change in the pointer of the secondary key (return the RRN as it is)

            pair<int, int> prevRRN_PKRRN = search_in_SI_IL (RRN, pk);
            if (prevRRN_PKRRN.second == -1)
            {
                cout << "no record with such primary key exists already";
                return -1;
            }
            else
            {
                int RRN_of_next_after_deleted_rec = il[prevRRN_PKRRN.second].pointer;
                add_to_avail_list(prevRRN_PKRRN.second);
                if (prevRRN_PKRRN.second == RRN)
                {
                    return RRN_of_next_after_deleted_rec;
                }
                else
                {
                    il[prevRRN_PKRRN.first].pointer = RRN_of_next_after_deleted_rec;                
                    return RRN;
                }
            }

            fstream invertedListFile(invertedListFileName, ios::out);
            for (int i = 0; i < il.size(); i++) {
                invertedListFile.write((char*)&il[i].RRN, sizeof(il[i].RRN));
                invertedListFile.write((char*)&il[i].PK, PK_SIZE);
                invertedListFile.write((char*)&il[i].pointer, sizeof(il[i].pointer));
            }
        }

        vector <string> search (int RRN) {
            vector <string> res;
            int i = RRN;
            while (!(i == -1 || i == -2)) {
                res.push_back(il[i].PK);
                i = il[i].pointer;
            }
            if (i == -2)
            {
                il.pop_back();
            }
            return res;
        }
};