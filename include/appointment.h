#ifndef _appointment_h
#define _appointment_h
#include <fstream>
class appointment {
 public:
  char AppointmentID[15];  // primary key
  char AppointmentDate[30];
  char DoctorID[15];  // secondary key
  appointment();
  // void Read(fstream& stream);
  // void Write(fstream& stream);
};

#endif