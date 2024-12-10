//
// Created by omaro on 12/7/2024.
//
#include "AppointmentIndexService.h"
#include "DoctorIndexService.h"
#include "appointmentFileService.h"
#include "doctorFileService.h"
#include "offsetService.h"
#ifndef UISERVICE_H
#define UISERVICE_H

class uiservice {
 private:
  DoctorIndexService doctorIndexService;
  DoctorFileService doctorFileService;
  AppointmentFileService appointmentFileService;
  AppointmentIndexService appointmentIndexService;
  offsetService offsetService;
  void addDoctor();
  void updateDoctor();
  void deleteDoctor();
  void addAppointment();
  void updateAppointment();
  void deleteAppointment();
  void printDoctorInfo();
  void printAppointmentInfo();

 public:
  void run();
};

#endif
