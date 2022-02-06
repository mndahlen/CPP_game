#include "HighscoreState.hpp"

HighscoreState::HighscoreState(sf::RenderWindow * window, DataHandler * datahandler,
                               std::map<std::string, sf::Texture*> * texture_map_ptr,
                               std::map<std::string, sf::Font*> * font_map_ptr) 
                               : 
                               State(window,datahandler,texture_map_ptr,font_map_ptr,7)                        
{
    initHighscoreMenu();
    initBackground();
}

void HighscoreState::updateState()
{
    sf::Mouse mouse; 
    bool left_pressed = mouse.isButtonPressed(sf::Mouse::Left);

    if (left_pressed)
    {
        auto mpos = mouse.getPosition(*window);
        int selected = highscoreMenu.getSelectedOption(mpos.x, mpos.y);
        
        if (selected == 1)
        {
            next_state_id = 0;
        }
    }
}

void HighscoreState::render()
{
    background.render(window);
    highscoreMenu.render(window);
}


void HighscoreState::initHighscoreMenu()
{   
    std::vector<int> highscore = datahandler->getHighscore();
    sf::Texture * menu_texture = texture_map->at("menu");
    sf::Texture * button_texture = texture_map->at("button");
    sf::Texture * transparent_texture = texture_map->at("transparent");
    sf::Font * font = font_map->at("arial");

    highscoreMenu.setTexture(menu_texture);
    highscoreMenu.addButton(100,200,150,50,button_texture, "Go to main menu", font);

    for (std::vector<int>::iterator it = highscore.begin(); 
                                       it != highscore.end(); 
                                       ++it)
    {
        int score_num{it - highscore.begin() + 1};
        std::string str_score_num = std::to_string(score_num);
        std::string str_score = std::to_string(*it);
        std::string highscore_str = str_score_num + ": " + str_score;
        
        highscoreMenu.addButton(100,25*(score_num),10,10,transparent_texture, highscore_str, font);
    }
}

void HighscoreState::initBackground()
{    
    sf::Texture * background_texture = texture_map->at("background");

    background.setTexture(background_texture);
}