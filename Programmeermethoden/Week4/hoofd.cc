#include <iostream> 
#include <string>
#include <cstdlib>
#include <fstream>
#include <climits>
#include "gobord.h"

using namespace std;

char leesOptie () {

	char keuze;

	cin.clear();
	cin.get(keuze);
	cin.ignore(10000, '\n');

	return keuze;
}
int leesGetal (int bovengrens) {

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

void hoofdMenu(Gobord &gobord) {

	bool goed = 0;
	char keuze;

	cout << " \e[4mM\e[0mens tegen CPU of \e[4mC\e[0mPU tegen CPU? ";

	while (!goed) {
		keuze = leesOptie();
		if (keuze == 'c' || keuze == 'C') {
			gobord.setCPU(1);
			goed = 1;
		} else if (keuze == 'm' || keuze == 'M') {
			gobord.setCPU(0);
			goed = 1;
		} else {
			cout << " Ongeldige keuze, probeer opnieuw: ";
		}
	}

	goed = 0;

	if (keuze == 'm' || keuze == 'M') {

		cout << " Met welke kleur wilt u spelen? (\e[4mW\e[0mit / \e[4mR\e[0mood) ";

		while (!goed) {
			keuze = leesOptie();
			if (keuze == 'w' || keuze == 'W') {
				gobord.setKleur('w');
				goed = 1;
			} else if (keuze == 'r' || keuze == 'R') {
				gobord.setKleur('r');
				goed = 1;
			} else {
				cout << " Ongeldige keuze, probeer opnieuw: ";
			}
		}
	}
}

int main() {

	Gobord gobord;

	hoofdMenu(gobord);
	
	return 0;
}
