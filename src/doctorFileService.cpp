#include "doctorFileService.h"

#include <string.h>

#include <fstream>
#include <string>

DoctorFileService::DoctorFileService() : FileService("doctors.txt") {}

int DoctorFileService::writeRecord(fstream &file, const string &field1,
                                   const string &field2, const string &field3) {
  doctor doc;
  strcpy(doc.id, field1.c_str());
  strcpy(doc.name, field2.c_str());
  strcpy(doc.address, field3.c_str());
  return doc.Write(file);
}
