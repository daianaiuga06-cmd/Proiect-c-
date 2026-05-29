#include <iostream>
#include <string>
#include <vector>
#include "Shared/H/Sala.h"
#include "Shared/H/Rezervare.h"
#include "Shared/H/Data.h"
#include "Shared/H/Utilitati2.h"
#include <fstream>

using namespace std;

int main(int argc,char* argv[])
{
    if (argc<2) {  //cazul in care nu e introdusa niciun argument
        cout << "Nu exista comanda!\n";
        return 0;
    }

    string comanda=argv[1];

    //afisari sali
    if (comanda=="afisare_sali"){
        afisareSali();
    }

    else if(comanda=="afisare_sali_disponibile"){
        afisariSaliDisponibile();
    }

    else if(comanda=="cautare_capacitate"){
        if(argc<3) {
            cout<<"Format: cautare_capacitate <capacitate>\n";
            return 0;
        }

        int capacitate=stoi(argv[2]); //se transfortma din string in int
        cautareDupaCapacitate(capacitate);
    }

    else if(comanda=="cautare_facilitati"){
        if (argc<3) {
            cout<<"Format: cautare_facilitati <facilitate>\n";
            return 0;
        }

        string f=argv[2];
        cautareDupaFacilitati(f);
    }

    //rezervari

    else if(comanda=="rezervare_directa"){

    if(argc < 10){
        cout << "Format: rezervare_directa <sala> <cap> <zi> <luna> <an> \"facilitati\" <nume> <prenume>\n";
        return 0;
    }

    string numeSala = argv[2];
    int cap = stoi(argv[3]);
    int zi = stoi(argv[4]);
    int luna = stoi(argv[5]);
    int an = stoi(argv[6]);

    // facilitatile sunt intre ghilimele si sunt tratate ca UN SINGUR argument
    string fac = argv[7];

    // ultimele 2 argumente = nume + prenume
    string client = string(argv[8]) + " " + string(argv[9]);

    rezervareSala(numeSala, cap, zi, luna, an, fac, client);
}

    // prerezervare

   else if(comanda=="rezervare_provizorie"){

    if(argc < 9){
        cout << "Format: rezervare_provizorie <sala> <cap> <zi> <luna> <an> \"facilitati\" <nume> <prenume>\n";
        return 0;
    }

    string numeSala = argv[2];
    int cap = stoi(argv[3]);
    int zi = stoi(argv[4]);
    int luna = stoi(argv[5]);
    int an = stoi(argv[6]);

    // toate facilitatile sunt citite ca un singur argument
    string fac = argv[7];

    string client = string(argv[8]) + " " + string(argv[9]);

    preRezervare(numeSala, cap, zi, luna, an, fac, client);
}

    else if (comanda=="afisare_rezervari_provizorii") {
        afisarePreRezervari();
    }

    else if (comanda=="confirma_rezervare_provizorie") {

        if (argc<4) {
            cout<<"Format: confirma_rezervare_provizorie <id> <numeClient>\n";
            return 0;
        }

        int id=stoi(argv[2]);
        string numeClient = string(argv[argc-2]) + " " + string(argv[argc-1]);

        confirmaPreRezervare(id,numeClient);
    }

    else if (comanda=="stergere_rezervare_provizorie") {

        if (argc<4) {
            cout << "Format: stergere_rezervare_provizorie <id> <numeClient>\n";
            return 0;
        }

        int id=stoi(argv[2]);
        string numeClient = string(argv[argc-2]) + " " + string(argv[argc-1]);

        stergerePreRezervare(id, numeClient);
    }

    // rezervari personale

    else if (comanda=="vizualizare_rezervari_personale") {

        if (argc<3) {
            cout << "Format: vizualizare_rezervari_personale <numeClient>\n";
            return 0;
        }

       string numeClient;
       if (argc>=4){  //pentru a afisa nume si prenume
               numeClient=string(argv[2])+ " " +string(argv[3]);
    } else{
    numeClient = argv[2];
    }
        vizualizareRezervariPersonale(numeClient);
    }
    
    else if(comanda=="afisare_rezervari") {
    afisareToateRezervarile();
    }

    else if (comanda == "anulare_rezervare") {

        if (argc<6) {
            cout <<"Format: anulare_rezervare <zi> <luna> <an> <id> <numeClient>\n";
            return 0;
        }

        int zi=stoi(argv[2]);
        int luna=stoi(argv[3]);
        int an=stoi(argv[4]);
        int id=stoi(argv[5]);
        string numeClient = string(argv[argc-2]) + " " + string(argv[argc-1]);

        anulareRezervari(zi, luna, an, id, numeClient);
    }

    // modificare data

    else if (comanda=="modificare_data") {

        if (argc<9) {
            cout << "Format: modificare_data <id> <client> <ziV> <lunaV> <anV> <ziN> <lunaN> <anN>\n";
            return 0;
        }

        int id=stoi(argv[2]);
        string client = argv[3];

        int ziV=stoi(argv[4]);
        int lunaV=stoi(argv[5]); //tot ce este de tip int este convertit in string
        int anV=stoi(argv[6]);

        int ziN=stoi(argv[7]);
        int lunaN=stoi(argv[8]);
        int anN=stoi(argv[9]);

        modificareData(id, client, ziV, lunaV, anV, ziN, lunaN, anN);
    }

    // informatii

    else if (comanda=="informatii") {
        informatiiUtileSali();
    }

    // in caz ca comanda e gresita

    else {
        cout<< "Comanda invalida!\n";
        cout<< "Comenzi disponibile:\n";
        cout<< "afisare_sali\n";
        cout<< "afisare_sali_disponibile\n";
        cout<< "cautare_capacitate\n";
        cout<< "cautare_facilitati\n";
        cout<< "rezervare_directa\n";
        cout<< "rezervare_provizorie\n";
        cout<< "afisare_rezervari_provizorii\n";
        cout<< "confirma_rezervare_provizorie\n";
        cout<< "stergere_rezervare_provizorie\n";
        cout<< "vizualizare_rezervari_personale\n";
        cout<< "anulare_rezervare\n";
        cout<< "modificare_data\n";
        cout<< "informatii\n";
    }

    return 0;
}