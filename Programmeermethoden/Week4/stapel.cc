#include "stapel.h"
#include <iostream>

using namespace std;

vakje::vakje() {
	i = 0;
	j = 0;
	volgende = NULL;
}

stapel::stapel() {
	ingang = NULL;
}

stapel::~stapel() {
	int i, j;

	while (!leeg()) {
		verwijder(i, j);
	}
}

bool stapel::leeg() {
	return !ingang;
}

void stapel::voegtoe(int i, int j) {

	vakje* vak = new vakje;
	vak->i = i;
	vak->j = j;
	vak->volgende = ingang;
}

void stapel::verwijder(int &i, int &j) {

	if (!leeg()) {
		vakje* vakje = ingang;
		i = ingang->i;
		j = ingang->j;
		ingang = ingang->volgende;
		delete vakje;
	}
}