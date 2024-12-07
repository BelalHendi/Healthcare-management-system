#include "fileService.h"

#include <fstream>
#include <string>

FileService::FileService(const string &path) : filePath(path) {
  fstream fout(filePath, ios::in | ios::out | ios::binary);
  fout.close();
  if (!fout.is_open()) {
    fout.open(filePath, ios::out | ios::in | ios::binary);
    int header = -1;
    fout.write((char *)&header, sizeof(header));
    fout.close();
  }
}

int FileService::addRecord(const string &field1, const string &field2,
                           const string &field3) {
  short len = field1.size() + field2.size() + field3.size() + 3;
  int header = -1;
  fstream fout(filePath, ios::in | ios::out | ios::binary);
  fout.read((char *)&header, sizeof(header));
  bool found = false;
  int prev = -2;
  short freeSpace = 0;

  if (header == -1) {
    fout.seekp(0, ios::end);
    return writeRecord(fout, field1, field2, field3);
  } else {
    while (header != -1 && !found) {
      fout.seekg(header, ios::beg);
      fout.read((char *)&freeSpace, sizeof(short));
      if (freeSpace >= len) {
        found = true;
        break;
      }
      prev = header;
      fout.read((char *)&header, sizeof(int));
    }
  }

  if (found) {
    fout.seekg(header + 2, ios::beg);
    int nextAvailable;
    fout.read((char *)&nextAvailable, sizeof(nextAvailable));
    fout.seekp(header, ios::beg);
    if (freeSpace - len >= 5) {
      short newSpace = freeSpace - len;
      fout.write((char *)&newSpace, sizeof(newSpace));
      fout.write((char *)&nextAvailable, sizeof(nextAvailable));
      fout.seekp(prev + 2, ios::beg);
      int newOffset = header + len;
      fout.write((char *)&newOffset, sizeof(int));
    } else {
      fout.seekp(prev + 2, ios::beg);
      fout.write((char *)&nextAvailable, sizeof(nextAvailable));
    }
    return writeRecord(fout, field1, field2, field3);
  } else {
    fout.seekp(0, ios::end);
    return writeRecord(fout, field1, field2, field3);
  }
}

string FileService::deleteRecord(int offset) {
  int header = -1;
  fstream fout(filePath, ios::in | ios::out | ios::binary);
  fout.seekp(0, ios::beg);
  fout.read((char *)&header, sizeof(header));
  fout.seekp(0, ios::beg);
  fout.write((char *)&offset, sizeof(int));
  fout.seekp(offset + 2, ios::beg);
  fout.write((char *)&header, sizeof(int));
  fout.put('*');
  string id;
  return id;
}
