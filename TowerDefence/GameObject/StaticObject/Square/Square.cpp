#include "Square.hpp"


Square::Square(float pos_x, float pos_y, sf::Texture * texture_ptr):
StaticObject(pos_x, pos_y, texture_ptr)
{
    sprite.setOrigin(0, 0);
}

bool Square::isOccupied()
{
  return occupied;
}

void Square::switchOccupied()
{
  occupied = !occupied;
}
