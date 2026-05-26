#pragma once
#include <string>
#include <iostream>

using namespace std;

class Sala {// Clasa care modeleaza o sala de evenimente
private:
    int id;
    string denumire;
    int capacitate;
    string f1, f2, f3;
    bool disponibilitate;
    double pretBaza;

public:
    Sala();//constructor implicit
    Sala(int, string, int, string, string, string, bool, double);

    int getID() const;
    string getDenumire() const;
    int getCapacitate() const;
    bool getDisponibilitate() const;

    string getF1() const;
    string getF2() const;
    string getF3() const;
    double getPretBaza() const;

    void setDisponibilitate(bool);

    friend ostream& operator<<(ostream&, const Sala&);// Supraincarcare operator pentru afisarea obiectului intr-un format usor de citit
};