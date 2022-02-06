#include "Projectile.hpp"

Projectile::Projectile(float pos_x, float pos_y, sf::Texture * texture_ptr,
                        nlohmann::json parameters, float x_dir, float y_dir)
            : DynamicObject(pos_x, pos_y, texture_ptr),
              speed{parameters["speed"]}, damage{parameters["damage"]},
              texture_scale_factor{parameters["texture_scale_factor"]}
{
    sprite.scale(texture_scale_factor, texture_scale_factor);
    float dir_norm_sq{std::pow(x_dir, 2) + std::pow(y_dir, 2)};

    if (std::abs(dir_norm_sq - 1.0f) < 1e-5)
    {
        direction.x = x_dir;
        direction.y = y_dir;
    }
    else
    {
        float dir_norm_sqrt{std::sqrt(dir_norm_sq)};

        direction.x = x_dir/dir_norm_sqrt;
        direction.y = y_dir/dir_norm_sqrt;
    }
    // Makes the direction have lenght of 1 unit.
}

void Projectile::destroy()
{
    active = false;
}

void Projectile::handleCollision(GameObject * collision_object_ptr)
{

}

void Projectile::updateObject()
{
    float dx{direction.x * speed};
    float dy{direction.y * speed};

    move(dx, dy);

    if(!isOnPlayingField())
    {
      destroy();
    }
}

float Projectile::getSpeed()
{
    return speed;
}

float Projectile::getDamage()
{
    return damage;
}

bool Projectile::isDestroyed()
{
    return !active;
}

bool Projectile::isOnPlayingField()
{
  sf::Vector2f cur_pos = getPosition();
  if (cur_pos.x > 700 || cur_pos.x < 0 || cur_pos.y < 0 || cur_pos.y > 700)
  {
    return false;
  }
  else
  {
    return true;
  }
}
