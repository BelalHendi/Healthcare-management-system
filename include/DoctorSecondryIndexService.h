//
// Created by omaro on 12/10/2024.
//
#include "SI.h"
#ifndef DOCTORSECONDRYINDEXSERVICE_H
#define DOCTORSECONDRYINDEXSERVICE_H

class doctorSecondryIndexService : public SI {
    private:
    static doctorSecondryIndexService* instance;
    doctorSecondryIndexService():SI(DOCTOR){}
    public:
    static doctorSecondryIndexService* getInstance() {
        if ( instance == nullptr ) {
            instance = new doctorSecondryIndexService();
        }
        return instance ;
    }
} ;

doctorSecondryIndexService* doctorSecondryIndexService::instance = nullptr ;

#endif //DOCTORSECONDRYINDEXSERVICE_H
