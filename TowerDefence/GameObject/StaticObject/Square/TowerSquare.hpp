#ifndef TOWERSQUARE_HPP
#define TOWERSQUARE_HPP

#include "Square.hpp"

class TowerSquare : public Square
{
  public:
    TowerSquare(float pos_x, float pos_y, sf::Texture * texture_ptr);
    void handleCollision(GameObject * collision_object) override;
    void updateObject() override;
};

#endif
