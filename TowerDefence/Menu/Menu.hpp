#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <iterator>
#include "../Button/Button.hpp"

class Menu
{
    public:
        Menu(float pos_x, float pos_y, float width,
             float height, sf::Texture * texture_ptr);
        Menu(float pos_x, float pos_y, float width,
             float height);
        Menu();
        ~Menu() = default;
        
        sf::Vector2f getPosition();
        void setTexture(sf::Texture * texture_ptr);
        void setPosition(float pos_x, float pos_y);
        void addButton(float rel_x, float rel_y, float width, 
                       float height, sf::Texture * texture_ptr,
                       std::string button_text, sf::Font * font_ptr);
        void render(sf::RenderWindow * window_ptr);
        int getSelectedOption(int mouse_x, int mouse_y);


    private:
        std::vector<Button> button_vector;
        sf::Sprite background_sprite{};
        sf::Texture * background_texture_ptr{};
        float sprite_height{};
        float sprite_width{};

        void setSize(int width, int height);
};

#endif