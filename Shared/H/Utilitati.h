#pragma once

#include <vector>
#include <string>
#include "../H/Sala.h"
#include "../H/Rezervare.h"
#include "../H/Data.h"

using namespace std;

// SALI
void citireSali(vector<Sala>&);
void salvareSali(const vector<Sala>&);
void afisareSali(const vector<Sala>&);
bool stergereSala(vector<Sala>&, int);
void afisareDisponibile(const vector<Sala>&);

// REZERVARI
void citireRezervari(vector<Rezervare>&, const vector<Sala>&);
void salvareRezervari(const vector<Rezervare>&);
void afisareRezervari(const vector<Rezervare>&);

bool adaugareRezervare(
    vector<Rezervare>&,
    vector<Sala>&,
    int,int,int,int,int,
    const string&,
    const string&
);

void stergereRezervare(vector<Rezervare>&, int);

// LOGICA
double incasariTotale(const vector<Rezervare>&);
int genereazaID(const vector<Rezervare>&);

// VALIDARI
bool numarPozitiv(int);
bool numarPozitivDouble(double);
bool textValid(const string&);
bool dataCalendaristicaValida(const Data&);
bool dataValidaViitor(const Data&);
bool existaRezervare(const vector<Rezervare>&, int, const Data&);
bool existaSala(const vector<Sala>&, int);