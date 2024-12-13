#ifndef _appointmentSecondryIndexService_h_
#define _appointmentSecondryIndexService_h_
#include "SI.h"
class appointmentSecondryIndexService : public SI{
private :
    static appointmentSecondryIndexService* instance ;
    appointmentSecondryIndexService() ;
public:
    static appointmentSecondryIndexService* getInstance() ;
    static void deleteInstance() ;
};
#endif

