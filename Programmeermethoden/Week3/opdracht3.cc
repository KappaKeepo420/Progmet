#include <iostream> 
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

int submenu() {
	int n = 0;
	char opties;
	cout << "Menu:\n";
	cout << "C voor legen.\n";
	cout << "R voor een nieuwe random waarde.\n";
	cout << "P voor parameters veranderen.\n";
	cout << "S voor stoppen.\n\n";
	cin.get (opties);
	switch(opties) {
		case 'C' :
			cout << "functie C\n";
			break;
		case 'R' :
			cout << "functie R\n";
			break;
		case 'P' :
			cout << "functie P\n";
			break;
		case 'S' :
			cout << "Tot ziens!\n";
			n = 1;
			break;
		default :
			cout << "Voer aub een geldige optie in.\n";
			break;
	}
	return n;
}

// int nonogram(int x, int y) {
// 	int yesyesgram[y][x];
// }

char mainmenu(char optiem) {
	switch(optiem) {
		case 'A' :
			submenu();
		default :
			cout << "geldige optie.\n";
			break;
	}
}

int leesgetal() {

}

int main() {
	char optiem;
	int x = 0, y = 0, n = 0;
	while (n != 1) {
		cout << "Voer A in.\n";
		cin.get (optiem);
		mainmenu(optiem);
	}
	return 0;
}