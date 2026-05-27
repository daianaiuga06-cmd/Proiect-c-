#include "Utilitati.h"
#include "Templates.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <ctime>

using namespace std;

// ================= VALIDARI =================

bool numarPozitiv(int x) {
    return x > 0;
}

bool numarPozitivDouble(double x) {
    return x > 0;
}

bool textValid(const string& s) {
    if (s.empty()) return false;

    for (char c : s) {
        if (!isalpha(c) && c != '_' && c != '-' && c != ' ')
            return false;
    }
    return true;
}

bool anBisect(int an) {
    return (an % 4 == 0 && an % 100 != 0) || (an % 400 == 0);
}

//verific daca data e in viitor 
bool dataValidaViitor(const Data& d) {
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int z = now->tm_mday;
    int l = now->tm_mon + 1;
    int a = now->tm_year + 1900;

    if (d.getAn() < a) return false;
    if (d.getAn() > a) return true;

    if (d.getLuna() < l) return false;
    if (d.getLuna() > l) return true;

    return d.getZi() >= z;
}

bool dataCalendaristicaValida(const Data& d) {
    int zile[] = {31,28,31,30,31,30,31,31,30,31,30,31};// aici am numarul de zile maxim din fiecare luna a anului

    if (d.getAn() < 1900) return false;
    if (d.getLuna() < 1 || d.getLuna() > 12) return false; //(1-12 luni)

    if (d.getLuna() == 2 && anBisect(d.getAn()))
        zile[1] = 29;

    return d.getZi() >= 1 && d.getZi() <= zile[d.getLuna() - 1]; // zilelesa fie de la 1 la [nr max de zile pe fiecare luna]
}

//verific daca am rezervare pe o sala la o data introdusa
bool existaRezervare(
    const vector<Rezervare>& rezervari,
    int idSala,
    const Data& d
) {
    for (const auto& r : rezervari) {
        if (r.getSala().getID() == idSala &&
            r.getData().getZi() == d.getZi() &&
            r.getData().getLuna() == d.getLuna() &&
            r.getData().getAn() == d.getAn())
            return true;
    }
    return false;
}

bool existaSala(const vector<Sala>& sali, int id) {
    for (const auto& s : sali)
        if (s.getID() == id)
            return true;
    return false;
}


bool stergereSala(vector<Sala>& sali, int id) {
    for (int i = 0; i < (int)sali.size(); i++) {
        if (sali[i].getID() == id) {
            sali.erase(sali.begin() + i);
            return true;
        }
    }
    return false;
}

// ================= SALI =================

void citireSali(vector<Sala>& sali) {
    ifstream fin("Sali.txt");
    if (!fin) return;

    int nr;
    fin >> nr;

    for (int i = 0; i < nr; i++) {
        int id, cap, disp;
        string d;
        double p;

        fin >> id >> d >> cap;

        int nrFac;
        fin >> nrFac;

        vector<string> fac;
        for (int j = 0; j < nrFac; j++) {
            string f;
            fin >> f;
            fac.push_back(f);
        }

        fin >> disp >> p;

        sali.push_back(Sala(id, d, cap, fac, disp == 1, p));
    }
}

void salvareSali(const vector<Sala>& sali) {
    ofstream fout("Sali.txt");

    fout << sali.size() << "\n";
    for (const auto& s : sali)
        fout << s << "\n";
}

void afisareSali(const vector<Sala>& sali) {
    for (const auto& s : sali)
        cout << s << "\n";
}

void afisareDisponibile(const vector<Sala>& sali) {
    for (const auto& s : sali)
        if (s.getDisponibilitate())
            cout << s << "\n";
}

// ================= REZERVARI =================

void citireRezervari(vector<Rezervare>& rez,
                     const vector<Sala>& sali) {

    ifstream fin("Rezervari.txt");

    if (!fin) return;

    while (true) {

        int zi, luna, an;

        char slash;

        fin >> zi >> slash >> luna >> slash >> an;

        if (fin.eof()) break;

        int id;
        fin >> id;

        string numeSala;
        fin.ignore();
        getline(fin, numeSala);

        string nume;
        getline(fin, nume);

        string prenume;
        getline(fin, prenume);

        Sala s;

        for (const auto& sala : sali) {
            if (sala.getDenumire() == numeSala) {
                s = sala;
                break;
            }
        }

        Data d(zi, luna, an);

        rez.push_back(
            Rezervare(id, s, d, nume, prenume, s.getPretBaza())
        );
    }
}

void afisareRezervari(const vector<Rezervare>& rez) {
    for (const auto& r : rez)
        cout << r << "\n";
}

void salvareRezervari(const vector<Rezervare>& rez) {

    ofstream fout("Rezervari.txt");

    for (const auto& r : rez) {

        fout << r.getData().getZi() << "/"
             << r.getData().getLuna() << "/"
             << r.getData().getAn() << "\n";

        fout << r.getID() << "\n";

        fout << r.getSala().getDenumire() << "\n";

        fout << r.getNume() << "\n";

        fout << r.getPrenume() << "\n";

        fout << r.getPretTotal() << "\n";

        fout << "\n";
    }
}

void adaugareRezervare(
    vector<Rezervare>& rezervari,
    vector<Sala>& sali,
    int idRez,
    int idSala,
    int zi,
    int luna,
    int an,
    const string& nume,
    const string& prenume
) {
    if (!numarPozitiv(idRez) || !numarPozitiv(idSala)) return;

    Data d(zi, luna, an);

    if (!dataCalendaristicaValida(d)){
        cout<<"Data calendaristică invalidă!";
         return;
        }
    if (!dataValidaViitor(d)){ 
        cout<<"Data calendaristică trebuie să fie în viitor!";
        return;
        }
    if (existaRezervare(rezervari, idSala, d)){ 
        cout<<"Sala este deja rezervată!";
        return;
        }

    for (auto& s : sali) {
        if (s.getID() == idSala) {
            rezervari.push_back(Rezervare(idRez, s, d, nume, prenume, s.getPretBaza()));
            salvareRezervari(rezervari);
            cout << "Rezervare adaugata!\n";
            return;
        }
    }
}

void stergereRezervare(vector<Rezervare>& rez, int id) {
    for (int i = 0; i < (int)rez.size(); i++) {
        if (rez[i].getID() == id) {
            rez.erase(rez.begin() + i);
            return;
        }
    }
}

// ================= INCASARI =================

double incasariTotale(const vector<Rezervare>& rez) {

    return acumuleaza(rez,
        [](const Rezervare& r) {
            return r.getPretTotal();
        });
}

int genereazaID(const vector<Rezervare>& rez) {
    int m = 0;
    for (const auto& r : rez)
        m = max(m, r.getID());
    return m + 1;
}