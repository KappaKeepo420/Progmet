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

void zetMenu(gobord &gobord) {

	char keuze = '\0';
	bool stop = 0;

	while (!stop) {

		gobord.drukAf();
		keuze = leesOptie();

		switch (keuze) {
			case '/':
				if (gobord.locatie(gobord.getMuisX(), gobord.getMuisY())->kleur != '\0') {
					break;
				}
				gobord.doeZet(gobord.getKleur(), gobord.getMuisX(), gobord.getMuisY());
				gobord.randomZet(gobord.getCPUKleur());
				break;
			case 'W': case 'w':
				gobord.verplaatsHoog();
				break;
			case 'A': case 'a':
				gobord.verplaatsLinks();
				break;
			case 'S': case 's':
				gobord.verplaatsLaag();
				break;
			case 'D': case 'd':
				gobord.verplaatsRechts();
				break;
			case 'V': case 'v':
				gobord.setVervolg(true);
				cout << "Vervolgpartijen: " << gobord.vervolgPartijen(gobord.getKleur()) << endl;
				gobord.setVervolg(false);
				break;
			case 'X': case 'x':
				stop = 1;
				break;
			default:
				cout << " Ongeldige selectie, probeer opnieuw." << endl;
				break;
		}
	}
}

void cpuVscpu(gobord &gobord) {

	while (true) {
		gobord.randomZet('w');
		gobord.drukAf();
		gobord.randomZet('b');
		gobord.drukAf();
	}
}

void hoofdMenu(gobord &gobord) {

	bool goed = 0, cpu = 0;
	char keuze;

	cout << " \e[4mM\e[0mens tegen CPU of \e[4mC\e[0mPU tegen CPU? ";

	while (!goed) {
		keuze = leesOptie();
		if (keuze == 'c' || keuze == 'C') {
			gobord.setCPU(1);
			goed = 1;
			cpu = 1;
		} else if (keuze == 'm' || keuze == 'M') {
			gobord.setCPU(0);
			goed = 1;
		} else {
			cout << " Ongeldige keuze, probeer opnieuw: ";
		}
	}

	goed = 0;

	if (keuze == 'm' || keuze == 'M') {

		cout << " Met welke kleur wilt u spelen? (\e[4mW\e[0mit / \e[4mB\e[0mlauw) ";

		while (!goed) {
			keuze = leesOptie();
			if (keuze == 'w' || keuze == 'W') {
				gobord.setKleur('w');
				goed = 1;
			} else if (keuze == 'b' || keuze == 'B') {
				gobord.setKleur('b');
				goed = 1;
			} else {
				cout << " Ongeldige keuze, probeer opnieuw: ";
			}
		}
	}
	if (cpu) {
		cpuVscpu(gobord);
	} else {
		zetMenu(gobord);
	}
}

int main() {

	gobord gobord(3,3);

	hoofdMenu(gobord);

	return 0;
}