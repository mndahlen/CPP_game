#ifndef STATICTOWER_HPP
#define STATICTOWER_HPP
#include <string>
#include "../StaticObject.hpp"
#include "../../DynamicObject/Projectile/Projectile.hpp"
#include "../../DynamicObject/Enemy/Enemy.hpp"
#include <vector>
#include <iostream>

class StaticTower : public StaticObject
{
public:
  StaticTower(float pos_x, float pos_y, sf::Texture * texture_ptr,
              nlohmann::json parameters);
  std::string getDescription() const;
  int getCost() const;
  int getDetectionRange() const;

protected:
  std::string description{};
  int cost{};
  int detection_range{};
  virtual Projectile * fire(float x, float y, float x_dir, float y_dir) = 0;
};

#endif
