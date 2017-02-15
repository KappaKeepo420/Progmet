/*  Auteurs         - Jort Gijzen       1874233
                    - Lennard Schaap    1914839
    Studie          - BSc Informatica
    Compiler        - g++ -std=c++11
    Datum           - 18 december 2016
    Opdracht        - Gomoku
    File			- hoofd.cc
    
    Dit programma stelt de gebruiker in staat om een gobord te maken en gomoku te spelen.
	Er kan tegen een computer worden gespeeld of er is de mogelijkheid om twee computers
	tegen elkaar te laten spelen. Wit mag altijd beginnen in deze implementatie.
	Het formaat van het bord kan door de gebruiker gekozen worden.
*/

#include <iostream> 
#include <string>
#include <cstdlib>
#include <fstream>
#include <climits>
#include <time.h>
#include "gobord.h"

#define MAX_HOOGTE 40
#define MAX_BREEDTE 40

using namespace std;

/*	Leest een karakter in met cin.get(). */
char leesOptie () {

	char keuze;

	cin.clear();
	cin.get(keuze);
	cin.ignore(10000, '\n');

	return keuze;
}

/*	Leest een getal karakter voor karakter in met cin.get(). Heeft als parameter de
	maximale waarde van het getal. */
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
	/* Als er geen geldige waarde wordt gegeven, wordt er een standaardwaarde doorgegeven. */
	if (getal > 0) {
		return getal;
	}
	return 19;
}

/* Wisselt de char 'w' naar 'b' en vice versa. */
char wisselKleur (char kl) {

	if (kl == 'w') {
		return 'b';
	}
	return 'w';
}

/* Het menu waarin er door de speler tegen een cpu gespeeld kan worden. */
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
			case 'T': case 't':
				gobord.zetTerug();
				gobord.zetTerug();
				break;
			case 'X': case 'x':
				stop = 1;
				break;
			default:
				cout << "Ongeldige selectie, probeer opnieuw." << endl;
				break;
		}
	}
}

/*	Laat twee cpu's tegen elkaar spelen door om de beurt een willekeurige zet te doen. */
void cpuVscpu(int hoogte, int breedte) {

	gobord gobord(hoogte, breedte);

	char kl = 'w';

	gobord.setCPU(true);

	while (gobord.randomZet(kl)) {
		//gobord.drukAf();
		kl = gobord.switchKleur(kl);
	}
}

/*	Het hoofdmenu van het programma. Laat de gebruiker kiezen of hij tegen een cpu wil spelen
	of twee cpu's tegen elkaar wil laten spelen voor een door de gebruiker te kiezen aantal rondes.
	Tevens mag de gebruiker de hoogte en breedte van het bord kiezen bij aanvang van het spel */
void hoofdMenu() {

	bool goed = false, cpu = false, stop = false;
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
		while (!goed) {
			cout << "Gebruik wasd om de cursor te bewegen. '/' om een zet te doen, 't' om" << endl;
			cout << "een zet terug te nemen en 'x' om het potje te stoppen." << endl;
			zetMenu(kleur, hoogte, breedte);
			cout << "Wilt u nog een keer spelen? (j/n) ";
			while (!stop) {
				keuze = leesOptie();
				if (keuze == 'n' || keuze == 'N') {
					goed = true;
					stop = true;
				} else {
					cout << "Ongeldige keuze, probeer opnieuw. " << endl;
				}
			}
		}
	} else {

		ofstream uitvoer;
		uitvoer.open("cpuvscpu.txt");

		cout << "Hoevaak wilt u dat de computers spelen? ";
		keuze = leesGetal(INT_MAX);

		double time_total = 0.0;

		for (int i = 0; i < 500; i++) {

			clock_t begin = clock();
			cpuVscpu(hoogte, breedte);
			clock_t end = clock();

			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			time_total += time_spent;
			uitvoer << hoogte << " " << time_spent << endl;
			hoogte++;
			breedte++;
		}
		cout << time_total << endl;
	}
}

/*	De main functie die het hoofdmenu aanroept. */
int main() {

	hoofdMenu();

	return 0;
}