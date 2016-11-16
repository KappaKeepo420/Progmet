/*	Auteurs 		- Jort Gijzen		1874233
					- Lennard Schaap	1914839
	Studie			- BSc Informatica
	Compiler		- G++
	Datum 			- 30 september 2016
	Opdracht		- Netjes

	Dit programma probeert een foutloos te compileren C++ programma een beetje te begrijpen.
	Het programma laat de uitvoerfile netjes inspringen en laat al het commentaar weg.
	Er worden om een door de gebruiker in te stellen paar regels statistieken over het
	bestand geprint.
	Ook wordt voor elk positief getal gekeken of dit een lychrel getal is.
*/

#include <iostream> 
#include <string>
#include <cstdlib>
#include <fstream>
#include <climits>

using namespace std; 

/*	Dit is de draaiom functie. Deze functie neemt een positieve integer en draait deze
	om door midden van een wiskundige formule.
*/
int draaiom (int getal) {

	int omgekeerd = 0;

	while (getal != 0) {
		omgekeerd = getal % 10 + omgekeerd * 10;
		getal = getal / 10;
	}

	return omgekeerd;
}

/* Dit is de islychrel functie. Deze functie kijkt voor elk geheel getal > 0 of het een
	Lychrel getal is. Op het scherm wordt geprint wat het aantal iteraties is om tot
	een palindroom te komen. Als er overflow gedetecteerd is, wordt dit geprint op het
	scherm.
*/
bool islychrel (int temp) {

	int getal = temp, omgekeerd = 0, teller = 0;
	bool overflow = 0;

	while (!overflow) {

		omgekeerd = draaiom(temp);

		if ((omgekeerd < 0) || (INT_MAX - temp < omgekeerd)) { // Checkt of er overflow gegenereerd zal worden;
			cout << getal << ": Overflow gedetecteerd na " << teller << " iteraties.\n" << endl;
			return 0;
		} else if (omgekeerd == temp) { // Palindroom gevonden. 

			cout << getal << " is geen lychrel getal." << endl;
			cout << "Palindroom gevonden na " << teller << " iteraties.\n" << endl;
			return 0;
		} else {
			temp += omgekeerd;
		}
		
		teller++;
	}

	return 1;
}

/*	Dit is de netjes functie. Deze functie laat de gebruiker een invoerfile kiezen. Hierna
	wordt de gebruiker gevraagd om een tabgrootte voor de uitvoerfile te kiezen. Als 
	laatste wordt de gebruiker gevraagd om ma welk aantal regels er statistieken moeten 
	worden weergegeven. Vervolgens wordt het invoerbestand gelezen. Commentaar wordt
	weggehaald en de inspring wordt netjes geregeld met de tabgrootte die de gebruiker 
	heeft ingesteld. Ook wordt elk geheel getal geevalueerd door de islychrel functie.
	Als het programma klaar is met inlezen wordt er nog een laatste blokje statistiek
	weergegeven.
*/
int netjes () {

	ifstream invoer;
	ofstream uitvoer;
	string filenaam;
	char kar;
	int lijnteller = 0, diepte = 0, tabgrootte = 0, getal = 0, gelezenkar = 0, geprintkar = 0;
	int cijfer = 0, endlines = 0, statistiekregel = 0;
	bool comment = 0, slash = 0, inspringen = 0, sluitacc = 0;

	cout << "------------------------------------------------------------" << endl;
	cout << "|  Auteurs:            - Jort Gijzen       1874233         |" << endl;
	cout << "|                      - Lennard Schaap    1914839         |" << endl;
	cout << "|  Studie:             - Bsc Informatica                   |" << endl;
	cout << "|  Opdracht:           - Tweede Opdracht: Netjes           |" << endl;
	cout << "|  Datum:              - Oktober 2016                      |" << endl;
	cout << "|                                                          |" << endl;
	cout << "|  Dit programma probeert een foutloos C++ net uit te      |" << endl;
	cout << "|  printen door commentaar eruit te halen, inspringen te   |" << endl;
	cout << "|  regelen en lychrel getallen te ontdekken.               |" << endl;
	cout << "------------------------------------------------------------" << endl;

	cout << "Welke file wilt u openen? ";
	cin >> filenaam;

	cout << "Kies een tabgrootte: ";
	cin >> tabgrootte;

	cout << "Om de hoeveel regels wilt u een statistiek?: ";
	cin >> statistiekregel;
	cout << endl;


	invoer.open (filenaam.c_str());
	uitvoer.open ("output.cc");

	if (invoer.fail()) {
		cout << filenaam << " kan niet worden geopend." << endl;
		return 1;
	}

	if (uitvoer.fail()) {
		cout << "output.cc kan niet worden gemaakt." << endl;
	}
	
	while (!invoer.eof()) { // De loop waarin de karakters in de invoerfile worden gelezen.

		invoer.get(kar);
		gelezenkar++;

		if (kar == '/' && !comment && !slash) {
			slash = 1;
		} else if (kar == '/' && slash) {
			comment = 1;
		} else if (kar != '/' && slash && !comment) {
			slash = 0;
			comment = 0;
			uitvoer.put('/');
		} else if (kar == '{' && !comment) {
			diepte++;
		/* Statistieken worden bijgehouden bij elke newline. */
		} else if (kar == '\n') {
			lijnteller++;
			comment = 0;
			inspringen = 1;
			slash = 0;
			endlines++;
		} else if (inspringen) {
			if (kar == ' ' || kar == '\t') {
				comment = 1;
			} else if (kar == '/') {
				slash = 1;
			} else if (!slash) {
				if (kar == '}') {
					diepte--;
					comment = 0;
				}
				/* Hier wordt de inspring in de uitvoerfile gezet */
				for (int i = 0; i < (diepte * tabgrootte); i++) {
					uitvoer.put(' ');
				}
				comment = 0;
				inspringen = 0;
			}
		} else if (kar == '}') {
			diepte--;
		} else {
			slash = 0;
		}

		/* Hier worden de tussenstatistieken geprint */
		if (endlines % statistiekregel == 0 && kar == '\n') {
			cout << "Huidige aantal ingelezen  karakters (voor regel " << endlines << "): " << gelezenkar << endl;
			cout << "Huidige aantal afgedrukte karakters (voor regel " << endlines << "): " << gelezenkar << "\n" << endl;
		}

		/* Leest getallen in de invoerfile en stopt deze in de islychrel functie. */
		if ((kar >= '0' && kar <= '9') && (!comment)){
			cijfer = kar - 48;
			getal = (getal * 10) + cijfer;
		} else if (getal != 0) {
			if (islychrel(getal)) {
				cout << " is een lychrel getal!" << endl;
			}
			getal = 0;
		}

		/* Hier worden de gelezen karakters in de uitvoerfile gezet */
		if (!slash && !comment) {
			uitvoer.put(kar);
			geprintkar++;
		}
	}

	/* Hier worden de laatste statistieken geprint */
	cout << "Uiteindelijke aantal ingelezen karakters: " << gelezenkar << endl;
	cout << "Uiteindelijke aantal ingelezen  karakters: " << gelezenkar << endl;
	cout << "Uiteindelijke aantal afgedrukte karakters: " << geprintkar << endl;
	cout << "Totaal gelezen regels: " << endlines << endl;
}

/*	Dit is de main functie. Deze roept de netjes functie aan, die de andere benodigde
	functies aanroept.
*/	
int main () {

	netjes();

	return 1;
}
