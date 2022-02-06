#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../DynamicObject.hpp"
#include "../Projectile/Spit.hpp"
#include "../../StaticObject/Base/Base.hpp"
#include <vector>
#include <iostream>

class Enemy : public DynamicObject
{
  public:
      Enemy(float pos_x, float pos_y,
            std::vector<sf::Texture *> textures,
            nlohmann::json parameters,
            std::vector<sf::Vector2f> * road_vector_ptr);
      void destroy();
      void handleCollision(GameObject *collision_object) override;
      void updateObject() override;
      int getDamage();
      int getHp();
      float getSpeed();
      bool isDestroyed();

  private:
      int damage{};
      float speed{};
      bool active{true};
      int i{1};
      int hp{};
      std::vector<sf::Vector2f> *road_vector{};
      Base * base_ptr{};
};

#endif
