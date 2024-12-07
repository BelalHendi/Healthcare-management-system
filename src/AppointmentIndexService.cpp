#include "PrimaryIndexService.h"

class AppointmentIndexService : public PrimaryIndexService {
 private:
  /* data */
 public:
  AppointmentIndexService()
      : PrimaryIndexService("appointmentIndexService.txt") {}
};
