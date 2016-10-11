
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
	int lijnteller, diepte, tabgrootte = 0;
	bool comment, stop, stopcomment, inspringen = false;

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
		
		if ((kar == '/') && (comment == false) && (quote == false)) {
			slash = true;
		} else if ((kar == '/') && (slash == true) && (quote == false)) {
			comment = true;
		} else if (kar == '\n') {
			lijnteller++;
			stop = false;
			comment = false;
			inspringen = true;
		} else {
			comment = false;
		} 

		if (kar == '"') {
			quote = true;
		}
		if (kar != '/' && slash == true) {
			uitvoer.put('/');
			slash = false;
			comment = false;
			stop = false;
		}

		if ((kar == '{') && (!stop)) {
			diepte += 1;
		} else if ((kar == '}') && (!stop)) {
			diepte -= 1;
		} else if ((kar == ' ') || (kar == '\t')) {
			if (inspringen == true) {
				stop = true;
			}
		} else if (inspringen == true) { // gebeurt nooit

			for (int i = 0; i < (diepte * tabgrootte); i++) {
				uitvoer.put(' ');
			}

			inspringen = false;
			stop = false;
		}

		if (!stop && !comment) {
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