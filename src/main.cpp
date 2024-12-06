#include <bits/stdc++.h>

#include "doctorFileService.h"

using namespace std;

int main() {
    doctorFileService service;
    cout<< "First Insertion: \n";
    service.addDoctor("1", "omar", "gol gamal");
    service.addDoctor("2", "osama", "ard el lwa");
    service.addDoctor("3", "hassan", "mazl2an");
    service.deleteDoctor(54);
    service.deleteDoctor(28);
    cout<< "Second Insertion: \n";
    service.addDoctor("2", "osama", "ard el lwa");
    service.addDoctor("3", "hassan", "mazl2an");
    return 0;
}