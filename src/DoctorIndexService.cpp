#include "PrimaryIndexService.h"

class DoctorIndexService : public PrimaryIndexService {
 private:
 public:
  DoctorIndexService() : PrimaryIndexService("doctorprimaryindex.txt") {}
};
