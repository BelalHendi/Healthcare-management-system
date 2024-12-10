#ifndef _appointmentIndexService_h_
#define _appointmentIndexService_h_
#include "PrimaryIndexService.h"

class AppointmentIndexService : public PrimaryIndexService {
 private:
    static AppointmentIndexService* instance ;
    AppointmentIndexService()
      : PrimaryIndexService("appointmentIndexService.txt") {}
 public:
    static AppointmentIndexService* getInstance() {
        if ( instance == nullptr )
            instance = new AppointmentIndexService();
        return instance;
    }
};

AppointmentIndexService* AppointmentIndexService::instance = nullptr ;

#endif