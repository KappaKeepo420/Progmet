/*  Auteurs         - Jort Gijzen       1874233
                    - Lennard Schaap    1914839
    Studie          - BSc Informatica
    Compiler        - g++ -std=c++11
    Datum           - 18 december 2016
    Opdracht        - Gomoku
    File            - gobord.h
    
    Dit is de headerfile van gobord.cc.
*/

#include "stapel.h"

/*  Defines voor het gemak. */

#define BOVEN 0
#define LINKS_BOVEN 1
#define RECHTS 2
#define RECHTS_ONDER 3
#define ONDER 4
#define LINKS_ONDER 5
#define LINKS 6
#define RECHTS_BOVEN 7

/*  De klasse bordvakje. Een bordvakje heeft een kleur en 8 buren. */
class bordvakje {
  public:
    char kleur;                    //     7 0 1
    bordvakje* buren[8];           //     6   2
    bordvakje();                   //     5 4 3
};//bordvakje

/*  De gobord klasse met memberfuncties- en variabelen. 
    Bij het aanmaken van een gobord wordt de stapel ook aangemaakt. */
class gobord {

  public:
    gobord();
    gobord(int hoogte, int breedte);
    ~gobord();
    void setCPU(bool cpu);
    void setKleur(char kl);
    char getKleur();
    char getCPUKleur();
    char switchKleur(char kl);
    int getMuisX();
    int getMuisY();
    int getHoogte();
    void verplaatsHoog();
    void verplaatsLaag();
    void verplaatsLinks();
    void verplaatsRechts();
    void bouwBord();
    bool randomZet(char kl);
    void mensZet(char kl, int & i, int & j);
    void drukAf();
    bool klaar();
    bool gewonnen();
    bool controleer (char kl);
    void doeZet(char kl, int i, int j);
    int vervolgPartijen(char kl);
    void setVervolg(bool vervolg);
    void zetTerug();
    bordvakje* locatie (int x, int y);
  private:
    bordvakje* ingang;
    bordvakje* laatstezet;
    stapel Stapel;
    bool cpu, vervolg;
    int hoogte, breedte, stukken;
    int muislocatie[2];
    void rits(bordvakje* boven, bordvakje* onder);
    bordvakje* maakRij(int aantal);
};