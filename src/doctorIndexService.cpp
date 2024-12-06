#include "doctorIndexService.h"

#include <algorithm>
#include <cstring>
#include <fstream>

using namespace std;

doctorIndexService::doctorIndexService() {
  fstream fin("primaryDoctorIndex.txt", ios::in);
  if (!fin.is_open()) {
    fin.close();
    fin.open("primaryDoctorIndex.txt", ios::out);
  }
  primaryIndex index;
  while (!fin.eof()) {
    fin.read(index.Id, 15);
    fin.read((char*)&index.offset, sizeof(index.offset));
    priamryIndexs.push_back(index);
  }

  fin.close();
}

void doctorIndexService::addIndex(string id, int offset) {
  primaryIndex index;
  strcpy(index.Id, id.c_str());
  index.offset = offset;
  priamryIndexs.push_back(index);
  sort(priamryIndexs.begin(), priamryIndexs.end());
  fstream fin("primaryDoctorIndex.txt", ios::out);
  for (int i = 0; i < priamryIndexs.size(); i++) {
    fin.write(priamryIndexs[i].Id, 15);
    fin.write((char*)&priamryIndexs[i].offset, sizeof(int));
  }
}