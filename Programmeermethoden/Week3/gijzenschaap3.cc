/*	Auteurs 		- Jort Gijzen		1874233
					- Lennard Schaap	1914839
	Studie			- BSc Informatica
	Compiler		- G++
	Datum 			- 
	Opdracht		- Nonogram

	-- Uitleg
*/

#include <iostream> 
#include <string>
#include <cstdlib>
#include <fstream>
#include <climits>
#include "nonogram.h"

using namespace std; 

int randomgetal (int range) {

	static int getal = 42;

	getal = (221 * getal + 1) % range;

	return getal;
}

int leesgetal (int bovengrens) {

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
				break;
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

char getkarakter () {

	char keuze;

	cin.clear();
	cin.get(keuze);
	cin.ignore(10000, '\n');

	return keuze;
}

void menu (bool t) {

	cout << "S\e[4mc\e[0mhoon | \e[4mR\e[0mandom | "
		"\e[4mP\e[0marameters | \e[4mS\e[0mtoppen\e[0m ";

	if (t)
		cout << "| \e[4mT\e[0merug ";
}

int parametermenu () {

	char keuze = '\0';
	bool stop = 0;

	while (!stop) {

		menu(1);
		keuze = getkarakter();

		switch (keuze) {

			case 'C':
			case 'c':
				cout << "c gekozen\n";
				break;
			case 'R':
			case 'r':
				cout << "r gekozen\n";
				break;
			case 'P':
			case 'p': 
				cout << "p gekozen\n";
				break;
			case 'S':
			case 's':
				exit(0);
				break;
			case 'T':
			case 't':
				stop = 1;
				break;
			default:
				cout << "Ongeldige selectie, probeer opnieuw.\n";
				break;
		}
	}
	return 0;
}

int keuzemenu () {

	char keuze = '\0';
	bool stop = 0;

	while (!stop) {

		menu(0);

		keuze = getkarakter();

		switch (keuze) {

			case 'C':
			case 'c':
				cout << "c gekozen\n";
				break;
			case 'R':
			case 'r':
				cout << "r gekozen\n";
				break;
			case 'P':
			case 'p': 
				cout << "p gekozen\n";
				parametermenu();
				break;
			case 'S':
			case 's':
				exit(0);
			default:
				cout << "Ongeldige selectie, probeer opnieuw.\n";
				break;
		}
	}

	return 0;
}

int main () {

	/*
		for (int i = 0; i < 99; i++) {
			cout << randomgetal(100) << endl;
		}
	*/

	nonogram a;

	a.drukaf();

	cout << "invoer: ";
	cout << "getal: " << leesgetal(10000) << "\n";

	//keuzemenu();

	return 1;

}