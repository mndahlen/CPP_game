#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "State.hpp"
#include "../Menu/Menu.hpp"

class PauseState : public State
{
    public:
        PauseState(sf::RenderWindow * window, DataHandler * datahandler,
                               std::map<std::string, sf::Texture*> * texture_map_ptr,
                               std::map<std::string, sf::Font*> * font_map_ptr);

        ~PauseState();

        void updateState() override;
        void render() override;

    private:
        Menu menu{450,250,200,500};
        Menu background{450,350,900,700};
        Button * leveldisplay{};
        Button * moneydisplay{};
        Button * hpdisplay{};

        void initMainMenu();
        void initBackground();
        void initButtons();

        void updateButtons();
};

#endif
