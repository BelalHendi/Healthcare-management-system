//
// Created by omaro on 12/10/2024.
//

#ifndef APPOINTMENTSECONDRYINDEXSERVICE_H
#define APPOINTMENTSECONDRYINDEXSERVICE_H
#include "SI.h"

class appointmentSecondryIndexService : public SI{
private :
    static appointmentSecondryIndexService* instance ;
    appointmentSecondryIndexService() : SI(APPOINTMENT) {}
public:
    static appointmentSecondryIndexService* getInstance() {
        if ( instance == nullptr ) {
            instance = new appointmentSecondryIndexService() ;
        }
        return instance ;
    }
};

appointmentSecondryIndexService* appointmentSecondryIndexService::instance = nullptr ;

#endif //APPOINTMENTSECONDRYINDEXSERVICE_H
