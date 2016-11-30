// file gobord.cc
#include <iostream>
#include "gobord.h"
using namespace std;

bordvakje::bordvakje() {
	
}

gobord::gobord() {

}

gobord::gobord(int hoogte, int breedte) {

	this->hoogte = hoogte;
	this->breedte = breedte;
}//gobord::gobord

void gobord::bouwBord() {

	for (int i = 0; i < breedte; i++) {
		bordvakje* top;
		top = new bordvakje;
		if (ingang != NULL) {
			top->buren[2] = ingang;
			ingang->buren[6] = top;
		}
		ingang = top;
		cout << "boem" << endl;
	}

	for (int j = 0; j < hoogte; j++) {
		rijenplakken();
	}
}

void gobord::rijenplakken() {

	for (int i = 0; i < breedte; i++) {
		bordvakje* nieuw;
		nieuw = new bordvakje;
		if (ingang != NULL) {
			nieuw->buren[0] = ingang;
			nieuw->buren[1] = ingang->buren[2];
			ingang = nieuw->buren[4];
			ingang->buren[3] = nieuw->buren[2];
		}
		ingang = nieuw;
		cout << "hatseflats" << endl;
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