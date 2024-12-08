//
// Created by omaro on 12/7/2024.
//

#include "uiservice.h"

#include <bits/stdc++.h>

#include "AppointmentIndexService.h"
#include "DoctorIndexService.h"
#include "appointmentFileService.h"
#include "doctorFileService.h"

using namespace std;

void uiservice::addDoctor() {
  string id, name, address;
  cout << "Enter id , name , address : ";
  cin >> id >> name >> address;
  id = id.substr(0, 15);
  name = name.substr(0, 30);
  address = address.substr(0, 30);

  if (doctorIndexService.getById(id) != -1) {
    cout << "the id is being is being used by a diffirent entity!\n";
    return;
  }
  int offset = doctorFileService.addRecord(id, name, address);
  doctorIndexService.addIndex(id, offset );
}

void uiservice::updateDoctor() {
  cout << "Enter Doctor id :";
  string id;
  cin >> id;
  int offset = doctorIndexService.getById(id);
  if (offset == -1) {
    cout << "there is no entity with this id!\n";
    return;
  }
  cout << "Enter new name : ";
  string name;
  cin >> name;
  vector<int> offsets;
  offsets.push_back(offset);
  doctor doctor = offsetService.offsetToDoctors(offsets).back();
  doctorFileService.deleteRecord(offset);
  doctorIndexService.removeById(id);
  offset = doctorFileService.addRecord(doctor.id, name, doctor.address);
  doctorIndexService.addIndex(id, offset);
}

void uiservice::deleteDoctor() {
  string id;
  cout << "Enter the id you wish to remove : ";
  cin >> id;
  int offset = doctorIndexService.getById(id);
  if (offset == -1) {
    cout << "there is no entity with this id!\n";
    return;
  }
  doctorIndexService.removeById(id);
  doctorFileService.deleteRecord(offset);
}

void uiservice::addAppointment() {
  string id, date, doctorID;
  cout << "Enter id , name , doctor id : ";
  cin >> id >> date >> doctorID;
  id = id.substr(0, 15);
  date = date.substr(0, 30);
  doctorID = doctorID.substr(0, 15);

  if (appointmentIndexService.getById(id) != -1) {
    cout << "the id is being is being used by a diffirent entity!\n";
    return;
  }
  cout << "asd" << '\n';
  appointmentIndexService.addIndex(
      id, appointmentFileService.addRecord(id, date, doctorID));
}

void uiservice::updateAppointment() {
  cout << "Enter Appointment id :";
  string id;
  cin >> id;
  int offset = appointmentIndexService.getById(id);
  if (offset == -1) {
    cout << "there is no entity with this id!\n";
    return;
  }
  cout << "Enter new Date : ";
  string date;
  cin >> date;
  vector<int> offsets;
  offsets.push_back(offset);
  appointment appointment = offsetService.offsetToAppointments(offsets).back();
  appointmentFileService.deleteRecord(offset);
  appointmentIndexService.removeById(id);
  offset = appointmentFileService.addRecord(appointment.AppointmentID,
                                            date,
                                            appointment.DoctorID);
  appointmentIndexService.addIndex(id, offset);
}

void uiservice::deleteAppointment() {
  string id;
  cout << "Enter the id of the record you wish to delete : " << '\n';
  cin >> id;
  int offset = appointmentIndexService.getById(id);
  if (offset == -1) {
    cout << "there is no entity with this id!\n";
    return;
  }
  appointmentIndexService.removeById(id);
  appointmentFileService.deleteRecord(offset);
}

void uiservice::printDoctorInfo() {
  string DoctorId;
  cout << "Enter doctor id: ";
  cin >> DoctorId;
  int offset = doctorIndexService.getById(DoctorId);
  vector<int> vec;
  vec.push_back(offset);
  vector<doctor> appointments = offsetService.offsetToDoctors(vec);

  for (doctor doc : appointments) {
    cout << "Doctor Info:" << endl;
    cout << "ID: " << doc.id << endl;
    cout << "Name: " << doc.name << endl;
    cout << "Address: " << doc.address << endl;
  }
}

void uiservice::printAppointmentInfo() {
  string appointmentId;
  cout << "Enter appointment ID: ";
  cin >> appointmentId;
  int offset = appointmentIndexService.getById(appointmentId);
  vector<int> vec;
  vec.push_back(offset);
  vector<appointment> appointments = offsetService.offsetToAppointments(vec);

  for (appointment app : appointments) {
    cout << "Appointment Info:" << endl;
    cout << "ID: " << app.AppointmentID << endl;
    cout << "Date: " << app.AppointmentDate << endl;
    cout << "Doctor ID: " << app.DoctorID << endl;
  }
}

void uiservice::run() {
  int choice;

  do {
    // Display the menu
    cout << "\nMenu Options:" << endl;
    cout << "1. Add New Doctor" << endl;       // done // tested
    cout << "2. Add New Appointment" << endl;  // done // tested
    cout << "3. Update Doctor Name (Doctor ID)" << endl;  // done // tested
    cout << "4. Update Appointment Date (Appointment ID)" << endl;  // done // tested
    cout << "5. Delete Appointment (Appointment ID)" << endl;      // done // tested
    cout << "6. Delete Doctor (Doctor ID)" << endl;                // done // tested
    cout << "7. Print Doctor Info (Doctor ID)" << endl;            // done // tested
    cout << "8. Print Appointment Info (Appointment ID)" << endl;  // done // tested
    cout << "9. Write Query" << endl;
    cout << "10. Exit" << endl;  // done // tested

    // Get user choice
    cout << "Enter your choice: ";
    cin >> choice;

    // Handle options with switch
    if (choice == 1) {
      addDoctor();
    } else if (choice == 2) {
      addAppointment();
    } else if (choice == 3) {
      updateDoctor();
    } else if (choice == 4) {
      updateAppointment();
    } else if (choice == 5) {
      deleteAppointment();
    } else if (choice == 6) {
      deleteDoctor();
    } else if (choice == 7) {
      printDoctorInfo();
    } else if (choice == 8) {
      printAppointmentInfo();
    } else if (choice == 9) {
      cout << "Writing query..." << endl;
    } else if (choice == 10) {
      cout << "Exiting the program. Goodbye!" << endl;
      break;
    } else {
      cout << "Invalid choice. Please try again." << endl;
    }

  } while (choice != 10);  // Exit when choice is 10
}