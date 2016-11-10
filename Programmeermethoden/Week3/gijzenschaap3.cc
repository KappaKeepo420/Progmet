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

const int MAX = 30;
const int START_HOOGTE = 20;
const int START_BREEDTE = 20;
const int START_RANDOM = 50;

int randomgetal ();
int leesgetal (int bovengrens);

class Nonogram {
	public:
		Nonogram();
		void drukaf(int beschrijven);
		void vulrandom();
		void maakschoon();
		void vullen();
		void verplaatshoog();
		void verplaatslinks();
		void verplaatsrechts();
		void verplaatslaag();
		void rijbeschrijving(int rij);
		void maakkolombeschrijving();
		void printkolombeschrijving();
		void setHoogte(int hoogte);
		void setBreedte(int breedte);
		void setPercentage(int percentage);
	private:
		bool nono[MAX][MAX];
		bool oplossing[MAX][MAX];
		int beschrijving [MAX][MAX] = {{0}};
		int muislocatie [2];
		int hoogte, breedte, percentage, aryhoogte;
};

Nonogram::Nonogram () {

	setHoogte(START_HOOGTE);
	setBreedte(START_BREEDTE);
	setPercentage(START_RANDOM);
	maakschoon();
}

void Nonogram::setHoogte (int hoogte) {

	this->hoogte = hoogte;
	this->muislocatie[0] = hoogte / 2;
}

void Nonogram::setBreedte (int breedte) {

	this->breedte = breedte;
	this->muislocatie[1] = breedte / 2;
}

void Nonogram::setPercentage (int percentage) {

	this->percentage = percentage;
}

void Nonogram::rijbeschrijving(int rij) {
	int rijen[hoogte][breedte];
	int teller = 0, nulteller = 0;
    int blok = 0;

	for (int i = 0; i < breedte; i++) {
		if (nono[rij][i] == 1) {
			teller++;
		} else if (teller != 0) {
			cout << teller << " ";
			rijen[rij][blok] = teller;
			teller = 0;
		} else {
			nulteller++;
		}
		if (i == breedte-1 && teller != 0) {
			cout << teller;
			rijen[rij][blok] = teller;
			blok++;
		}
	}
	rijen[rij][blok] = 0;
	if (nulteller -1 == breedte) {
		cout << "0";
	}
}

void Nonogram::maakkolombeschrijving() {

	int num = 0, teller = 0;

	for (int i = 0; i <= breedte; i++) {
		for (int j = 0; j <= hoogte; j++) {
			if (nono[j][i] == 1) {
				teller++;
			} else if (teller != 0) {
				beschrijving[i][num] = teller;
				teller = 0;
				num++;
			}
		}
		if (num > aryhoogte) {
			aryhoogte = num;
		}
		num = 0;
	}
}

void Nonogram::printkolombeschrijving() {

	for (int j = 0; j < aryhoogte; j++) {
		for (int i = 0; i < breedte; i++) {
			if (beschrijving[i][j] <= 9) {
				cout << " ";
			}
			if (j == 0 || beschrijving[i][j] != 0) {
				cout << " " << beschrijving[i][j];
			} else {
				cout << "  ";
			}
		}
		cout << endl;
	}
}

void Nonogram::drukaf (int beschrijven) {

	if ((hoogte != 0) && (breedte != 0)) {
		for (int i = 0; i < hoogte; i++) {
			cout << "  ";
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
			rijbeschrijving(i);
			cout << endl;
		}
	} else {
		cout << " Uw nonogram is leeg!" << endl;
	}
	if (beschrijven == 1) {
		maakkolombeschrijving();
		beschrijven = 0;
	}
	printkolombeschrijving();
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
			int getal = randomgetal();
			if ((getal/10) < percentage) {
				nono[i][j] = 1;
			} else {
				nono[i][j] = 0;
			}
		}
	}
}	

void Nonogram::vullen () {

	for (int i = 0; i < hoogte; i++) {
		for (int j = 0; j < breedte; j++) {
			if (this->muislocatie[0] == i && this->muislocatie[1] == j) {
				if (nono[i][j] == 0) {
					nono[i][j] = 1;
				} else {
					nono[i][j] = 0;
				}
			}
		}
	}
}

void Nonogram::verplaatshoog () {
	if (this->muislocatie[0] == 0) {
		this->muislocatie[0] = hoogte - 1;
	} else {
		this->muislocatie[0]--;
	}
}

void Nonogram::verplaatslaag () {
	if (this->muislocatie[0] == hoogte - 1) {
		this->muislocatie[0] = 0;
	} else {
		this->muislocatie[0]++;
	}
}

void Nonogram::verplaatslinks () {
	if (this->muislocatie[1] == 0) {
		this->muislocatie[1] = breedte - 1;
	} else {
		this->muislocatie[1]--;
	}
}

void Nonogram::verplaatsrechts () {
	if (this->muislocatie[1] == breedte - 1) {
		this->muislocatie[1] = 0;
	} else {
		this->muislocatie[1]++;
	}
}

int randomgetal () {

	static int getal = 50;

	getal = (221 * getal + 1) % 1000;

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
		"\e[4mP\e[0marameters | \e[4mT\e[0moggle cursor | \e[4mS\e[0mtoppen\e[0m "
		"| Reset \e[4mB\e[0meschrijving ";
	}
	if (optie == 1) {
		cout << " \e[4mH\e[0moogte | \e[4mB\e[0mreedte | \e[4mP\e[0mercentage |";
		cout << "  \e[4mT\e[0merug ";
	}
	if (optie == 2) {
		cout << " Gebruik 'ijkl' om de cursor te bewegen en '/' om te toggelen. | \e[4mT\e[0merug ";
	}
}

int cursormenu (Nonogram &a) {

	char keuze = '\0';
	bool stop = 0;

	while (!stop) {

		a.drukaf(0);
		menu(2);
		keuze = getkarakter();

		switch (keuze) {
			case '/':
				a.vullen();
				break;
			case 'I': case 'i':
				a.verplaatshoog();
				break;
			case 'J': case 'j':
				a.verplaatslinks();
				break;
			case 'K': case 'k':
				a.verplaatslaag();
				break;
			case 'L': case 'l':
				a.verplaatsrechts();
				break;
			case 't': case 'T':
				stop = 1;
				break;
			default:
				cout << " Ongeldige selectie, probeer opnieuw." << endl;
				break;
		}
	}
	return 0;
}

int parametermenu (Nonogram &a) {

	char keuze = '\0';
	bool stop = 0;

	while (!stop) {

		a.drukaf(0);
		menu(1);
		keuze = getkarakter();

		switch (keuze) {
			case 'H': case 'h':
				cout << " Kies uw hoogte: ";
				a.setHoogte(leesgetal(MAX));
				break;
			case 'B': case 'b':
				cout << " Kies uw breedte: ";
				a.setBreedte(leesgetal(MAX));
				break;
			case 'P': case 'p':
				cout << " Voor hoeveel procent wilt u het nonogram gevuld hebben? (0-100) ";
				a.setPercentage(leesgetal(100));
				a.vulrandom();
				break;
			case 'T': case 't':
				stop = 1;
				break;
			default:
				cout << " Ongeldige selectie, probeer opnieuw." << endl;
				break;
		}
	}
	return 0;
}

int keuzemenu (Nonogram &a) {

	char keuze = '\0';
	bool stop = 0;

	while (!stop) {
		menu(0);
		keuze = getkarakter();

		switch (keuze) {
			case 'C': case 'c':
				a.maakschoon();
				a.drukaf(0);
				break;
			case 'R': case 'r':
				a.vulrandom();
				a.drukaf(0);
				break;
			case 'P': case 'p':
				parametermenu(a);
				a.drukaf(0);
				break;
			case 'S': case 's':
				exit(0);
				a.drukaf(0);
			case 'T': case 't':
				cursormenu(a);
				a.drukaf(0);
				break;
			case 'B': case 'b':
				a.drukaf(1);
				break;
			default:
				cout << " Ongeldige selectie, probeer opnieuw." << endl;
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
	a.drukaf(0);
	keuzemenu(a);

	return 1;
}