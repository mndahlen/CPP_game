#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <vector>
#include <utility>
#include <cmath>
#include <SFML/Graphics.hpp>

//Third party
#include "../../third_party/nlohmann/json.hpp"

class GameObject
{
    public:
        GameObject(float pos_x, float pos_y, sf::Texture * texture_ptr_in);
        virtual ~GameObject();

        // Basic functions
        sf::Vector2f getPosition();
        sf::Vector2f getMiddleCoord();
        void setPosition(float pos_x, float pos_y);
        void setRotation(float angle);
        void setScale(int x, int y);
        void setTexture(sf::Texture * texture);
        float getRotation();
        void rotate(float angle);
        void move(float dX, float dY);
        virtual sf::FloatRect getBounds();

        // Collision functions
        bool checkCollision(GameObject * other_object_ptr);
        virtual void handleCollision(GameObject * collision_object) = 0;

        // Frame functions
        virtual void render(sf::RenderWindow * window_ptr);
        virtual void updateObject() = 0;

    protected:
        sf::Sprite sprite{};
        sf::Texture * texture_ptr{};
};

#endif
