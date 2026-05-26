#include "Sala.h"

Sala::Sala() {
    id = 0;
    denumire = "";
    capacitate = 0;
    f1 = f2 = f3 = "";
    disponibilitate = true;
    pretBaza = 0;
}

Sala::Sala(int i, string d, int c, string a, string b, string c3, bool disp, double p) {
    id = i;
    denumire = d;
    capacitate = c;
    f1 = a;
    f2 = b;
    f3 = c3;
    disponibilitate = disp;
    pretBaza = p;
}

int Sala::getID() const { return id; }
string Sala::getDenumire() const { return denumire; }
int Sala::getCapacitate() const { return capacitate; }
bool Sala::getDisponibilitate() const { return disponibilitate; }

string Sala::getF1() const { return f1; }
string Sala::getF2() const { return f2; }
string Sala::getF3() const { return f3; }
double Sala::getPretBaza() const { return pretBaza; }

void Sala::setDisponibilitate(bool d) {
    disponibilitate = d;
}

ostream& operator<<(ostream& out, const Sala& s) {
    out << s.id << " "
        << s.denumire << " "
        << s.capacitate << " "
        << s.f1 << " "
        << s.f2 << " "
        << s.f3 << " "
        << s.disponibilitate << " "
        << s.pretBaza;
    return out;
}