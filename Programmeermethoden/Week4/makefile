all: hoofd.o gobord.o
	g++ -std=c++11 -Wall -o hetspel gobord.o hoofd.o
gobord.o: gobord.cc gobord.h
	g++ -std=c++11 -Wall -c gobord.cc
hoofd.o: hoofd.cc gobord.h
	g++ -std=c++11 -Wall -c hoofd.cc
clean:
	\rm gijzenschaap4.tar
	\rm *.o hetspel
tar:
	tar cfv gijzenschaap4.tar gobord.cc gobord.h hoofd.cc