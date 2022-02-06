#ifndef MONEYBAG_HPP
#define MONEYBAG_HPP

#include "DynamicObject.hpp"
#include "PlayerFigure.hpp"
#include "../StaticObject/Base/Base.hpp"

class MoneyBag : public DynamicObject
{
public:
  MoneyBag(float pos_x, float pos_y, float direction_,
            std::vector<sf::Texture*> texture_ptr_vector,
            nlohmann::json parameters, Base * base_ptr);

  void destroy();
  bool isDestroyed();
  void updateObject() override;
  void handleCollision(GameObject * collision_object) override;

private:
  int speed{};
  bool active{true};
  int money_added{};
  int playingfield_size{};
  int direction{};
  Base * base_ptr{};
};


#endif
