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
		void drukaf(bool beschrijven);
		void vulrandom();
		void maakschoon();
		void vullen();
		void maakrijbeschrijving(int rij);
		void printrijbeschrijving(int rij);
		void controleerrijen(int rij);
		void verplaatshoog(int func);
		void verplaatslinks(int func);
		void verplaatsrechts(int func);
		void verplaatslaag(int func);
		void maakkolombeschrijving();
		void printkolombeschrijving();
		void controleerkolommen();
		void setHoogte(int hoogte);
		void setBreedte(int breedte);
		void setPercentage(int percentage);
	private:
		bool nono[MAX][MAX];
		bool oplossing[MAX][MAX];
		int rijen[MAX][MAX] = {{0}};
		int rijennu[MAX][MAX] = {{0}};
		int kolommen[MAX][MAX] = {{0}};
		int kolommennu[MAX][MAX] = {{0}};
		int vink[MAX] = {0};
		int aryhoogteary[MAX] = {0};
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

void Nonogram::maakrijbeschrijving(int rij) {

	int num = 0, teller = 0;

	for (int i = 0; i < breedte; i++) {

		rijennu[rij][i] = 0;

		if (nono[rij][i] == 1) {
			teller++;
		} else if (teller != 0) {
			rijennu[rij][num] = teller;
			teller = 0;
			num++;
		}
		if (i == breedte - 1) {
			rijennu[rij][num] = teller;
			num++;
		}
	}
}

void Nonogram::printrijbeschrijving(int rij) {

	int teller = 0;
	
	for (int i = 0; i < breedte; i++) {
		if (i == 0 || rijen[rij][i] != 0) {
			cout << rijen[rij][i] << " ";
		}
		if (rijen[rij][i] == rijennu[rij][i]) {
			teller++;
		}
	}
	if (teller == breedte) {
		cout << "\u2713";
	}
}

void Nonogram::controleerrijen(int rij) {

	for (int i = 0; i < breedte; i++) {
		rijen[rij][i] = rijennu[rij][i];
	}
}

void Nonogram::maakkolombeschrijving() {

	int num = 0, teller = 0;
	aryhoogte = 0;

	for (int i = 0; i < breedte; i++) {
		for (int j = 0; j < hoogte; j++) {
			
			kolommennu[i][j] = 0;

			if (nono[j][i] == 1) {
				teller++;
			} else if (teller != 0) {
				kolommennu[i][num] = teller;
				teller = 0;
				num++;
			}
			if (j == hoogte - 1) {
				kolommennu[i][num] = teller;
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
			if (kolommennu[i][j] == kolommen[i][j]) {
				vink[i] == 1;
			}
			if (kolommen[i][j] <= 9) {
				cout << " ";
			}
			if (j == 0 || kolommen[i][j] != 0) {
				cout << " " << kolommen[i][j];
			} else {
				cout << "  ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < breedte; i++) {
		if (vink[i] == 1) {
			cout << " \u2713";
		} else {
			cout << "  ";
		}
	}
	cout << endl;
}

void Nonogram::controleerkolommen() {

	for (int i = 0; i < breedte; i++) {
		for (int j = 0; j < hoogte; j++) {
			kolommen[i][j] = kolommennu[i][j];
		}
	}
}

void Nonogram::drukaf (bool beschrijven) {

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
			if (beschrijven){
				controleerrijen(i);
			}
			maakrijbeschrijving(i);
			printrijbeschrijving(i);
			cout << endl;
		}
	} else {
		cout << " Uw nonogram is leeg!" << endl;
	}
	if (beschrijven) {
		controleerkolommen();
	}
	maakkolombeschrijving();
	printkolombeschrijving();

	beschrijven = 0;
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
				nono[i][j] = !nono[i][j];
			}
		}
	}
}

void Nonogram::verplaatshoog (int func) {
	if (this->muislocatie[0] == 0) {
		this->muislocatie[0] = hoogte - 1;
	} else {
		this->muislocatie[0]--;
	}
	if (func == 1) {
		nono[this->muislocatie[0]][this->muislocatie[1]] = 1;
	} else if (func == 2) {
		nono[this->muislocatie[0]][this->muislocatie[1]] = 0;
	}
}

void Nonogram::verplaatslaag (int func) {
	if (this->muislocatie[0] == hoogte - 1) {
		this->muislocatie[0] = 0;
	} else {
		this->muislocatie[0]++;
	}
	if (func == 1) {
		nono[this->muislocatie[0]][this->muislocatie[1]] = 1;
	} else if (func == 2) {
		nono[this->muislocatie[0]][this->muislocatie[1]] = 0;
	}
}

void Nonogram::verplaatslinks (int func) {
	if (this->muislocatie[1] == 0) {
		this->muislocatie[1] = breedte - 1;
	} else {
		this->muislocatie[1]--;
	}
	if (func == 1) {
		nono[this->muislocatie[0]][this->muislocatie[1]] = 1;
	} else if (func == 2) {
		nono[this->muislocatie[0]][this->muislocatie[1]] = 0;
	}
}

void Nonogram::verplaatsrechts (int func) {
	if (this->muislocatie[1] == breedte - 1) {
		this->muislocatie[1] = 0;
	} else {
		this->muislocatie[1]++;
	}
	if (func == 1) {
		nono[this->muislocatie[0]][this->muislocatie[1]] = 1;
	} else if (func == 2) {
		nono[this->muislocatie[0]][this->muislocatie[1]] = 0;
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
	int func = 0;
	
	while (!stop) {

		a.drukaf(0);
		menu(2);
		keuze = getkarakter();

		switch (keuze) {
			case '/':
				a.vullen();
				break;
			case 'I': case 'i':
				a.verplaatshoog(func);
				break;
			case 'J': case 'j':
				a.verplaatslinks(func);
				break;
			case 'K': case 'k':
				a.verplaatslaag(func);
				break;
			case 'L': case 'l':
				a.verplaatsrechts(func);
				break;
			case 'U': case 'u':
				func = 1;
				break;
			case 'O': case 'o':
				func = 2;
				break;
			case 'N': case 'n':
				func = 0;
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
	cout << " -> Toggle een vakje door een / in te toetsen gevolgd door een enter.\n" << endl;
}

int main() {

	welkommenu();

	Nonogram a = Nonogram();

	a.drukaf(1);

	keuzemenu(a);

	return 1;
}