#include "appointment.h"

#include <cstring>
#include <strstream>

using namespace std;
appointment::appointment() {
  memset(AppointmentID, '\0', sizeof(AppointmentID));
  memset(AppointmentDate, '\0', sizeof(AppointmentDate));
  memset(DoctorID, '\0', sizeof(DoctorID));
  nextRec = -1;
}

int appointment::Write(fstream& stream) {
  char* record = new char[65];
  memset(record, '\0', sizeof(record));
  strcat(record, this->AppointmentID);
  strcat(record, "|");
  strcat(record, this->AppointmentDate);
  strcat(record, "|");
  strcat(record, this->DoctorID);
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

void appointment::Read(fstream& stream) {
  short length;
  stream.read((char*)&length, sizeof(short));
  stream.seekg(5, ios::beg);
  char* record = new char[length];
  stream.read(record, length);
  istrstream strbuff(record);
  string str;
  strbuff >> str;
  strcpy(this->AppointmentID, str.c_str());
  strbuff >> str;
  strcpy(this->AppointmentDate, str.c_str());
  strbuff >> str;
  strcpy(this->DoctorID, str.c_str());
  delete[] record;
}