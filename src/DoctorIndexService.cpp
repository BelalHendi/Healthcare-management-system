#include "DoctorIndexService.h"

DoctorIndexService* DoctorIndexService::instance = nullptr ;

DoctorIndexService::DoctorIndexService() : PrimaryIndexService("doctorprimaryindex.txt") {}

DoctorIndexService* DoctorIndexService::getInstance() {
    if ( instance == nullptr )
        instance = new DoctorIndexService();
    return instance ;
}
