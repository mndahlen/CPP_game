#include "RoadSquare.hpp"

RoadSquare::RoadSquare(float pos_x, float pos_y, sf::Texture * texture_ptr) :
Square(pos_x, pos_y, texture_ptr)
{
    occupied = true;
}

void RoadSquare::handleCollision(GameObject * collision_object)
{

}

void RoadSquare::updateObject()
{

}
