#include "PauseState.hpp"

PauseState::PauseState(sf::RenderWindow * window, DataHandler * datahandler,
                               std::map<std::string, sf::Texture*> * texture_map_ptr,
                               std::map<std::string, sf::Font*> * font_map_ptr)
                               :
                               State(window,datahandler,texture_map_ptr,font_map_ptr,2)
{
    while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        // waiting until escape is released
    }
    initMainMenu();
    initBackground();
    initButtons();
}

PauseState::~PauseState()
{
    delete leveldisplay;
    delete moneydisplay;
    delete hpdisplay;
}

void PauseState::updateState()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            // waiting until escape is released
        }
        next_state_id = 1;
    }

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
        else if (selected == 3)
        {
            next_state_id = 1;
        }
    }

    updateButtons();
}

void PauseState::render()
{
    background.render(window);
    menu.render(window);

    leveldisplay->render(window);
    moneydisplay->render(window);
    hpdisplay->render(window);
}

void PauseState::initMainMenu()
{
    sf::Texture * menu_texture = texture_map->at("menu");
    sf::Texture * button_texture = texture_map->at("button");
    sf::Texture * transparent = texture_map->at("transparent");
    sf::Font * font = font_map->at("arial");

    menu.setTexture(menu_texture);
    menu.addButton(100, 220, 150, 50, button_texture, "Exit", font);
    menu.addButton(100, 160, 150, 50, button_texture, "Main Menu", font);
    menu.addButton(100, 100, 150, 50, button_texture, "Continue", font);
    menu.addButton(100, 25, 150, 10, transparent, "Game paused!", font);
    menu.addButton(100, 380, 150, 10, transparent, "Stats: ", font);
}

void PauseState::initBackground()
{
    sf::Texture *background_texture = texture_map->at("background");

    background.setTexture(background_texture);
}

void PauseState::initButtons()
{
    sf::Texture * transparent_texture = texture_map->at("transparent");
    sf::Font * font = font_map->at("arial");

    leveldisplay = new Button(430,400,100,40,transparent_texture,"level",font);
    moneydisplay = new Button(430,420,100,40,transparent_texture,"money",font);
    hpdisplay = new Button(430,440,100,40,transparent_texture,"hp",font);
}

void PauseState::updateButtons()
{
    Base * base = datahandler->getBasePtr();
    int level = datahandler->getCurrentLevel();
    std::string level_str = "Level: " + std::to_string(level);
    leveldisplay->changeText(level_str);

    std::string money_str = "Money: " + std::to_string(base->getMoney());
    moneydisplay->changeText(money_str);

    std::string hp_string = "HP: " + std::to_string(base->getLife());
    hpdisplay->changeText(hp_string);
}
