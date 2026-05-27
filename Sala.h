#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Sala {
private:
    int id;
    string denumire;
    int capacitate;

    vector<string> facilitati;

    bool disponibilitate;
    double pretBaza;

public:
    Sala();

    Sala(int,
         string,
         int,
         const vector<string>&,
         bool,
         double);

    int getID() const;
    string getDenumire() const;
    int getCapacitate() const;
    bool getDisponibilitate() const;

    vector<string> getFacilitati() const;

    double getPretBaza() const;

    void setDisponibilitate(bool);

    friend ostream& operator<<(ostream&, const Sala&);
};