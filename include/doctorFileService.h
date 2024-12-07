#ifndef _doctor_file_service_h_
#define _doctor_file_service_h_
#include <cstring>

#include "doctor.h"
class doctorFileService {
 public:
  doctorFileService();
  int addDoctor(string id, string name, string address);
  void deleteDoctor(int offset);
};

#endif