/*	Auteurs 		- Jort Gijzen		1874233
					- Lennard Schaap	1914839
	Studie			- BSc Informatica
	Compiler		- G++
	Datum 			- 
	Opdracht		- Nonogram

	-- Uitleg
*/

#include <iostream> 
#include <string>
#include <cstdlib>
#include <fstream>
#include <climits>

using namespace std;

const int MAX = 50;
const int START_HOOGTE = 20;
const int START_BREEDTE = 20;

int randomgetal (int range);

class Nonogram {
	public:
		Nonogram();
		void drukaf();
		void vulrandom();
		void maakschoon();
		void maakbeschrijvingen();
		void zetpercentage();
		void setHoogte(int hoogte);
		void setBreedte(int breedte);
	private:
		bool nono[MAX][MAX];
		int muislocatie [2];
		int rijen[MAX][MAX];
		int kolommen[MAX][MAX];
		int hoogte, breedte, precentage, penstatus;
		void maaklijnbeschrijving (bool lijn[], int ell, int beschr[]);
};

Nonogram::Nonogram () {

	setHoogte(START_HOOGTE);
	setBreedte(START_BREEDTE);
}

void Nonogram::setHoogte (int hoogte) {

	this->hoogte = hoogte;
	this->muislocatie[0] = hoogte / 2;
	this->muislocatie[1] = breedte / 2;
	maakschoon();
}

void Nonogram::setBreedte (int breedte) {

	this->breedte = breedte;
	this->muislocatie[0] = hoogte / 2;
	this->muislocatie[1] = breedte / 2;
	maakschoon();
}

void Nonogram::drukaf () {
	
	if ((breedte != 0) && (hoogte != 0)) {
		for (int i = 0; i < hoogte; i++) {
			cout << " ";
			for (int j = 0; j < breedte; j++) {
				if (this->muislocatie[0] == i && this->muislocatie[1] == j) {
					if (nono[i][j] == 0) {
						cout << "\e[92m\u25A1\e[0m  ";
					} else {
						cout << "\e[92m\u25A0\e[0m  ";
					}
				} else if (nono[i][j] == 1) {
					cout << "\u25A0  ";
				} else {
					cout << "\u25A1  ";
				}
			}
			cout << endl;
		}
	} else {
		cout << " Uw nonogram is leeg!" << endl;
	}
}

void Nonogram::maakschoon () {

	for (int i = 0; i < hoogte; i++) {
		for (int j = 0; j < breedte; j++) {
			nono[i][j] = 0;
		}
	}
}

void Nonogram::vulrandom () {

	for (int i = 0; i < hoogte; i++) {
		for (int j = 0; j < breedte; j++) {
			nono[i][j] = 1;
		}
	}
}	

int randomgetal (int range) {

	static int getal = 42;

	getal = (221 * getal + 1) % range;

	return getal;
}

int leesgetal (int bovengrens) {

	int cijfer = 0, getal = 0;
	char kar = cin.get();

	while (kar == '\n') {
		kar = cin.get();
	}

	while (kar != '\n') {
		if (kar >= '0' && kar <= '9') {
			cijfer = kar - 48;

			if (getal >= (INT_MAX - cijfer) / 10) {
				cout << " Overflow gedetecteerd, probeer opnieuw." << endl;
				getal = 0;
				cijfer = 0;
				cin.clear();
				return 0;
			}

			getal = (getal * 10) + cijfer;
		}
		kar = cin.get();
	}

	while (getal > bovengrens) {
		getal /= 10;
	}

	return getal;
}

char getkarakter () {

	char keuze;

	cin.clear();
	cin.get(keuze);
	cin.ignore(10000, '\n');

	return keuze;
}

void menu (int optie) {

	if (optie == 0) { 
		cout << " S\e[4mc\e[0mhoon | \e[4mR\e[0mandom | "
		"\e[4mP\e[0marameters | \e[4mS\e[0mtoppen\e[0m ";
	}
	if (optie == 1) {
		cout << " \e[4mH\e[0moogte | \e[4mB\e[0mreedte | \e[4mT\e[0merug | \e[4mS\e[0mtoppen\e[0m ";
	} 
	if (optie == 2) {
		cout << " \e[4mN\e[0monogram | \e[4mS\e[0mtoppen\e[0m ";
	}
}

int parametermenu (Nonogram &a) {

	char keuze = '\0';
	int hoogte = 0, breedte = 0;
	bool stop = 0;

	while (!stop) {

		a.drukaf();

		menu(1);
		keuze = getkarakter();

		switch (keuze) {

			case 'H':
			case 'h':
				cout << " Kies uw hoogte: ";
				hoogte = leesgetal(MAX);
				a.setHoogte(hoogte);
				break;
			case 'B':
			case 'b':
				cout << " Kies uw breedte: ";
				breedte = leesgetal(MAX);
				a.setBreedte(breedte);
				break;
			case 'T':
			case 't':
				stop = 1;
				break;
			case 'S':
			case 's':
				exit(0);
				break;
			default:
				cout << " Ongeldige selectie, probeer opnieuw.\n";
				break;
		}
	}
	return 0;
}

int keuzemenu (Nonogram &a) {

	char keuze = '\0';
	bool stop = 0;

	while (!stop) {

		a.drukaf();

		menu(0);

		keuze = getkarakter();

		switch (keuze) {

			case 'C':
			case 'c':
				a.maakschoon();
				break;
			case 'R':
			case 'r':
				a.vulrandom();
				break;
			case 'P':
			case 'p': 
				parametermenu(a);
				break;
			case 'S':
			case 's':
				exit(0);
			default:
				cout << " Ongeldige selectie, probeer opnieuw.\n";
				break;
		}
	}

	return 0;
}

void welkommenu() {

	cout << " ------------------------------------------------------------" << endl;
	cout << " |  Auteurs:            - Jort Gijzen       1874233         |" << endl;
	cout << " |                      - Lennard Schaap    1914839         |" << endl;
	cout << " |  Studie:             - Bsc Informatica                   |" << endl;
	cout << " |  Opdracht:           - Derde Opgave: Nonogram            |" << endl;
	cout << " |  Datum:              - November 2016                     |" << endl;
	cout << " |                                                          |" << endl;
	cout << " |  Welkom bij nonogram.cc! Dit programma stelt de          |" << endl;
	cout << " |  gebruiker in staat om een nonogram te maken en          |" << endl;
	cout << " |  op te lossen via een menu-systeem.                      |" << endl;
	cout << " ------------------------------------------------------------" << endl;

	cout << " -> Controls: Gebruik IJKL gevolgd door een enter om de" << endl;
	cout << " cursor te bewegen.\n" << endl;
	cout << " -> Gebruik het menu door de onderstreepte letter gevolgd door" << endl;
	cout << " een enter in te toetsen.\n" << endl;
	cout << " -> Toggle een vakje door een x in te toetsen gevolgd door een enter.\n" << endl;
}

int main() {

	welkommenu();

	Nonogram a = Nonogram();

	keuzemenu(a);

	return 1;
}