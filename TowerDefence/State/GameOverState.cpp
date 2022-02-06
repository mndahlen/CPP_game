#include "GameOverState.hpp"

GameOverState::GameOverState(sf::RenderWindow *window, DataHandler *datahandler,
                                     std::map<std::string, sf::Texture *> *texture_map_ptr,
                                     std::map<std::string, sf::Font *> *font_map_ptr)
    : State(window, datahandler, texture_map_ptr, font_map_ptr, 8)
{
    initMainMenu();
    initBackground();
    initButtons();
}

GameOverState::~GameOverState()
{
    delete leveldisplay;
    delete moneydisplay;
    delete hpdisplay;
}

void GameOverState::updateState()
{
    sf::Mouse mouse;
    bool left_pressed = mouse.isButtonPressed(sf::Mouse::Left);

    if (left_pressed)
    {
        auto mpos = mouse.getPosition(*window);
        int selected = menu.getSelectedOption(mpos.x, mpos.y);

        if (selected == 1)
        {
            next_state_id = -1;
        }
        else if (selected == 2)
        {
            next_state_id = 0;
        }
    }

    updateButtons();
}

void GameOverState::render()
{
    background.render(window);
    menu.render(window);

    leveldisplay->render(window);
    moneydisplay->render(window);
    hpdisplay->render(window);
}

void GameOverState::initMainMenu()
{
    sf::Texture * menu_texture = texture_map->at("menu");
    sf::Texture * button_texture = texture_map->at("button");
    sf::Texture * transparent = texture_map->at("transparent");
    sf::Font * font = font_map->at("arial");

    menu.setTexture(menu_texture);
    menu.addButton(100, 200, 150, 50, button_texture, "Exit", font);
    menu.addButton(100, 75, 150, 50, button_texture, "Main Menu", font);
    menu.addButton(100, 25, 150, 10, transparent, "Game over!", font);
    menu.addButton(100, 250, 150, 10, transparent, "Stats : ", font);
}

void GameOverState::initBackground()
{
    sf::Texture *background_texture = texture_map->at("background");

    background.setTexture(background_texture);
}

void GameOverState::initButtons()
{
    sf::Texture * transparent_texture = texture_map->at("transparent");
    sf::Font * font = font_map->at("arial");

    leveldisplay = new Button(430,370,100,40,transparent_texture,"level",font);
    moneydisplay = new Button(430,390,100,40,transparent_texture,"money",font);
    hpdisplay = new Button(430,410,100,40,transparent_texture,"hp",font);
}

void GameOverState::updateButtons()
{
    Base * base = datahandler->getBasePtr();
    int level = datahandler->getCurrentLevel();
    std::string level_str = "Level : " + std::to_string(level);
    leveldisplay->changeText(level_str);

    std::string money_str = "Money : " + std::to_string(base->getMoney());
    moneydisplay->changeText(money_str);

    std::string hp_string = "HP : " + std::to_string(base->getLife());
    hpdisplay->changeText(hp_string);
}
