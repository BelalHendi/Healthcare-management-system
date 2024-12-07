#ifndef _FILESERVICE_H
#define _FILESERVICE_H

#include <fstream>
#include <string>
using namespace std;

class FileService {
private:
    string filePath;

protected:
    virtual int writeRecord(fstream &file, const string &field1, const string &field2, const string &field3) = 0;

public:
    FileService(const string &path);

    void addRecord(const string &field1, const string &field2, const string &field3);

    void deleteRecord(int offset);

    void updateRecord(int offset, const string &field1, const string &field2, const string &field3);

};

#endif
