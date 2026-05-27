#include "Data.h"
using namespace std;

Data::Data() : zi(0), luna(0), an(0) {}

Data::Data(int z, int l, int a) : zi(z), luna(l), an(a) {}

int Data::getZi() const {
     return zi; 
    }
int Data::getLuna() const {
     return luna; 
    }
int Data::getAn() const {
     return an; 
    }

bool Data::esteValida() const {
    return (zi >= 1 && zi <= 31 &&
            luna >= 1 && luna <= 12 &&
            an >= 2020);
}

ostream& operator<<(ostream& out, const Data& d) {
    out << d.zi << "/" << d.luna << "/" << d.an;
    return out;
}