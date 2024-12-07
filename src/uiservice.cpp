//
// Created by omaro on 12/7/2024.
//
#include "uiservice.h"

#include <bits/stdc++.h>

#include "DoctorIndexService.cpp"
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
  doctorIndexService.addIndex(id,
                              doctorFileService.addRecord(id, name, address));
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
  appointmentIndexService.addIndex(
      id, appointmentFileService.addRecord(id, date, doctorID));
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
  string id;
  cout << "Enter doctor id : ";
  cin >> id;
}

void uiservice::printAppointmentInfo() {}

void uiservice::menu() {
  int choice;

  do {
    // Display the menu
    cout << "\nMenu Options:" << endl;
    cout << "1. Add New Doctor" << endl;       // done
    cout << "2. Add New Appointment" << endl;  // done
    cout << "3. Update Doctor Name (Doctor ID)" << endl;
    cout << "4. Update Appointment Date (Appointment ID)" << endl;
    cout << "5. Delete Appointment (Appointment ID)" << endl;      // done
    cout << "6. Delete Doctor (Doctor ID)" << endl;                // done
    cout << "7. Print Doctor Info (Doctor ID)" << endl;            // done
    cout << "8. Print Appointment Info (Appointment ID)" << endl;  // done
    cout << "9. Write Query" << endl;
    cout << "10. Exit" << endl;  // done

    // Get user choice
    cout << "Enter your choice: ";
    cin >> choice;

    // Handle options with switch
    if (choice == 1) {
      addDoctor();
    } else if (choice == 2) {
      addAppointment();
    } else if (choice == 3) {
      cout << "Updating doctor name (Doctor ID)..." << endl;
      // Add your logic here
    } else if (choice == 4) {
      cout << "Updating appointment date (Appointment ID)..." << endl;
      // Add your logic here
    } else if (choice == 5) {
      deleteAppointment();
    } else if (choice == 6) {
      deleteDoctor();
    } else if (choice == 7) {
      string id;
      cout << "Enter doctor id : ";
      cin >> id;
      int offset = doctorIndexService.getById(id);
      vector<int> vec;
      vec.push_back(offset);
      vector<doctor> doctors = offsetService.offsetToDoctors(vec);
      for (doctor doc : doctors) {
        cout << "Doctor Info :" << endl;
        cout << "ID: " << doc.id << endl;
        cout << "Name: " << doc.name << endl;
        cout << "Address: " << doc.address << endl;
      }
    } else if (choice == 8) {
      string appointmentId;
      cout << "Enter appointment ID: ";
      cin >> appointmentId;
      int offset = appointmentIndexService.getById(
          appointmentId);  // Assuming appointmentIndexService.getById() returns
                           // the offset
      vector<int> vec;
      vec.push_back(offset);
      vector<appointment> appointments = offsetService.offsetToAppointments(
          vec);  // Retrieve the appointment data

      for (appointment app : appointments) {
        cout << "Appointment Info:" << endl;
        cout << "ID: " << app.AppointmentID << endl;
        cout << "Date: " << app.AppointmentDate << endl;
        cout << "Doctor ID: " << app.DoctorID << endl;
      }
    } else if (choice == 9) {
      cout << "Writing query..." << endl;
    } else if (choice == 10) {
      cout << "Exiting the program. Goodbye!" << endl;
    } else {
      cout << "Invalid choice. Please try again." << endl;
    }

  } while (choice != 10);  // Exit when choice is 10
}

void uiservice::run() {}