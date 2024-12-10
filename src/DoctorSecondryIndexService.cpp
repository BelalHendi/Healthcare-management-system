#include "DoctorSecondryIndexService.h"

doctorSecondryIndexService* doctorSecondryIndexService::instance = nullptr ;

doctorSecondryIndexService::doctorSecondryIndexService(): SI(DOCTOR){}

doctorSecondryIndexService* doctorSecondryIndexService::getInstance() {
    if ( instance == nullptr ) {
        instance = new doctorSecondryIndexService();
    }
    return instance ;
}


