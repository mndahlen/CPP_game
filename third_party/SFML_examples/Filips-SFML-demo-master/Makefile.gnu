CPPFLAGS=-Wall -Wextra -pedantic -std=c++17 -Weffc++ -Wold-style-cast -Wsuggest-attribute=const -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wduplicated-cond -Wzero-as-null-pointer-constant -Wuseless-cast -fconcepts -Woverloaded-virtual -I$(SFML_ROOT)/include

LDFLAGS=-L$(SFML_ROOT)/lib -lsfml-graphics -lsfml-window -lsfml-system

FILES=shooter shooter-1 shooter-2 shooter-3 shooter-4 shooter-5 shooter-6 shooter-7 shooter-8 tetris

.SUFFIXES:

all: $(FILES)

.PHONY: clean
clean:
	rm -f $(FILES)

.PHONY: superclean
superclean: clean
	rm -rf CMakeFiles
	rm -f Makefile CMakeCache.txt cmake_install.cmake *~ *.o

%.o: %.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

%: %.o
	g++ $< $(LDFLAGS) -o $@
