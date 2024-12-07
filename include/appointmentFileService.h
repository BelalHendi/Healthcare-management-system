#ifndef _APPOINTMENTFILESERVICE_H
#define _APPOINTMENTFILESERVICE_H

#include <string>
#include "fileService.h"
#include "appointment.h"

class AppointmentFileService : public FileService {
protected:
    int writeRecord(fstream &file, const string &field1, const string &field2, const string &field3) override;

public:
    AppointmentFileService();
};

#endif // _APPOINTMENTFILESERVICE_H
