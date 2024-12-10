#ifndef _Primary_index_Service_h_
#define _Primary_index_Service_h_
#include <iostream>
#include <vector>

#include "primaryIndex.h"
using namespace std;
class PrimaryIndexService {
 private:
  vector<primaryIndex> primaryIndexs;
  int insertPrimaryIndex( primaryIndex index ) ;
  void bubbleDown( int RRN ) ;
  void bubbleup( int RRN ) ;
  string fileName;

 public:
  PrimaryIndexService(string fileName);
  void addIndex(string id, int offset);
  int getById(string id);
  vector<int> getByIds(vector<string> id);
  int removeById(string id);
  void printIndexs();
};

#endif