#include "Shared/H/Utilitati.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string toLowerStr(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

bool safeStoi(const string &s, int &out) {
    try {
        out = stoi(s);
        return true;
    } catch (...) {
        return false;
    }
}

bool safeStod(const string &s, double &out) {
    try {
        out = stod(s);
        return true;
    } catch (...) {
        return false;
    }
}

int main(int argc, char* argv[]) {

    vector<Sala> sali;
    vector<Rezervare> rezervari;

    citireSali(sali);
    citireRezervari(rezervari, sali);

    if (argc < 2) {
        cout << "Comanda invalida!\n";
        return 1;
    }

    string cmd = argv[1];

    // ================= VIZUALIZARE =================

    if (cmd == "vizualizare_sali") {
        afisareSali(sali);
    }

    else if (cmd == "vizualizare_rezervari") {
        afisareRezervari(rezervari);
    }

    else if (cmd == "vizualizare_disponibilitate") {
        afisareDisponibile(sali);
    }

    // ================= ADAUGARE SALA =================

    else if (cmd == "adaugare_sala") {

    if (argc < 9) {
        cout << "Utilizare:\n";
        cout << "./app adaugare_sala <ID> <denumire> <capacitate> <facilitati...> <disponibilitate> <pret>\n";
        return 1;
    }

    int id, cap;
    double pret;

    // CONVERSII 
    if (!safeStoi(argv[2], id) ||
        !safeStoi(argv[4], cap) ||
        !safeStod(argv[argc - 1], pret)) {
        cout << "Date invalide!\n";
        return 1;
    }

    string den = argv[3];

    string dispStr = toLowerStr(argv[argc - 2]);
    bool disp;

    if (dispStr == "da") disp = true;
    else if (dispStr == "nu") disp = false;
    else {
        cout << "Disponibilitate invalida (foloseste da/nu)!\n";
        return 1;
    }

    // VALIDARI LOGICE 

    if (!numarPozitiv(id)) {
        cout << "ID invalid!\n";
        return 1;
    }

    if (!numarPozitiv(cap)) {
        cout << "Capacitatea trebuie sa fie > 0!\n";
        return 1;
    }

    if (!numarPozitivDouble(pret)) {
        cout << "Pret invalid!\n";
        return 1;
    }

    if (!textValid(den)) {
        cout << "Denumire invalida!\n";
        return 1;
    }

    if (existaSala(sali, id)) {
        cout << "Sala cu acest ID exista deja!\n";
        return 1;
    }

    // FACILITATI 
    vector<string> facilitati;

    for (int i = 5; i < argc - 2; i++) {
        if (!textValid(argv[i])) {
            cout << "Facilitati invalide!\n";
            return 1;
        }
        facilitati.push_back(argv[i]);
    }

    // ADAUGARE 
    sali.push_back(Sala(id, den, cap, facilitati, disp, pret));

    salvareSali(sali);

    cout << "Sala adaugata cu succes!\n";
    return 0;
}

    // ================= STERGERE SALA =================

    else if (cmd == "stergere_sala") {

        if (argc < 3) {
            cout << "Utilizare: ./app stergere_sala <ID>\n";
            return 1;
        }

        int id;

        if (!safeStoi(argv[2], id)) {
            cout << "ID invalid!\n";
            return 1;
        }

        if (stergereSala(sali, id)) {
            salvareSali(sali);
            cout << "Sala stearsa!\n";
        }
        else {
            cout << "Sala nu exista!\n";
        }
    }

    // ================= MODIFICARE DATE =================

    else if (cmd == "modificare_date") {

        if (argc < 4) {
            cout << "Utilizare:<ID> <capacitate/facilitati/disponibilitate> <noua_capacitate/facilitati/disponibilitate>\n";
            return 1;
        }

        int id;
        if (!safeStoi(argv[2], id)) {
            cout << "ID invalid!\n";
            return 1;
        }

        string tip = argv[3];

        for (auto &s : sali) {

            if (s.getID() == id) {

                if (tip == "capacitate") {

                    int cap;
                    if (!safeStoi(argv[4], cap)) {
                        cout << "Capacitate invalida!\n";
                        return 1;
                    }

                    s = Sala(s.getID(), s.getDenumire(), cap,
                             s.getFacilitati(), s.getDisponibilitate(), s.getPretBaza());
                }

                else if (tip == "facilitati") {

                    vector<string> facilitati;
                    for (int i = 4; i < argc; i++) {
                    facilitati.push_back(argv[i]);
                    }

                    s = Sala(s.getID(), s.getDenumire(), s.getCapacitate(),
                             facilitati, s.getDisponibilitate(), s.getPretBaza());
                }

                else if (tip == "disponibilitate") {

                    if (argc < 5) {
                        cout << "Utilizare: <ID> disponibilitate <da/nu>\n";
                        return 1;
                    }

                    string val = toLowerStr(argv[4]);
                    bool disp;

                    if (val == "da") disp = true;
                    else if (val == "nu") disp = false;
                    else {
                        cout << "Valoare invalida!\n";
                        return 1;
                    }

                    s.setDisponibilitate(disp);
                }

                salvareSali(sali);
                cout << "Sala modificata!\n";
                return 0;
            }
        }

        cout << "Sala nu exista!\n";
    }

    // ================= ADAUGARE REZERVARE =================

    else if (cmd == "adaugare_rezervare") {

    int idRez, idSala, zi, luna, an;

    if (argc < 9) {
        cout << "Utilizare: <IDrez> <IDSala> <zi> <luna> <an> <numeClient> <prenumeClient>\n";
        return 1;
    }

    // CONVERSII 
    if (!safeStoi(argv[2], idRez) ||
        !safeStoi(argv[3], idSala) ||
        !safeStoi(argv[4], zi) ||
        !safeStoi(argv[5], luna) ||
        !safeStoi(argv[6], an)) {
        cout << "Date invalide!\n";
        return 1;
    }

    string nume = argv[7];
    string prenume = argv[8];

    // VALIDARI NUMERICE 
    if (!numarPozitiv(idRez)) {
        cout << "ID rezervare invalid!\n";
        return 1;
    }

    if (!numarPozitiv(idSala)) {
        cout << "ID sala invalid!\n";
        return 1;
    }

    // VALIDARI TEXT 
    if (!textValid(nume) || !textValid(prenume)) {
        cout << "Nume client invalid!\n";
        return 1;
    }

    // VALIDARE SALA EXISTENTA 
    if (!existaSala(sali, idSala)) {
        cout << "Sala nu exista!\n";
        return 1;
    }

    // VALIDARE DATA 
    Data d(zi, luna, an);

    if (!dataCalendaristicaValida(d)) {
        cout << "Data calendaristica invalida!\n";
        return 1;
    }

    if (!dataValidaViitor(d)) {
        cout << "Data trebuie sa fie in viitor!\n";
        return 1;
    }

    // ADAUGARE 
    if (adaugareRezervare(rezervari, sali, idRez, idSala, zi, luna, an, nume, prenume)) {
    cout << "Rezervare adaugata!\n";
    } else {
    cout << "Rezervarea NU a fost adaugata!\n";
    }
}

    // ==========STERGERE REZERVARE============ 

    else if (cmd == "stergere_rezervare") {

        if (argc < 3) {
            cout << "Utilizare: ./app stergere_rezervare <ID>\n";
            return 1;
        }

        int id;

        if (!safeStoi(argv[2], id)) {
            cout << "ID invalid!\n";
            return 1;
        }

        stergereRezervare(rezervari, id);
        salvareRezervari(rezervari);

        cout << "Rezervare stearsa!\n";
    }

    // ================= INCASARI =================

    else if (cmd == "incasari_totale") {

        cout << "Total incasari: " << incasariTotale(rezervari) << " lei\n";
    }

    // ================= ACTUALIZARE DISPONIBILITATE =================

    else if (cmd == "actualizare_disponibilitate") {

    if (argc < 4) {
        cout << "Utilizare: app1.exe actualizare_disponibilitate <ID> <da/nu>\n";
        return 1;
    }

    int id;

    if (!safeStoi(argv[2], id)) {
        cout << "ID invalid!\n";
        return 1;
    }

    string val = toLowerStr(argv[3]);

    bool disp;

    if (val == "da")
        disp = true;

    else if (val == "nu")
        disp = false;

    else {
        cout << "Valoare invalida! Foloseste da sau nu.\n";
        return 1;
    }

    bool gasit = false;

    for (auto &s : sali) {

        if (s.getID() == id) {

            s.setDisponibilitate(disp);

            gasit = true;

            break;
        }
    }

    if (!gasit) {
        cout << "Sala nu exista!\n";
        return 1;
    }

    salvareSali(sali);

    cout << "Disponibilitate actualizata!\n";
}

    // ================= COMANDA NECUNOSCUTA =================

    else {
        cout << "Comanda necunoscuta!\n";
        cout << "Comenzi disponibile:\n";
        cout << "vizualizare_sali\n";
        cout << "vizualizare_rezervari\n";
        cout << "vizualizare_disponibilitate\n";
        cout << "adaugare_sala\n";
        cout << "adaugare_rezervare\n";
        cout << "stergere_sala\n";
        cout << "stergere_rezervare\n";
        cout << "modificare_date\n";
        cout << "actualizare_disponibilitate\n";
        cout << "incasari_totale\n";
    }

    return 0;
}