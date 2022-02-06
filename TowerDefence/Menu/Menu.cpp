#include "Menu.hpp"

Menu::Menu(float pos_x, float pos_y, float width, 
           float height, sf::Texture * texture_ptr) 
           : sprite_width{width}, sprite_height{height}
{
    background_texture_ptr = texture_ptr;

    background_sprite.setTexture(*background_texture_ptr);
    background_sprite.setOrigin(0, 0);
    setPosition(pos_x, pos_y);
    setSize(width, height);
}

Menu::Menu(){}

Menu::Menu(float pos_x, float pos_y, float width, 
           float height)
           : sprite_width{width}, sprite_height{height}
{   
    setPosition(pos_x, pos_y);
}

void Menu::setTexture(sf::Texture * texture_ptr)
{
    background_texture_ptr = texture_ptr;

    background_sprite.setTexture(*background_texture_ptr);
    background_sprite.setOrigin(0, 0);
    setSize(sprite_width, sprite_height);
}

int Menu::getSelectedOption(int mouse_x, int mouse_y)
{    
    for (std::vector<Button>::iterator it = button_vector.begin(); 
                                       it != button_vector.end(); 
                                       ++it)
    {
        int vector_index{it - button_vector.begin()};
        if (it->mouseOnButton(mouse_x, mouse_y))
        {
            return (vector_index + 1);
        }
    }

    return 0;
}

sf::Vector2f Menu::getPosition()
{
    sf::Vector2f position = background_sprite.getPosition();
    sf::Vector2f corrected_position{position.x + sprite_width/2, 
                                    position.y + sprite_height/2};

    return corrected_position;
}

void Menu::setPosition(float new_x, float new_y)
{
    sf::Vector2f current_menu_pos = getPosition();

    background_sprite.setPosition(new_x - sprite_width/2, 
                                  new_y - sprite_height/2);  

    for (std::vector<Button>::iterator it = button_vector.begin(); 
                                       it != button_vector.end(); 
                                       ++it)
    {
        int vector_index{it - button_vector.begin()};
        sf::Vector2f current_button_position = it->getPosition();

        int relative_x = current_button_position.x - current_menu_pos.x;
        int relative_y = current_button_position.y - current_menu_pos.y;
        
        it->setPosition(new_x + relative_x, new_y + relative_y);
    } 
}

void Menu::render(sf::RenderWindow * window_ptr)
{  
    window_ptr->draw(background_sprite);

    for (std::vector<Button>::iterator it = button_vector.begin(); 
                                       it != button_vector.end(); 
                                       ++it)
    {
        int vector_index{it - button_vector.begin()};
        Button current_button = button_vector.at(vector_index);
        current_button.render(window_ptr);
    }
}

void Menu::setSize(int new_width, int new_height)
{
    sf::FloatRect local_bounds = background_sprite.getLocalBounds();

    float current_width = local_bounds.width;
    float current_height = local_bounds.height;

    float width_scale_factor = new_width/current_width;
    float height_scale_factor = new_height/current_height;

    background_sprite.scale(width_scale_factor, height_scale_factor);
}

void Menu::addButton(float rel_x, float rel_y, float width, 
               float height, sf::Texture * texture_ptr,
               std::string button_text, sf::Font * font_ptr)
{   
    sf::Vector2f menu_pos = getPosition();
    Button new_button(menu_pos.x + rel_x - sprite_width/2, 
                      menu_pos.y + rel_y - sprite_height/2, 
                      width, height, texture_ptr, button_text, font_ptr);
    button_vector.push_back(new_button);
}