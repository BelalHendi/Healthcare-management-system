#ifndef _DOCTORFILESERVICE_H
#define _DOCTORFILESERVICE_H
#include <string>

#include "doctor.h"
#include "fileService.h"

class DoctorFileService : public FileService {
 protected:
  int writeRecord(fstream &file, const string &field1, const string &field2,
                  const string &field3) override;

 public:
  DoctorFileService();
};

#endif