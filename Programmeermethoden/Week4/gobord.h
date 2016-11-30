// file gobord.h

class bordvakje {
  public:
    char kleur;           //     7 0 1
    bordvakje* buren[8];  //     6   2
    bordvakje();          //     5 4 3
};//bordvakje

class gobord {

  public:
    gobord();
    gobord(int hoogte, int breedte);
    ~gobord();
    void setCPU(bool cpu);
    void setKleur(char kleur);
    void bouwBord();
    void rijenplakken();
    void randomZet(char kl, int & i, int & j);
    void mensZet(char kl, int & i, int & j);
    void drukaf();
    bool klaar();
    bool gewonnen(char & kl);
    void doezet(char kl, int i, int j);
    // TODO
  private:
    bordvakje* ingang;
    int hoogte, breedte;
    char kleur;
    bool cpu;
    void rits(bordvakje* boven, bordvakje* onder);
    bordvakje* maakRij(int aantal);
    // TODO

};//gobord