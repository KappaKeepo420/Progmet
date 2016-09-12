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

    if (d < 1) {
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

int main ( ) {
	
	int j, m, d;
	int jaarnu, maandnu, dagnu;
	int leeftijdj;
	int leeftijdm;
	int aantaljaren;
	int aantalmaanden;
	int maandextra;
	string jeu;

	string dagen [7] = {"Maandag", "Dinsdag", "Woensdag", "Donderdag", "Vrijdag", "Zaterdag", "Zondag"};

	tm s;
	time_t t;

	time (&t);
	s = * localtime (&t);

	jaarnu  = s.tm_year + 1900;
	maandnu = s.tm_mon + 1;
	dagnu	= s.tm_mday;

	cout << "Geef uw geboortedatum (dd/mm/jjjj): ";

   	cin >> d;

	if (cin.get() != '/') {
		cout << "Onjuiste input, probeer opnieuw.\n";
		return 1;
	}

	cin >> m;

	if (cin.get() != '/') {
		cout << "Onjuiste input, probeer opnieuw.\n";
		return 1;
	}

	cin >> j;

	

	cout << "Leeftijd in jaren: " << leeftijdj << " jaren en " << maandextra << " maanden.\n";
	cout << "Leeftijd in maanden: " << leeftijdm << "\n";

	int a = j - (14 - m) / 12;
	int b = a + a / 4 - a / 100 + a / 400;
	int c = m + 12 * ((14 - m) / 12) - 2;
	int dag = (d + b + (31 * c) / 12) % 7;

	cout << "U bent geboren op een: " + dagen[dag-1] << endl;

	return 1;
}

tuple<int, int, int> bereken_leeftijd(int d, int m, int j) {
	
	aantaljaren = jaarnu - j;

	if (m > maandnu) {
		leeftijdj = aantaljaren - 1;
	}
	else {
		leeftijdj = aantaljaren;
	}

	cout << leeftijdj << "\n";

	if (m >= maandnu) {
		maandextra = m - maandnu;
	}
	else {
		maandextra = 12 - maandnu + m;
	}

	aantalmaanden = leeftijdj * 12 + maandextra;

	if (d > dagnu) {
		leeftijdm = aantalmaanden - 1;
	}
}