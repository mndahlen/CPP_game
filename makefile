CC := g++
FLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Werror -Weffc++
FLAGS_NO_WERROR := -std=c++17 #-Wall -Wextra -Wpedantic -Weffc++
FLAGS_ONLY_ERROR := -std=c++17

LIB := -L${SFML_ROOT}/lib -I${SFML_ROOT}/include -lsfml-window -lsfml-graphics -lsfml-system
GAME_DEPENDENCIES := $(shell find TowerDefence -name *.cpp) #../TowerDefence/main.o

main: $(GAME_DEPENDENCIES)
	$(CC) $(FLAGS_ONLY_ERROR) $(GAME_DEPENDENCIES) -o play $(LIB)

