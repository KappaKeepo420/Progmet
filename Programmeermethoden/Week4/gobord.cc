/*	Auteurs 		- Jort Gijzen		1874233
					- Lennard Schaap	1914839
	Studie			- BSc Informatica
	Compiler		- g++ -std=c++11
	Datum 			- 18 december 2016
	Opdracht		- Gomoku
	File			- gobord.cc
	
	Dit zijn de memberfuncties van de gobord klasse.
*/

#include <iostream>
#include <random>
#include "gobord.h"
using namespace std;

/*	De random-functie mt19937 die ons de willekeurige getallen zal leveren.
	Zie https://en.wikipedia.org/wiki/Mersenne_Twister voor meer informatie. */
int getRandmt19937(const int& A, const int& B) {

	static random_device randDev;
	static mt19937 twister(randDev());
	static uniform_int_distribution<int> dist;

	dist.param(uniform_int_distribution<int>::param_type(A, B));

	return dist(twister);
}

/*	Bordvakje constructor: Initialiseert alle buren naar NULL. */
bordvakje::bordvakje() {
	
	for (int i = 0; i < 8; i++) {
		this->buren[i] = NULL;
	}
	this->kleur = '\0';
}

/*	Gobord constructor: Initialiseert de beginwaarden. */ 
gobord::gobord() {

	this->ingang = NULL;
	this->laatstezet = NULL;
	this->vervolg = false;
	this->cpu = false;
	this->stukken = 0;
	this->hoogte = 19;
	this->breedte = 19;
	this->muislocatie[0] = breedte / 2;
	this->muislocatie[1] = hoogte / 2;
	bouwBord();
}

/*	Gobord constructor met parameters: Initialiseert de beginwaarden. */ 
gobord::gobord(int breedte, int hoogte) {

	this->ingang = NULL;
	this->laatstezet = NULL;
	this->vervolg = false;
	this->cpu = false;
	this->stukken = 0;
	this->hoogte = hoogte;
	this->breedte = breedte;
	this->muislocatie[0] = breedte / 2;
	this->muislocatie[1] = hoogte / 2;
	bouwBord();
}

/*	Gobord destructor. Verwijdert alle aangemaakte bordvakjes. */
gobord::~gobord() {

	bordvakje* boven;

	while (ingang->buren[ONDER]) {
		boven = ingang;
		ingang = ingang->buren[ONDER];
		while (boven->buren[RECHTS]) {
			boven = boven->buren[RECHTS];
			delete boven->buren[LINKS];
		}
		boven = boven->buren[ONDER];
		delete boven->buren[BOVEN];
	}
	while (ingang->buren[RECHTS]) {
		ingang = ingang->buren[RECHTS];
		delete ingang->buren[LINKS];
	}
	delete ingang;
}

/*	Verplaatst de cursor naar boven. */
void gobord::verplaatsHoog () {
	if (this->muislocatie[1] == 0) {
		this->muislocatie[1] = hoogte - 1;
	} else {
		this->muislocatie[1]--;
	}
}

/*	Verplaatst de cursor naar beneden. */
void gobord::verplaatsLaag () {
	if (this->muislocatie[1] == hoogte - 1) {
		this->muislocatie[1] = 0;
	} else {
		this->muislocatie[1]++;
	}
}

/*	Verplaatst de cursor naar links. */
void gobord::verplaatsLinks () {
	if (this->muislocatie[0] == 0) {
		this->muislocatie[0] = breedte - 1;
	} else {
		this->muislocatie[0]--;
	}
}

/*	Verplaatst de cursor naar rechts. */
void gobord::verplaatsRechts () {
	if (this->muislocatie[0] == breedte - 1) {
		this->muislocatie[0] = 0;
	} else {
		this->muislocatie[0]++;
	}
}

/*	Maakt het gobord aan door rijen aan te maken en te ritsen. */
void gobord::bouwBord() {

	bordvakje* rij1 = maakRij(breedte);

	ingang = rij1;

	for (int i = 1; i < hoogte; i++) {
		bordvakje* rij2 = maakRij(breedte);
		rits(rij1, rij2);
		rij1 = rij2;
	}
}

/*	Maakt een dubbelverbonden pointerlijst door bordvakjes aan elkaar te verbinden. */
bordvakje* gobord::maakRij(int aantal) {

	bordvakje* rijingang = NULL;

	for (int i = 0; i < aantal; i++) {
		bordvakje* temp;
		temp = new bordvakje;
		if (rijingang != NULL) {
			temp->buren[RECHTS] = rijingang;
			rijingang->buren[LINKS] = temp;
		}
		rijingang = temp;
	}

	return rijingang;
}

/*	Verbind twee rijen die door maakRij zijn gemaakt verticaal aan elkaar. */
void gobord::rits(bordvakje* boven, bordvakje* onder) {

	while (boven && onder) {

		onder->buren[BOVEN] = boven;
		boven->buren[ONDER] = onder;

		if (boven->buren[RECHTS]) {
			onder->buren[RECHTS_BOVEN] = boven->buren[RECHTS];
		}
		if (boven->buren[LINKS]) {
			onder->buren[LINKS_BOVEN] = boven->buren[LINKS];
		}
		if (onder->buren[RECHTS]) {
			boven->buren[RECHTS_ONDER] = onder->buren[RECHTS];
		}
		if (onder->buren[LINKS]) {
			boven->buren[LINKS_ONDER] = onder->buren[LINKS];
		}

		boven = boven->buren[RECHTS];
		onder = onder->buren[RECHTS];
	}
}

/*	Geeft een pointer naar het veld (i, j) terug. */
bordvakje* gobord::locatie (int x, int y) {

	bordvakje* loc = ingang;

	while (loc->buren[RECHTS] && x != 0) {
		loc = loc->buren[RECHTS];
		x--;
	}
	while (loc->buren[ONDER] && y != 0) {
		loc = loc->buren[ONDER];
		y--;
	}

	return loc;
}

/*	Verandert de kleur van het bordvakje(i, j) naar de kleur die de zet doet.
	Slaat de locatie op in de laatstezet pointer.
	Voegt de zet toe aan de stapel.
*/
void gobord::doeZet (char kl, int i, int j) {

	laatstezet = locatie(i, j);
	locatie(i, j)->kleur = kl;
	Stapel.voegtoe(i, j);
	stukken++;
}

/*	Controleert of er een winnaar is of dat het bord vol is voordat er een zet wordt gezet.
	Genereert een willekeurig getallen op het bord om een zet op te doen.
	Als het vakje al bezet is wordt er een nieuw vakje gekozen.
*/
bool gobord::randomZet (char kl) {

	int ranX, ranY;

	if (controleer(switchKleur(kl))) {
		return false;
	}

	do {
		ranX = getRandmt19937(0, breedte - 1);
		ranY = getRandmt19937(0, hoogte - 1);
	} while (locatie(ranX, ranY)->kleur != '\0');
	
	doeZet(kl, ranX, ranY);

	return true;
}

/*	Controleert of er een winnaar is of dat het bord vol is. */
bool gobord::controleer (char kl) {

	string kleur;

	if (kl == 'w') {
		kleur = "Wit";
	} else {
		kleur = "Blauw";
	}

	if (gewonnen()) {
		stukken = 0;
		//drukAf();
		//cout << kleur << " heeft gewonnen!" << endl;
		return true;
	}
	if (klaar()) {
		stukken = 0;
		//drukAf();
		//cout << "Het bord is vol! Gelijkspel." << endl;
		return true;
	}
	return false;
}

/*	Rekent uit of de laatste zet een winnende zet is door in elke richting te controleren
	of er x vakjes op een rij staan. */
bool gobord::gewonnen () {

	if (laatstezet) {

		bordvakje* loc = laatstezet;
		int teller = 0;

		for (int i = 0; i < 4; i++) {
			teller = 0;
			loc = laatstezet;
			while (loc->buren[i] && loc->kleur == loc->buren[i]->kleur) {
				teller++;
				loc = loc->buren[i];
			}
			if (teller >= 2) {
				return true;
			}
			teller = 0;
			while (loc->buren[i + 4] && loc->kleur == loc->buren[i + 4]->kleur) {
				teller++;
				loc = loc->buren[i + 4];
			}
			if (teller >= 4) {
				return true;
			}
		}
	}
	return false;
}

/*	Returnt of het bord vol is of niet. */
bool gobord::klaar () {

	return (stukken == hoogte * breedte);
}

/*	Haalt de laatste zet van de stapel en maakt het bijbehorende bordvakje leeg. */
void gobord::zetTerug () {

	int i = 0, j = 0;

	Stapel.verwijder(i, j);
	locatie(i, j)->kleur = '\0';
	stukken--;
}

/*	Berekent het aantal vervolgpartijen voor de huidige bordstand door deze functie
	recursief aan te roepen. */
int gobord::vervolgPartijen (char kl) {

	int partijen = 0;

	if (klaar()) {
		return 1;
	}

	for (int j = 0; j < hoogte; j++) {
		for (int i = 0; i < breedte; i++) {
			/*	Bekijkt of er een leeg vakje is om een zet op te doen. */
			if (locatie(i, j)->kleur == '\0') {
				/* Doet een zet op een leeg vakje. */
				doeZet(kl, i, j);
				switchKleur(kl);
				if (gewonnen()) {
					partijen++;
				} else {
					/*	Roept de functie recursief aan als er niet gewonnen is. */
					partijen += vervolgPartijen(kl);
				}
				/*	Zet de laaste zet terug als er een winaar is of als de functie iets
					heeft gereturned. */
				zetTerug();
				switchKleur(kl);
			}
		} 
	}
	return partijen;
}

/*	Wisselt de char 'w' naar 'b' en vice versa. */
char gobord::switchKleur (char kl) {

	if (kl == 'w') {
		return 'b';
	} else {
		return 'w';
	}
	return '\0';
}

/*	Drukt het huidige gobord af. Als er een mens speelt zal de huidige cursorlocatie
	geprint worden in een andere kleur. */
void gobord::drukAf () {

	bordvakje* hulp = ingang;
	bordvakje* temp = ingang;
	int j = 0;

	if (cpu) {
		muislocatie[0] = -1;
		muislocatie[1] = -1;
	}

	for (int i = 0; i < hoogte; i++) {

		while (hulp) {
			if (muislocatie[0] == j && muislocatie[1] == i) {
				if (hulp->kleur == 'w') {
					cout << "\e[36m\u25CF\e[0m  ";
				} else if (hulp->kleur == 'b') {
					cout << "\e[36m\u25CF\e[0m  ";
				} else if (hulp->kleur == '\0') {
					cout << "\e[36m\u25A1\e[0m  ";
				}
			} else {
				if (hulp->kleur == 'w') {
					cout << "\e[39m\u25CF\e[0m  ";
				} else if (hulp->kleur == 'b') {
					cout << "\e[34m\u25CF\e[0m  ";
				} else if (hulp->kleur == '\0') {
					cout << "\u25A1  ";
				}
			}
			hulp = hulp->buren[RECHTS];
			j++;
		}
		temp = temp->buren[ONDER];
		hulp = temp;
		j = 0;
		cout << endl;
	}
	cout << endl;
}

/*	Retunt de x en y waarden van de muislocatie respectievelijk. */

int gobord::getMuisX() {
	return muislocatie[0];
}

int gobord::getMuisY() {
	return muislocatie[1];
}

/* Verandert de cpu variabele van de gobord klasse naar true of false. */
void gobord::setCPU(bool cpu) {
	this->cpu = cpu;
}