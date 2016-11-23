// file gobord.cc
#include <iostream>
#include "gobord.h"
using namespace std;

gobord::gobord ( ) {
  // TODO
}//gobord::gobord

gobord::~gobord ( ) {
  // TODO
}//gobord::~gobord

void gobord::drukaf ( ) {
	cin >> hoogte;
	cin >> breedte;
	for (int i = 0; i < hoogte; i++) {
		for (int j = 0; j < breedte; j++) {
			cout << "\e[92m\u25A1\e[0m  ";
		}
		cout << endl;
	}
  // TODO
}