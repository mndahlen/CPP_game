CC := g++
FLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Werror -Weffc++
LIB := -L${SFML_ROOT}/lib -I${SFML_ROOT}/include -lsfml-window -lsfml-graphics -lsfml-system

all: start v1 v2 v3 v4 v5 v6 v7 v8 v9

start: sfml_start.cc
	$(CC) $(FLAGS) sfml_start.cc -o start $(LIB)

v1: sfml_v1.cc
	$(CC) $(FLAGS) sfml_v1.cc -o v1 $(LIB)

v2: sfml_v2.cc
	$(CC) $(FLAGS) sfml_v2.cc -o v2 $(LIB)

v3: sfml_v3.cc
	$(CC) $(FLAGS) sfml_v3.cc -o v3 $(LIB)

v4: sfml_v4.cc
	$(CC) $(FLAGS) sfml_v4.cc -o v4 $(LIB)

v5: sfml_v5.cc
	$(CC) $(FLAGS) sfml_v5.cc -o v5 $(LIB)

v6: sfml_v6.cc
	$(CC) $(FLAGS) sfml_v6.cc -o v6 $(LIB)

v7: sfml_v7.cc
	$(CC) $(FLAGS) sfml_v7.cc -o v7 $(LIB)

v8: sfml_v8.cc
	$(CC) $(FLAGS) sfml_v8.cc -o v8 $(LIB)

v9: sfml_v9.cc
	$(CC) $(FLAGS) sfml_v9.cc -o v9 $(LIB)

# make sure that 'clean' is not run accidentally
.PHONY: clean

clean:
	rm start v1 v2 v3 v4 v5 v6 v7 v8 v9
