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
	}
	nepingang = ingang;
	for (int j = 0; j < hoogte; j++) {
		rijenplakken();
	}
}

void gobord::rijenplakken() {

	for (int i = 0; i < breedte; i++) {
		bordvakje* nieuw;
		nieuw = new bordvakje;
		if (dingang != NULL) {
			nieuw->buren[2] = dingang;
			dingang->buren[6] = nieuw;
			if (dingang->buren[2] != NULL) {
				nieuw->buren[0] = nepingang;
				nieuw->buren[1] = nepingang->buren[2];
				nepingang->buren[4] = nieuw;
				nepingang->buren[2]->buren[5] = nieuw;
				nepingang = nepingang->buren[2];
				nieuw = nieuw->buren[2];
			}
		}
		dingang = nieuw;
	}
	nepingang = dingang;
}

void gobord::drukaf() {

	printer = ingang;
	nepingang = ingang;
	for (int j = 0; j < hoogte; j++) {
		for (int i = 0; i < breedte; i++) {
			if (printer != NULL) {
				cout << "X ";
			}
			printer = printer->buren[2];
		}
		cout << endl;
		nepingang = nepingang->buren[4];
		printer = nepingang;
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