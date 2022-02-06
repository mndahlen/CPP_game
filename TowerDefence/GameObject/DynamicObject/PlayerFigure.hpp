#ifndef PLAYERFIGURE_HPP
#define PLAYERFIGURE_HPP

#include "DynamicObject.hpp"
#include <vector>
#include <string>

class PlayerFigure : public DynamicObject
{
public:
    PlayerFigure(float pos_x, float pos_y,
                  std::vector <sf::Texture*> texture_ptr_vector,
                  nlohmann::json parameters);

    void handleCollision(GameObject* collision_object_ptr) override;
    void updateObject() override;
    void setVelocity();
    void controlPlayer();
    void animate();

private:
    int framecounter{0};
    int current_texture{0};
    int num_textures{0};
    int frames_per_texture{0};

    sf::Vector2f velocity;
    float speed{};
    std::string current_button{""};
    std::vector <sf::Texture*> textures;
};

#endif
