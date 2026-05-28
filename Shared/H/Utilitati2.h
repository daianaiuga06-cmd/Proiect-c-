#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../H/Sala.h"
#include "../H/Rezervare.h"
#include "../H/Data.h"

using namespace std;

template<typename T>
T maxim(T a, T b) {
    if(a>b){
        return a;
    }
    return b;
}

// SALI
vector<Sala> citireSali();
void afisareSali();
void afisariSaliDisponibile();

// CAUTARI
void cautareDupaCapacitate(int capacitate);
void cautareDupaFacilitati(string facilitatiCautate);

// REZERVARI
void preRezervare(string numeSala,int capacitateMin,int zi,int luna,int an,string facilitateDorita,string numeClient);
void confirmaPreRezervare(int id, string numeClient);
void afisarePreRezervari();
void stergerePreRezervare(int idCautat, string numeClientCautat);

void rezervareSala(string numeSala,int capacitateMin,int zi,int luna,int an,string facilitateDorita,string numeClient);
void anulareRezervari(int zi,int luna,int an,int idCautat,string numeClientCautat);
void afisareToateRezervarile();
void vizualizareRezervariPersonale(string numeClientCautat);
void modificareData(int idCautat,string numeClientCautat,int ziV,int lunaV,int anV,int ziN,int lunaN,int anN);

void informatiiUtileSali();