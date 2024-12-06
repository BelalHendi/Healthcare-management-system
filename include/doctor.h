#ifndef _doctor_h_
#define _doctor_h_
#include <fstream>
using namespace std;

class doctor {
 private:
  int nextRec;
  char deleted;

 public:
  char id[15];
  char name[30];
  char address[30];
  const int max_record_length = 100;
  doctor();
  int Write(fstream&);
  void Read(fstream&);
};

#endif