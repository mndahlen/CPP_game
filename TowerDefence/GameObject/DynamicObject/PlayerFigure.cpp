#include "PlayerFigure.hpp"

PlayerFigure::PlayerFigure(float pos_x, float pos_y,
                           std::vector<sf::Texture *> texture_ptr_vector,
                           nlohmann::json parameters)
    : DynamicObject(pos_x, pos_y, texture_ptr_vector.at(0)),
      speed{parameters["speed"]},
      velocity{velocity},
      textures{texture_ptr_vector}
{
    num_textures = textures.size();
    frames_per_texture = parameters["frames_per_texture"];
}

void PlayerFigure::updateObject()
{
    framecounter++;
    setVelocity();
    move(velocity.x, velocity.y);

    sf::Vector2f cur_pos = getPosition();
    if (cur_pos.x > 700)
    {
      setPosition(700, cur_pos.y);
      cur_pos = getPosition();
    }

    else if (cur_pos.x < 0)
    {
      setPosition(0, cur_pos.y);
      cur_pos = getPosition();
    }

    if (cur_pos.y > 700)
    {
      setPosition(cur_pos.x, 700);
    }

    else if (cur_pos.y < 0)
    {
      setPosition(cur_pos.x, 0);
    }

    if (!(current_button == ""))
    {
        animate();
    }

    if (velocity.x < 0)
    {
        sprite.setScale(-1,1);
    }
    else if (velocity.x > 0)
    {
        sprite.setScale(1,1);
    }
}

void PlayerFigure::handleCollision(GameObject *collision_object_ptr)
{

}

void PlayerFigure::controlPlayer()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            current_button = "wa";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            current_button = "";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            current_button = "wd";
        }
        else
        {
            current_button = "w";
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            current_button = "wa";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            current_button = "";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            current_button = "sa";
        }
        else
        {
            current_button = "a";
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            current_button = "sa";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            current_button = "";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            current_button = "sd";
        }
        else
        {
            current_button = "s";
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            current_button = "wd";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            current_button = "";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            current_button = "sd";
        }
        else
        {
            current_button = "d";
        }
    }
    else
    {
        current_button = "";
    }
}

void PlayerFigure::setVelocity()
{
    if (current_button == "w")
    {
        velocity.x = 0 * speed;
        velocity.y = -1 * speed;
    }
    else if (current_button == "a")
    {
        velocity.x = -1 * speed;
        velocity.y = 0 * speed;
    }
    else if (current_button == "s")
    {
        velocity.x = 0 * speed;
        velocity.y = 1 * speed;
    }
    else if (current_button == "d")
    {
        velocity.x = 1 * speed;
        velocity.y = 0 * speed;
    }
    else if (current_button == "wa")
    {
        velocity.x = -1 * speed / std::sqrt(2);
        velocity.y = -1 * speed / std::sqrt(2);
    }
    else if (current_button == "wd")
    {
        velocity.x = 1 * speed / std::sqrt(2);
        velocity.y = -1 * speed / std::sqrt(2);
    }
    else if (current_button == "sa")
    {
        velocity.x = -1 * speed / std::sqrt(2);
        velocity.y = 1 * speed / std::sqrt(2);
    }
    else if (current_button == "sd")
    {
        velocity.x = 1 * speed / std::sqrt(2);
        velocity.y = 1 * speed / std::sqrt(2);
    }
    else
    {
        velocity.x = 0;
        velocity.y = 0;
    }
}

void PlayerFigure::animate()
{
    if (framecounter%frames_per_texture == 0)
    {
        sprite.setTexture(*textures[current_texture]);
        if (current_texture + 1 < num_textures)
        {
            current_texture++;
        }
        else
        {
            current_texture = 0;
        }
    }
}
