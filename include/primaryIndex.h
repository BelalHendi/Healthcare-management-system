#ifndef _primary_index_h
#define _primary_index_h
#include <cstring>

class primaryIndex {
 public:
  char Id[15];
  int offset;
  primaryIndex() { memset(Id, '\0', 15); }
  bool operator<(const primaryIndex& index) const {
    return strcmp(this->Id, index.Id) < 0;
  }
};

#endif