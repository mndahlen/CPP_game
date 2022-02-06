#ifndef HIGHSCORESTATE_HPP
#define HIGHSCORESTATE_HPP

#include "State.hpp"
#include "../Menu/Menu.hpp"
#include "../DataHandler/DataHandler.hpp"

class HighscoreState : public State
{
    public:
        HighscoreState(sf::RenderWindow * window, DataHandler * datahandler,
                      std::map<std::string, sf::Texture*> * texture_map_ptr,
                      std::map<std::string, sf::Font*> * font_map_ptr);

        void updateState() override;
        void render() override;

    private:
        Menu highscoreMenu{450,400,200,250};
        Menu background{450,350,900,700};
        sf::Texture * menu_texture;
        sf::Texture * background_texture;
        sf::Texture * button_texture;
        sf::Texture * transparent_texture;

        void initHighscoreMenu();
        void initBackground();
};

#endif
