#pragma once
#include <vector>
#include "Sala.h"
#include "Rezervare.h"

using namespace std;

template <typename T>
void raportRezervari(const vector<T>& );

void citireSali(vector<Sala>&);
void salvareSali(const vector<Sala>&);

void afisareSali(const vector<Sala>&);
void stergereSala(vector<Sala>&, int);

void cautareSali(const vector<Sala>&, int);
void afisareDisponibile(const vector<Sala>&);

void citireRezervari(vector<Rezervare>&);
void salvareRezervari(const vector<Rezervare>&);
void afisareRezervari(const vector<Rezervare>&);