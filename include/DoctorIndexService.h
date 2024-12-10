#ifndef DOCTOR_INDEX_SERVICE_H
#define DOCTOR_INDEX_SERVICE_H
#include "PrimaryIndexService.h"

class DoctorIndexService : public PrimaryIndexService {
 private:
    static DoctorIndexService *instance;
    DoctorIndexService() : PrimaryIndexService("doctorprimaryindex.txt") {}
public:
    static DoctorIndexService* getInstance() {
        if ( instance == nullptr )
            instance = new DoctorIndexService();
        return instance ;
    }
};

DoctorIndexService* DoctorIndexService::instance = nullptr ;

#endif  // DOCTOR_INDEX_SERVICE_H