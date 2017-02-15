/*  Auteurs         - Jort Gijzen       1874233
                    - Lennard Schaap    1914839
    Studie          - BSc Informatica
    Compiler        - g++ -std=c++11
    Datum           - 18 december 2016
    Opdracht        - Gomoku
    File            - stapel.cc
    
    Dit is de headerfile van gobord.cc.
*/

#include "stapel.h"
#include <iostream>

using namespace std;

/*	De vakje-constructor. */
vakje::vakje() {
	i = 0;
	j = 0;
	volgende = NULL;
}

/*	De stapel constructor.. */
stapel::stapel() {
	ingang = NULL;
}

/*	De stapel destructor. */
stapel::~stapel() {
	int i, j;

	while (!leeg()) {
		verwijder(i, j);
	}
}

/*	Checkt of de stapel leeg is. */
bool stapel::leeg() {
	return (!ingang);
}

/* Voegt een vakje toe aan de stapel. */
void stapel::voegtoe(int i, int j) {
	vakje* vak = new vakje;
	vak->i = i;
	vak->j = j;
	vak->volgende = ingang;
	ingang = vak;
}

/* Verwijdert het bovenste vakje van de stapel. */
void stapel::verwijder(int &i, int &j) {
	if (!leeg()) {
		vakje* vakje = ingang;
		i = ingang->i;
		j = ingang->j;
		ingang = ingang->volgende;
		delete vakje;
	}
}