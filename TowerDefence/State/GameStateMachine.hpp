#ifndef GAMESTATEMACHINE_HPP
#define GAMESTATEMACHINE_HPP

#include "GameFinishedState.hpp"
#include "GameOverState.hpp"
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "PauseState.hpp"
#include "HighscoreState.hpp"
#include "../DataHandler/DataHandler.hpp"
#include <utility>
#include <string>
#include <sstream>
#include <iostream> //DEBUG syfte
#include <SFML/Graphics.hpp>

/* 

    STATE               ID
--------------------------------------
- Quit                  -1
- MainMenuState         0
- GameState             1
- PauseState            2
- GameFinishedState     5
- HighScoreState        7
- GameOverState         8
--------------------------------------

**/

class GameStateMachine
{
    public:
        GameStateMachine(std::string texture_folder_path,
                         std::string font_folder_path,
                         DataHandler * datahandler_);
        ~GameStateMachine();

        void runState();
        void updateState();
        void renderState();
        void updateCurrentState(State * next_state);
        int getNextStateID();
        State * createState(int state_id);

        /* Function for testing */
        State * getCurrentState();
        State * getSavedState();

    private:
        State * current_state{};
        State * saved_game_state{};
        DataHandler * datahandler{};
        sf::RenderWindow window{sf::VideoMode{900, 700},"TowerDefence"};
        std::map<std::string, sf::Texture*> texture_map{};
        std::map<std::string, sf::Font*> font_map{};

        /* Functions for loading textures and fonts from file */
        void loadTextures(std::string const & folder_path);
        void loadFonts(std::string const & folder_path);
        void addTexture(std::string const & folder_path, 
                        std::string const & texture_name,
                        std::string const & filename);
        void addFont(std::string const & folder_path, 
                     std::string const & font_name,
                     std::string const & filename);

};

#endif