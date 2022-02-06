#ifndef BASE_HPP
#define BASE_HPP

#include "../StaticObject.hpp"

class Base : public StaticObject
{
    public:
        Base(float pos_x, float pos_y,
              std::vector<sf::Texture*> texture_ptr_vector,
              nlohmann::json parameters);

        void addMoney(int amount);
        void spendMoney(int amount);
        void takeDamage(int amount);
        int getLife();
        int getMoney();

        void handleCollision(GameObject * collision_object) override;
        void updateObject() override;

    private:
        int money{};
        int life{};

};

#endif
