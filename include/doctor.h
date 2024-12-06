#ifndef _doctor_h_
#define _doctor_h_
#include <fstream>
using namespace std;

class doctor {
 private:
  int nextRec;
  char delted;

 public:
  char Id[15];
  char Name[30];
  char Address[30];
  doctor();
  void Write(fstream&);
  void Read(fstream&);
};

#endif