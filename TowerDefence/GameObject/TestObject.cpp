#include "GameObject.hpp"

// For testing GameObject.
// Also an example of how to use GameObject as a base class.

class TestObject : public GameObject
{
    public:
        TestObject(float pos_x, float pos_y, sf::Texture * texture) :
            GameObject(pos_x, pos_y, texture) {}

        void handleCollision(GameObject * collision_object) override
        {
            collision_object->rotate(0);
        }
        void updateObject() override
        {
            int test{1};
            test = test;
        }
};
