#ifndef ROADSQUARE_HPP
#define ROADSQUARE_HPP

#include "Square.hpp"

class RoadSquare : public Square
{
    public:
      RoadSquare(float pos_x, float pos_y, sf::Texture * texture_ptr);

      void handleCollision(GameObject * collision_object) override;
      void updateObject() override;

    private:
};

#endif
