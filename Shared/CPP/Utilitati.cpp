#include "../H/Utilitati.h"
#include "../H/Templates.h"
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
        if (!isalpha(c) && c != '_' && c != '-' && c != ' ') //permite doar semnele astea
            return false;
    }
    return true;
}
// verific daca anul este bisect
// conform regulilor calendarului gregorian
bool anBisect(int an) {
    return (an % 4 == 0 && an % 100 != 0) || (an % 400 == 0);
}

// preiau data curenta a sistemului
// folosind functiile din biblioteca ctime
bool dataValidaViitor(const Data& d) {
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int z = now->tm_mday;
    int l = now->tm_mon + 1;
    int a = now->tm_year + 1900;

    // compar data introdusa cu data curenta
    // pentru a permite doar rezervari viitoare
    if (d.getAn() < a) return false;
    if (d.getAn() > a) return true;

    if (d.getLuna() < l) return false;
    if (d.getLuna() > l) return true;

    return d.getZi() >= z;
}

// vectorul contine numarul maxim de zile
// pentru fiecare luna a anului
bool dataCalendaristicaValida(const Data& d) {
    int zile[] = {31,28,31,30,31,30,31,31,30,31,30,31};// aici am numarul de zile maxim din fiecare luna a anului

    if (d.getAn() < 1900) return false;
    if (d.getLuna() < 1 || d.getLuna() > 12) return false; //(1-12 luni)

    if (d.getLuna() == 2 && anBisect(d.getAn()))
        zile[1] = 29;

    return d.getZi() >= 1 && d.getZi() <= zile[d.getLuna() - 1]; // zilelesa fie de la 1 la [nr max de zile pe fiecare luna]
}

// caut in lista de rezervari daca
// exista deja o rezervare pentru
// aceeasi sala si aceeasi data
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

// rescriu complet fisierul cu
// datele actualizate ale salilor
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
    ifstream fin("Shared/TXT/Sali.txt");
    if (!fin) return; //daca nu pot gasi/deschise fisierul

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
    ofstream fout("Shared/TXT/Sali.txt");

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
// citesc fiecare rezervare din fisier
// folosind formatul:
// zi/luna/an idSala numeSala nume prenume pret
void citireRezervari(vector<Rezervare>& rez,
                     const vector<Sala>& sali) {

    ifstream fin("Shared/TXT/Rezervari.txt");
    if (!fin.is_open()) return; //daca fisierul nu poate fi deschis

    int zi, luna, an;
    char slash;

    int id;
    string numeSala;
    string nume;
    string prenume;

    double pret;

    while (fin >> zi >> slash >> luna >> slash >> an
               >> id
               >> numeSala
               >> nume
               >> prenume
               >> pret) {

        Sala s;

        for (const auto& sala : sali) {
            if (sala.getDenumire() == numeSala) {
                s = sala;
                break;
            }
        }

        Data d(zi, luna, an);

        rez.push_back(
            Rezervare(id, s, d, nume, prenume, pret)
        );
    }
}

void afisareRezervari(const vector<Rezervare>& rez) {
    for (const auto& r : rez)
        cout << r << "\n";
}

void salvareRezervari(const vector<Rezervare>& rez) {

    ofstream fout("Shared/TXT/Rezervari.txt");

    for (const auto& r : rez) {

        fout << r.getData().getZi() << "/"
             << r.getData().getLuna() << "/"
             << r.getData().getAn() << " "
             << r.getID() << " "
             << r.getSala().getDenumire() << " "
             << r.getNume() << " "
             << r.getPrenume() << " "
             << r.getPretTotal() << "\n";
    }
}

// functia valideaza toate datele
// introduse inainte de adaugarea rezervarii
bool adaugareRezervare(
    vector<Rezervare>& rezervari,
    vector<Sala>& sali,
    int idRez,
    int idSala,
    int zi,
    int luna,
    int an,
    const string& nume,
    const string& prenume
) { //VALIDEZ TOATE DATELE
    if (!numarPozitiv(idRez) || !numarPozitiv(idSala))
        return false;

    Data d(zi, luna, an);

    if (!dataCalendaristicaValida(d)) {
        cout << "Data calendaristică invalidă!\n";
        return false;
    }

    if (!dataValidaViitor(d)) {
        cout << "Data trebuie să fie în viitor!\n";
        return false;
    }

    if (existaRezervare(rezervari, idSala, d)) {
        cout << "Sala este deja rezervată!\n";
        return false;
    }
    // dupa adaugare salvez automat
    // modificarile in fisier
    for (auto& s : sali) {
        if (s.getID() == idSala) {

            rezervari.push_back(
                Rezervare(idRez, s, d, nume, prenume, s.getPretBaza())
            );

            salvareRezervari(rezervari);
            return true;
        }
    }

    cout << "Sala nu exista!\n";
    return false;
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
// folosesc functia template 'acumuleaza'
// pentru a calcula suma tuturor incasarilor
double incasariTotale(const vector<Rezervare>& rez) {

    return acumuleaza(rez,
        [](const Rezervare& r) {
            return r.getPretTotal();
        });
}
// generez automat un ID unic
// pe baza celui mai mare ID existent
int genereazaID(const vector<Rezervare>& rez) {
    int m = 0;
    for (const auto& r : rez)
        m = max(m, r.getID());
    return m + 1;
}