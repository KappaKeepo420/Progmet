// file gobord.h
class bordvakje {
  public:
    char kleur;           //     7 0 1
    bordvakje* buren[8];  //     6   2
    bordvakje ( );        //     5 4 3
};//bordvakje

class gobord {
  private:
    bordvakje* ingang;
    int hoogte, breedte;
    void rits (bordvakje* boven, bordvakje* onder);
    bordvakje* maakrij (int aantal);
    // TODO
  public:
    gobord ( );
    gobord (int hoogte, int breedte);
    ~gobord ( );
    void bouwbord ( );
    void randomzet (char kl, int & i, int & j);
    void menszet (char kl, int & i, int & j);
    void drukaf ( );
    bool klaar ( );
    bool gewonnen (char & kl);
    void doezet (char kl, int i, int j);
    // TODO
};//gobord

