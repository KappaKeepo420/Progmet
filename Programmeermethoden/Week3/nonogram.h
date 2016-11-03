#define MAX 30

class Nonogram {
	public:
		Nonogram();
		void drukaf();
		void vulrandom();
		void maakschoon();
		void maakbeschrijvingen();
		void zetpercentage();
	private:
		bool nono[MAX][MAX];
		int rijen[MAX][MAX];
		int kolommen[MAX][MAX];
		int hoogte, breedte, precentage, penstatus;
		void maaklijnbeschrijving (bool lijn[], int ell, int beschr[]);
};