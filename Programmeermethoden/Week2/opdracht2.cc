
/*	Auteurs 		- Jort Gijzen		1874233
					- Lennard Schaap	1914839
	Studie			- BSc Informatica
	Compiler		- G++
	Datum 			- 30 september 2016

	-----Uitleg
*/

#include <iostream> 
#include <string>
#include <cstdlib>
#include <fstream>
#include <climits>

using namespace std; 

int draaiom (int n) {

	int omgekeerd = 0;

	while (n != 0) {
		omgekeerd = n % 10 + omgekeerd * 10;
		n = n / 10;
	}

	return n;
}

bool islychrel (int a) {

	int n = 0;

	while (!(a <= INT_MAX)) {

		n = a;
		draaiom(n);

		if (n == a) {
			return 0;
		} else {
			a += n;
		}
	}

	return 1;
}

int main () {

	ifstream invoer;
	ofstream uitvoer;
	string filenaam;
	char kar;
	int lijnteller = 0, diepte = 0, tabgrootte = 0, getal = 0;
	bool comment = 0, slash = 0, inspringen = 0, sluitacc = 0, poep = 0;
/*
	int testgetal = 12345;

	cout << draaiom(testgetal);
	cout << islychrel(testgetal);
*/
	cout << "Welke file wilt u openen? ";
	cin >> filenaam;

	cout << "Kies een tabgrootte: ";
	cin >> tabgrootte;

	invoer.open (filenaam.c_str());
	uitvoer.open ("output.cc");

	if (invoer.fail()) {
		cout << filenaam << " kan niet worden geopend.\n";
		return 1;
	}

	if (uitvoer.fail()) {
		cout << "output.cc kan niet worden gemaakt.\n";
	}
	
	while (!invoer.eof()) {

		invoer.get(kar);

		if (kar == '/' && !comment && !slash) {
			slash = 1;
		} else if (kar == '/' && slash) {
			comment = 1;
		} else if (kar != '/' && slash && !comment) {
			slash = 0;
			comment = 0;
			uitvoer.put('/');
		} else if (kar == '{' && !comment) {
			diepte++;
		} else if (kar == '\n') {
			lijnteller++;
			comment = 0;
			inspringen = 1;
			slash = 0;
		} else if (inspringen) {
			if (kar == ' ' || kar == '\t') {
				comment = 1;
			} else if (kar == '/') {
				slash = 1;
			} else if (!slash) {
				if (kar == '}') {
					diepte--;
					comment = 0;
				}

				for (int i = 0; i < (diepte * tabgrootte); i++) {
					uitvoer.put(' ');
				}
				comment = 0;
				inspringen = 0;
			}
		} else if (kar == '}') {
			diepte--;
		} else {
			slash = 0;
		}

		if (kar >= '0' && kar <= '9') {
			getal = getal * 10 + kar;
		} else if (getal != 0) {
				islychrel(getal);
			}
			getal = 0;
		}

		if (!slash && !comment) {
			uitvoer.put(kar);
		}
	}
}






/*
void doewat (ifstream &invoer, ofstream &uitvoer) {


*/