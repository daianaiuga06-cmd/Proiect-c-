#include "Data.h"

Data::Data() {
    zi = luna = an = 0;
}

Data::Data(int z, int l, int a) {
    zi = z;
    luna = l;
    an = a;
}

int Data::getZi() const { return zi; }
int Data::getLuna() const { return luna; }
int Data::getAn() const { return an; }

ostream& operator<<(ostream& out, const Data& d) {
    out << d.zi << "/" << d.luna << "/" << d.an;
    return out;
}