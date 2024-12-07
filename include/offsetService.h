#ifndef _offset_service_h_
#define _offset_service_h_
#include <iostream>
#include <vector>

#include "appointment.h"
#include "doctor.h"
using namespace std;
class offsetService {
 private:
  string doctorFilePath = "doctors.txt";
  string appointmentFilePath = "appointments.txt";

 public:
  vector<appointment> offsetToAppointments(vector<int> offsets);
  vector<doctor> offsetToDoctors(vector<int> offsets);
};

#endif