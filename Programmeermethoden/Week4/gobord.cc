// file gobord.cc
#include <iostream>
#include <random>
#include "gobord.h"
using namespace std;

int getRandmt19937(const int& A, const int& B) {

	static random_device randDev;
	static mt19937 twister(randDev());
	static uniform_int_distribution<int> dist;

	dist.param(uniform_int_distribution<int>::param_type(A, B));

	return dist(twister);
}

bordvakje::bordvakje() {
	
	for (int i = 0; i < 8; i++) {
		this->buren[i] = NULL;
	}
	this->kleur = '\0';
}

gobord::gobord() {

	this->ingang = NULL;
	this->laatstezet = NULL;
	this->vervolg = false;
	this->cpu = false;
	this->hoogte = 19;
	this->breedte = 19;
	this->muislocatie[0] = breedte / 2;
	this->muislocatie[1] = hoogte / 2;
	bouwBord();
}

gobord::gobord(int breedte, int hoogte) {

	this->ingang = NULL;
	this->laatstezet = NULL;
	this->vervolg = false;
	this->cpu = false;
	this->hoogte = hoogte;
	this->breedte = breedte;
	this->muislocatie[0] = breedte / 2;
	this->muislocatie[1] = hoogte / 2;
	bouwBord();
}

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

void gobord::bouwBord() {

	bordvakje* rij1 = maakRij(breedte);

	ingang = rij1;

	for (int i = 1; i < hoogte; i++) {
		bordvakje* rij2 = maakRij(breedte);
		rits(rij1, rij2);
		rij1 = rij2;
	}
}

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

void gobord::doeZet (char kl, int i, int j) {

	locatie(i, j)->kleur = kl;
	laatstezet = locatie(i, j);
	Stapel.voegtoe(i,j);
	stukken++;
}

void gobord::randomZet (char kl) {

	int ranX, ranY;

	do {
		ranX = getRandmt19937(0, breedte);
		ranY = getRandmt19937(0, hoogte);
	} while (locatie(ranX, ranY)->kleur != '\0');
	
	doeZet(kl, ranX, ranY);
}

bool gobord::controleer (char kl) {

	string kleur;

	if (kl == 'w') {
		kleur = "Wit";
	} else {
		kleur = "Blauw";
	}

	if (gewonnen()) {
		drukAf();
		cout << kleur << " heeft gewonnen!" << endl;
		return true;
	}
	if (klaar()) {
		drukAf();
		cout << "Het bord is vol! Gelijkspel." << endl;
		return true;
	}
	return false;
}

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
			if (!loc->buren[i]) {
				cout << "leeg" << endl;
			} else {
				cout << "t " << teller << " i " << i << "k " << loc->kleur << "k2 " << loc->buren[i]->kleur << endl;
			}
			if (teller >= 2) {
				return true;
			}
			teller = 0;
			while (loc->buren[i + 4] && loc->kleur == loc->buren[i + 4]->kleur) {
				teller++;
				loc = loc->buren[i + 4];
			}
			if (!loc->buren[i + 4]) {
				cout << "leeg" << endl;
			} else {
				cout << "a " << teller << " i " << i << "k " << loc->kleur << "k2 " << loc->buren[i + 4]->kleur << endl;
			}
			if (teller >= 2) {
				return true;
			}
		}
	}
	return false;
}

bool gobord::klaar () {

	return (stukken == hoogte * breedte);
}

void gobord::zetTerug (int i, int j) {

	locatie(i, j)->kleur = '\0';
	Stapel.verwijder(i, j);
	stukken--;
}

int gobord::vervolgPartijen (char kl) {

	int partijen = 0;

	if (klaar()) {
		return 1;
	}

	for (int j = 0; j < hoogte; j++) {
		for (int i = 0; i < breedte; i++) {
			if (locatie(i, j)->kleur == '\0') {
				doeZet(kl, i, j);
				switchKleur(kl);
				if (gewonnen()) {
					partijen++;
				} else {
					partijen += vervolgPartijen(kl);
				}
				zetTerug(i, j);
				switchKleur(kl);
			}
		} 
	}
	return partijen;
}

char gobord::switchKleur (char kl) {

	if (kl == 'w') {
		return 'b';
	} else {
		return 'w';
	}
	return '\0';
}

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

void gobord::setKleur(char kl) {
 	this->kleur = kl;
}

char gobord::getKleur() {
	return kleur;
}

char gobord::getCPUKleur() {
	if (kleur == 'w') {
		return 'b';
	} else {
		return 'w';
	}
}

int gobord::getMuisX() {
	return muislocatie[0];
}

int gobord::getMuisY() {
	return muislocatie[1];
}

int gobord::getHoogte() {
	return hoogte;
}

void gobord::setCPU(bool cpu) {
	this->cpu = cpu;
}

void gobord::setVervolg(bool vervolg) {
	this->vervolg = vervolg;
}