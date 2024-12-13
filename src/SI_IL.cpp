// #include "SI.h"
// using namespace std;
//
// class SI_IL_Rec {
//  public:
//   int RRN;
//   char *PK;
//   int refPtr;
//   //-2 -> deleted
//   //-1 -> last binding
//   //>= 0 -> still more bindings
//   int availList_refPtr;
//
//   SI_IL_Rec(int RRN_value = 0, char *PK_value = NULL, int refPtr_value = -1) {
//     RRN = RRN_value;
//
//     PK = new char[15];
//     if (PK_value = NULL) {
//       memset(PK, '\0', 15);
//     } else {
//       for (int i = 0; i < 15; i++) {
//         PK[i] = PK_value[i];
//       }
//     }
//
//     refPtr = refPtr_value;
//     availList_refPtr = -1;
//   }
//
//   ~SI_IL_Rec() { delete[] PK; }
//
//   SI_IL_Rec operator=(const SI_IL_Rec &other) {
//     this->RRN = other.RRN;
//     char *temp = new char[15];
//     for (int i = 0; i < 15; i++) {
//       temp[i] = other.PK[i];
//     }
//     this->PK = temp;
//     this->refPtr = other.refPtr;
//     this->availList_refPtr = other.availList_refPtr;
//   }
// };
//
// class SI_IL {
//  private:
//   vector<SI_IL_Rec> il;
//   const string invertedListFileName;
//   int avail_list_header;
//
//   bool isEmpty() {
//     fstream invertedListFile(invertedListFileName, ios::in);
//     invertedListFile.seekg(0, ios::end);
//     return invertedListFile.tellg() == 0;
//   }
//
//   void write_avail_list_header(int RRN) {
//     fstream invertedListFile(invertedListFileName, ios::in | ios::out);
//     invertedListFile.seekp(0, ios::beg);
//     string headerRef = to_string(RRN) + "\n";
//     invertedListFile.write((char *)&headerRef, sizeof(int) + 1);
//   }
//
//   void add_to_avail_list(int RRN) {
//     int second_node_refPtr = avail_list_header;
//     avail_list_header = RRN;
//     il[RRN].availList_refPtr = second_node_refPtr;
//     il[RRN].refPtr = -2;
//   }
//
//   int remove_from_avail_list() {
//     int RRN_of_removed_node = -1;
//     int first_node_refPtr = il[avail_list_header].availList_refPtr;
//     il[avail_list_header].refPtr = -1;
//     il[avail_list_header].availList_refPtr = -1;
//     avail_list_header = first_node_refPtr;
//     return RRN_of_removed_node;
//   }
//
//  public:
//   SI_IL(string invertedListFileName_value)
//       : invertedListFileName(invertedListFileName_value) {
//     fstream invertedListFile(invertedListFileName, ios::in | ios::out);
//     if (invertedListFile.fail()) {
//       cout << "there was an error opening this file\n";
//     } else {
//       if (isEmpty()) {
//         write_avail_list_header(-1);
//       } else {
//         invertedListFile.read((char *)&avail_list_header, sizeof(int));
//         invertedListFile.seekg(1, ios::cur);
//         SI_IL_Rec rec;
//         while (!invertedListFile.eof()) {
//           invertedListFile.read((char *)&rec.RRN, sizeof(rec.RRN));
//           invertedListFile.seekg(1, ios::cur);
//           invertedListFile.read((char *)&(rec.PK), 15);
//           invertedListFile.seekg(1, ios::cur);
//           invertedListFile.read((char *)&(rec.refPtr), sizeof(rec.refPtr));
//           invertedListFile.seekg(1, ios::cur);
//           invertedListFile.read((char *)&(rec.availList_refPtr),
//                                 sizeof(rec.availList_refPtr));
//           invertedListFile.seekg(1, ios::cur);
//           il.push_back(rec);
//         }
//       }
//     }
//     invertedListFile.close();
//   }
//
//   ~SI_IL() {
//     fstream invertedListFile(invertedListFileName, ios::trunc | ios::binary);
//     for (int i = 0; i < il.size(); i++) {
//       invertedListFile.write((char *)&il[i].RRN, sizeof(il[i].RRN));
//       invertedListFile.write((char *)'|', 1);
//       invertedListFile.write((char *)&il[i].PK, 15);
//       invertedListFile.write((char *)'|', 1);
//       invertedListFile.write((char *)&il[i].refPtr, sizeof(il[i].refPtr));
//       invertedListFile.write((char *)'|', 1);
//       invertedListFile.write((char *)&il[i].availList_refPtr,
//                              sizeof(il[i].availList_refPtr));
//       invertedListFile.write((char *)'\n', 1);
//     }
//     write_avail_list_header(avail_list_header);
//   }
//
//   int reflectOnAdd(int RRN, string pk) {
//     int RRN_of_deleted_rec = remove_from_avail_list();
//     int RRN_of_added_rec;
//     if (RRN_of_deleted_rec == -1) {
//       SI_IL_Rec rec((int)il.size(), (char *)&pk);
//       il.push_back(rec);
//       RRN_of_added_rec = il.size() - 1;
//     } else {
//       SI_IL_Rec rec(RRN_of_deleted_rec, (char *)&pk);
//       il[RRN_of_deleted_rec] = rec;
//       RRN_of_added_rec = RRN_of_deleted_rec;
//     }
//     if (RRN != -1) {
//       int prev;
//       while (RRN != -1) {
//         prev = RRN;
//         RRN = il[RRN].refPtr;
//       }
//       RRN = prev;
//       il[RRN].refPtr = RRN_of_added_rec;
//     }
//     return RRN_of_added_rec;
//   }
//
//   pair<int, int> reflectOnDelete(int RRN, string pk) {
//     pair<int, int> RNN_before_and_containing = search_in_SI_IL(RRN, pk);
//     if (RNN_before_and_containing.second == -1) {
//       cout << "no record with such primary key exists already";
//       return {-1, -1};
//     }
//     if (RNN_before_and_containing.first != -1) {
//       il[RNN_before_and_containing.first].refPtr =
//           il[RNN_before_and_containing.second].refPtr;
//     }
//     add_to_avail_list(RNN_before_and_containing.second);
//     return RNN_before_and_containing;
//   }
//
//   pair<int, int> search_in_SI_IL(int RRN, string target) {
//     pair<int, int> p;
//     p.first = -1;
//     p.second = -1;
//     while (RRN != -1) {
//       if (il[RRN].PK == target) {
//         p.second = RRN;
//         break;
//       } else {
//         p.first = RRN;
//         RRN = il[RRN].refPtr;
//       }
//     }
//     return p;
//   }
//
//   vector<string> search(int RRN) {
//     vector<string> res;
//     int i = RRN;
//     while (i != -1 && i != -2) {
//       res.push_back(il[i].PK);
//       i = il[i].refPtr;
//     }
//     if (i == -2) {
//       il.pop_back();
//     }
//     return res;
//   }
// };