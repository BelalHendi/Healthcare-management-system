//
// Created by omaro on 12/10/2024.
//
#ifndef DOCTOR_SECONDRY_INDEX_SERVICE
#define DOCTOR_SECONDRY_INDEX_SERVICE
#include "SI.h"

class doctorSecondryIndexService : public SI {
    private:
    static doctorSecondryIndexService* instance;
    doctorSecondryIndexService();
    public:
    static doctorSecondryIndexService* getInstance();
} ;

#endif
