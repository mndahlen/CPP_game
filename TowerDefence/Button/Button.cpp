#include "Button.hpp"

Button::Button(float pos_x, float pos_y, float width, 
               float height, sf::Texture * texture_ptr_in,
               std::string button_text, sf::Font * font_ptr_in) 
               : sprite_width{width}, sprite_height{height}
{
    texture_ptr = texture_ptr_in;
    font_ptr = font_ptr_in;

    sprite.setTexture(*texture_ptr);
    sprite.setOrigin(0, 0);
    setPosition(pos_x, pos_y);
    setSize(width, height);
    setText(button_text);
}

sf::Vector2f Button::getPosition()
{
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2f corrected_position{position.x + sprite_width/2, 
                                    position.y + sprite_height/2};

    return corrected_position;
}

void Button::setPosition(float pos_x, float pos_y)
{
    sprite.setPosition(pos_x - sprite_width/2, pos_y - sprite_height/2);
    text.setPosition(pos_x, pos_y);
}

bool Button::mouseOnButton(int mouse_x, int mouse_y)
{
    auto mouse_bounds = sprite.getGlobalBounds();

    return mouse_bounds.contains(mouse_x, mouse_y);
}

void Button::render(sf::RenderWindow * window_ptr)
{   
    window_ptr->draw(sprite);
    window_ptr->draw(text);
}

void Button::setSize(int new_width, int new_height)
{
    sf::FloatRect local_bounds = sprite.getLocalBounds();

    float current_width = local_bounds.width;
    float current_height = local_bounds.height;

    float width_scale_factor = new_width/current_width;
    float height_scale_factor = new_height/current_height;

    sprite.scale(width_scale_factor, height_scale_factor);
}

void Button::changeText(std::string button_text)
{
    text.setString(button_text);
}

void Button::setText(std::string button_text)
{
    // Set font and string
    text.setFont(*font_ptr);
    text.setString(button_text);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Yellow);

    // Center text in button (5 is for good measure)
    sf::FloatRect text_bounds = text.getGlobalBounds();
    text.setOrigin((text_bounds.width)/2,(text_bounds.height)/2 + 5);
    sf::Vector2f button_position = getPosition();
    text.setPosition(button_position.x, button_position.y);
}
            