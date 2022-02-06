#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "State.hpp"
#include "../Menu/Menu.hpp"

class MainMenuState : public State
{
    public:
        MainMenuState(sf::RenderWindow * window, DataHandler * datahandler,
                      std::map<std::string, sf::Texture*> * texture_map_ptr,
                      std::map<std::string, sf::Font*> * font_map_ptr);
        ~MainMenuState();
        void updateState() override;
        void render() override;
    
    private:
        Menu * menu{};
        Menu * background{};
        sf::Texture * menu_texture;
        sf::Texture * background_texture;
        sf::Texture * button_texture;

        void initMainMenu();
        void initBackground();
};

#endif