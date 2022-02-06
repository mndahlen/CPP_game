#ifndef STATICOBJECT_HPP
#define STATICOBJECT_HPP

#include "../GameObject.hpp"

class StaticObject : public GameObject
{
    public:
        StaticObject(float pos_x, float pos_y, sf::Texture * texture_ptr);
};

#endif