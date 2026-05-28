#include "../H/Rezervare.h"
using namespace std;
Rezervare::Rezervare() : id(0), pret(0) {}

Rezervare::Rezervare(int i, const Sala& s, const Data& d,
                     string n, string p, double pr)
    : id(i), sala(s), data(d), nume(n), prenume(p), pret(pr) {}

int Rezervare::getID() const {
     return id; 
    }
Sala Rezervare::getSala() const {
     return sala; 
    }
Data Rezervare::getData() const {
     return data; 
    }
string Rezervare::getNume() const {
     return nume; 
    }
string Rezervare::getPrenume() const {
     return prenume; 
    }
double Rezervare::getPretTotal() const {
     return pret; 
    }

ostream& operator<<(ostream& out, const Rezervare& r) {
    out << r.id << " "
        << r.sala.getDenumire() << " "
        << r.nume << " "
        << r.prenume << " "
        << r.data << " "
        << r.pret;
    return out;
}