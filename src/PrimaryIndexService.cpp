#include "PrimaryIndexService.h"

#include <algorithm>
#include <cstring>
#include <fstream>

#include "primaryIndex.h"

using namespace std;

int PrimaryIndexService::insertPrimaryIndex( primaryIndex index ) {
  primaryIndexs.push_back(index);
  int j = primaryIndexs.size() - 2;
  while ( j >= 0 && strcmp(primaryIndexs[j].Id, primaryIndexs[j + 1].Id) > 0  ) {
    swap(primaryIndexs[j], primaryIndexs[j + 1]);
    j-- ;
  }
  return j + 1 ;
}

void PrimaryIndexService::bubbleDown( int RRN ) {
  fstream file ( fileName , ios_base::in | ios_base::out );
  file.seekp ( RRN * 19 );
  for ( int i = RRN ; i < primaryIndexs.size() ; i++ ) {
    file.write( primaryIndexs[i].Id , 15 );
    file.write( (char*)& primaryIndexs[i].offset , sizeof(int) );
  }

  file.close() ;
}
void PrimaryIndexService::bubbleup( int RRN ) {
  ofstream trunc (fileName, ios::out ) ;
  for ( const primaryIndex& index : primaryIndexs ) {
    trunc.write(index.Id , 15 );
    trunc.write( (char*)& index.offset , sizeof(int) );
  }
}

PrimaryIndexService::PrimaryIndexService(string fileName) {
  this->fileName = fileName;
  fstream fin(fileName, ios::in);
  if (!fin.is_open()) {
    fin.open(fileName, ios::out );
    fin.close();
    return;
  }
  primaryIndex index;
  while (fin.read(index.Id, 15) && fin.read((char*)&index.offset, sizeof(index.offset)) ) {
    primaryIndexs.push_back(index);
  }

  fin.close();
}

int PrimaryIndexService::getById(string id) {
  char charId[15];
  memset(charId, '\0', 15);
  strcpy(charId, id.c_str());
  int l = 0;
  int r = primaryIndexs.size() - 1;
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
  int offset = -1 ;
  int mid = 0;
  while (l <= r) {
    mid = ( l + r ) / 2;
    int cmp = strcmp(primaryIndexs[mid].Id, charId);
    if (cmp == 0) {
      offset = primaryIndexs[mid].offset;
      primaryIndexs.erase(primaryIndexs.begin() + mid);
      break;
    } else if (cmp < 0) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }

  bubbleup( mid );

  return offset;
}

void PrimaryIndexService::addIndex(string id, int offset) {
  primaryIndex index;
  strcpy(index.Id, id.c_str());
  index.offset = offset;
  const int RRN = insertPrimaryIndex(index) ;
  bubbleDown( RRN ) ;
}