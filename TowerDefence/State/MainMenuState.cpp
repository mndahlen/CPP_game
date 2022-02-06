#include "MainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow * window, DataHandler * datahandler,
                               std::map<std::string, sf::Texture*> * texture_map_ptr,
                               std::map<std::string, sf::Font*> * font_map_ptr)
                               :
                               State(window,datahandler,texture_map_ptr,font_map_ptr,0)
{
    initMainMenu();
    initBackground();
}

MainMenuState::~MainMenuState()
{
    delete menu;
    delete background;
}

void MainMenuState::updateState()
{
    sf::Mouse mouse;
    bool left_pressed = mouse.isButtonPressed(sf::Mouse::Left);

    if (left_pressed)
    {
        auto mpos = mouse.getPosition(*window);
        int selected = menu->getSelectedOption(mpos.x, mpos.y);

        if (selected == 1)
        {
            next_state_id = 1;
        }
        else if (selected == 2)
        {
            next_state_id = 7;
        }
        else if (selected == 3)
        {
            next_state_id = -1;
        }
    }
}

void MainMenuState::render()
{
    background->render(window);
    menu->render(window);
}

void MainMenuState::initMainMenu()
{
    sf::Texture * menu_texture = texture_map->at("menu");
    sf::Texture * button_texture = texture_map->at("button");
    sf::Font * font = font_map->at("arial");
    menu = new Menu{450,350,200,250, menu_texture};

    menu->addButton(100,50,150,50,button_texture, "Start Game", font);
    menu->addButton(100,125,150,50,button_texture, "Highscore", font);
    menu->addButton(100,200,150,50,button_texture, "Exit", font);
}

void MainMenuState::initBackground()
{
    sf::Texture * background_texture = texture_map->at("background");
    background = new Menu{450,350,900,700, background_texture};
}
