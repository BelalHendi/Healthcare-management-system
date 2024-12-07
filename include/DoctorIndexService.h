#ifndef DOCTOR_INDEX_SERVICE_H
#define DOCTOR_INDEX_SERVICE_H
#include "PrimaryIndexService.h"

class DoctorIndexService : public PrimaryIndexService {
 private:
 public:
  DoctorIndexService() : PrimaryIndexService("doctorprimaryindex.txt") {}
};

#endif  // DOCTOR_INDEX_SERVICE_H