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
    primaryIndexs.push_back(index);
  }

  fin.close();
}

int doctorIndexService::getById(string id) {
  char charId[15];
  memset(charId, '\0', 15);
  strcpy(charId, id.c_str());
  int l = 0;
  int r = 0;
  while (l <= r) {
    int mid = l + (r - l) / 2;
    int cmp = strcmp(primaryIndexs[mid].Id, charId);

    if (cmp == 0) {
      return primaryIndexs[mid].offset;
    } else if (cmp < 0) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }

  return -1;
}

int doctorIndexService::removeById(string id) {
  char charId[15];
  memset(charId, '\0', 15);
  strcpy(charId, id.c_str());
  int l = 0;
  int r = primaryIndexs.size() - 1;

  while (l <= r) {
    int mid = l + (r - l) / 2;
    int cmp = strcmp(primaryIndexs[mid].Id, charId);

    if (cmp == 0) {
      int offset = primaryIndexs[mid].offset;
      primaryIndexs.erase(primaryIndexs.begin() + mid);
      return offset;
    } else if (cmp < 0) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }

  return -1;
}

void doctorIndexService::addIndex(string id, int offset) {
  primaryIndex index;
  strcpy(index.Id, id.c_str());
  index.offset = offset;
  primaryIndexs.push_back(index);
  sort(primaryIndexs.begin(), primaryIndexs.end());
  fstream fin("primaryDoctorIndex.txt", ios::out);
  for (int i = 0; i < primaryIndexs.size(); i++) {
    fin.write(primaryIndexs[i].Id, 15);
    fin.write((char*)&primaryIndexs[i].offset, sizeof(int));
  }
}