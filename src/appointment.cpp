#include "appointment.h"

#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

appointment::appointment() {
  memset(AppointmentID, '\0', sizeof(AppointmentID));
  memset(AppointmentDate, '\0', sizeof(AppointmentDate));
  memset(DoctorID, '\0', sizeof(DoctorID));
}

void appointment::Write(fstream& stream) {
  char record[61];
  record[0] = '\0';

  strcat(record, this->AppointmentID);
  strcat(record, "|");
  strcat(record, this->AppointmentDate);
  strcat(record, "|");
  strcat(record, this->DoctorID);
  strcat(record, "|");

  short length = strlen(record);

  stream.write((char*)&length, sizeof(short));
  stream.write(record, length);
}

void appointment::Read(fstream& stream) {
  short length;
  stream.read((char*)&length, sizeof(short));

  char* record = new char[length + 1];
  stream.read(record, length);
  record[length] = '\0';

  stringstream strbuff(record);
  string field;

  getline(strbuff, field, '|');
  strncpy(this->AppointmentID, field.c_str(), sizeof(AppointmentID) - 1);
  this->AppointmentID[sizeof(AppointmentID) - 1] = '\0';

  getline(strbuff, field, '|');
  strncpy(this->AppointmentDate, field.c_str(), sizeof(AppointmentDate) - 1);
  this->AppointmentDate[sizeof(AppointmentDate) - 1] = '\0';

  getline(strbuff, field, '|');
  strncpy(this->DoctorID, field.c_str(), sizeof(DoctorID) - 1);
  this->DoctorID[sizeof(DoctorID) - 1] = '\0';

  delete[] record;
}