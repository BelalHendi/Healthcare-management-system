#ifndef _doctor_index_service_h_
#define _doctor_index_service_h_
#include <iostream>
#include <vector>

#include "primaryIndex.h"
using namespace std;
class doctorIndexService {
 private:
  vector<primaryIndex> priamryIndexs;

 public:
  doctorIndexService();
  void addIndex(string id, int offset);
  int getById(string id);
};

#endif