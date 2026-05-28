#include <iostream>
#include <string>
#include <vector>
#include "Sala.h"
#include "Rezervare.h"
#include "Data.h"
#include "Utilitati2.h"
#include <fstream>

using namespace std;

int main(int argc,char* argv[])
{
    if (argc<2) {
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

        int capacitate=stoi(argv[2]);
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

    if (argc<9) {
        cout<<"Format: rezervare_directa <numeSala> <capacitate> <zi> <luna> <an> <facilitate> <nume> <prenume>\n";
        return 0;
    }

    string numeSala=argv[2];
    int cap=stoi(argv[3]);
    int zi=stoi(argv[4]);
    int luna=stoi(argv[5]);
    int an=stoi(argv[6]);
    string fac=argv[7];

    string client="";
     for (int i=8; i<argc; i++) {
        client += string(argv[i]);
        if (i<argc-1) client+= " ";
    }

    rezervareSala(numeSala, cap, zi, luna, an, fac, client);
}

    // prerezervare

    else if(comanda=="rezervare_provizorie") {

        if (argc<9) {
            cout<<"Format corect: rezervare_provizorie <numeSala> <capacitate> <zi> <luna> <an> <facilitate> <numeClient>\n";
            return 0;
        }

         string numeSala=argv[2];
         int cap=stoi(argv[3]);
         int zi=stoi(argv[4]);
         int luna=stoi(argv[5]);
         int an=stoi(argv[6]);
         string fac=argv[7];

        string client= "";
         for (int i=8; i<argc; i++) {
           client += string(argv[i]);
           if (i<argc-1) client+= " ";
      }
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
        string client=argv[3];

        confirmaPreRezervare(id,client);
    }

    else if (comanda=="stergere_rezervare_provizorie") {

        if (argc<4) {
            cout << "Format: stergere_rezervare_provizorie <id> <numeClient>\n";
            return 0;
        }

        int id=stoi(argv[2]);
        string client=argv[3];

        stergerePreRezervare(id, client);
    }

    // rezervari personale

    else if (comanda=="vizualizare_rezervari_personale") {

        if (argc<3) {
            cout << "Format: vizualizare_rezervari_personale <numeClient>\n";
            return 0;
        }

       string numeClient;
       if (argc>=4){
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
        string client=argv[6];

        anulareRezervari(zi, luna, an, id, client);
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
        int lunaV=stoi(argv[5]);
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