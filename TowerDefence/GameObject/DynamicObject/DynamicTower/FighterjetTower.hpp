#ifndef FIGHTERJETTOWER_HPP
#define FIGHTERJETTOWER_HPP

#include "DynamicTower.hpp"
#include "../../DynamicObject/Projectile/Spit.hpp"

class FighterjetTower : public DynamicTower
{
public:
  FighterjetTower(float pos_x, float pos_y,
                  std::vector <sf::Texture*> textures_,
                  nlohmann::json parameters,
                  std::vector <Projectile*> * projectiles_,
                  nlohmann::json spit_parameters_);
    int getSpitCooldown() const;
    int getXdir() const;
    int getYdir() const;
    Spit * fire(float x, float y, float x_dir, float y_dir) override;
    void updateObject() override;
    void handleCollision(GameObject * collision_object) override;

private:
    int framecounter{0};
    int speed{0};
    int spit_cooldown{0};
    int pos_x;
    int pos_y;
    float left_travel_distance;
    float x_dir{1};
    float y_dir{1};
    float texture_scale_factor{1};
    float radians{};
    std::vector <Projectile*> * projectiles;
    std::vector<sf::Texture*> textures{};
    nlohmann::json spit_parameters{};

    void animate();

};


#endif
