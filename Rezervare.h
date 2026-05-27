#pragma once

#include <iostream>
#include <string>
#include "Sala.h"
#include "Data.h"

using namespace std;

class Rezervare {
private:
    int id;
    Sala sala;
    Data data;
    string nume;
    string prenume;
    double pret;

public:
    Rezervare();//constructor implicit
    Rezervare(int, const Sala&, const Data&, string, string, double);

    int getID() const;
    Sala getSala() const;
    Data getData() const;
    string getNume() const;
    string getPrenume() const;
    double getPretTotal() const;

    friend ostream& operator<<(ostream&, const Rezervare&);
};