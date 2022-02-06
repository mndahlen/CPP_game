#include "HandSanitizerTower.hpp"

HandSanitizerTower::HandSanitizerTower(float pos_x_, float pos_y_,
                                       std::vector<sf::Texture *> texture_ptr_vector_,
                                       nlohmann::json parameters,
                                       std::vector<Projectile *> *projectile_vector_ptr_,
                                       nlohmann::json spit_parameters_)
    : StaticTower(pos_x_, pos_y_, texture_ptr_vector_.at(0), parameters)
{
    pos_x = pos_x_;
    pos_y = pos_y_;
    cooldown = 0;
    projectile_vector_ptr = projectile_vector_ptr_;
    max_cooldown = parameters["max_cooldown"];
    textures = texture_ptr_vector_;
    spit_parameters = spit_parameters_;
}

Spit *HandSanitizerTower::fire(float x, float y, float x_dir, float y_dir)
{
    cooldown = max_cooldown;
    std::vector<sf::Texture*> spit_textures;
    spit_textures.push_back(textures.back());
    return new Spit(pos_x, pos_y, spit_textures, spit_parameters,
                    x_dir, y_dir);
}

void HandSanitizerTower::handleCollision(GameObject *collision_object)
{
    if(dynamic_cast <Enemy*> (collision_object))
    {
        if (cooldown == 0)
          {
              sf::Vector2f col_obj_pos = collision_object->getPosition();
              float x_dir = col_obj_pos.x - pos_x;
              float y_dir = col_obj_pos.y - pos_y;
              if (x_dir < 0)
              {
                  setScale(-1,1);
              }
              else
              {
                  setScale(1,1);
              }
              projectile_vector_ptr->push_back(fire(pos_x, pos_y, x_dir, y_dir));
          }
    }
}

void HandSanitizerTower::updateObject()
{
    if(cooldown > 0)
    {
        cooldown--;
    }
    framecounter++;
}

int HandSanitizerTower::getCooldown()
{
    return cooldown;
}

sf::FloatRect HandSanitizerTower::getBounds()
{
  sf::FloatRect sprite_bounds = sprite.getGlobalBounds();
  sf::FloatRect col_box(pos_x - (sprite_bounds.width * getDetectionRange() / 2),
                        pos_y - (sprite_bounds.height * getDetectionRange() / 2),
                        sprite_bounds.width * getDetectionRange(),
                        sprite_bounds.height * getDetectionRange());
  return col_box;
}
