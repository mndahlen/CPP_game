#ifndef GAMEFINISHEDSTATE_HPP
#define GAMEFINISHEDSTATE_HPP

#include "State.hpp"
#include "../Menu/Menu.hpp"

class GameFinishedState : public State
{
    public:
        GameFinishedState(sf::RenderWindow * window, DataHandler * datahandler,
                               std::map<std::string, sf::Texture*> * texture_map_ptr,
                               std::map<std::string, sf::Font*> * font_map_ptr);
        
        ~GameFinishedState();

        void updateState() override;
        void render() override;

    private:
        Menu menu{450,350,200,500};
        Menu background{450,350,900,700};
        sf::Texture * menu_texture;
        sf::Texture * background_texture;
        sf::Texture * button_texture;
        Button * leveldisplay{};
        Button * moneydisplay{};
        Button * hpdisplay{};

        void initMainMenu();
        void initBackground();
        void initButtons();
        
        void updateButtons();
};

#endif