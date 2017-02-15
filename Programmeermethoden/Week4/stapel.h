/*  Auteurs         - Jort Gijzen       1874233
                    - Lennard Schaap    1914839
    Studie          - BSc Informatica
    Compiler        - g++ -std=c++11
    Datum           - 18 december 2016
    Opdracht        - Gomoku
    File            - stapel.cc
    
    Dit is de headerfile van stapel.cc.
*/

#ifndef STAPEL_H
#define STAPEL_H

/* Het vakje met inhoud i en j en een pointer naar het volgende vakje. */
struct vakje {
	vakje();
	int i;
	int j;
	vakje* volgende;
};

/* De stapel klasse met de memberfuncties- en variabelen. */
class stapel {
  public:
  	stapel();
  	~stapel();
  	void voegtoe(int i, int j);
  	void verwijder(int &i, int &j);
  	bool leeg();
  private:
  	vakje* ingang;
};

#endif //STAPEL_H

