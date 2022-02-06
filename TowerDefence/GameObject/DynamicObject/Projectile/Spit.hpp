#ifndef SPITPROJECTILE_HPP
#define SPITPROJECTILE_HPP

#include "Projectile.hpp"

class Spit : public Projectile
{
    public:
        Spit(float pos_x, float pos_y,
            std::vector <sf::Texture*> texture_ptr_vector,
            nlohmann::json parameters,
            float dir_x, float dir_y);
};


#endif
