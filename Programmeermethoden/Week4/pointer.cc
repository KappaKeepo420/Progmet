
//                                                                      
// Programmeermethoden 2016
//
// http://www.liacs.leidenuniv.nl/~kosterswa/pm/pointer.cc
// C++-programma om te oefenen in het gebruik van pointers.
// Er moet een enkelverbonden pointerlijst gefabriceerd worden,
// waarbij de "vakjes" die met elkaar verbonden worden bestaan uit
//   1. Een int(eger)
//   2. Een pointer naar een int(eger) (of NULL)
//   3. Een pointer naar het volgende vakje (of NULL)
// Schrijf de functies Afdrukken, MaakVakje, Toevoegen en Verwijderen   
// --- in deze volgorde.  
// Dit is de bijbehorende opgave: 
//   http://www.liacs.leidenuniv.nl/~kosterswa/pm/oefpoint.cc
//                        
// Compiler: GNU g++
// Datum: 14 november 2016
// Auteur: Walter Kosters, Informatica Universiteit Leiden
//         email w.a.kosters@liacs.leidenuniv.nl
//

#include <iostream>
using namespace std;

// het soort vakje waar het om draait:
class vakje {              // een struct mag ook
  public:                  
    int info;    
    int* andere;
    vakje* volgende;    
};//vakje

//
//   +-----+        +----+----+-----+        +----+----+-----+
//   |   --+------> | 34 |  | |   --+------> | 56 |  | | NULL|
//   +-----+        +----+--+-+-----+        +----+--+-+-----+
//  ingang                  |                        |
//                          V                        V
//                       +----+                   +----+
//                       | 23 |                   | 18 |
//                       +----+                   +----+
//       
// ingang wijst dus een vakje uit een lijst vakjes aan
// waarbij ieder vakje informatie bevat (het info-veld), 
// een pointer naar een int(eger) (het andere-veld),
// en een pointer naar het volgende vakje; om zulke 
// structuurtjes te maken is doorgaans in totaal steeds 
// twee maal new nodig, voor het voorbeeld hierboven in totaal vier
// Een voorbeeld: het getal 34 (in het eerste vakje)
// wordt afgedrukt via:  
//   cout << ingang->info << endl;
// En het getal 18 (toegankelijk door het tweede vakje) via:
//   cout << *(ingang->volgende->andere) << endl;
// En een pointer hulp (vakje* hulp) gaat naar het vakje
// met onder andere 56 erin wijzen via:
//   hulp = ingang->volgende;
//

// ************************************************************************

void Afdrukken (vakje* ingang) {
// druk lijst met ingang als ingang af 
  vakje* p = ingang;  // pointertje om lijst mee door te lopen 
  while ( p != NULL ) {
    cout << " # " << p->info << " | ";
    if ( p->andere != NULL )
      cout << *(p->andere) << " # " << endl;
    else
      cout << "--" << " # " << endl;
    p = p->volgende;
  }//while
  cout << endl;
}//Afdrukken
 
void Toevoegen (vakje* & ingang, int een, int twee) {
// voeg vakje met een en twee erin vooraan lijst ingang toe
// preciezer: nieuw vakje met getal een en een POINTER naar een     
// nieuwe int met getal twee erin                                   
// als twee = -1, dan p->andere NULL maken
  vakje* p;  // hulppointertje
  p = new vakje;
  p->info = een;
  if ( twee != -1 ) {
    p->andere = new int;
    *(p->andere) = twee;
  }//if
  else
    p->andere = NULL;
  p->volgende = ingang;
  ingang = p;
}//Toevoegen

void Verwijderen (vakje* & ingang) {
// gooi eerste vakje van lijst ingang weg als ingang niet NULL is
  vakje* p = ingang;  // hulppointertje
  if ( ingang != NULL ) {
    ingang = ingang->volgende;
    if ( p->andere != NULL )
      delete p->andere;   // !!! 
    delete p;           // in deze volgorde
  }  // if
}//Verwijderen

void LeesInGetallen (int & een, int & twee) {
// lees integers een en twee in
  cout << "Eerste getal svp .. ";
  cin >> een;
  cout << "Tweede getal svp .. ";
  cin >> twee;
}//LeesInGetallen

// *********************************************************************

int main () {

  vakje* ingang = NULL; // ingang van de op te bouwen lijst (nu nog leeg)
  char keuze;           // wat wil de gebruiker?
  int een, twee;        // toe te voegen getallen

  do {
    cout << "Kies uit: [s]toppen, [t]oevoegen,   " << endl
         << "          [a]fdrukken, [v]erwijderen" << endl
         << "Uw keuze: ";
    cin >> keuze;
    switch (keuze) {
      case 's': case 'S':
        cout << "Dat was het dan ..." << endl; 
        break;
      case 't': case 'T':
        LeesInGetallen (een,twee);
        Toevoegen (ingang,een,twee);
        break;
      case 'a': case 'A':
        Afdrukken (ingang);
        break;
      case 'v': case 'V':
        Verwijderen (ingang);
        break; 
      default:
        cout << "Niet toegestane menukeuze ..." << endl;
    }//switch
  }//do
  while ( ! ( keuze == 's' ) && ! ( keuze == 'S' ) );

  while ( ingang != NULL )  // netjes opruimen
    Verwijderen (ingang);

  return 0;

}//main

