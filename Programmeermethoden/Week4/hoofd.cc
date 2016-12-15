#include <iostream> 
#include <string>
#include <cstdlib>
#include <fstream>
#include <climits>
#include "gobord.h"

#define MAX_HOOGTE 40
#define MAX_BREEDTE 40

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
				cout << "Overflow gedetecteerd, probeer opnieuw." << endl;
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

char wisselKleur (char kl) {

	if (kl == 'w') {
		return 'b';
	}
	return 'w';
}

void zetMenu(char kl, int hoogte, int breedte) {

	char keuze = '\0';
	bool stop = 0;

	gobord gobord(hoogte, breedte);

	while (!stop) {

		gobord.drukAf();
		keuze = leesOptie();

		switch (keuze) {
			case '/':
				if (gobord.locatie(gobord.getMuisX(), gobord.getMuisY())->kleur != '\0') {
					break;
				}
				gobord.doeZet(kl, gobord.getMuisX(), gobord.getMuisY());
				if (gobord.controleer(kl)) {
					return;
				}
				gobord.drukAf();
				gobord.randomZet(wisselKleur(kl));
				if (gobord.controleer(wisselKleur(kl))) {
					return;
				}
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
				cout << "Vervolgpartijen: " << gobord.vervolgPartijen(kl) << endl;
				break;
			// case 'G': case 'g':
			// 	cout << "Geef de hoogte van uw bord: ";
			// 	gobord.setoogte = leesGetal(MAX_HOOGTE);
			// 	cout << "Geef de breedte van uw bord: ";
			// 	breedte = leesGetal(MAX_BREEDTE);
			// 	break;
			case 'X': case 'x':
				stop = 1;
				break;
			default:
				cout << "Ongeldige selectie, probeer opnieuw." << endl;
				break;
		}
	}
}

void cpuVscpu(int hoogte, int breedte) {

	gobord gobord(hoogte, breedte);

	char kl = 'w';

	gobord.setCPU(true);

	while (!gobord.controleer(wisselKleur(kl))) {
		gobord.drukAf();
		gobord.randomZet(kl);
		gobord.controleer(kl);
		kl = gobord.switchKleur(kl);
	}
}

void hoofdMenu() {

	bool goed = false, cpu = false;
	int hoogte, breedte;
	char keuze, kleur;

	cout << "\e[4mM\e[0mens tegen CPU of \e[4mC\e[0mPU tegen CPU? ";

	while (!goed) {
		keuze = leesOptie();
		if (keuze == 'c' || keuze == 'C') {
			goed = true;
			cpu = true;
		} else if (keuze == 'm' || keuze == 'M') {
			goed = true;
		} else {
			cout << "Ongeldige keuze, probeer opnieuw: ";
		}
	}

	goed = false;

	if (keuze == 'm' || keuze == 'M') {

		cout << "Met welke kleur wilt u spelen? (\e[4mW\e[0mit / \e[4mB\e[0mlauw) ";

		while (!goed) {
			keuze = leesOptie();
			if (keuze == 'w' || keuze == 'W') {
				kleur = 'w';
				goed = true;
			} else if (keuze == 'b' || keuze == 'B') {
				kleur = 'b';
				goed = true;
			} else {
				cout << "Ongeldige keuze, probeer opnieuw: ";
			}
		}
	}

	goed = false;

	cout << "Geef de hoogte van uw bord: ";
	hoogte = leesGetal(MAX_HOOGTE);
	cout << "Geef de breedte van uw bord: ";
	breedte = leesGetal(MAX_BREEDTE);

	if (!cpu) {
		cout << " LUL" << endl;
		while (!goed) {
			zetMenu(kleur, hoogte, breedte);
			cout << "Wilt u nog een keer spelen? (j/n) ";
			keuze = leesOptie();
			if (keuze == 'n' || keuze == 'N') {
				goed = true;
			}
		}
	} else {

		cout << "Hoevaak wilt u dat de computers spelen? ";
		keuze = leesGetal(10000);
		for (int i = 0; i < keuze; i++) {
			cpuVscpu(hoogte, breedte);
		}
	}
}

int main() {

	hoofdMenu();

	return 0;
}