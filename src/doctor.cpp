#include "doctor.h"

#include <cstring>
#include <strstream>
#include <iostream>
doctor::doctor() {
  memset(id, '\0', sizeof(id));
  memset(name, '\0', sizeof(name));
  memset(address, '\0', sizeof(address));
  nextRec = -1;
}

int doctor::Write(fstream& stream) {
  char* record = new char[80];
  memset(record, '\0', sizeof(record));
  strcat(record, this->id);
  strcat(record, "|");
  strcat(record, this->name);
  strcat(record, "|");
  strcat(record, this->address);
  strcat(record, "|");
  short length = strlen(record);
  int offset = stream.tellp();
//  cout<< "cur_off: " << stream.tellp() << endl;
  stream.write((char*)&length, sizeof(short));
  stream.write((char*)&nextRec, sizeof(int));
  stream.put(' ');
  stream.write(record, length);
  delete[] record;
  return offset;
}

void doctor::Read(fstream& stream) {
  short length;
  stream.read((char*)&length, sizeof(short));
  stream.seekg(5, ios::beg);
  char* record = new char[length];
  stream.read(record, length);
  istrstream strbuff(record);
  string str;
  strbuff >> str;
  strcpy(this->id, str.c_str());
  strbuff >> str;
  strcpy(this->name, str.c_str());
  strbuff >> str;
  strcpy(this->address, str.c_str());
  delete[] record;
}