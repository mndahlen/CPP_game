#ifndef DYNAMICOBJECT_HPP
#define DYNAMICOBJECT_HPP

#include "../GameObject.hpp"

class DynamicObject : public GameObject
{   
    public:
        DynamicObject(float pos_x, float pos_y, sf::Texture * texture_ptr);
};

#endif