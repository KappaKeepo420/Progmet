// file gobord.cc
#include <iostream>
#include "gobord.h"
using namespace std;

Gobord::Gobord() {
	
}//gobord::gobord

Gobord::~Gobord() {
  // TODO
}//gobord::~gobord

void Gobord::setKleur(char kleur) {
 	this->kleur = kleur;
}

void Gobord::setCPU(bool cpu) {
	this->cpu = cpu;
}