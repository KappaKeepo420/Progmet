#include <iostream> 
#include <string>
#include <ctime>

using namespace std; 

bool schrikkeljaar(int j) {

	bool schrikkel = false;

	if ((j % 4 == 0) && (j % 100 != 0)) {
		schrikkel = true;
	}
	if (j % 400 == 0) {
		schrikkel = true;
	}

	return schrikkel;
}

bool geldige_datum(int d, int m, int j) {

    bool schrikkel = schrikkeljaar(j);

    if ((d < 1) || (m < 1)) {
        return false;
    }

    if ((d > 31) || (m > 12)) {
    	return false;
    }

    if (j < 1900) {
        return false;
    }

    if (((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
       && (d > 31)) {
        return false;
    }

    if ((m == 2) && (schrikkel == true) && (d > 29)) {
        return false;
    }

    if ((m == 2) && (schrikkel == false) && (d > 28)) {
        return false;
    }

    if (((m == 4) || (m == 6) || (m == 9) || (m == 11)) && (d > 30)) {
        return false;
    }

    return true;
}

int bereken_dag(int d, int m, int j) {

	int a = j - (14 - m) / 12;
	int b = a + a / 4 - a / 100 + a / 400;
	int c = m + 12 * ((14 - m) / 12) - 2;
	int dag = (d + b + (31 * c) / 12) % 7;

	return dag;
}

int bereken_leeftijd(int d, int m, int j) {

	int jaarnu, maandnu, dagnu;
	int leeftijdm, leeftijdj;
	int aantaljaren, aantalmaanden;
	int maandextra;
	string jeuw = "";
	string jeu = "";

	tm s;
	time_t t;

	time (&t);
	s = * localtime (&t);

	jaarnu  = s.tm_year + 1900;
	maandnu = s.tm_mon + 1;
	dagnu	= s.tm_mday;

	aantaljaren = jaarnu - j;

	if (m > maandnu) {
		leeftijdj = aantaljaren - 1;
	} else {
		leeftijdj = aantaljaren;
	}

	if (m >= maandnu) {
		maandextra = m - maandnu;
	} else {
		maandextra = 12 - maandnu;
	}

	aantalmaanden = leeftijdj * 12 + maandextra;

	if (d > dagnu) {
		leeftijdm = aantalmaanden - 1;
	} else {
		leeftijdm = aantalmaanden;
	}

	if (leeftijdj > 100) {
		cout << "U bent geschikt \u2610  ongeschikt \u2611 .\n";
		return NULL;
	}
	if (leeftijdj < 10) {
		cout << "Je bent geschikt \u2610  ongeschikt \u2611 .\n";
		return NULL;
	}

	if (leeftijdj > 30) {
		jeuw = "Uw";
	} else {
		jeuw = "Jouw";
	}

	cout << jeuw << " leeftijd in jaren: " << leeftijdj << " jaar en " << maandextra
				 << " maanden.\n";
	cout << jeuw << " leeftijd in maanden: " << leeftijdm << ".\n";


	if (d == dagnu && m == maandnu) {
		cout << "Gefeliciteerd met " << jeuw << " verjaardag!";
	}

	else if (d == dagnu) {
		cout << "Gefeliciteerd met " << jeuw << " vermaandag!";

	}

	return leeftijdj;
}

int main () {
	
	int d, m, j;
	int juisteantwoord;
	string antwoord;

	tm s;
	time_t t;
	time (&t);
	s = * localtime (&t);
	int jaarnu  = s.tm_year + 1900;

	string dagen [7] = {"Maandag", "Dinsdag", "Woensdag", "Donderdag", "Vrijdag",
						"Zaterdag", "Zondag"};

	string dagenafk [7] = {"m", "di", "w", "do", "v"
						, "za", "zo"};

	cout << "Geef uw geboortejaar: ";
	cin >> j;

	if (j < jaarnu - 102) {
		cout << "U bent geschikt \u2610  ongeschikt \u2611 .\n";
		return 1;
	}
	if (j > jaarnu - 10) {
		cout << "Je bent geschikt \u2610  ongeschikt \u2611 .\n";
		return 1;
	}

	cout << "Geef uw geboortemaand: ";
	cin >> m;

	cout << "Geef uw geboortedag: ";
 	cin >> d;

	if (geldige_datum(d, m, j)) {
		if (bereken_leeftijd(d, m, j) == NULL) {
			return 1;
		}
	} else {
		cout << "Voer een geldige datum in.\n";
	}

	cout << "Op welke dag van de week bent u geboren? ";
	cin >> antwoord;

	juisteantwoord = bereken_dag(d, m, j);

	for (int i = 0; i < sizeof(dagenafk); i++) {
		if (dagenafk[i] == antwoord) {
			if (i == juisteantwoord) {
				cout << "Correct!";
			} else {
				cout << "Helaas, het juiste antwoord is: " << dagen[juisteantwoord];
			}
		} else {
			cout << "Geef uw dag met 1 of 2 letters.";
		}
	}

	return 1;
}