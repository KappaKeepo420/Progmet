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
}

gobord::gobord() {

}

gobord::gobord(int breedte, int hoogte) {

	this->hoogte = hoogte;
	this->breedte = breedte;
	this->muislocatie[0] = breedte / 2;
	this->muislocatie[1] = hoogte / 2;

	bouwBord();
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
	stukken++;
	if (gewonnen(kl, locatie(i,j))) {
		cout << "GG EZ" << endl;
	}
	klaar();
}

void gobord::randomZet (char kl) {

	int ranX, ranY;

	do {
		ranX = getRandmt19937(0, breedte);
		ranY = getRandmt19937(0, hoogte);
	} while (locatie(ranX, ranY)->kleur != '\0');
	
	doeZet(kl, ranX, ranY);
}

bool gobord::gewonnen (char &kleur, bordvakje* laatstezet) {

	bordvakje* loc = laatstezet;
	int teller [8] = {0};
	int j;
	bool gedraaid = 0;

	for (int i = 0; i < 8; i++) {
		gedraaid = 0;
		while (loc->buren[i] != NULL && !gedraaid) {
			if (loc->kleur == loc->buren[i]->kleur) {
				teller[i]++;
				loc = loc->buren[i];
				if (teller[i] == 4) {
					return 1;
				}
			} else if (!gedraaid) {
				teller[i] = 1;
				j = i;
				gedraaid++;

				if (j < 4) {
					j += 4;
				} else {
					j -= 4;
				}
				while (loc->buren[j] != NULL && loc->kleur == loc->buren[j]->kleur) {
					if (loc->kleur == loc->buren[j]->kleur) {
						teller[i]++;
					}
					if (teller[i] == 5) {
						return 1;
					}
					loc = loc->buren[j];
				}
				gedraaid = 1;
			}
		}
	}
	return 0;
}

bool gobord::klaar () {

	if (stukken == hoogte * breedte) {
		return 1;
	}
	return 0;
}

void gobord::drukAf (bordvakje* temp) {

	bordvakje* hulp = temp;
	int j = 0;

	for (int i = 0; i < hoogte; i++) {

		while (hulp != NULL) {

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
}

gobord::~gobord() {
  // TODO
}//gobord::~gobord

void gobord::setKleur(char kleur) {
 	this->kleur = kleur;
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

bordvakje* gobord::getIngang() {
	return ingang;
}