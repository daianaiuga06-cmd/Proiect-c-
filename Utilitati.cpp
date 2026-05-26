#include "Utilitati.h"
#include <fstream>
#include <iostream>

using namespace std;

void raportRezervari(const vector<T>& v) {
    int count = v.size();
    double suma = 0;

    for (const auto& r : v)
        suma += r.getPretTotal();

    cout << "=== RAPORT REZERVARI ===\n";
    cout << "Numar rezervari: " << count << endl;
    cout << "Suma incasata: " << suma << " RON" << endl;

    if (count > 0)
        cout << "Valoare medie: " << suma / count << " RON" << endl;
}

void citireSali(vector<Sala>& sali) {// Citeste datele salilor din fisierul Sali.txt
    // Fiecare sala este transformata in obiect si adaugata in vector
    ifstream fin("Sali.txt");

    int nr;
    fin >> nr;

    for (int i = 0; i < nr; i++) {
        int id, cap, disp;
        string d, f1, f2, f3;
        double pret;

        fin >> id >> d >> cap >> f1 >> f2 >> f3 >> disp >> pret;

        sali.push_back(Sala(id, d, cap, f1, f2, f3, disp == 1, pret));// Convertim valoarea 1/0 din fisier in true/false pentru disponibilitate
    }
}

void salvareSali(const vector<Sala>& sali) {// Salveaza toate salile din vector in fisier
// Prima linie contine numarul total de sali
    ofstream fout("Sali.txt");

    fout << sali.size() << endl;

    for (auto s : sali) {
        fout << s.getID() << " "
             << s.getDenumire() << " "
             << s.getCapacitate() << " "
             << s.getF1() << " "
             << s.getF2() << " "
             << s.getF3() << " "
             << s.getDisponibilitate() << " "
             << s.getPretBaza()
             << endl;
    }
}

void afisareSali(const vector<Sala>& sali) {
    for (auto s : sali)
        cout << s << endl;
}

void stergereSala(vector<Sala>& sali, int id) {// Cauta sala dupa ID si o elimina din vector
    for (int i = 0; i < sali.size(); i++) {
        if (sali[i].getID() == id) {
            sali.erase(sali.begin() + i);// erase muta automat elementele ramase
            return;
        }
    }
}

void afisareDisponibile(const vector<Sala>& sali) {
    for (auto s : sali)
        if (s.getDisponibilitate())
            cout << s << endl;
}

void cautareSali(const vector<Sala>& sali, int capMin) {
    for (auto s : sali)
        if (s.getCapacitate() >= capMin)
            cout << s << endl;
}

void citireRezervari(vector<Rezervare>& rez) {// Citeste rezervarile din fisier si reconstruieste obiectele Data, Sala si Rezervare
    ifstream fin("Rezervari.txt");

    int zi, luna, an;
    int idSala;
    string denumire;
    string nume, prenume;
    double pret;

    while (fin >> zi >> luna >> an
               >> idSala >> denumire
               >> nume >> prenume
               >> pret) {

        Data d(zi, luna, an);
        Sala s(idSala, denumire, 0, "", "", "", true, 0);// Cream un obiect Sala minimal, folosind doar informatiile necesare rezervarii
        Rezervare r(0, s, d, nume, prenume, pret);

        rez.push_back(r);
    }
}

void salvareRezervari(const vector<Rezervare>& rez) {
    ofstream fout("Rezervari.txt");

    for (auto r : rez) {
        fout << r.getData().getZi() << " "
             << r.getData().getLuna() << " "
             << r.getData().getAn() << " "
             << r.getSala().getID() << " "
             << r.getSala().getDenumire() << " "
             << r.getNumeClient() << " "
             << r.getPrenumeClient() << " "
             << r.getPretTotal()
             << endl;
    }
}

void afisareRezervari(const vector<Rezervare>& rez) {
    for (auto r : rez) {
        cout << "Data: "
             << r.getData().getZi() << "/"
             << r.getData().getLuna() << "/"
             << r.getData().getAn()
             << " | Sala: " << r.getSala().getDenumire()
             << " | Client: " << r.getNumeClient()
             << " " << r.getPrenumeClient()
             << " | Pret: " << r.getPretTotal()
             << endl;
    }
}
