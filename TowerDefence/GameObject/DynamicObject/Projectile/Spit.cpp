#include "Spit.hpp"

Spit::Spit(float pos_x, float pos_y,
            std::vector <sf::Texture*> texture_ptr_vector,
            nlohmann::json parameters, 
            float x_dir, float y_dir)
            : 
            Projectile(pos_x, pos_y, 
                       texture_ptr_vector.back(),
                       parameters, x_dir, y_dir)
{

}
