#ifndef HANDSANITIZERTOWER_HPP
#define HANDSANITIZERTOWER_HPP

#include "StaticTower.hpp"
#include "../../DynamicObject/Projectile/Spit.hpp"

class HandSanitizerTower : public StaticTower
{
public:
  HandSanitizerTower(float pos_x, float pos_y,
    std::vector <sf::Texture*> texture_ptr_vector, nlohmann::json parameters,
    std::vector<Projectile*> * projectile_vector_ptr,
    nlohmann::json spit_parameters);

    int getCooldown();
    Spit * fire(float x, float y, float x_dir, float y_dir) override;
    void handleCollision(GameObject * collision_object);
    void updateObject();
    sf::FloatRect getBounds() override;

private:
    std::vector <Projectile*> * projectile_vector_ptr{};
    std::vector <sf::Texture*> textures{};
    int cooldown;
    int max_cooldown;
    int pos_x;
    int pos_y;
    int framecounter{0};
    nlohmann::json spit_parameters{};

    void animate();
};

#endif
