#include "../H/Sala.h"
using namespace std;

Sala::Sala()
    : id(0),
      capacitate(0),
      disponibilitate(true),
      pretBaza(0) {}

Sala::Sala(int i,
           std::string d,
           int c,
           const vector<string>& f,
           bool disp,
           double p)
    : id(i),
      denumire(d),
      capacitate(c),
      facilitati(f),
      disponibilitate(disp),
      pretBaza(p) {}

int Sala::getID() const {
    return id;
}

string Sala::getDenumire() const {
    return denumire;
}

int Sala::getCapacitate() const {
    return capacitate;
}

bool Sala::getDisponibilitate() const {
    return disponibilitate;
}

vector<string> Sala::getFacilitati() const {
    return facilitati;
}

double Sala::getPretBaza() const {
    return pretBaza;
}

void Sala::setDisponibilitate(bool d) {
    disponibilitate = d;
}

ostream& operator<<(ostream& out, const Sala& s) {

    out << s.id << " "
        << s.denumire << " "
        << s.capacitate << " ";

    out << s.facilitati.size() << " ";

    for (const auto& f : s.facilitati)
        out << f << " ";

    out << s.disponibilitate << " "
        << s.pretBaza;

    return out;
}