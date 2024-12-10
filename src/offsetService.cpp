#include "offsetService.h"

#include <fstream>
using namespace std;
vector<appointment> offsetService::offsetToAppointments(vector<int> offsets) {
  fstream fin(appointmentFilePath, ios::in);
  vector<appointment> appointments;
  for (int i = 0; i < offsets.size(); i++) {
    appointment appointment;
    fin.seekg(offsets[i]);
    appointment.Read(fin);
    appointments.push_back(appointment);
  }
  return appointments;
}

vector<doctor> offsetService::offsetToDoctors(vector<int> offsets) {
  fstream fin(doctorFilePath, ios::in);
  vector<doctor> doctors;
  for (int i = 0; i < offsets.size(); i++) {
    doctor doctor;
    fin.seekg(offsets[i] , ios::beg);
    doctor.Read(fin);
    doctors.push_back(doctor);
  }
  return doctors;
}

