#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include "../DataHandler/DataHandler.hpp"
#include <iostream>

class State
{
    public:
        State(sf::RenderWindow * window_ptr, 
              DataHandler * datahandler_ptr,
              std::map<std::string, sf::Texture*> * texture_map_ptr,
              std::map<std::string, sf::Font*> * font_map_ptr,
              int id);

        int getStateID();
        int getNextStateID();
        virtual void updateState() = 0;
        virtual void render() = 0;

    protected:
        int state_id{};
        int next_state_id{};
        int level{1};

        sf::RenderWindow * window;
        DataHandler * datahandler;
        std::map<std::string, sf::Texture*> * texture_map;
        std::map<std::string, sf::Font*> * font_map;
};

#endif