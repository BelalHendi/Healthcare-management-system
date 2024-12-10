#ifndef DoctorIndexService_h
#define DoctorIndexService_h
#include "PrimaryIndexService.h"

class DoctorIndexService : public PrimaryIndexService {
 private:
    static DoctorIndexService *instance;
    DoctorIndexService() ;
public:
    static DoctorIndexService* getInstance() ;
};

#endif