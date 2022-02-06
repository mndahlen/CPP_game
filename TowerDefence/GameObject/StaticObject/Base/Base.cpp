#include "Base.hpp"

Base::Base(float pos_x, float pos_y,
            std::vector<sf::Texture*> texture_ptr_vector,
            nlohmann::json parameters)
            :
            StaticObject(pos_x, pos_y, texture_ptr_vector[0]), money{parameters["money"]},
            life{parameters["life"]}
{
    sprite.scale(1,1);
}


void Base::addMoney(int amount)
{
   money += amount;
}

void Base::spendMoney(int amount)
{
    money -= amount;
}

void Base::takeDamage(int amount)
{
    life -= amount;
}

int Base::getLife()
{
    return life;
}

int Base::getMoney()
{
    return money;
}

void Base::handleCollision(GameObject * collision_object)
{
    // done by enemy
}

void Base::updateObject()
{
    // doesnt change
}
