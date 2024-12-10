#include "AppointmentIndexService.h"

AppointmentIndexService::AppointmentIndexService() : PrimaryIndexService("appointmentIndexService.txt") {}

AppointmentIndexService* AppointmentIndexService::getInstance() {
    if ( instance == nullptr )
        instance = new AppointmentIndexService();
    return instance;
}

AppointmentIndexService* AppointmentIndexService::instance = nullptr ;
