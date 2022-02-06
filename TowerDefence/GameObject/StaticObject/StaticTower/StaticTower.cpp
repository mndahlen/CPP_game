#include "StaticTower.hpp"

StaticTower::StaticTower(float pos_x, float pos_y, sf::Texture * texture_ptr,
                          nlohmann::json parameters)
  : StaticObject(pos_x, pos_y, texture_ptr),
    description{parameters["description"]}, cost{parameters["cost"]},
    detection_range{parameters["detection_range"]}
{

}

std::string StaticTower::getDescription() const
{
  return description;
}

int StaticTower::getCost() const
{
  return cost;
}

int StaticTower::getDetectionRange() const
{
  return detection_range;
}
