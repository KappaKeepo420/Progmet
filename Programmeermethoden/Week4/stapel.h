#ifndef STAPEL_H
#define STAPEL_H

struct vakje {
	vakje();
	int i;
	int j;
	vakje* volgende;
};

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

