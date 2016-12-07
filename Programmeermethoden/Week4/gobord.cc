// file gobord.cc
#include <iostream>
#include "gobord.h"
using namespace std;

bordvakje::bordvakje() {
	
	for (int i = 0; i < 8; i++) {
		this->buren[i] = NULL;
	}
}

gobord::gobord() {

}

gobord::gobord(int hoogte, int breedte) {

	this->hoogte = hoogte;
	this->breedte = breedte;

	bouwBord();
}

void gobord::bouwBord() {

	bordvakje* rij1 = maakRij(breedte);
	bordvakje* rij2 = maakRij(breedte);

	ingang = rij1;

	for (int i = 0; i < hoogte; i++) {
		rits(rij1, rij2);
		rij1 = rij2;
		rij2 = maakRij(breedte);
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

		if (boven->buren[RECHTS]) {
			boven = boven->buren[RECHTS];
		} else {
			break;
		}
		if (onder->buren[LINKS]) {
			onder = onder->buren[RECHTS];
		} else {
			break;
		}
	}
}

void gobord::drukAf (bordvakje* temp) {

	bordvakje* hulp = temp;

	for (int i = 0; i < hoogte; i++) {

		while (hulp != NULL) {

			cout << "\e[92m\u25A1\e[0m  " << temp->kleur;

			hulp = hulp->buren[RECHTS];
		}
		temp = temp->buren[ONDER];
		hulp = temp;
		cout << endl;
	}
}

gobord::~gobord() {
  // TODO
}//gobord::~gobord

void gobord::setKleur(char kleur) {
 	this->kleur = kleur;
}

void gobord::setCPU(bool cpu) {
	this->cpu = cpu;
}

bordvakje* gobord::getIngang() {

	return ingang;
}