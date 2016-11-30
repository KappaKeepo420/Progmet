// file gobord.h

class Bordvakje {
  public:
    char kleur;           //     7 0 1
    Bordvakje* buren[8];  //     6   2
    Bordvakje();          //     5 4 3
};//bordvakje

class Gobord {

  public:
    Gobord();
    Gobord (int hoogte, int breedte);
    ~Gobord();
    void setCPU(bool cpu);
    void setKleur(char kleur);
    void bouwBord();
    void randomZet(char kl, int & i, int & j);
    void mensZet(char kl, int & i, int & j);
    void drukaf();
    bool klaar();
    bool gewonnen(char & kl);
    void doezet(char kl, int i, int j);
    // TODO
  private:
    Bordvakje* ingang;
    int hoogte, breedte;
    char kleur;
    bool cpu;
    void rits(Bordvakje* boven, Bordvakje* onder);
    Bordvakje* maakRij(int aantal);
    // TODO

};//gobord

