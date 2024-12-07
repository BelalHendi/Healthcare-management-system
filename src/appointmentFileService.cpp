#include <fstream>
#include <string>

#include "../include/appointmentFileService.h"

#include <string.h>
AppointmentFileService::AppointmentFileService() : FileService("../output/appointments.txt") {}

int AppointmentFileService::writeRecord(fstream &file, const string &field1, const string &field2, const string &field3) {
    appointment app;
    strcpy(app.AppointmentID, field1.c_str());
    strcpy(app.AppointmentDate, field2.c_str());
    strcpy(app.DoctorID, field3.c_str());
    return app.Write(file);
}
