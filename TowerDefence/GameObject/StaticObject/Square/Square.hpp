#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "../StaticObject.hpp"

class Square : public StaticObject
{
    public:
      Square(float pos_x, float pos_y, sf::Texture * texture_ptr);
      void switchOccupied();
      bool isOccupied();

    protected:
      bool occupied{false};
};

#endif
