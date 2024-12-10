//
// Created by omaro on 12/7/2024.
//
#include "AppointmentIndexService.h"
#include "DoctorIndexService.h"
#include "appointmentFileService.h"
#include "doctorFileService.h"
#include "offsetService.h"
#include "SI.h"
#include "dataFileType.h"
#ifndef UISERVICE_H
#define UISERVICE_H

class uiservice {
 private:
  DoctorFileService doctorFileService;
  AppointmentFileService appointmentFileService;
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
