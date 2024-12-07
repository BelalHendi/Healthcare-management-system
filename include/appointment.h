#ifndef _appointment_h
#define _appointment_h
#include <fstream>

class appointment {
 public:
  char AppointmentID[15];
  char AppointmentDate[30];
  char DoctorID[15];
  appointment();
  void Read(fstream& stream);
  void Write(fstream& stream);
};

#endif