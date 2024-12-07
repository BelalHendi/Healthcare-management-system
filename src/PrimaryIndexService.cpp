#include "PrimaryIndexService.h"

#include <algorithm>
#include <cstring>
#include <fstream>

#include "primaryIndex.h"

using namespace std;

PrimaryIndexService::PrimaryIndexService(string fileName) {
  this->fileName = fileName;
  fstream fin(fileName, ios::in);
  if (!fin.is_open()) {
    fin.open(fileName, ios::out | ios::binary);
    fin.close();
    return;
  }
  primaryIndex index;
  while (!fin.eof()) {
    fin.read(index.Id, 15);
    fin.read((char*)&index.offset, sizeof(index.offset));
    primaryIndexs.push_back(index);
  }

  fin.close();
}

int PrimaryIndexService::getById(string id) {
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

vector<int> PrimaryIndexService::getByIds(vector<string> id) {
  vector<int> offsets;
  for (string idx : id) {
    offsets.push_back(getById(idx));
  }
  return offsets;
}

void PrimaryIndexService::printIndexs() {
  for (primaryIndex index : primaryIndexs) {
    cout << index.Id << " " << index.offset << endl;
  }
}

int PrimaryIndexService::removeById(string id) {
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

  fstream fin(fileName, ios::out);
  for (int i = 0; i < primaryIndexs.size(); i++) {
    fin.write(primaryIndexs[i].Id, 15);
    fin.write((char*)&primaryIndexs[i].offset, sizeof(int));
  }

  return -1;
}

void PrimaryIndexService::addIndex(string id, int offset) {
  primaryIndex index;
  strcpy(index.Id, id.c_str());
  index.offset = offset;
  primaryIndexs.push_back(index);
  sort(primaryIndexs.begin(), primaryIndexs.end());
  fstream fin(fileName, ios::out);
  for (int i = 0; i < primaryIndexs.size(); i++) {
    fin.write(primaryIndexs[i].Id, 15);
    fin.write((char*)&primaryIndexs[i].offset, sizeof(int));
  }
}