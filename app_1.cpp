#include "Sala.h"
#include "Rezervare.h"
#include "Utilitati.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Aplicatia functioneaza pe baza de comenzi din linia de comanda (CLI)
    argv[1] reprezinta comanda principala
    argv[2...] reprezinta parametrii aferenti fiecarei comenzi
*/

int main(int argc, char* argv[]) {

    vector<Sala> sali;
    vector<Rezervare> rezervari;

    // incarcam datele existente din fisiere la pornirea aplicatiei
    citireSali(sali);
    citireRezervari(rezervari);

    // verificam daca a fost introdusa o comanda valida
    if (argc < 2) {
        cout << "Comanda invalida!\n";
        return 1;
    }

    // extragem comanda principala
    string comanda = argv[1];

    // 1. afisarea tuturor salilor existente
    if (comanda == "vizualizare_sali") {
        afisareSali(sali);
    }

    // 2. afisarea rezervarilor existente
    else if (comanda == "vizualizare_rezervari") {
        afisareRezervari(rezervari);
    }

    // 3. filtrarea salilor disponibile (cele care pot fi rezervate)
    else if (comanda == "vizualizare_disponibilitate") {
        afisareDisponibile(sali);
    }

    // 4. adaugarea unei noi sali in sistem
    // ID-ul este generat automat pentru a evita duplicarea
    else if (comanda == "adaugare_sala") {

        if (argc != 9) {
            cout << "Numar gresit de argumente!\n";
            return 1;
        }

        int idNou = 1;

        // cautam cel mai mare ID existent pentru a genera unul nou unic
        for (auto s : sali)
            if (s.getID() >= idNou)
                idNou = s.getID() + 1;

        string denumire = argv[2];
        int capacitate = stoi(argv[3]);
        string f1 = argv[4];
        string f2 = argv[5];
        string f3 = argv[6];
        bool disp = (string(argv[7]) == "da");
        double pret = stod(argv[8]);

        sali.push_back(Sala(idNou, denumire, capacitate, f1, f2, f3, disp, pret));
        salvareSali(sali);

        cout << "Sala adaugata!\n";
    }

    // 5. stergerea unei sali dupa ID
    else if (comanda == "stergere_sala") {

        if (argc != 3) {
            cout << "Numar gresit de argumente!\n";
            return 1;
        }

        int id = stoi(argv[2]);
        stergereSala(sali, id);
        salvareSali(sali);

        cout << "Sala stearsa!\n";
    }

    // 6. modificarea datelor unei sali (capacitate sau facilitati)
    else if (comanda == "modificare_date") {

        if (argc < 5) {
            cout << "Numar gresit de argumente!\n";
            return 1;
        }

        int id = stoi(argv[2]);
        string tip = argv[3];

        for (auto& s : sali) {
            if (s.getID() == id) {

                // modificare capacitate
                if (tip == "capacitate") {
                    int capNoua = stoi(argv[4]);

                    s = Sala(
                        s.getID(),
                        s.getDenumire(),
                        capNoua,
                        s.getF1(),
                        s.getF2(),
                        s.getF3(),
                        s.getDisponibilitate(),
                        s.getPretBaza()
                    );
                }

                // modificare facilitati (3 valori simultan)
                else if (tip == "facilitati") {
                    if (argc != 7) {
                        cout << "Trebuie 3 facilitati noi!\n";
                        return 1;
                    }

                    s = Sala(
                        s.getID(),
                        s.getDenumire(),
                        s.getCapacitate(),
                        argv[4],
                        argv[5],
                        argv[6],
                        s.getDisponibilitate(),
                        s.getPretBaza()
                    );
                }

                // salvam modificarile in fisier
                salvareSali(sali);
                cout << "Date modificate!\n";
                return 0;
            }
        }

        cout << "Sala nu exista!\n";
    }

    // 7. actualizarea disponibilitatii unei sali
    else if (comanda == "actualizare_disponibilitate") {

        if (argc != 4) {
            cout << "Numar gresit de argumente!\n";
            return 1;
        }

        int id = stoi(argv[2]);
        bool disp = (string(argv[3]) == "da");

        for (auto& s : sali) {
            if (s.getID() == id) {

                s.setDisponibilitate(disp);
                salvareSali(sali);

                cout << "Disponibilitate actualizata!\n";
                return 0;
            }
        }

        cout << "Sala nu exista!\n";
    }

    // 8. raport statistic al rezervarilor (numar + suma incasata)
    else if (comanda == "raport_rezervari") {
        raportRezervari(rezervari);
    }

    else {
        cout << "Comanda necunoscuta!\n";
    }

    return 0;
}