#include "MoneyBag.hpp"

MoneyBag::MoneyBag(float pos_x, float pos_y, float direction_,
                  std::vector<sf::Texture*> texture_ptr_vector,
                  nlohmann::json parameters, Base * base_ptr)
  : DynamicObject(pos_x, pos_y, texture_ptr_vector.at(0)),
    direction{direction_}, speed{parameters["speed"]}, base_ptr{base_ptr},
    playingfield_size{parameters["playingfield_size"]},
    money_added{parameters["money_added"]}
{

}

void MoneyBag::destroy()
{
    active = false;
}

bool MoneyBag::isDestroyed()
{
  return !active;
}

void MoneyBag::updateObject()
{
  sf::Vector2f pos{this->getPosition()};
  if (pos.y > playingfield_size)
  {
    destroy();
  }

  float dy{direction * speed};
  float dx{0};

  move(dx, dy);
}

void MoneyBag::handleCollision(GameObject * collision_object)
{
  // Checks if the GameObject is PlayerFigure
      if (dynamic_cast <PlayerFigure*> (collision_object))
      {
          destroy();
          base_ptr -> addMoney(money_added);
      }
}
