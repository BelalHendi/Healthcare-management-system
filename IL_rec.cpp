#include "IL_rec.h"

IL_rec::IL_rec (int RRN_value, string PK_value, int ptr_value, bool is_deleted_value) {
    RRN = RRN_value;
    PK = PK_value;
    pointer = ptr_value;
    is_deleted = is_deleted_value;
}

IL_rec& IL_rec::operator= (const IL_rec &other) {
    this->RRN = other.RRN;
    this->PK = other.PK;
    this->pointer = other.pointer;
    this->is_deleted = other.is_deleted;
    return *this;
}