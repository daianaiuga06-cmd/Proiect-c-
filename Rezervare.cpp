#include "Rezervare.h"

Rezervare::Rezervare() {
    idRez = 0;
    numeClient = "";
    prenumeClient = "";
    pretTotal = 0;
}

Rezervare::Rezervare(int id, Sala s, Data d, string nume, string prenume, double p) {
    idRez = id;
    sala = s;
    data = d;
    numeClient = nume;
    prenumeClient = prenume;
    pretTotal = p;
}

int Rezervare::getID() const { return idRez; }
Sala Rezervare::getSala() const { return sala; }
Data Rezervare::getData() const { return data; }
string Rezervare::getNumeClient() const { return numeClient; }
string Rezervare::getPrenumeClient() const { return prenumeClient; }
double Rezervare::getPretTotal() const { return pretTotal; }

ostream& operator<<(ostream& out, const Rezervare& r) {
    out << r.idRez << " "
        << r.sala.getDenumire() << " "
        << r.numeClient << " "
        << r.prenumeClient << " "
        << r.data << " "
        << r.pretTotal;
    return out;
}