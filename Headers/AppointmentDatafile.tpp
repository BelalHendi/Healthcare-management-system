// Created by pc on 12/5/2024.
#include <iostream>
#include <fstream>
using namespace std;
struct Appointment{
    char AppointmentID[15]; //primary key
    char AppointmentDate[30];
    char DoctorID[15];// secondary key
};

class AppointmentFile{
private:
    fstream file;
};
#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_APPOINTMENTDATAFILE_TPP
#define HEALTHCARE_MANAGEMENT_SYSTEM_APPOINTMENTDATAFILE_TPP

#endif //HEALTHCARE_MANAGEMENT_SYSTEM_APPOINTMENTDATAFILE_TPP
