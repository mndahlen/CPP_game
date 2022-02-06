#include "State.hpp"

State::State(sf::RenderWindow * window_ptr, 
            DataHandler * datahandler_ptr,
            std::map<std::string, sf::Texture*> * texture_map_ptr,
            std::map<std::string, sf::Font*> * font_map_ptr,
            int id = 0)
            : 
            state_id{id}, next_state_id{id},
            texture_map{texture_map_ptr}, font_map{font_map_ptr},
            window{window_ptr}, datahandler{datahandler_ptr} 
            {}

int State::getStateID()
{
    return state_id;
}

int State::getNextStateID()
{
    return next_state_id;
}