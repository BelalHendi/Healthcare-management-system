#ifndef _appointmentIndexService_h_
#define _appointmentIndexService_h_
#include "PrimaryIndexService.h"

class AppointmentIndexService : public PrimaryIndexService {
 private:
    static AppointmentIndexService* instance ;
    AppointmentIndexService();
 public:
    static AppointmentIndexService* getInstance() ;
};


#endif