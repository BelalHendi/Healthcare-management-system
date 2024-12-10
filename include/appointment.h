#ifndef _appointment_h
#define _appointment_h
#include <fstream>

using namespace std;
class appointment {
private:
    int nextRec;
    char deleted;

 public:
  char AppointmentID[15];  // primary key
  char AppointmentDate[30];
  char DoctorID[15];  // secondary key
  appointment();
  void Read(fstream& stream);
  int Write(fstream& stream);
};

#endif