#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button
{
    public:
        Button(float pos_x, float pos_y, float width, 
               float height, sf::Texture * texture_ptr_in,
               std::string button_text, sf::Font * font_ptr_in); 
        ~Button() = default;
        
        // Basic functions
        sf::Vector2f getPosition();
        void setPosition(float pos_x, float pos_y);
        bool mouseOnButton(int mouse_x, int mouse_y);
        void changeText(std::string button_text);

        // Frame functions
        void render(sf::RenderWindow * window_ptr);

    private:
        sf::Sprite sprite{};
        sf::Text text{};
        sf::Texture * texture_ptr{};
        sf::Font * font_ptr{};

        float sprite_height{};
        float sprite_width{};

        void setSize(int width, int height);
        void setText(std::string text);
};

#endif