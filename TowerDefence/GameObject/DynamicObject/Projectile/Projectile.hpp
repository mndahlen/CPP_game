#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "../DynamicObject.hpp"
#include <iostream>

class Projectile : public DynamicObject
{
    public:
        Projectile(float pos_x, float pos_y, sf::Texture * texture_ptr,
                    nlohmann::json parameters, float x_dir, float y_dir);

        void destroy();
        virtual void handleCollision(GameObject * collision_object) override;
        virtual void updateObject() override;
        float getSpeed();
        float getDamage();
        bool isDestroyed();
        bool isOnPlayingField();

    protected:
        float speed{};
        float damage{};
        bool active{true};
        sf::Vector2f direction{};
        float texture_scale_factor{1};
};


#endif
