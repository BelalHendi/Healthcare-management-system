#include "doctor.h"

#include <cstring>
#include <strstream>

doctor::doctor() {
  memset(Id, '\0', sizeof(Id));
  memset(Name, '\0', sizeof(Name));
  memset(Address, '\0', sizeof(Address));
  nextRec = -1;
}

void doctor::Write(fstream& stream) {
  char* record = new char[78];
  memset(record, '\0', sizeof(record));
  strcat(record, this->Id);
  strcat(record, "|");
  strcat(record, this->Name);
  strcat(record, "|");
  strcat(record, this->Address);
  strcat(record, "|");
  short length = strlen(record);
  stream.write((char*)&length, sizeof(short));
  stream.write((char*)&nextRec, sizeof(int));
  stream.put(' ');
  stream.write(record, length);
  delete[] record;
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
  strcpy(this->Id, str.c_str());
  strbuff >> str;
  strcpy(this->Name, str.c_str());
  strbuff >> str;
  strcpy(this->Address, str.c_str());
  delete[] record;
}