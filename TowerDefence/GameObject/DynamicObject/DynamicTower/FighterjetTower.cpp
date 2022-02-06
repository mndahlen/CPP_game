#include "FighterjetTower.hpp"

FighterjetTower::FighterjetTower(float pos_x, float pos_y,
                std::vector <sf::Texture*> textures_,
                nlohmann::json parameters,
                std::vector <Projectile*> * projectiles_,
                nlohmann::json spit_parameters_)
                :
                DynamicTower(pos_x, pos_y, textures_.at(0), parameters),
                pos_x{pos_x}, pos_y{pos_y},
                projectiles{projectiles_}
{
    textures = textures_;
    spit_parameters = spit_parameters_;
    texture_scale_factor = parameters["texture_scale_factor"];
    left_travel_distance = parameters["left_travel_distance"];
    speed = parameters["speed"];
    spit_cooldown = parameters["spit_cooldown"];
    framecounter = -1 * left_travel_distance;

    setRotation(270);
    setScale(texture_scale_factor, texture_scale_factor);
}

int FighterjetTower::getSpitCooldown() const
{
  return spit_cooldown;
}

int FighterjetTower::getXdir() const
{
  return x_dir;
}

int FighterjetTower::getYdir() const
{
  return y_dir;
}

Spit * FighterjetTower::fire(float pos_x, float pos_y, float x_dir, float y_dir)
{
    Spit * new_spit = new Spit(pos_x, pos_y,
                               textures,
                               spit_parameters,
                               x_dir, y_dir);
    return new_spit;
}

void FighterjetTower::updateObject()
{
    sf::Vector2f position = getPosition();
    pos_x = position.x;
    pos_y = position.y;

    if (framecounter < 0)
    {
        x_dir = -1;
        y_dir = 0;
    }
    else
    {
        if (framecounter == 0 || getRotation() == 360)
        {
            setRotation(0);
        }
        else
        {
            setRotation(getRotation() + 1);
        }

        radians = (getRotation() - 90) * 3.1415926535 / 180;

        x_dir = cos(radians);
        y_dir = sin(radians);

        if (framecounter%spit_cooldown == 0)
        {
            projectiles -> push_back(fire(pos_x, pos_y, x_dir, y_dir));
        }
    }

    move(x_dir * speed, y_dir * speed);
    framecounter++;
}

void FighterjetTower::handleCollision(GameObject * collision_object)
{
    // does not collide
}
