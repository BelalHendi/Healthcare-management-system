#include <bits/stdc++.h>

#include "SI_IL.cpp"

using namespace std;

class SI_Rec {
 public:
  char *DoctorID;
  int refPtr;

  SI_Rec(char *DoctorID_value = NULL, int referencePointer_value = -1) {
    DoctorID = new char[15];
    if (DoctorID_value = NULL) {
      memset(DoctorID, '\0', 15);
    } else {
      for (int i = 0; i < 15; i++) {
        DoctorID[i] = DoctorID_value[i];
      }
    }
    refPtr = referencePointer_value;
  }

  ~SI_Rec() { delete[] DoctorID; }

  bool operator<(const SI_Rec &other) const {
    return this->DoctorID < other.DoctorID;
  }

  SI_Rec operator=(const SI_Rec &other) {
    char *temp = new char[15];
    for (int i = 0; i < 15; i++) {
      temp[i] = other.DoctorID[i];
    }
    this->DoctorID = temp;
    this->refPtr = other.refPtr;
  }
};

class SI {
 private:
  vector<SI_Rec> si;
  const string indexFileName;
  unsigned int indexFile_no_recs;
  unsigned int indexFile_no_real_recs;
  SI_IL invertedList;

  void reclaim() {
    for (int i = 0; i < indexFile_no_recs; i++) {
      if (si[i].refPtr == -1) {
        si.erase(si.begin() + i);
        i--;
        indexFile_no_recs--;
      }
    }
  }

  bool isEmpty() {
    fstream indexFile(indexFileName, ios::in);
    indexFile.seekg(0, ios::end);
    return indexFile.tellg() == 0;
  }

  void write_statusFlag(bool state) {
    fstream indexFile(indexFileName, ios::in | ios::out);
    indexFile.seekp(0, ios::beg);
    string flag = state ? "1" : "0";
    string STATUS_FLAG = flag + "\n";
    indexFile.write((char *)&STATUS_FLAG, 2);
  }

 public:
  SI(string indexFileName_value, string invertedListFileName_value)
      : indexFileName(indexFileName_value),
        invertedList(invertedListFileName_value) {
    fstream indexFile(indexFileName, ios::in | ios::out);
    if (indexFile.fail()) {
      cout << "there was an error opening this file\n";
    } else {
      indexFile_no_recs = 0;
      indexFile_no_real_recs = 0;
      if (isEmpty()) {
        write_statusFlag(true);
      }
      // file opened successfully and is not empty
      else {
        indexFile.seekg(2, ios::beg);
        SI_Rec rec;
        while (!indexFile.eof()) {
          indexFile.read(rec.DoctorID, 15);
          indexFile.seekg(1, ios::cur);
          indexFile.read((char *)&(rec.refPtr), sizeof(rec.refPtr));
          indexFile.seekg(1, ios::cur);
          si.push_back(rec);
          indexFile_no_recs++;
          indexFile_no_real_recs++;
        }
      }
    }
    indexFile.close();
  }

  ~SI() {
    fstream indexFile(indexFileName, ios::trunc | ios::binary);
    for (int i = 0; i < indexFile_no_recs; i++) {
      indexFile.write((char *)&si[i].DoctorID, 15);
      indexFile.write((char *)'|', 1);
      indexFile.write((char *)&si[i].refPtr, sizeof(si[i].refPtr));
      indexFile.write((char *)'\n', 1);
    }
    write_statusFlag(false);
  }

  void reflectOnAdd(string sk, string pk) {
    int RRN_of_SK_of_addedRecord = search_in_SI(sk, 0, indexFile_no_recs - 1);
    if (RRN_of_SK_of_addedRecord == -1) {
      int newRefPtr = invertedList.reflectOnAdd(-1, pk);
      SI_Rec rec((char *)&(sk), newRefPtr);
      si.push_back(rec);
      sort(si.begin(), si.end());
      indexFile_no_recs++;
      indexFile_no_real_recs++;
    } else if (si[RRN_of_SK_of_addedRecord].refPtr == -1) {
      int newRefPtr = invertedList.reflectOnAdd(-1, pk);
      si[RRN_of_SK_of_addedRecord].refPtr = newRefPtr;
      indexFile_no_real_recs++;
    } else {
      invertedList.reflectOnAdd(si[RRN_of_SK_of_addedRecord].refPtr, pk);
    }
  }

  void reflectOnDelete(string sk, string pk) {
    int RRN_of_SK_of_deletedRecord = search_in_SI(sk, 0, indexFile_no_recs - 1);
    if (RRN_of_SK_of_deletedRecord == -1 ||
        si[RRN_of_SK_of_deletedRecord].refPtr == -1) {
      cout << "no record with this secondary key exists already";
    } else {
      pair<int, int> prev_and_newRefPtr = invertedList.reflectOnDelete(
          si[RRN_of_SK_of_deletedRecord].refPtr, pk);
      if (prev_and_newRefPtr.first == -1) {
        si[RRN_of_SK_of_deletedRecord].refPtr =
            si[prev_and_newRefPtr.second].refPtr;
      }

      if (prev_and_newRefPtr.second == -1) {
        indexFile_no_real_recs--;
      }
      if (indexFile_no_real_recs < floor(0.75 * indexFile_no_recs)) {
        reclaim();
      }
    }
  }

  int search_in_SI(string target, int beg, int end) {
    if (beg > end) {
      return -1;
    }
    int mid = beg + (end - beg) / 2;
    if (si[mid].DoctorID < target) {
      return search_in_SI(target, mid + 1, end);
    } else if (si[mid].DoctorID > target) {
      return search_in_SI(target, beg, mid - 1);
    } else {
      return mid;
    }
  }

  vector<string> search(string sk) {
    int RRN_of_SK = search_in_SI(sk, 0, indexFile_no_recs - 1);
    return invertedList.search(si[RRN_of_SK].refPtr);
  }
};