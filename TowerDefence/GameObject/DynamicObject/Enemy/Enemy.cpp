#include  "Enemy.hpp"

Enemy::Enemy(float pos_x, float pos_y,
             std::vector<sf::Texture *> textures,
             nlohmann::json parameters,
             std::vector<sf::Vector2f> * road_vector_ptr)
             :
             DynamicObject(pos_x, pos_y, textures[0]), base_ptr{base_ptr},
             damage{parameters["dmg"]}, hp{parameters["hp"]},
             speed{parameters["speed"]}
{
  road_vector = road_vector_ptr;
}

void Enemy::destroy()
{
  active = false;
}

void Enemy::handleCollision(GameObject* collision_object)
{
  auto object_ptr{dynamic_cast<Projectile*>(collision_object)};

  if (object_ptr)
  {
    hp -= object_ptr->getDamage();
    object_ptr -> destroy();
  }

  auto object_ptr2{dynamic_cast<Base*>(collision_object)};

  if (object_ptr2)
  {
    object_ptr2 -> takeDamage(damage);
    destroy();
  }
}

void Enemy::updateObject()
{
  if (hp <= 0)
  {
    destroy();
  }

    float dist_left{speed};

    float x_dir;
    float y_dir;
    float dir;

    while (dist_left > 0)
    {
      float dest_x = road_vector->at(i).x;
      float dest_y = road_vector->at(i).y;

      x_dir = dest_x - getPosition().x;
      y_dir = dest_y - getPosition().y;

      float dir_sq{std::pow(x_dir, 2) + std::pow(y_dir, 2)};
      dir = std::sqrt(dir_sq);

      if (dist_left >= dir)
      {
        move(x_dir, y_dir);

        dist_left -= dir;
        ++i;
      }
      else
      {
        x_dir = x_dir/dir * dist_left;
        y_dir = y_dir/dir * dist_left;

        move(x_dir, y_dir);

        dist_left -= dir;
      }

    }
}

int Enemy::getDamage()
{
  return damage;
}

float Enemy::getSpeed()
{
  return speed;
}

int Enemy::getHp()
{
  return hp;
}

bool Enemy::isDestroyed()
{
    return !active;
}
