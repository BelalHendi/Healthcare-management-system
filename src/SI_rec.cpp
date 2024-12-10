#include "SI_rec.h"

SI_rec::SI_rec (string SK_value, int pointer_value = -1) {
    SK = SK_value;
    pointer = pointer_value;
}

bool SI_rec::operator< (const SI_rec& index) const {
    return this->SK < index.SK;
}