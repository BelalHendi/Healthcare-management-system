#ifndef _appointmentIndexService_h_
#define _appointmentIndexService_h_
#include "PrimaryIndexService.h"

class AppointmentIndexService : public PrimaryIndexService {
 private:
 public:
  AppointmentIndexService()
      : PrimaryIndexService("appointmentIndexService.txt") {}
};

#endif