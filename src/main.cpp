#include <bits/stdc++.h>

#include "PrimaryIndexService.h"
#include "doctorFileService.h"
using namespace std;

int main() {
  doctorFileService service;
  PrimaryIndexService doctorIndex("doctorprimaryindex.txt");
  cout << "First Insertion: \n";
  doctorIndex.addIndex("1", service.addDoctor("1", "omar", "gol gamal"));
  doctorIndex.addIndex("2", service.addDoctor("2", "osama", "ard el lwa"));
  doctorIndex.addIndex("3", service.addDoctor("3", "hassan", "mazl2an"));
  doctorIndex.printIndexs();
  //   cout << "Second Insertion: \n";
  //   service.addDoctor("2", "osama", "ard el lwa");
  //   service.addDoctor("3", "hassan", "mazl2an");
  return 0;
}