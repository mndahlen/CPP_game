#ifndef DYNAMICTOWER_HPP
#define DYNAMICTOWER_HPP

#include "../DynamicObject.hpp"
#include "../../DynamicObject/Projectile/Projectile.hpp"
#include <vector>
#include <string>


class DynamicTower : public DynamicObject
{
public:
  DynamicTower(float pos_x, float pos_y, sf::Texture * texture_ptr,
                nlohmann::json parameters);
  std::string getDescription() const;
  int getCost() const;

protected:
  std::string description{};
  int cost{};
  virtual Projectile * fire(float x, float y, float x_dir, float y_dir) = 0;
};


#endif
