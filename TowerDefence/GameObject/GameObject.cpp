#include "GameObject.hpp"

GameObject::~GameObject()
{

}

GameObject::GameObject(float pos_x, float pos_y, sf::Texture *texture_ptr_in)
                                                : texture_ptr{texture_ptr_in}
{
    // Set position of sprite
    sprite.setPosition(pos_x, pos_y);
    sprite.setTexture(*texture_ptr);

    // Set origin for local transformation (Ex. Rotation)
    auto size{texture_ptr->getSize()};
    sprite.setOrigin(size.x/2, size.y/2);
}

void GameObject::setScale(int x, int y)
{
    sprite.setScale(x,y);
}

void GameObject::setTexture(sf::Texture * texture)
{
    sprite.setTexture(*texture);
}


sf::Vector2f GameObject::getPosition()
{
    return sprite.getPosition();
}

sf::Vector2f GameObject::getMiddleCoord()
{
  int x_middle{getPosition().x + sprite.getTexture()->getSize().x/2};
  int y_middle{getPosition().y + sprite.getTexture()->getSize().y/2};

  sf::Vector2f mid_coord{x_middle, y_middle};

  return mid_coord;
}

void GameObject::setPosition(float pos_x, float pos_y)
{
    sprite.setPosition(pos_x, pos_y);
}

void GameObject::setRotation(float angle)
{
    sprite.setRotation(angle);
}

float GameObject::getRotation()
{
    return sprite.getRotation();
}

void GameObject::rotate(float angle)
{
    sprite.rotate(angle);
}

void GameObject::move(float dX, float dY)
{
    sprite.move(dX, dY);
}

sf::FloatRect GameObject::getBounds()
{
    return sprite.getGlobalBounds();
}

bool GameObject::checkCollision(GameObject * other_object_ptr)
{
    sf::FloatRect other_bounds = other_object_ptr->getBounds();
    sf::FloatRect self_bounds = getBounds();

    if(other_bounds.intersects(self_bounds))
    {
        other_object_ptr->handleCollision(this);
        handleCollision(other_object_ptr);

        return true;
    }
    else
    {
        return false;
    }
}

void GameObject::render(sf::RenderWindow * window_ptr)
{
    window_ptr->draw(sprite);
}
