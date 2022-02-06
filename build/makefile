CC := g++
FLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Werror -Weffc++
FLAGS_NO_WERROR := -std=c++17 #-Wall -Wextra -Wpedantic -Weffc++
FLAGS_ONLY_ERROR := -std=c++17

LIB := -L${SFML_ROOT}/lib -I${SFML_ROOT}/include -lsfml-window -lsfml-graphics -lsfml-system
GAMEOBJECT_DEPENDENCIES := $(shell find ../TowerDefence/GameObject -name *.cpp)
STATE_DEPENDENCIES := $(shell find ../TowerDefence/State -name *.cpp)
DATAHANDLER_DEPENCENCIES := ../TowerDefence/DataHandler/DataHandler.cpp
BUTTON_DEPENDENCIES := ../TowerDefence/Button/Button.cpp
MENU_DEPENDENCIES := ../TowerDefence/Menu/Menu.cpp
GAME_DEPENDENCIES_FOR_TEST := $(GAMEOBJECT_DEPENDENCIES) $(STATE_DEPENDENCIES) $(MENU_DEPENDENCIES) $(BUTTON_DEPENDENCIES) $(DATAHANDLER_DEPENCENCIES)
TEST_DEPENDENCIES := $(GAME_DEPENDENCIES_FOR_TEST) ../catch/catch_files/test_main.o
GAME_DEPENDENCIES := $(shell find ../TowerDefence -name *.cpp) #../TowerDefence/main.o

debug_main: $(GAME_DEPENDENCIES)
	$(CC) $(FLAGS_ONLY_ERROR) -Wall -g $(GAME_DEPENDENCIES) $(LIB)
	#cd ../TowerDefence
	gdb a.out

main: $(GAME_DEPENDENCIES)
	$(CC) $(FLAGS_ONLY_ERROR) $(GAME_DEPENDENCIES) $(LIB)
	#cd ../TowerDefence
	./a.out

test: $(TEST_DEPENDENCIES)
	$(CC) $(FLAGS_NO_WERROR) $(TEST_DEPENDENCIES) ../catch/*_test.cpp $(LIB)
	cd ../catch
	./a.out
	\rm a.out

test_GameObjects: $(TEST_DEPENDENCIES)
	$(CC) $(FLAGS_NO_WERROR) $(TEST_DEPENDENCIES) ../catch/*_GO_test.cpp ../catch/GameObject_test.cpp $(LIB)
	cd ../catch
	./a.out
	\rm a.out

test_GameStateMachine: $(TEST_DEPENDENCIES)
	$(CC) $(FLAGS_NO_WERROR) $(TEST_DEPENDENCIES) ../catch/GameStateMachine_test.cpp $(LIB)
	cd ../catch
	./a.out
	\rm a.out

.PHONY: clean

clean:
	\rm a.out


############################## SPECIFIC TESTS ##############################
ADAM_DEPENDENCIES := ../TowerDefence/GameObject/StaticObject/PlayingField/test_adam_main.cpp ../TowerDefence/GameObject/StaticObject/PlayingField/PF1711.cpp ../TowerDefence/GameObject/GameObject.cpp ../TowerDefence/GameObject/DynamicObject/DynamicObject.cpp ../TowerDefence/GameObject/DynamicObject/PlayerFigure.cpp ../TowerDefence/GameObject/StaticObject/PlayingField/PF1711.cpp ../TowerDefence/GameObject/StaticObject/StaticObject.cpp ../TowerDefence/GameObject/DynamicObject/Enemy/Enemy.cpp


test_Button: $(BUTTON_DEPENDENCIES)
	$(CC) $(FLAGS_NO_WERROR) $(BUTTON_DEPENDENCIES) $(LIB)
	./a.out
	\rm a.out

test_Menu : $(MENU_DEPENDENCIES)
	$(CC) $(FLAGS_NO_WERROR) $(MENU_DEPENDENCIES) $(BUTTON_DEPENDENCIES) $(LIB)
	./a.out
	\rm a.out

adam : $(ADAM_DEPENDENCIES)
	$(CC) $(FLAGS_NO_WERROR) $(ADAM_DEPENDENCIES) $(LIB)
	./a.out
	\rm a.out

# test_GameObject: ../TowerDefence/GameObject/GameObject.cpp ../TowerDefence/GameObject/TestObject.cpp ../catch/GameObject_test.cpp ../catch/catch_files/test_main.o
#  	$(CC) $(FLAGS_NO_WERROR) ../TowerDefence/GameObject/GameObject.cpp ../TowerDefence/GameObject/TestObject.cpp ../catch/GameObject_test.cpp ../catch/catch_files/test_main.o $(LIB)
#  	cd ../catch
#  	./a.out
#  	\rm a.out


# test_StaticTower: ../TowerDefence/GameObject/StaticObject/StaticTower/HandSanitizerTower.cpp ../TowerDefence/GameObject/StaticObject/StaticTower/StaticTower.cpp ../TowerDefence/GameObject/StaticObject/StaticObject.cpp ../TowerDefence/GameObject/GameObject.cpp ../catch/StaticTower_test.cpp ../catch/catch_files/test_main.o
# 	$(CC) $(FLAGS_NO_WERROR) ../TowerDefence/GameObject/StaticObject/StaticTower/HandSanitizerTower.cpp ../TowerDefence/GameObject/StaticObject/StaticTower/StaticTower.cpp ../catch/StaticTower_test.cpp ../TowerDefence/GameObject/StaticObject/StaticObject.cpp ../TowerDefence/GameObject/GameObject.cpp ../catch/catch_files/test_main.o $(LIB)
# 	 	cd ../catch
# 	 	./a.out
# 	 	\rm a.out
