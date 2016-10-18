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

using namespace std; 

char getkarakter () {

	char keuze;

	cin.clear();
	keuze = cin.get();
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

		cout << "penis";

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

keuzemenu();

return 1;

}