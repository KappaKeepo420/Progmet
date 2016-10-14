
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

using namespace std; 

int main () {

	ifstream invoer;
	ofstream uitvoer;
	string filenaam;
	char kar;
	int lijnteller = 0, diepte = 0, tabgrootte = 0;
	bool comment = 0, slash = 0, inspringen = 0, sluitacc = 0, poep = 0;

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
		} else if (kar == '}') {
			diepte--;
			if (inspringen) {
				sluitacc = 1;
			}
		} else if (kar == '\n') {
			lijnteller++;
			comment = 0;
			inspringen = 1;
			slash = 0;
			if (sluitacc) {
				uitvoer.put('}');
				sluitacc = 0;
			}
		} else if (inspringen) {
			if (kar == ' ' || kar == '\t') {
				comment = 1;
			} else if (kar == '/') {
				slash = 1;
			} else if (!slash) {
				for (int i = 0; i < (diepte * tabgrootte); i++) {
					uitvoer.put(' ');
				}
				comment = 0;
				inspringen = 0;
			}
		} else {
			slash = 0;
		}

		if (!slash && !comment && !sluitacc) {
			uitvoer.put(kar);
		}
	}
}

/*
void doewat (ifstream &invoer, ofstream &uitvoer) {

}
while(n != 0) {
	reverse = n % 10 + reverse * 10;
	n = n / 10;
}
*/