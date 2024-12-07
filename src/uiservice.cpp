//
// Created by omaro on 12/7/2024.
//
#include "uiservice.h"

#include <bits/stdc++.h>
using namespace std;
void uiservice::menu() {
  int choice;

  do {
    // Display the menu
    cout << "\nMenu Options:" << endl;
    cout << "1. Add New Doctor" << endl;
    cout << "2. Add New Appointment" << endl;
    cout << "3. Update Doctor Name (Doctor ID)" << endl;
    cout << "4. Update Appointment Date (Appointment ID)" << endl;
    cout << "5. Delete Appointment (Appointment ID)" << endl;
    cout << "6. Delete Doctor (Doctor ID)" << endl;
    cout << "7. Print Doctor Info (Doctor ID)" << endl;
    cout << "8. Print Appointment Info (Appointment ID)" << endl;
    cout << "9. Write Query" << endl;
    cout << "10. Exit" << endl;

    // Get user choice
    cout << "Enter your choice: ";
    cin >> choice;

    // Handle options with switch
    switch (choice) {
      case 1:
        cout << "Adding new doctor..." << endl;
        // Add your logic here
        break;
      case 2:
        cout << "Adding new appointment..." << endl;
        // Add your logic here
        break;
      case 3:
        cout << "Updating doctor name (Doctor ID)..." << endl;
        // Add your logic here
        break;
      case 4:
        cout << "Updating appointment date (Appointment ID)..." << endl;
        // Add your logic here
        break;
      case 5:
        cout << "Deleting appointment (Appointment ID)..." << endl;
        // Add your logic here
        break;
      case 6:
        cout << "Deleting doctor (Doctor ID)..." << endl;
        // Add your logic here
        break;
      case 7:
        cout << "Printing doctor info (Doctor ID)..." << endl;
        // Add your logic here
        break;
      case 8:
        cout << "Printing appointment info (Appointment ID)..." << endl;
        // Add your logic here
        break;
      case 9:
        cout << "Writing query..." << endl;
        // Add your logic here
        break;
      case 10:
        cout << "Exiting the program. Goodbye!" << endl;
        break;
      default:
        cout << "Invalid choice. Please try again." << endl;
    }
  } while (choice != 10);  // Exit when choice is 10
}

void uiservice::run() {}