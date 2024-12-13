#include "appointmentSecondryIndexService.h"

appointmentSecondryIndexService::appointmentSecondryIndexService() : SI(APPOINTMENT){}

appointmentSecondryIndexService* appointmentSecondryIndexService::instance = nullptr ;

appointmentSecondryIndexService* appointmentSecondryIndexService::getInstance() {
    if ( instance == nullptr ) {
        instance = new appointmentSecondryIndexService() ;
    }
    return instance ;
}

void appointmentSecondryIndexService::deleteInstance() {
    delete instance;
}
