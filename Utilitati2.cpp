#include"Utilitati2.h"
#include<fstream>
#include<ctime>
#include<map>

//VALIDARI

bool validareCapacitate(int c){
         if(c<=0)return false;
         return true;
}

bool validareNume(string s){
          if(s=="")return false;
           return true;
}

bool validareFacilitate(string s){
         if(s=="")return false;
           return true;
}

bool validareData(int zi,int luna,int an){
time_t t=time(0);
tm*acum=localtime(&t);

int zc=acum->tm_mday;
int lc=acum->tm_mon+1;
int ac=acum->tm_year+1900;

     if(an<ac)return false;

        if(an==ac){
          if(luna<lc)return false;
             if(luna==lc){
              if(zi<zc)return false;
          }
      }

        if(luna<1||luna>12)return false;
        if(zi<1||zi>31)return false;

     return true;
    }

//CITIRE SALI

vector<Sala>citireSali(){
vector<Sala>sali;
  ifstream fin("Sali.txt");
   if(!fin)return sali;

    int nr;
    fin>>nr;

        for(int i=0;i<nr;i++){
            int id,cap,nrFac;
            string den;
            bool disp;
            double pret;

            fin>>id>>den>>cap>>nrFac;

            vector<string>fac;
           for(int j=0;j<nrFac;j++){
           string f;
           fin>>f;
          fac.push_back(f);
        }

          fin>>disp>>pret;
        sali.push_back(Sala(id,den,cap,fac,disp,pret));
    }
        return sali;
    }

//AFISARI
void afisareSali(){
     vector<Sala>s=citireSali();
     cout<<"\n ---AFISAREA TUTUROR SALILOR ---\n";
     if(s.empty()){
        cout<<"Nu exista sali in fisier\n";
     }
      for(auto&x:s)cout<<x<<endl;
    } 

void afisariSaliDisponibile(){
         vector<Sala>s=citireSali();
         cout<<"\n --- AFISAREA TUTUROR SALILOR DISPONIBILE --- \n";
        bool gasit=false;

          for(auto&x:s){
            if(x.getDisponibilitate()){
               cout<<x<<endl;
               gasit=true;
            }
        }
        if(!gasit)cout<<"Nu exista sali disponibile!\n";
}

//CAUTARI

void cautareDupaCapacitate(int c){
         vector<Sala>s=citireSali();
         cout<<"\n --- CAUTARE DUPA CAPACITATE ---\n";
         bool gasit=false;
        for(auto&x:s){
         if(x.getCapacitate()==c){
           cout<<x<<endl;
           gasit=true;
        }
    }
        if(!gasit) cout<<"Nu exista sali cu aceasta capacitate\n";
        else cout<<"Cautare finalizata!\n";
}
void cautareDupaFacilitati(string f){
        vector<Sala>s=citireSali();
        cout<<"\n --- CAUTARE DUPA FACILITATI ---\n";
        bool gasit=false;

              for(auto&x:s){
                for(auto&g:x.getFacilitati()){
                if(g==f){
                    cout<<x<<endl;
                    gasit=true;
                    break;
                }
           }
      }
      if(!gasit) cout<<"Nu exista sali cu aceasta facilitate\n";
      else cout<<"Cautare finalizata!\n";
}

//PRE REZERVARE

void preRezervare(string numeSala,int cap,int zi,int luna,int an,string fac,string client){

         if(!validareCapacitate(cap)){
             cout<<"Capacitate invalida!\n";
               return;
     }

           if(!validareData(zi,luna,an)){
             cout<<"Data invalida!\n";
               return;
    }

           if(!validareNume(client)){
              cout<<"Nume invalid!\n";
              return;
     }

         if(!validareFacilitate(fac)){
           cout<<"Facilitate invalida!\n";
              return;
       }

vector<Sala>s=citireSali();
Sala gasita;
bool exista=false;

        for(auto&x:s){
          if(x.getDenumire()==numeSala){
           gasita=x;
           exista=true;
           break;
        }
    }

        if(!exista){
        cout<<"Sala nu exista!\n";
        return;
    }

        if(gasita.getCapacitate()<cap){
           cout<<"Capacitate insuficienta!\n";
            return;
        }

       bool ok=false;
      for(auto&f:gasita.getFacilitati())
             if(f==fac)ok=true;

          if(!ok){
          cout<<"Nu are facilitatea!\n";
          return;
        }

      ifstream fin("preRezervari.txt");
          int lastId=0;

        string data,sala,clientFis;
         int id;

          while(fin>>data>>id>>sala>>clientFis)
             if(id>lastId)lastId=id;

       fin.close();

          ofstream fout("preRezervari.txt",ios::app);

     fout<<to_string(zi)<<"/"<<to_string(luna)<<"/"<<to_string(an)<<" "<<lastId+1<<" "<<gasita.getDenumire()<<" "<<client<<"\n";

       cout<<"Adaugata in lista provizorie!\n";
}

//CONFIRMARE PREREZERVARE

void confirmaPreRezervare(int id,string client){
ifstream fin("preRezervari.txt");
ofstream fout("temp.txt");

int idF,zi,luna,an;
string den,cl;
double pret;
bool gasit=false;

     while(fin>>idF>>den>>cl>>zi>>luna>>an>>pret){
        if(idF==id&&cl==client){
        ofstream r("Rezervari.txt",ios::app);
        r<<idF<<" "<<den<<" "<<cl<<" "<<zi<<" "<<luna<<" "<<an<<" "<<pret<<"\n";
        r.close();
         gasit=true;
        }
        else{
            fout<<idF<<" "<<den<<" "<<cl<<" "<<zi<<" "<<luna<<" "<<an<<" "<<pret<<"\n";
        }
    }
    fin.close();
    fout.close();
    
    remove("preRezervari.txt");
    rename("temp.txt","preRezervari.txt");
    if(gasit)cout<<"Rezervare confirmata!\n";
    else cout<<"Nu exista!\n";
}

//REZERVARE

void rezervareSala(string numeSala,int cap,int zi,int luna,int an,string fac,string client){

        if(!validareCapacitate(cap)){
          cout<<"Capacitate invalida!\n";
          return;
        }

         if(!validareData(zi,luna,an)){
          cout<<"Data invalida!\n";
          return;
        }

          vector<Sala>s=citireSali();
           for(auto&x:s){
            if(x.getDenumire()==numeSala){
                if(x.getCapacitate()<cap){
                    cout<<"Capacitate insuficienta!\n";
                    return;
                }

               if(!x.getDisponibilitate()){
                 cout<<"Sala indisponibila!\n";
                   return;
                }

           bool ok=false;
           for(auto&f:x.getFacilitati())
           if(f==fac)ok=true;
           
           if(!ok){
            cout<<"Nu are facilitatea dorita!\n";
            return;
}

   ifstream fin("Rezervari.txt");
   int lastId=0;

       string data,sala,cl;
     int id;

           while(fin>>data>>id>>sala>>cl)
            if(id>lastId)lastId=id;

           fin.close();

       ofstream fout("Rezervari.txt",ios::app);

   fout<<to_string(zi)<<"/"<<to_string(luna)<<"/"<<to_string(an)<<" "<<lastId+1<<" "<<x.getDenumire()<<" "<<client<<"\n";
 
          cout<<"REZERVARE EFECTUATA!\n";
         return;
        }
    }

      cout<<"Sala nu exista!\n";
}

//ANULARE REZERVARE
void anulareRezervari(int zi,int luna,int an,int idCautat,string numeClientCautat)
{
    ifstream fin("Rezervari.txt");
    ofstream fout("temp.txt");

    if(!fin){
        cout<<"Fisierul Rezervari.txt nu exista!\n";
        return;
    }

    string data,sala,nume,prenume;
    int id;

    string dataCautata=to_string(zi)+"/"+to_string(luna)+"/"+to_string(an);

    bool gasit=false;

    while(fin>>data>>id>>sala>>nume>>prenume)
    {
        string full=nume+" "+prenume;

        if(data==dataCautata && id==idCautat && full==numeClientCautat)
        {
            gasit=true;
            continue;
        }

        fout<<data<<" "<<id<<" "<<sala<<" "<<nume<<" "<<prenume<<"\n";
    }

    fin.close();
    fout.close();

    remove("Rezervari.txt");
    rename("temp.txt","Rezervari.txt");

    if(!gasit)
        cout<<"REZERVARE ANULATA CU SUCCES!\n";
    else
        cout<<"NU S-A GASIT REZERVAREA!\n";
}

//STERGERE

void stergerePreRezervare(int id,string client){
ifstream fin("preRezervari.txt");
ofstream temp("temp.txt");
        int idF,zi,luna,an;
        string den,cl;
        double pret;

        bool gasit=false;

            while(fin>>idF>>den>>cl>>zi>>luna>>an>>pret){
                  if(!(idF==id&&cl==client)){
                    temp<<idF<<" "<<den<<" "<<cl<<" "<<zi<<" "<<luna<<" "<<an<<" "<<pret<<"\n";
                }
                else gasit=true;
            }

          fin.close();
          temp.close();

            remove("preRezervari.txt");
            rename("temp.txt","preRezervari.txt");

            if(!gasit)cout<<"REZERVAREA PROVIZORIE A FOST STEARSA!\n";
            else cout<<"Nu exista!\n";
        }

//AFISARI REZERVARI

   void afisarePreRezervari(){
     ifstream fin("preRezervari.txt");
     cout<<"\n ---LISTA REZERVARI PROVIZORII ---\n";
           string data;
           int id;
           string sala,client;

           bool gasit=false;

         while(fin>>data>>id>>sala>>client){
          cout<<data<<" "<<id<<" "<<sala<<" "<<client<<"\n";
          gasit=true;
         }
         if(!gasit) cout<<"Nu exista rezervari provizorii!\n";
}   

         void afisareToateRezervarile(){
              ifstream fin("Rezervari.txt");
              cout<<"\n --- LISTA TUTUROR REZERVARILOR ---\n";
              string data;
              int id;
              string sala,client;
              bool gasit=false;

           while(fin>>data>>id>>sala>>client){
               cout<<data<<" "<<id<<" "<<sala<<" "<<client<<"\n";
               gasit=true;
           }
           if(!gasit) cout<<"Nu exista rezervari!\n";
}

//REZERVARI PERSONALE

void vizualizareRezervariPersonale(string client){
ifstream fin("Rezervari.txt");
  cout<<"\n --- AFISARE REZERVARI PERSONALE ---\n";
  string data,sala,n1,n2;
  int id;
  bool gasit=false;
      while(fin>>data>>id>>sala>>n1>>n2){
         string full=n1+" "+n2;
         if(full==client){
         cout<<data<<" "<<id<<" "<<sala<<" "<<full<<"\n";
         gasit=true;
        }
    }
    if(!gasit) cout<<"Nu ati efectuati rezervari!\n";
}

//MODIFICARE DATA

void modificareData(int id,string client,int z1,int l1,int a1,int z2,int l2,int a2){
ifstream fin("Rezervari.txt");
ofstream fout("temp.txt");

string data,sala,n1,n2;
int idF;
bool gasit=false;

    string vechi=to_string(z1)+"/"+to_string(l1)+"/"+to_string(a1);
    string nou=to_string(z2)+"/"+to_string(l2)+"/"+to_string(a2);

       while(fin>>data>>idF>>sala>>n1>>n2){
         if(data==vechi&&idF==id){
            data=nou;
            gasit=true;
         }
         fout<<data<<" "<<idF<<" "<<sala<<" "<<n1<<" "<<n2<<"\n";
        }

fin.close();
fout.close();

remove("Rezervari.txt");
rename("temp.txt","Rezervari.txt");

if(gasit) cout<<"Data a fost modificata!\n";
else cout<<"Data nu a putut fi gasita!\n";
}

//INFORMATII

void informatiiUtileSali(){
vector<Sala>s=citireSali();

int maxCap=0;
double maxPret=0;

for(auto&x:s){
    if(x.getCapacitate()>maxCap)maxCap=x.getCapacitate();
    if(x.getPretBaza()>maxPret)maxPret=x.getPretBaza();
}

ifstream fin("Rezervari.txt");

map<string,int>freq;

string data,sala,n1,n2;
int id;

while(fin>>data>>id>>sala>>n1>>n2)
freq[sala]++;

      string best="";
        int mx=0;

        for(auto&p:freq){
           if(p.second>mx){
            mx=p.second;
            best=p.first;
        }
    }

cout<<"\n---INFORMATII---\n";
cout<<"Capacitatea maxima: "<<maxCap<<"\n";
cout<<"Pretul maxim: "<<maxPret<<"\n";
cout<<"Cea mai dorita sala: "<<best<<"\n";
cout<<"Numarul de rezervari a celei mai dorite sali: "<<mx<<"\n";
}