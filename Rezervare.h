#pragma once
#include <string>
#include <iostream>
#include "Sala.h"
#include "Data.h"

using namespace std;

class Rezervare {// Clasa care reprezinta o rezervare facuta pentru o sala
private:
    int idRez;
    Sala sala;
    Data data;
    string numeClient;
    string prenumeClient;
    double pretTotal;

public:
    Rezervare();//constructor implicit
    Rezervare(int, Sala, Data, string, string, double);

    int getID() const;
    Sala getSala() const;
    Data getData() const;
    string getNumeClient() const;
    string getPrenumeClient() const;
    double getPretTotal() const;

    friend ostream& operator<<(ostream&, const Rezervare&);
};