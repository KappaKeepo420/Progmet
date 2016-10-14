/*	Jort Gijzen		- 1874233
	Lennard Schaap 	- 1914839
	BSc Informatica

	Dit bestand probeert te bepalen of iemand geschikt is voor een studie aan de universiteit:
	er is immers geen loting. Daartoe moeten enkele vragen beantwoord worden.
	De kandidaat moet eerst zijn geboortedatum geven. Het programma berekent vervolgens de 
	geboortedag van de kandidaat. De kanditaat moet vervolgens zijn/haar geboortejaar,
	geboortemaand en geboortedag invoeren als gehele getallen. De kanditaat wordt vervolgens 
	gevraagd op welke dag hij/zij geboren is. Als de kandidaat deze vraag fout beantwoord, 
	wordt het programma gesloten. Vervolgens moet de kandidaat een schatting geven van het 
	product van twee integers. Als de gebruiker dit fout beantwoord, is hij/zij niet geschikt
	voor een betastudie. Tot slot wordt er eer vraag over literatuur gesteld, om te bepalen
	of de kandidaat misschien wel geschikt is voor een alphastudie. Als de kandidaat deze
	vraag fout beantwoord, is hij/zij niet geschikt voor een universitaire studie en wordt
	het programma afgesloten.

	Gebruikte functies: schrikkeljaar		(Berekent of een jaar een schrikkeljaar is)
						geldige_datum		(Berekent of een gegeven datum bestaat)
						bereken_dag			(Berekent de dag van een bepaalde datum)
						bereken_leeftijd	(Berekent de leeftijd aan de hand van geboortedatum)
						quiz1				(Berekent het product van twee getallen)
						quiz2				(Stelt een vraag over literatuur)
						main 				(Stelt vragen en roept de andere functies aan)
*/

#include <iostream> 
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std; 

/*	Deze functie berekent of een gegeven jaar j een schrikkeljaar is of niet en returnt
	de bijbehorende boolean waarde. */

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

/*	Deze functie berekent of een gegeven datum (dag, maand, jaar) een geldige datum is (d.w.z. 
	de datum heeft bestaan) met verschillende if-statements en returnt de bijbehorende 
	boolean waarde. */

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

/*	Deze functie berekent de weekdag die bij de gegeven datum (dag, maand, jaar) hoort en 
	returnt deze. */

int bereken_dag(int d, int m, int j) {

	int a = j - (14 - m) / 12;
	int b = a + a / 4 - a / 100 + a / 400;
	int c = m + 12 * ((14 - m) / 12) - 2;
	int dag = (d + b + (31 * c) / 12) % 7;

	return dag;
}

/*	Deze functie berekent de leeftijd in jaren en maanden die bij een gegeven geboortedatum
	(dag, maand, jaar) hoort en returnt deze. Ook filtert deze functie kandidaten onder de
	10 en boven de 100 jaar uit het programma. Vervolgens wordt de leeftijd in jaren en
	maanden geprint op het scherm. Ook wordt er een berichtje gegeven als de kandidaat 
	jarig of maandig is.*/

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

	/* Huidig jaar, maand en dag uit ctime. */

	jaarnu  = s.tm_year + 1900;
	maandnu = s.tm_mon + 1;
	dagnu	= s.tm_mday;

	/* Het algoritme om de leeftijd van de kandidaat in maanden en jaren te berekenen. */

	aantaljaren = jaarnu - j;

	if (m > maandnu) {
		leeftijdj = aantaljaren - 1;
	} else {
		leeftijdj = aantaljaren;
	}

	if (m >= maandnu) {
		maandextra = m - maandnu;
	} else {
		maandextra = maandnu - m;
	}

	aantalmaanden = leeftijdj * 12 + maandextra;

	if (d > dagnu) {
		leeftijdm = aantalmaanden - 1;
	} else {
		leeftijdm = aantalmaanden;
	}

	if (leeftijdj > 100) {
		cout << "U bent geschikt \u2610  ongeschikt \u2611 .\n";
		return 0;
	}
	if (leeftijdj < 10) {
		cout << "Je bent geschikt \u2610  ongeschikt \u2611 .\n";
		return 0;
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

/*	Deze functie stelt een betavraag aan de kandidaat. Er worden twee willekeurige getallen
	gegenereerd waarvan de kandidaat het product moet bepalen. Ongeveer 10% van de tijd zal het
	antwoord 0 zijn. Als de kandidaat het fout heeft, is hij niet geschikt voor de betastudie en 
	wordt er een nieuwe vraag gesteld die bepaalt of hij geschikt is voor een alpha studie */

bool quiz1 (string a, string b) {

	srand (time(NULL));
	int getal1, getal2, qantwoord1, question1, random1;

	/* Hier worden de twee willekeurige getallen gegenereerd. */

	random1 = rand() % 9;
	getal2 = rand() % 214748;

	if (random1 == 0) {
		getal1 = 0;
	} else {
		getal1 = rand() % 10000;
	}

	question1 = getal1 * getal2;

	cout << "Deze quiz controleert of " << a << " geschikt bent voor een beta of alpha studie.\n";
	cout << "Vraag 1: Wat is het product van " << getal1 << " en " << getal2 << "?\n";

	cout << b << " antwoord: ";

	cin >> qantwoord1;

	/* Het antwoord van de kandidaat mag tot 10% verschillen van het werkelijke antwoord. */

	if ((qantwoord1 > (question1 * 1.1)) || (qantwoord1 < (question1 * 0.9))) {
		return false;
	} else {
		return true;
	}

	return false;
}

/*	In deze functie wordt er een vraag over literatuur gesteld, als de kandidaat het antwoord
	fout heeft, is hij/zij niet geschikt voor een universitaire studie. */

bool quiz2 (string a, string b) {

	string qantwoord2 = "";

	cout << "Deze quiz controleert of " << a << " misschien geschikt bent voor een alpha studie.\n";
	cout << "Vraag 2: Welke schrijvers worden tot De Grote Drie van de naoorlogse";
	cout <<	" Nederlandse schrijvers gerekend?\n\n";
	cout << "A: Arnon Grunberg, A.F.Th. van der Heijden en Harry Mulisch.\n";
	cout << "B: A.F.Th. van der Heijden, Eduard Douwes Dekker en Jan Wolkers.\n";
	cout << "C: Gerard Reve, Harry Mulisch en A.F.Th, van der Heijden.\n";
	cout << "D: Willem Frederik Hermans, Gerard Reve en Harry Mulisch.\n";

	cout << b << " antwoord: ";

	cin >> qantwoord2;

	cout << "\n";

	if ((qantwoord2 == "d") || (qantwoord2 == "D")) {
		return true;
	} else {
		return false;
	}

	return false;
}
/*	Deze functie is de main functie. Hierin worden alle gebruikte functies en booleans aangeroepen
	die gebruikt zijn in dit programma. Ook maken we hier gebruik van ctime, wat de huidige tijd
	bepaald. Ook wordt in deze functie de geboortedatum van de gebruiker gevraagd. Verder wordt de 
	gebruiker getest of hij weet wat zijn geboortedag is. */

int main () {
	
	int d, m, j;
	int juisteantwoord;
	string antwoord, jeu, jeuk, jeuw = "";
	int leeftijd;
	bool b = false;

	tm s;
	time_t t;
	time (&t);
	s = * localtime (&t);
	int jaarnu  = s.tm_year + 1900; // Huidig jaar uit ctime.

	string dagen [7] = {"Maandag", "Dinsdag", "Woensdag", "Donderdag", "Vrijdag",
						"Zaterdag", "Zondag"};

	string dagenafk [7] = {"m", "di", "w", "do", "v"
						, "za", "zo"};

	cout << "------------------------------------------------------------\n";
	cout << "- Jort Gijzen en Lennard Schaap                            -\n";
	cout << "- 1874233        1914839                                   -\n";
	cout << "- Eerste programmeeropgave: IQ                             -\n";
	cout << "- 22 september 2016                                        -\n";
	cout << "-                                                          -\n";
	cout << "- Dit programma probeert te bepalen of iemand geschikt is  -\n";
	cout << "- voor een studie aan de universiteit.                     -\n";
	cout << "-                                                          -\n";
	cout << "------------------------------------------------------------\n";

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

 	/* Als de gegeven datum bestaat wordt de leeftijd van de kandidaat berekend. */

	if (geldige_datum(d, m, j)) {

		leeftijd = bereken_leeftijd(d, m, j);
		if (leeftijd == 0) {
			return 1;
		}
	} else {
		cout << "Voer een geldige datum in.\n";
		return 1;
	}

	cout << "Op welke dag van de week bent u geboren? ";
	cin >> antwoord;

	if (leeftijd > 30) {
		jeu = "U";
		jeuk = "u";
		jeuw = "Uw";
	} else {
		jeu = "Je";
		jeuk = "je";
		jeuw = "Jouw";
	}

	/* Hier wordt de geboortedag van de kandidaat berekend. */

	juisteantwoord = bereken_dag(d, m, j);

	/* Hier wordt gekeken of de gebruiker een juiste invoer heeft gegeven en dan of de gegeven
		dag gelijk is aan de hiervoor berekende geboortedag van de gebruiker. */

	for (int i = 0; i < 6; i++) {
		if (dagenafk[i] == antwoord) {
			b = true;
			if (i == (juisteantwoord - 1) ){
				cout << "Correct!\n\n";
				break;
			} else {
				cout << "Helaas, het juiste antwoord is: " << dagen[juisteantwoord - 1] << "\n\n";
				return 1;
			}
		}
	}
	
	if (b == false) {
		cout << "Voer AUB de dag in met 1 of 2 letters.";
		return 1;
	}

	if (quiz1(jeuk, jeuw) == true) {
		cout << "Correct! " << jeu << " bent geschikt \u2611  ongeschikt \u2610  "
		"voor een betastudie.\n\n";
		return 1;
	} else {
		cout << "Fout! " << jeu << " bent geschikt \u2610  ongeschikt \u2611  "
		"voor een betastudie.\n\n";
	}

	if (quiz2(jeuk, jeuw) == true) {
		cout << "Correct! " << jeu << " bent geschikt \u2611  ongeschikt \u2610  "
		"voor een alphastudie.\n\n";
		return 1;
	} else {
		cout << "Fout! " << jeu << " bent geschikt \u2610  ongeschikt \u2611  "
		"voor een alphastudie.\n\n";
	}

	return 1;
}