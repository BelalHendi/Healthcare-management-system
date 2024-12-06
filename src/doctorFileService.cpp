#include "doctorFileService.h"

#include "doctor.h"

doctorFileService::doctorFileService() {
  fstream fout("doctors.txt", ios::in);
  if (!fout.is_open()) {
    fout.close();
    fout.open("doctors.txt", ios::out);
    int headerPointer = -1;
    fout.write((char*)&headerPointer, sizeof(int));
  }
  fout.close();
}

int doctorFileService::addDoctor(string Id, string Name, string Address) {
  doctor doc;
  strcpy(doc.Id, Id.c_str());
  strcpy(doc.Name, Name.c_str());
  strcpy(doc.Address, Address.c_str());
  int len = Id.size() + Name.size() + Address.size() + 3;

  // fstream fout("doctors.txt", ios::in | ios::out);
  // int header = -1;
  // fout.read((char*)&header, sizeof(int));
  // bool found = false;
  // if (header == -1) {
  //   fout.seekp(0, ios::end);
  //   doc.Write(fout);
  // } else {
  //   while (header != -1 && !found) {
  //     fout.seekg(header, ios::beg);
  //     short freeSpace = 0;
  //     int nextPointer = 0;
  //     fout.read((char*)&freeSpace, sizeof(short));
  //     fout.read((char*)&nextPointer, sizeof(int));
  //     if (freeSpace >= len) found = true;
  //   }
  // }
}

// 7     // el size = 9
// 4/ 10 -1 '*'
// 5/ 7 4 '*'
// 7/ 6 5 '*'

// xx 0000 ( ' ' or 'x' ) [] => len(xx)

void doctorFileService::deleteDoctor(int offset) {
  fstream fout("doctors.txt", ios::in | ios::out);
  fout.seekp(0, ios::beg);
  int header = -1;
  fout.read((char*)&header, sizeof(header));
  fout.seekp(0, ios::beg);
  fout.write((char*)&offset, sizeof(int));
  fout.seekp(offset + 2, ios::beg);
  fout.write((char*)&header, sizeof(int));
  fout.put('*');
}