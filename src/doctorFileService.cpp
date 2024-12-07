#include "doctorFileService.h"

#include "doctor.h"

doctorFileService::doctorFileService() {
  fstream fout("doctors.txt", ios::in | ios::out);
  if (!fout.is_open()) {
    fout.open("doctors.txt", ios::out );
    int header = -1;
    fout.write((char *)&header, sizeof(header));
    fout.close();
    fout.open("doctors.txt", ios::out | ios::in );
  }

  fout.close();
}

// I changed the return type to void and made function doc.Write return int
// instead. fell free to change this if needed there is a variable int off.
int doctorFileService::addDoctor(string id, string name, string address) {
  doctor doc;
  strcpy(doc.id, id.c_str());
  strcpy(doc.name, name.c_str());
  strcpy(doc.address, address.c_str());
  short len = id.size() + name.size() + address.size() + 3;
  //    cout<< "cur_len: " <<  len << endl;
  int header = -1;
  fstream fout("doctors.txt", ios::in | ios::out);
  fout.read((char *)&header, sizeof(header));
  bool found = false;
  int prev = -2;
  int off = -1;
  short freeSpace = 0;
  if (header == -1) {
    fout.seekp(0, ios::end);
    return doc.Write(fout);
  } else {
    while (header != -1 && !found) {
      fout.seekg(header, ios::beg);
      fout.read((char *)&freeSpace, sizeof(short));
      if (freeSpace >= len) {
        found = true;
        break;
      }
      prev = header;
      fout.read((char *)&header, sizeof(int));
    }
  }
  if (found) {
    // get the next in availlist.
    fout.seekg(header + 2, ios::beg);
    int nxt_avail;
    fout.read((char *)&nxt_avail, sizeof(nxt_avail));
    // insert the new record
    fout.seekp(header, ios::beg);
    off = doc.Write(fout);  // use it to update index
    // reclaiming space.
    if (freeSpace - len >= 5) {
      short new_space = freeSpace - len;
      fout.write((char *)&new_space, sizeof(new_space));
      fout.write((char *)&nxt_avail, sizeof(nxt_avail));
      // prev is the header.
      fout.seekp(prev + 2, ios::beg);
      int new_off = header + len;
      fout.write((char *)&new_off, sizeof(int));
    } else {
      fout.seekp(prev + 2, ios::beg);
      fout.write((char *)&nxt_avail, sizeof(nxt_avail));
    }
  } else {
    fout.seekp(0, ios::end);
    off = doc.Write(fout);  // use it to update index
  }
  return off;
}

void doctorFileService::deleteDoctor(int offset) {
  int header = -1;
  fstream fout("doctors.txt", ios::in | ios::out);
  fout.seekp(0, ios::beg);
  fout.read((char *)&header, sizeof(header));
  fout.seekp(0, ios::beg);
  fout.write((char *)&offset, sizeof(int));
  fout.seekp(offset + 2, ios::beg);
  fout.write((char *)&header, sizeof(int));
  fout.put('*');
}