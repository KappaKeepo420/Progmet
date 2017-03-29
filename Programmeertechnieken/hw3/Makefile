# Behorende bij Programmeertechnieken huiswerk 3: unit testing.
#

# De Makefile is zo geschreven dat deze goed werkt op de NUWD systemen
# van de universiteit in het "pt2017 environment".
CXX = g++
# http://stackoverflow.com/a/19792966
GCOV_CXXFLAGS = -g -O0 -coverage -fno-inline -fno-inline-small-functions -fno-default-inline
CXXFLAGS = -Wall -Wextra -std=c++14 $(GCOV_CXXFLAGS)
BOOST_CXXFLAGS = -I/vol/share/groups/liacs/scratch/pt2017/include -DBOOST_TEST_DYN_LINK
BOOST_LIBS = -lboost_unit_test_framework
LDFLAGS = -L/vol/share/groups/liacs/scratch/pt2017/lib


all: mystacktest

mystacktest:	mystacktest.cc mystack.h
		$(CXX) $(CXXFLAGS) $(BOOST_CXXFLAGS) $(LDFLAGS) -o $@ $< $(BOOST_LIBS)

# Unit tests uitvoeren
check:	mystacktest
	./$<

# Unit tests uitvoeren onder valgrind
memorycheck:	mystacktest
		valgrind --leak-check=full ./$<

# Code coverage statistieken genereren
gencov:	mystacktest
	lcov --capture -i --directory . -o coverage.baseline
	./$<
	lcov --capture --directory . --output-file coverage.out
	lcov -a coverage.baseline -a coverage.out -o coverage.info
	genhtml coverage.info --demangle-cpp --output-directory html

clean:
	rm -f mystacktest
	rm -f mystacktest.gcno mystacktest.gcda
	rm -f coverage.info coverage.out coverage.baseline
	rm -rf html
