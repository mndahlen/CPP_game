#include "DynamicTower.hpp"

DynamicTower::DynamicTower(float pos_x, float pos_y, sf::Texture * texture_ptr,
                            nlohmann::json parameters)
  : DynamicObject(pos_x, pos_y, texture_ptr),
    description{parameters["description"]}, cost{parameters["cost"]}
{

}

std::string DynamicTower::getDescription() const
{
  return description;
}

int DynamicTower::getCost() const
{
  return cost;
}
